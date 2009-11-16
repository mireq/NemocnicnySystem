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
	}
	catch (Nemocnice::DuplicateDataException &e) {
		delete novaNemocnica;
		Nemocnice::Iterator it = m_nemocnice.find(nazov);
		Nemocnica *nemocnica = it.next();
		if (nemocnica->zrusena()) {
			nemocnica->setZrusena(false);
		}
		else {
			throw NemocnicaDuplicitaException(nazov);
		}
	}
}


bool NemocnicnySystem::odoberNemocnicu(const QString &nazov)
{
	Nemocnice::Iterator it = m_nemocnice.find(nazov);
	if (it.hasNext()) {
		Nemocnica *n = it.next();
		m_nemocnice.remove(n);
		delete n;
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
		return true;
	}
	return false;
}


void NemocnicnySystem::pridajPacienta(const Pacient &pacient)
{
	Pacient *novyPacient = new Pacient(pacient);
	try {
		m_pacienti.insert(novyPacient);
	}
	catch (Pacienti::DuplicateDataException &e) {
		delete novyPacient;
		throw PacientDuplicitaException(pacient);
	}
}


