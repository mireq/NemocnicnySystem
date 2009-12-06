/*
 * =====================================================================================
 *    _____                              __
 *   / ___/__  __ _  ___  ___ ________ _/ /____  ____
 *  / /__/ _ \/  ' \/ _ \/ _ `/ __/ _ `/ __/ _ \/ __/
 *  \___/\___/_/_/_/ .__/\_,_/_/  \_,_/\__/\___/_/
 *                /_/
 *
 *        Version:  1.0
 *        Created:  30.10.2009 10:22:11
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
 * Deklarácia štandardného komparátora.
 */

#ifndef  COMPARATOR_H
#define  COMPARATOR_H

/**
 * Základné enumeračné typy komparátora.
 */
class ComparatorBase
{
public:
	/**
	 * Typy porovnania.
	 */
	enum ComparisonType {
		Lt       = -1, /**< Menšie než */
		Eql      = 0,  /**< Rovnaké (podľa kľúča) */
		Gt       = 1,  /**< Väčšie než */
		ExactEql = 2   /**< Rovnaké (podľa primárneho kľúča) */
	};
};

/**
 * Štandardný komparátor pre porovnanie dvoch objektov, ktoré majú operácie <, >
 * a ==.
 */
template <typename DataT, typename KeyT>
class Comparator: public ComparatorBase
{
public:
	/**
	 * Porovnanie ovjektu DataT a KeyT.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		KeyT b,
		ComparatorBase::ComparisonType type);
};


template <typename DataT, typename KeyT>
ComparatorBase::ComparisonType
	Comparator<DataT, KeyT>::operator()(
		DataT a,
		KeyT b,
		ComparatorBase::ComparisonType type)
{
	if (a == b) {
		return Eql;
	}
	if (a < b && type == Lt) {
		return Eql;
	}
	if (a > b && type == Gt) {
		return Eql;
	}
	if (a < b) {
		return Lt;
	}
	else {
		return Gt;
	}
}

/**
 * Porovnávanie rodných čísel pacientov.
 */
template <typename DataT, typename KeyT>
class PacientRodCisComparator: public Comparator<DataT, KeyT>
{
public:
	/**
	 * Porovnanie pacienta a rodného čísla.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		const KeyT &b,
		ComparatorBase::ComparisonType type);

	/**
	 * Porovnanie dvoch pacientov na základe ich rodných čísel.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};

/**
 * Porovnanie pacientov v prvom rade podľa mena a pri použití
 * ComparatorBase::ExactEql porovnáva pri rovnakých menách aj rodné čísla.
 */
template <typename DataT, typename KeyT>
class PacientMenoComparator: public Comparator<DataT, KeyT>
{
public:
	/**
	 * Porovnanie pacienta a mena.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		const KeyT &b,
		ComparatorBase::ComparisonType type);

	/**
	 * Porovnanie dvoch pacientov podľa mien.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};


/**
 * Porovnanie pacientov podľa poisťovne. Pri použití ComparatorBase::ExactEql sa
 * buden najskôr porovnávať poisťovňa potom rodné číslo.
 */
template <typename DataT, typename KeyT>
class PacientPoistovnaComparator: public Comparator<DataT, KeyT>
{
public:
	/**
	 * Porovnanie pacienta s poisťovňou.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		KeyT b,
		ComparatorBase::ComparisonType type);

	/**
	 * Porovnanie dvoch pacientov podľa poisťovní.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};


/**
 * Porovnanie nemocnice podľa názvu.
 */
template <typename DataT, typename KeyT>
class NemocnicaNazovComparator: public Comparator<DataT, KeyT>
{
public:
	/**
	 * Porovnanie nemocnice a názvu nemocnice.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		const KeyT &b,
		ComparatorBase::ComparisonType type);

	/**
	 * Porovnanie dvoch nemocníc.
	 */
	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};

#endif   /* ----- #ifndef COMPARATOR_H  ----- */

