/*
 * =====================================================================================
 *
 *       Filename:  Hospitalizacia.h
 *     __ __              _ __       ___              _
 *    / // /__  ___ ___  (_) /____ _/ (_)__ ___ _____(_)__ _
 *   / _  / _ \(_-</ _ \/ / __/ _ `/ / /_ // _ `/ __/ / _ `/
 *  /_//_/\___/___/ .__/_/\__/\_,_/_/_//__/\_,_/\__/_/\_,_/
 *               /_/
 *
 *        Version:  1.0
 *        Created:  17.11.2009 15:20:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  HOSPITALIZACIA_H
#define  HOSPITALIZACIA_H

#include "serialization.h"

#include <QDate>
#include <QString>

#include <ostream>

class Nemocnica;

class Hospitalizacia
{
public:
	Hospitalizacia();
	Hospitalizacia(Nemocnica *nemocnica, const QString &diagnoza, const QDate &zaciatok, const QDate &koniec = QDate());
	Nemocnica *nemocnica() const;
	const QString &diagnoza() const;
	const QDate &zaciatok() const;
	const QDate &koniec() const;
	bool ukoncena() const;
	bool isValid() const;

	template <class Archive>
	void serialize(Archive &ar, const unsigned int & /* version */)
	{
		ar & boost::serialization::make_nvp("nemocnica", m_nemocnica);
		ar & boost::serialization::make_nvp("diagnoza", m_diagnoza);
		ar & boost::serialization::make_nvp("zaciatok", m_zaciatok);
		ar & boost::serialization::make_nvp("koniec", m_koniec);
	}
private:
	Nemocnica *m_nemocnica;
	QString m_diagnoza;
	QDate m_zaciatok;
	QDate m_koniec;

friend std::ostream &operator << (std::ostream &os, Hospitalizacia &hospitalizacia);
};

std::ostream &operator << (std::ostream &os, Hospitalizacia &hospitalizacia);

#endif   /* ----- #ifndef HOSPITALIZACIA_H  ----- */

