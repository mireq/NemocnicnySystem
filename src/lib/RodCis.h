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
 *         Author:  Miroslav Bendik
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
#include "serialization.h"

class RodCis
{
public:
	enum {RodCisloDlzka = 10};

	RodCis();
	RodCis(const char *rodCislo);
	bool isValid() const;

	bool inline operator <(const RodCis &other) const
	{
		for (int i = 0; i < RodCisloDlzka; ++i) {
			if (m_rodCislo[i] < other.m_rodCislo[i]) {
				return true;
			}
			else if (m_rodCislo[i] > other.m_rodCislo[i]) {
				return false;
			}
		}
		return false;
	}

	bool inline operator >(const RodCis &other) const
	{
		for (int i = 0; i < RodCisloDlzka; ++i) {
			if (m_rodCislo[i] > other.m_rodCislo[i]) {
				return true;
			}
			else if (m_rodCislo[i] < other.m_rodCislo[i]) {
				return false;
			}
		}
		return false;
	}

	bool inline operator ==(const RodCis &other) const
	{
		for (int i = 0; i < RodCisloDlzka; ++i) {
			if (m_rodCislo[i] != other.m_rodCislo[i]) {
				return false;
			}
		}
		return true;
	}

	template <class Archive>
	void serialize(Archive &ar, const unsigned int &)
	{
		boost::serialization::binary_object rc(m_rodCislo, RodCisloDlzka);
		ar & boost::serialization::make_nvp("rc", rc);
	}

private:
	char m_rodCislo[RodCisloDlzka + 1];
	bool m_valid;
	friend std::ostream &operator << (std::ostream &os, RodCis &rodCislo);
};

#endif   /* ----- #ifndef RODCIS_H  ----- */

