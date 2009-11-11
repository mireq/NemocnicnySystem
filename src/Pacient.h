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
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Deklarácia pacienta.
 */

#ifndef  PACIENT_H
#define  PACIENT_H

#include "Meno.h"
#include "RodCis.h"

#include <QDate>
#include <QString>
#include <QStringList>

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

	bool isValid() const;

private:
	RodCis m_rodCislo;
	Meno m_meno;
	QDate m_datumNarodenia;
	int m_poistovna;
	QString m_adresa;
	QStringList m_alergie;

	bool m_valid;

	friend std::ostream &operator << (std::ostream &os, Pacient &pacient);
};

std::ostream &operator << (std::ostream &os, Pacient &pacient);

#endif   /* ----- #ifndef PACIENT_H  ----- */

