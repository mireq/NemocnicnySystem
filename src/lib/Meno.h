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
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file
 * Deklarácia mena pacienta.
 */

#ifndef  MENO_H
#define  MENO_H

#include <QString>
#include <ostream>

#include "serialization.h"

class Meno
{
public:
	Meno();
	Meno(QString meno, QString priezvisko);
	bool isValid() const;
	QString toString() const;

	bool inline operator <(const Meno &other) const
	{
		// Odkomentovať pre porovnávanie na základe lokálnych nastavení
		/*
		int priezviskoComp = m_priezvisko.localeAwareCompare(other.m_priezvisko);
		if (priezviskoComp < 0) {
			return true;
		}
		if (priezviskoComp > 0) {
			return false;
		}

		int menoComp = m_meno.localeAwareCompare(other.m_meno);
		if (menoComp < 0) {
			return true;
		}
		else {
			return false;
		}*/
		
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
		// Odkomentovať pre porovnávanie na základe lokálnych nastavení
		/*
		int priezviskoComp = m_priezvisko.localeAwareCompare(other.m_priezvisko);
		if (priezviskoComp > 0) {
			return true;
		}
		if (priezviskoComp < 0) {
			return false;
		}

		int menoComp = m_meno.localeAwareCompare(other.m_meno);
		if (menoComp > 0) {
			return true;
		}
		else {
			return false;
		}
		*/
		
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
		// Odkomentovať pre porovnávanie na základe lokálnych nastavení
		/*
		if (m_priezvisko.localeAwareCompare(other.m_priezvisko) == 0 
			&& m_meno.localeAwareCompare(other.m_meno) == 0) {
			return true;
		}
		else {
			return false;
		}
		*/

		if (m_priezvisko == other.m_priezvisko && m_meno == other.m_meno) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class Archive>
	void serialize(Archive &ar, const unsigned int & /* version */)
	{
		ar & boost::serialization::make_nvp("k_meno", m_meno);
		ar & boost::serialization::make_nvp("priezvisko", m_priezvisko);
	}

private:
	QString m_meno;
	QString m_priezvisko;
	int a;

	friend std::ostream &operator << (std::ostream &os, Meno &meno);
};

// Serializácia do streamu
std::ostream &operator << (std::ostream &os, Meno &meno);

#endif   /* ----- #ifndef MENO_H  ----- */

