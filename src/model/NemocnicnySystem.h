/*
 * =====================================================================================
 *
 *       Filename:  NemocnicnySystem.h
 *     _  __                        _               ____         __
 *    / |/ /__ __ _  ___  _______  (_)______  __ __/ __/_ _____ / /____ __ _
 *   /    / -_)  ' \/ _ \/ __/ _ \/ / __/ _ \/ // /\ \/ // (_-</ __/ -_)  ' \
 *  /_/|_/\__/_/_/_/\___/\__/_//_/_/\__/_//_/\_, /___/\_, /___/\__/\__/_/_/_/
 *                                          /___/    /___/
 *        Version:  1.0
 *        Created:  15.11.2009 10:49:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  NEMOCNICNYSYSTEM_H
#define  NEMOCNICNYSYSTEM_H

#include <QString>
#include <QObject>

#include "serialization.h"

#include "AVLTree.h"
#include "Nemocnica.h"
#include "Comparator.h"
#include "RodCis.h"


class NemocnicnySystem: public QObject
{
Q_OBJECT
public:
	typedef AVLTree<Nemocnica *, QString, NemocnicaNazovComparator> Nemocnice;
	typedef AVLTree<Pacient *, RodCis, PacientRodCisComparator> Pacienti;

	NemocnicnySystem();
	~NemocnicnySystem();
	void pridajNemocnicu(const QString &nazov);
	bool odoberNemocnicu(const QString &nazov);
	bool zrusNemocnicu(const QString &nazov);
	void pridajPacienta(const Pacient &pacient);
	void pridajPacienta(Pacient *pacient);
	void hospitalizuj(Nemocnica *nemocnica, Pacient *pacient, const Hospitalizacia &hospitalizacia);
	Pacienti::Iterator pacienti();
	Pacienti::Iterator najdiPacienta(const RodCis &rc);
	Nemocnice::Iterator najdiNemocnicu(const QString &nazov);
	Nemocnice::Iterator nemocnice() { return m_nemocnice.iterator(); };

	void uloz(const QString &nazovSuboru);
	void otvor(const QString &nazovSuboru);
	void zatvor();
	bool zmenene() const;
	const QString &nazovSuboru() const;

	template <class Archive>
	void serialize(Archive &ar, const unsigned  int & /* version */)
	{
		ar & boost::serialization::make_nvp("pacienti", m_pacienti);
		ar & boost::serialization::make_nvp("nemocnice", m_nemocnice);
	}

	/* ----- NemocnicaDuplicitaException ----- */
	class NemocnicaDuplicitaException
	{
	public:
		const QString &nazov() const { return m_nazov; };
	protected:
		NemocnicaDuplicitaException(const QString &nazov): m_nazov(nazov) {};
		~NemocnicaDuplicitaException() {};
	private:
		QString m_nazov;
	friend class NemocnicnySystem;
	};

	/* ----- PacientDuplicitaException ----- */
	class PacientDuplicitaException
	{
	public:
		const Pacient &pacient() const { return m_pacient; };
	protected:
		PacientDuplicitaException(const Pacient &pacient): m_pacient(pacient) {};
		~PacientDuplicitaException() {};
	private:
		Pacient m_pacient;
	friend class NemocnicnySystem;
	};

	/* ----- SuborException ----- */
	class SuborException
	{
	public:
		enum ExceptionType {
			Access = 0,
			Format = 1
		};
		ExceptionType type() const { return m_type; };
	private:
		SuborException(ExceptionType type) : m_type(type) {};
		ExceptionType m_type;
	friend class NemocnicnySystem;
	};

signals:
	void zmenaStavuSuboru(bool zmenene, const QString &nazovSuboru);
	void zmenaNemocnic();

private:
	void setZmenene(bool zmenene, const QString &subor = QString());

private:
	Nemocnice m_nemocnice;
	Pacienti m_pacienti;

	QString m_nazovSuboru;
	bool m_zmenene;
};

#endif   /* ----- #ifndef NEMOCNICNYSYSTEM_H  ----- */

