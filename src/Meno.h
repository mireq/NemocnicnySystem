/*
 * =====================================================================================
 *     __  ___
 *    /  |/  /__ ___  ___
 *   / /|_/ / -_) _ \/ _ \
 *  /_/  /_/\__/_//_/\___/
 *
 *       Filename:  Meno.h
 *
 *        Version:  1.0
 *        Created:  05.11.2009 09:43:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Deklarácia mena pacienta.
 */

#ifndef  MENO_H
#define  MENO_H

#include <string>
#include <ostream>

class Meno
{
public:
	Meno(std::string meno, std::string priezvisko);

	bool inline operator <(const Meno &other) const
	{
		if (m_priezvisko < other.m_priezvisko) {
			return true;
		}
		if (m_priezvisko > other.m_priezvisko) {
			return false;
		}

		// Priezviská sú rovnaké - porovnávamé mená
		if (m_meno < other.m_meno) {
			return true;
		}
		else {
			return false;
		}
	}

	bool inline operator >(const Meno &other) const
	{
		if (m_priezvisko > other.m_priezvisko) {
			return true;
		}
		if (m_priezvisko < other.m_priezvisko) {
			return false;
		}

		// Priezviská sú rovnaké - porovnávamé mená
		if (m_meno > other.m_meno) {
			return true;
		}
		else {
			return false;
		}
	}

	bool inline operator ==(const Meno &other) const
	{
		if (m_priezvisko == other.m_priezvisko && m_meno == other.m_meno) {
			return true;
		}
		else {
			return false;
		}
	}

private:
	std::string m_meno;
	std::string m_priezvisko;

	friend std::ostream &operator << (std::ostream &os, Meno &meno);
};

std::ostream &operator << (std::ostream &os, Meno &meno);

#endif   /* ----- #ifndef MENO_H  ----- */

