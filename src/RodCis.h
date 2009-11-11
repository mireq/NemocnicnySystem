/*
 * =====================================================================================
 *     ___          ________
 *    / _ \___  ___/ / ___(_)__
 *   / , _/ _ \/ _  / /__/ (_-<
 *  /_/|_|\___/\_,_/\___/_/___/
 *
 *       Filename:  RodCis.h
 *
 *        Version:  1.0
 *        Created:  05.11.2009 11:40:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Deklarácia rodného čísla.
 */

#ifndef  RODCIS_H
#define  RODCIS_H

#include <ostream>

class RodCis
{
public:
	RodCis(const char *rodCis);

	bool inline operator <(const RodCis &other) const
	{
		for (int i = 0; i < RodCisDlzka; ++i) {
			if (m_rodCis[i] < other.m_rodCis[i]) {
				return true;
			}
			else if (m_rodCis[i] > other.m_rodCis[i]) {
				return false;
			}
		}
		return false;
	}

	bool inline operator >(const RodCis &other) const
	{
		for (int i = 0; i < RodCisDlzka; ++i) {
			if (m_rodCis[i] > other.m_rodCis[i]) {
				return true;
			}
			else if (m_rodCis[i] < other.m_rodCis[i]) {
				return false;
			}
		}
		return false;
	}

	bool inline operator ==(const RodCis &other) const
	{
		for (int i = 0; i < RodCisDlzka; ++i) {
			if (m_rodCis[i] != other.m_rodCis[i]) {
				return false;
			}
		}
		return true;
	}

private:
	enum {RodCisDlzka = 10};
	char m_rodCis[RodCisDlzka];
	friend std::ostream &operator << (std::ostream &os, RodCis &rodCis);
};

#endif   /* ----- #ifndef RODCIS_H  ----- */

