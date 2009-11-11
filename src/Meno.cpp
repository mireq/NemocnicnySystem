/*
 * =====================================================================================
 *
 *       Filename:  Meno.cpp
 *
 *        Version:  1.0
 *        Created:  05.11.2009 09:57:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Definícia mena pacienta.
 */

#include "Meno.h"

Meno::Meno(std::string meno, std::string priezvisko)
{
	m_meno = meno;
	m_priezvisko = priezvisko;
}

std::ostream &operator << (std::ostream &os, Meno &meno)
{
	os << meno.m_priezvisko << " " << meno.m_meno;
	return os;
}

