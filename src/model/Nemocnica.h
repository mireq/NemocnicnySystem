/*
 * =====================================================================================
 *
 *       Filename:  Nemocnica.h
 *     _  __                        _
 *    / |/ /__ __ _  ___  _______  (_)______ _
 *   /    / -_)  ' \/ _ \/ __/ _ \/ / __/ _ `/
 *  /_/|_/\__/_/_/_/\___/\__/_//_/_/\__/\_,_/
 *
 *        Version:  1.0
 *        Created:  13.11.2009 09:48:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  NEMOCNICA_H
#define  NEMOCNICA_H

#include "AVLTree.h"
#include "Pacient.h"
#include "serialization.h"

#include <QString>

class Nemocnica
{
public:
	Nemocnica(): m_zrusena(true) {};
	Nemocnica(const QString &nazov);
	~Nemocnica();
	const QString &nazov() const;
	void setNazov(const QString &nazov);
	void setZrusena(bool zrusena);
	bool zrusena() const;

	template <class Archive>
	void serialize(Archive &ar, const unsigned int &/*version*/)
	{
		ar & boost::serialization::make_nvp("nazov", m_nazov);
		ar & boost::serialization::make_nvp("zrusena", m_zrusena);
		ar & boost::serialization::make_nvp("pacienti_meno", m_pacientiMeno);
		ar & boost::serialization::make_nvp("pacienti_poist", m_pacientiPoistovna);
	}
private:
	QString m_nazov;
	bool m_zrusena;
	AVLTree<Pacient *, Meno, PacientMenoComparator> m_pacientiMeno;
	AVLTree<Pacient *, int, PacientPoistovnaComparator> m_pacientiPoistovna;
};

#endif   /* ----- #ifndef NEMOCNICA_H  ----- */

