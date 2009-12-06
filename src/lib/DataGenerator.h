/*
 * =====================================================================================
 *
 *       Filename:  DataGenerator.h
 *     ___       __       _____                      __
 *    / _ \___ _/ /____ _/ ___/__ ___  ___ _______ _/ /____  ____
 *   / // / _ `/ __/ _ `/ (_ / -_) _ \/ -_) __/ _ `/ __/ _ \/ __/
 *  /____/\_,_/\__/\_,_/\___/\__/_//_/\__/_/  \_,_/\__/\___/_/
 *
 *
 *        Version:  1.0
 *        Created:  19.11.2009 05:47:32
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
 * Deklarácia generátora náhodných hospitalizácií.
 */

#ifndef  DATAGENERATOR_H
#define  DATAGENERATOR_H

#include <QVector>
#include <QPair>
#include <QDate>
#include <QChar>

#include "Meno.h"
#include "RodCis.h"
#include "Hospitalizacia.h"

class Nemocnica;
class Pacient;

class DataGenerator
{
public:
	static QVector<Nemocnica *> generujNahodneNemocnice(int pocet);
	static QVector<Pacient *> generujPacientov(int pocet);
	static QVector<QPair<Pacient *, Hospitalizacia> > generujHospitalizacie(const QVector<Nemocnica *> &nemocnice, const QVector<Pacient *> &pacienti);
	static QString nahodnyText(int min, int max);
	static Meno nahodneMeno();
	static RodCis nahodneRodCis();
	static QDate nahodnyDatumNar();
	static int nahodnaPoistovna();
private:
	enum {PocetSpoluhlasok = 24};
	enum {PocetSamohlasok = 12};
	static const QChar spoluhlasky[PocetSpoluhlasok];
	static const QChar samohlasky[PocetSamohlasok];
};

#endif   /* ----- #ifndef DATAGENERATOR_H  ----- */

