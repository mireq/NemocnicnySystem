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
}


RodCis::RodCis(const char *rodCislo)
{
	for (int i = 0; i < RodCisloDlzka; ++i) {
		m_rodCislo[i] = rodCislo[i];
	}
}


std::ostream &operator << (std::ostream &os, RodCis &rodCislo)
{
	char rc[RodCis::RodCisloDlzka + 1];
	for (int i = 0; i < RodCis::RodCisloDlzka; ++i) {
		rc[i] = rodCislo.m_rodCislo[i];
	}
	rc[RodCis::RodCisloDlzka] = '\0';
	os << "Rodne cislo: " << rc << std::endl;
	return os;
}

