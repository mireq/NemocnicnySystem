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
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Definícia pacienta.
 */

#include "Hospitalizacia.h"

#include "Pacient.h"


Pacient::Pacient()
	: m_poistovna(0),
	  m_valid(false)
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
	m_rodCislo = RodCis(rodCislo.toUtf8().data());
	m_valid = m_rodCislo.isValid();
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


bool Pacient::hospitalizovanyVCase(const QDate &zaciatok, const QDate &koniec, Nemocnica *nemocnica) const
{
	foreach (const Hospitalizacia &hospitalizacia, m_hospitalizacie) {
		if (nemocnica == NULL || nemocnica == hospitalizacia.nemocnica()) {
			if (hospitalizacia.koniec().isNull() || hospitalizacia.koniec() >= zaciatok) {
				if (hospitalizacia.zaciatok().isNull() || hospitalizacia.zaciatok() <= koniec) {
					return true;
				}
			}
		}
	}
	return false;
}


Nemocnica *Pacient::hospitalizovanyV() const
{
	if (m_hospitalizacie.count() == 0) {
		return NULL;
	}

	const Hospitalizacia h = m_hospitalizacie.last();
	if (!h.koniec().isValid()) {
		return h.nemocnica();
	}
	else {
		return NULL;
	}
}


const QList<Hospitalizacia> &Pacient::hospitalizacie() const
{
	return m_hospitalizacie;
}


const Hospitalizacia &Pacient::poslednaHospitalizacia() const
{
	return m_hospitalizacie.last();
}


void Pacient::pridajHospitalizaciu(const Hospitalizacia &hospitalizacia)
{
	Hospitalizacia h = hospitalizacia;
	if (m_hospitalizacie.count() != 0 && m_hospitalizacie.last().koniec().isNull()) {
		m_hospitalizacie.removeLast();
	}

	m_hospitalizacie.append(hospitalizacia);
}


bool Pacient::isValid() const
{
	return m_meno.isValid() && m_rodCislo.isValid();
}


std::ostream &operator << (std::ostream &os, Pacient &pacient)
{
	os << pacient.m_rodCislo << pacient.m_meno;
	os << "Datum narodenia: " << pacient.m_datumNarodenia.toString(Qt::SystemLocaleShortDate).toUtf8().constData() << std::endl;
	os << "Poistovna: " << pacient.m_poistovna << std::endl;
	os << "Adresa:" << std::endl;
	os << pacient.m_adresa.toUtf8().constData() << std::endl;
	os << "Alergie:" << std::endl;
	foreach (const QString &alergia, pacient.m_alergie) {
		os << alergia.toUtf8().constData() << std::endl;
	}
	return os;
}

