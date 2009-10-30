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
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Deklarácia štandardného komparátora.
 */

#ifndef  COMPARATOR_H
#define  COMPARATOR_H

template <typename DataT, typename KeyT> class Comparator
{
public:
	int operator()(DataT a, KeyT b);
};

// Je potrebná aj implementácia
#include "Comparator.cpp"

#endif   /* ----- #ifndef STDCOMPARATOR_H  ----- */

