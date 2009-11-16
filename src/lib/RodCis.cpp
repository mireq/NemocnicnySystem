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
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Definícia rodného čísla.
 */

#include "RodCis.h"

#include <QDebug>

RodCis::RodCis()
	: m_valid(false)
{
	for (int i = 0; i < RodCisloDlzka; ++i) {
		m_rodCislo[i] = '0';
	}
	m_rodCislo[RodCisloDlzka] = '\0';
}


RodCis::RodCis(const char *rodCislo)
	: m_valid(false)
{
	char rc[RodCisloDlzka + 1];
	rc[RodCisloDlzka] = '\0';
	int idx = 0;
	for (int i = 0; i < RodCisloDlzka + 1; ++i) {
		char znak = rodCislo[i];
		if (i == 6) {
			if (znak != '/') {
				m_valid = false;
				return;
			}
		}
		else {
			if (znak < '0' || znak > '9') {
				m_valid = false;
				return;
			}
			rc[idx] = znak;
			idx++;
		}
	}
	for (int i = 0; i < RodCisloDlzka + 1; ++i) {
		m_rodCislo[i] = rc[i];
	}
	m_valid = true;
}


bool RodCis::isValid() const
{
	return m_valid;
}


std::ostream &operator << (std::ostream &os, RodCis &rodCislo)
{
	os << "Rodne cislo: " << rodCislo.m_rodCislo << std::endl;
	return os;
}

