/*
 * =====================================================================================
 *
 *       Filename:  NemocnicnySystem.cpp
 *
 *        Version:  1.0
 *        Created:  15.11.2009 10:49:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "NemocnicnySystem.h"


NemocnicnySystem::NemocnicnySystem()
{
}


NemocnicnySystem::~NemocnicnySystem()
{
}


void NemocnicnySystem::pridajNemocnicu(const QString &nazov)
{
	Nemocnica *novaNemocnica = new Nemocnica(nazov);
	try {
		m_nemocnice.insert(novaNemocnica);
	}
	catch (Nemocnice::DuplicateDataException *e) {
		delete novaNemocnica;
		throw NemocnicaDuplicitaException(nazov);
	}
}


bool NemocnicnySystem::odoberNemocnicu(const QString &nazov)
{
	Nemocnice::Iterator it = m_nemocnice.find(nazov);
	if (it.hasNext()) {
		Nemocnica *n = it.next();
		m_nemocnice.remove(n);
		delete n;
		return true;
	}
	return false;
}

