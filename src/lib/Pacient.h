/*
 * =====================================================================================
 *     ___           _          __
 *    / _ \___ _____(_)__ ___  / /_
 *   / ___/ _ `/ __/ / -_) _ \/ __/
 *  /_/   \_,_/\__/_/\__/_//_/\__/
 *
 *       Filename:  Pacient.h
 *
 *        Version:  1.0
 *        Created:  05.11.2009 11:34:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file
 * Deklarácia pacienta.
 */

#ifndef  PACIENT_H
#define  PACIENT_H

#include "Hospitalizacia.h"
#include "Meno.h"
#include "RodCis.h"
#include "serialization.h"

#include <QDate>
#include <QString>
#include <QStringList>
#include <QList>

#include <ostream>

class Pacient
{
public:
	Pacient();
	Pacient(const RodCis &rodCislo, const Meno &meno);
	const Meno &meno() const;
	void setMeno(const Meno &meno);
	const RodCis &rodCislo() const;
	void setRodCislo(const RodCis &rodCislo);
	void setRodCislo(QString rodCislo);
	const QDate &datumNarodenia() const;
	void setDatumNarodenia(const QDate &datum);
	int poistovna() const;
	void setPoistovna(int poistovna);
	const QString &adresa() const;
	void setAdresa(const QString &adresa);
	const QStringList &alergie() const;
	void setAlergie(const QStringList &alergie);
	void pridajAlergiu(const QString &alergia);
	void odoberAlergiu(int index);
	bool hospitalizovanyVCase(const QDate &zaciatok, const QDate &koniec, Nemocnica *nemocnica = NULL) const;
	int dniHospitalizacieVCase(const QDate &zaciatok, const QDate &koniec) const;
	Nemocnica *hospitalizovanyV() const;
	const QList<Hospitalizacia> &hospitalizacie() const;
	const Hospitalizacia &poslednaHospitalizacia() const;
	void pridajHospitalizaciu(const Hospitalizacia &hospitalizacia);

	bool isValid() const;

	template <class Archive>
	void serialize(Archive &ar, const unsigned int & /* version */)
	{
		ar & boost::serialization::make_nvp("rc", m_rodCislo);
		ar & boost::serialization::make_nvp("meno", m_meno);
		ar & boost::serialization::make_nvp("dat_nar", m_datumNarodenia);
		ar & boost::serialization::make_nvp("poistovna", m_poistovna);
		ar & boost::serialization::make_nvp("adresa", m_adresa);
		ar & boost::serialization::make_nvp("alergie", m_alergie);
		ar & boost::serialization::make_nvp("hosp", m_hospitalizacie);
	}

private:
	RodCis m_rodCislo;
	Meno m_meno;
	QDate m_datumNarodenia;
	int m_poistovna;
	QString m_adresa;
	QStringList m_alergie;
	QList<Hospitalizacia > m_hospitalizacie;

	bool m_valid;

friend std::ostream &operator << (std::ostream &os, Pacient &pacient);
};

std::ostream &operator << (std::ostream &os, Pacient &pacient);

#endif   /* ----- #ifndef PACIENT_H  ----- */

