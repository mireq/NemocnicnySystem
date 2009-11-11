/*
 * =====================================================================================
 *
 *       Filename:  Pacient.cpp
 *
 *        Version:  1.0
 *        Created:  05.11.2009 11:38:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Definícia pacienta.
 */

#include "Pacient.h"

Pacient::Pacient(const RodCis &rodCis, const Meno &meno)
	: m_rodCis(rodCis),
	m_meno(meno)
{
}


const Meno &Pacient::meno() const
{
	return m_meno;
}


const RodCis &Pacient::rodCis() const
{
	return m_rodCis;
}


std::ostream &operator << (std::ostream &os, Pacient &pacient)
{
	os << pacient.m_rodCis << " " << pacient.m_meno;
	return os;
}

