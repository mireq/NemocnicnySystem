/*
 * =====================================================================================
 *
 *       Filename:  Pacient.cpp
 *
 *        Version:  1.0
 *        Created:  05.11.2009 11:38:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Definícia pacienta.
 */

#include "Pacient.h"

#include <QDebug>

Pacient::Pacient()
	: m_valid(false)
{
}


Pacient::Pacient(const RodCis &rodCislo, const Meno &meno)
	: m_rodCislo(rodCislo),
	m_meno(meno),
	m_valid(true)
{
}


const Meno &Pacient::meno() const
{
	return m_meno;
}


void Pacient::setMeno(const Meno &meno)
{
	m_meno = meno;
}


const RodCis &Pacient::rodCislo() const
{
	return m_rodCislo;
}


void Pacient::setRodCislo(const RodCis &rodCislo)
{
	m_rodCislo = rodCislo;
	m_valid = true;
}


void Pacient::setRodCislo(QString rodCislo)
{
	if (rodCislo.length() != 11) {
		m_valid = false;
		return;
	}

	char rc[RodCis::RodCisloDlzka];
	int idx = 0;
	for (int i = 0; i < 11; ++i) {
		QChar znak = rodCislo[i];
		if (i == 6) {
			if (znak != '/') {
				m_valid = false;
				return;
			}
		}
		else {
			char zn = znak.toLatin1();
			if (zn < '0' || zn > '9') {
				m_valid = false;
			}
			rc[idx] = zn;
			idx++;
		}
	}
	m_rodCislo = RodCis(rc);
	m_valid = true;
}


const QDate &Pacient::datumNarodenia() const
{
	return m_datumNarodenia;
}


void Pacient::setDatumNarodenia(const QDate &datumNarodenia)
{
	m_datumNarodenia = datumNarodenia;
}


int Pacient::poistovna() const
{
	return m_poistovna;
}


void Pacient::setPoistovna(int poistovna)
{
	m_poistovna = poistovna;
}


const QString &Pacient::adresa() const
{
	return m_adresa;
}


void Pacient::setAdresa(const QString &adresa)
{
	m_adresa = adresa;
}


const QStringList &Pacient::alergie() const
{
	return m_alergie;
}


void Pacient::setAlergie(const QStringList &alergie)
{
	m_alergie = alergie;
}


void Pacient::pridajAlergiu(const QString &alergia)
{
	m_alergie.append(alergia);
}


void Pacient::odoberAlergiu(int index)
{
	m_alergie.removeAt(index);
}


std::ostream &operator << (std::ostream &os, Pacient &pacient)
{
	os << pacient.m_rodCislo << pacient.m_meno;
	return os;
}

