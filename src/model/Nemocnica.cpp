/*
 * =====================================================================================
 *
 *       Filename:  Nemocnica.cpp
 *
 *        Version:  1.0
 *        Created:  13.11.2009 09:48:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "Nemocnica.h"
#include "Hospitalizacia.h"

Nemocnica::Nemocnica(const QString &nazov)
	: m_nazov(nazov),
	  m_zrusena(false)
{
}


Nemocnica::~Nemocnica()
{
}


const QString &Nemocnica::nazov() const
{
	return m_nazov;
}


void Nemocnica::setNazov(const QString &nazov)
{
	m_nazov = nazov;
}


void Nemocnica::setZrusena(bool zrusena)
{
	m_zrusena = zrusena;
}


bool Nemocnica::zrusena() const
{
	return m_zrusena;
}


void Nemocnica::hospitalizuj(Pacient *pacient, Hospitalizacia hospitalizacia)
{
	if (hospitalizacia.koniec().isValid()) {
		if (m_praveHospitalizovani.hasValue(pacient)) {
			m_praveHospitalizovani.remove(pacient);
		}

	}
	else {
		if (!m_praveHospitalizovani.hasValue(pacient)) {
			m_praveHospitalizovani.insert(pacient);
		}
	}

	if (!m_hospitalizovaniRc.hasValue(pacient)) {
		m_hospitalizovaniRc.insert(pacient);
		m_hospitalizovaniMeno.insert(pacient);
	}
	hospitalizacia.setNemocnica(this);
	pacient->pridajHospitalizaciu(hospitalizacia);
}


Nemocnica::PacientiRC::Iterator Nemocnica::hladajPacienta(const RodCis &rc)
{
	return m_hospitalizovaniRc.find(rc);
}


Nemocnica::PacientiMeno::Iterator Nemocnica::hladajPacienta(const Meno &meno)
{
	return m_hospitalizovaniMeno.find(meno);
}

