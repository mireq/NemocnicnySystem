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

#include <ostream>

class Pacient
{
public:
	Pacient(const RodCis &rodCis, const Meno &meno);
	const Meno &meno() const;
	const RodCis &rodCis() const;

private:
	RodCis m_rodCis;
	Meno m_meno;

	friend std::ostream &operator << (std::ostream &os, Pacient &pacient);
};

std::ostream &operator << (std::ostream &os, Pacient &pacient);

#endif   /* ----- #ifndef PACIENT_H  ----- */

