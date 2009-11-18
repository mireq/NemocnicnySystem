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

#include <QString>

#include "AVLTree.h"
#include "Pacient.h"
#include "serialization.h"

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
	void hospitalizuj(Pacient *pacient, Hospitalizacia hospitalizacia);

	template <class Archive>
	void serialize(Archive &ar, const unsigned int & /* version */)
	{
		ar & boost::serialization::make_nvp("nazov", m_nazov);
		ar & boost::serialization::make_nvp("zrusena", m_zrusena);
		ar & boost::serialization::make_nvp("hosp", m_hospitalizovani);
		ar & boost::serialization::make_nvp("pr_hosp", m_praveHospitalizovani);
	}
private:
	QString m_nazov;
	bool m_zrusena;
	AVLTree<Pacient *, RodCis, PacientRodCisComparator> m_hospitalizovani;
	AVLTree<Pacient *, int, PacientPoistovnaComparator> m_praveHospitalizovani;
};

#endif   /* ----- #ifndef NEMOCNICA_H  ----- */

