/*
 * =====================================================================================
 *
 *       Filename:  RodCis.cpp
 *
 *        Version:  1.0
 *        Created:  05.11.2009 11:38:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Definícia rodného čísla.
 */

#include "RodCis.h"

RodCis::RodCis()
{
	for (int i = 0; i < RodCisloDlzka; ++i) {
		m_rodCislo[i] = '0';
	}
	m_rodCislo[RodCisloDlzka] = '\0';
}


RodCis::RodCis(const char *rodCislo)
{
	for (int i = 0; i < RodCisloDlzka; ++i) {
		m_rodCislo[i] = rodCislo[i];
	}
	m_rodCislo[RodCisloDlzka] = '\0';
}


std::ostream &operator << (std::ostream &os, RodCis &rodCislo)
{
	os << "Rodne cislo: " << rodCislo.m_rodCislo << std::endl;
	return os;
}

