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

RodCis::RodCis()
{
	for (int i = 0; i < RodCisloDlzka + 1; ++i) {
		m_rodCislo[i] = '\0';
	}
}


RodCis::RodCis(const char *rodCislo)
{
	char rc[RodCisloDlzka + 1];
	rc[RodCisloDlzka] = '\0';
	int idx = 0;
	for (int i = 0; i < RodCisloDlzka + 1; ++i) {
		char znak = rodCislo[i];
		if (i == 6) {
			/*if (znak != '/') {
				m_rodCislo[0] = '\0';
				return;
			}*/
			if (znak == '/') {
				continue;
			}
			else if (znak < '0' || znak > '9') {
				m_rodCislo[0] = '\0';
				return;
			}
			else {
				rc[idx] = znak;
				idx++;
			}
		}
		else {
			if (znak < '0' || znak > '9') {
				m_rodCislo[0] = '\0';
				return;
			}
			rc[idx] = znak;
			idx++;
			if (idx == RodCisloDlzka) {
				break;
			}
		}
	}
	for (int i = 0; i < RodCisloDlzka + 1; ++i) {
		m_rodCislo[i] = rc[i];
	}
}


bool RodCis::isValid() const
{
	if (m_rodCislo[0] != '\0') {
		return true;
	}
	else {
		return false;
	}
}


QString RodCis::toString() const
{
	if (isValid()) {
		char rc[RodCisloDlzka + 2];
		rc[RodCisloDlzka + 1] = '\0';
		for (int i = 0; i < 6; ++i) {
			rc[i] = m_rodCislo[i];
		}
		rc[6] = '/';
		for (int i = 6; i < 10; ++i) {
			rc[i + 1] = m_rodCislo[i];
		}
		return QString(rc);
	}
	else {
		return QString();
	}
}


std::ostream &operator << (std::ostream &os, RodCis &rodCislo)
{
	os << "Rodne cislo: " << rodCislo.m_rodCislo << std::endl;
	return os;
}

