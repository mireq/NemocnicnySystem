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

RodCis::RodCis(const char *rodCis)
{
	for (int i = 0; i < RodCisDlzka; ++i) {
		m_rodCis[i] = rodCis[i];
	}
}


std::ostream &operator << (std::ostream &os, RodCis &rodCis)
{
	char rc[RodCis::RodCisDlzka + 1];
	for (int i = 0; i < RodCis::RodCisDlzka; ++i) {
		rc[i] = rodCis.m_rodCis[i];
	}
	rc[RodCis::RodCisDlzka] = '\0';
	os << rc;
	return os;
}

