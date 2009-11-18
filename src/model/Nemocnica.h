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
	typedef AVLTree<Pacient *, RodCis, PacientRodCisComparator> PacientiRC;
	typedef AVLTree<Pacient *, Meno, PacientMenoComparator> PacientiMeno;
	typedef AVLTree<Pacient *, int, PacientPoistovnaComparator> PacientiPoistovna;
	Nemocnica(): m_zrusena(true) {};
	Nemocnica(const QString &nazov);
	~Nemocnica();
	const QString &nazov() const;
	void setNazov(const QString &nazov);
	void setZrusena(bool zrusena);
	bool zrusena() const;
	void hospitalizuj(Pacient *pacient, Hospitalizacia hospitalizacia);
	PacientiRC::Iterator pacienti();
	PacientiRC::Iterator hladajPacienta(const RodCis &rc);
	PacientiMeno::Iterator hladajPacienta(const Meno &meno);
	PacientiPoistovna::Iterator hospitalizovaniPacienti();
	PacientiPoistovna::Iterator hospitalizovaniPacientiPoistovna(int poistovna);

	template <class Archive>
	void serialize(Archive &ar, const unsigned int & /* version */)
	{
		ar & boost::serialization::make_nvp("nazov", m_nazov);
		ar & boost::serialization::make_nvp("zrusena", m_zrusena);
		ar & boost::serialization::make_nvp("hosprc", m_hospitalizovaniRc);
		ar & boost::serialization::make_nvp("hospmeno", m_hospitalizovaniMeno);
		ar & boost::serialization::make_nvp("pr_hosp", m_praveHospitalizovani);
	}
private:
	QString m_nazov;
	bool m_zrusena;
	PacientiRC m_hospitalizovaniRc;
	PacientiMeno m_hospitalizovaniMeno;
	PacientiPoistovna m_praveHospitalizovani;
};

#endif   /* ----- #ifndef NEMOCNICA_H  ----- */

