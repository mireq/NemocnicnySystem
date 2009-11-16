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
 * \file Deklarácia štandardného komparátora.
 */

#ifndef  COMPARATOR_H
#define  COMPARATOR_H


class ComparatorBase
{
public:
	enum ComparisonType {
		Lt       = -1,
		Eql      = 0,
		Gt       = 1,
		ExactEql = 2
	};
};

template <typename DataT, typename KeyT>
class Comparator: public ComparatorBase
{
	//int operator()(DataT a, KeyT b, typename AVLTree<DataT, KeyT, ::Comparator>::ComparisonType type);
public:
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


template <typename DataT, typename KeyT>
class PacientRodCisComparator: public Comparator<DataT, KeyT>
{
public:
	ComparatorBase::ComparisonType operator()(
		DataT a,
		const KeyT &b,
		ComparatorBase::ComparisonType type);

	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};


template <typename DataT, typename KeyT>
class PacientMenoComparator: public Comparator<DataT, KeyT>
{
public:
	ComparatorBase::ComparisonType operator()(
		DataT a,
		const KeyT &b,
		ComparatorBase::ComparisonType type);

	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};


template <typename DataT, typename KeyT>
class PacientPoistovnaComparator: public Comparator<DataT, KeyT>
{
public:
	ComparatorBase::ComparisonType operator()(
		DataT a,
		KeyT b,
		ComparatorBase::ComparisonType type);

	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};


template <typename DataT, typename KeyT>
class NemocnicaNazovComparator: public Comparator<DataT, KeyT>
{
public:
	ComparatorBase::ComparisonType operator()(
		DataT a,
		const KeyT &b,
		ComparatorBase::ComparisonType type);

	ComparatorBase::ComparisonType operator()(
		DataT a,
		DataT b,
		ComparatorBase::ComparisonType type);
};

#endif   /* ----- #ifndef COMPARATOR_H  ----- */

