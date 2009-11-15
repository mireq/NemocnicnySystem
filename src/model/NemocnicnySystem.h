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

#include "AVLTree.h"
#include "Nemocnica.h"
#include "Comparator.h"


class NemocnicnySystem
{
public:
	typedef AVLTree<Nemocnica *, QString, NemocnicaNazovComparator> Nemocnice;

	NemocnicnySystem();
	~NemocnicnySystem();
	void pridajNemocnicu(const QString &nazov);
	bool odoberNemocnicu(const QString &nazov);

	// -------------------------------- NemocnicaDuplicitaException --------------------------------
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
private:
	Nemocnice m_nemocnice;
};

#endif   /* ----- #ifndef NEMOCNICNYSYSTEM_H  ----- */
