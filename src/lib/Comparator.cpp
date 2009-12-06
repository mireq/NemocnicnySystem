/*
 * =====================================================================================
 *
 *       Filename:  Comparator.cpp
 *
 *        Version:  1.0
 *        Created:  30.10.2009 10:21:34
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
 * Implementácia štandardného komparátora.
 */

#include "Comparator.h"
#include "Pacient.h"
#include "Nemocnica.h"

template <>
ComparatorBase::ComparisonType
	PacientMenoComparator<Pacient *, Meno>::operator()(
		Pacient *a,
		const Meno &b,
		ComparatorBase::ComparisonType type)
{
	if (a->meno() < b) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (a->meno() > b) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}
	return Eql;
}


template <>
ComparatorBase::ComparisonType
	PacientMenoComparator<Pacient *, Meno>::operator()(
		Pacient *a,
		Pacient *b,
		ComparatorBase::ComparisonType type)
{
	if (a->meno() < b->meno()) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (a->meno() > b->meno()) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}

	// Sú rovnaké
	if (type != ExactEql) {
		return Eql;
	}
	// Chceme presné zaradenie - kontrolujeme rodné číslo
	if (a->rodCislo() < b->rodCislo()) {
		return Lt;
	}
	if (a->rodCislo() > b->rodCislo()) {
		return Gt;
	}
	return Eql;
}


template <>
ComparatorBase::ComparisonType
	PacientRodCisComparator<Pacient *, RodCis>::operator()(
		Pacient *a,
		Pacient *b,
		ComparatorBase::ComparisonType type)
{
	if (a->rodCislo() < b->rodCislo()) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (a->rodCislo() > b->rodCislo()) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}
	return Eql;
}


template <>
ComparatorBase::ComparisonType
	PacientRodCisComparator<Pacient *, RodCis>::operator()(
		Pacient *a,
		const RodCis &b,
		ComparatorBase::ComparisonType type)
{
	if (a->rodCislo() < b) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (a->rodCislo() > b) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}
	return Eql;
}


template <>
ComparatorBase::ComparisonType
	PacientPoistovnaComparator<Pacient *, int>::operator()(
		Pacient *a,
		Pacient *b,
		ComparatorBase::ComparisonType type)
{
	if (a->poistovna() < b->poistovna()) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (a->poistovna() > b->poistovna()) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}

	// Sú rovnaké
	if (type != ExactEql) {
		return Eql;
	}
	// Chceme presné zaradenie - kontrolujeme rodné číslo
	if (a->rodCislo() < b->rodCislo()) {
		return Lt;
	}
	if (a->rodCislo() > b->rodCislo()) {
		return Gt;
	}
	return Eql;
}


template <>
ComparatorBase::ComparisonType
	PacientPoistovnaComparator<Pacient *, int>::operator()(
		Pacient *a,
		int b,
		ComparatorBase::ComparisonType type)
{
	if (a->poistovna() < b) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (a->poistovna() > b) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}
	return Eql;
}


template <>
ComparatorBase::ComparisonType
	NemocnicaNazovComparator<Nemocnica *, QString>::operator()(
		Nemocnica *a,
		Nemocnica *b,
		ComparatorBase::ComparisonType type)
{
	int cmp = a->nazov().localeAwareCompare(b->nazov());
	if (cmp < 0) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (cmp > 0) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}
	return Eql;
}


template <>
ComparatorBase::ComparisonType
	NemocnicaNazovComparator<Nemocnica *, QString>::operator()(
		Nemocnica *a,
		const QString &b,
		ComparatorBase::ComparisonType type)
{
	int cmp = a->nazov().localeAwareCompare(b);
	if (cmp < 0) {
		if (type == Lt) {
			return Eql;
		}
		else {
			return Lt;
		}
	}
	if (cmp > 0) {
		if (type == Gt) {
			return Eql;
		}
		else {
			return Gt;
		}
	}
	return Eql;
}


