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

Meno::Meno()
	: m_meno(QString()),
	m_priezvisko(QString())
{
}


Meno::Meno(QString meno, QString priezvisko)
	: m_meno(meno),
	m_priezvisko(priezvisko)
{
}


std::ostream &operator << (std::ostream &os, Meno &meno)
{
	os << "Meno   " << meno.m_meno.toUtf8().data() << std::endl << "Priezv " << meno.m_priezvisko.toUtf8().data() << std::endl;
	return os;
}

