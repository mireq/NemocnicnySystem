/*
 * =====================================================================================
 *
 *       Filename:  NemocnicnySystem.cpp
 *
 *        Version:  1.0
 *        Created:  15.11.2009 10:49:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "NemocnicnySystem.h"


NemocnicnySystem::NemocnicnySystem()
	: QObject(),
	  m_zmenene(false)
{
}


NemocnicnySystem::~NemocnicnySystem()
{
	m_nemocnice.deleteData();
	m_pacienti.deleteData();
}


void NemocnicnySystem::pridajNemocnicu(const QString &nazov)
{
	Nemocnica *novaNemocnica = new Nemocnica(nazov);
	try {
		m_nemocnice.insert(novaNemocnica);
		setZmenene(true);
		emit zmenaNemocnic();
	}
	catch (Nemocnice::DuplicateDataException &e) {
		delete novaNemocnica;
		Nemocnice::Iterator it = m_nemocnice.find(nazov);
		Nemocnica *nemocnica = it.next();
		if (nemocnica->zrusena()) {
			nemocnica->setZrusena(false);
			setZmenene(true);
			emit zmenaNemocnic();
		}
		else {
			throw NemocnicaDuplicitaException(nazov);
		}
	}
}


void NemocnicnySystem::pridajNemocnicu(Nemocnica *nemocnica)
{
	try {
		m_nemocnice.insert(nemocnica);
		setZmenene(true);
	}
	catch (Nemocnice::DuplicateDataException &e) {
		delete nemocnica;
	}
}


bool NemocnicnySystem::odoberNemocnicu(const QString &nazov)
{
	Nemocnice::Iterator it = m_nemocnice.find(nazov);
	if (it.hasNext()) {
		Nemocnica *n = it.next();
		m_nemocnice.remove(n);
		delete n;
		setZmenene(true);
		emit zmenaNemocnic();
		return true;
	}
	return false;
}


bool NemocnicnySystem::zrusNemocnicu(const QString &nazov)
{
	Nemocnice::Iterator it = m_nemocnice.find(nazov);
	if (it.hasNext()) {
		Nemocnica *n = it.next();
		n->setZrusena(true);
		setZmenene(true);
		emit zmenaNemocnic();
		return true;
	}
	return false;
}


void NemocnicnySystem::pridajPacienta(const Pacient &pacient)
{
	Pacient *novyPacient = new Pacient(pacient);
	try {
		m_pacienti.insert(novyPacient);
		setZmenene(true);
	}
	catch (Pacienti::DuplicateDataException &e) {
		delete novyPacient;
		throw PacientDuplicitaException(pacient);
	}
}


void NemocnicnySystem::pridajPacienta(Pacient *pacient)
{
	try {
		m_pacienti.insert(pacient);
		setZmenene(true);
	}
	catch (Pacienti::DuplicateDataException &e) {
		delete pacient;
		throw PacientDuplicitaException(*pacient);
	}
}


void NemocnicnySystem::hospitalizuj(Nemocnica *nemocnica, Pacient *pacient, const Hospitalizacia &hospitalizacia)
{
	nemocnica->hospitalizuj(pacient, hospitalizacia);
	setZmenene(true);
}


NemocnicnySystem::Pacienti::Iterator NemocnicnySystem::pacienti()
{
	return m_pacienti.iterator();
}


NemocnicnySystem::Pacienti::Iterator NemocnicnySystem::najdiPacienta(const RodCis &rc)
{
	return m_pacienti.find(rc);
}


NemocnicnySystem::Nemocnice::Iterator NemocnicnySystem::najdiNemocnicu(const QString &nazov)
{
	return m_nemocnice.find(nazov);
}


void NemocnicnySystem::uloz(const QString &nazovSuboru)
{
	try {
		Serializer<NemocnicnySystem>::serialize(*this, "system", nazovSuboru.toUtf8().data());
	}
	catch (Serializer<NemocnicnySystem>::FileAccessException &) {
		throw SuborException(SuborException::Access);
	}
	catch (Serializer<NemocnicnySystem>::FileFormatException &) {
		throw SuborException(SuborException::Format);
	}
	setZmenene(false, nazovSuboru);
}


void NemocnicnySystem::otvor(const QString &nazovSuboru)
{
	zatvor();
	try {
		Serializer<NemocnicnySystem>::unserialize(*this, "system", nazovSuboru.toUtf8().data());
	}
	catch (Serializer<NemocnicnySystem>::FileAccessException &) {
		throw SuborException(SuborException::Access);
	}
	catch (Serializer<NemocnicnySystem>::FileFormatException &) {
		throw SuborException(SuborException::Format);
	}
	setZmenene(false, nazovSuboru);
	emit zmenaNemocnic();
}


void NemocnicnySystem::zatvor()
{
	m_nemocnice.deleteData();
	m_pacienti.deleteData();
	m_nazovSuboru = QString();
	setZmenene(false);
	emit zmenaNemocnic();
}


bool NemocnicnySystem::zmenene() const
{
	return m_zmenene;
}


const QString &NemocnicnySystem::nazovSuboru() const
{
	return m_nazovSuboru;
}


void NemocnicnySystem::setZmenene(bool zmenene, const QString &subor)
{
	bool zmena = false;
	if (zmenene != m_zmenene) {
		m_zmenene = zmenene;
		zmena = true;
	}

	if (!subor.isNull() && subor != m_nazovSuboru) {
		m_nazovSuboru = subor;
		zmena = true;
	}

	if (zmena) {
		emit zmenaStavuSuboru(zmenene, m_nazovSuboru);
	}
}


