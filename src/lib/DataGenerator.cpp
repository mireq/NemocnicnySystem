/*
 * =====================================================================================
 *
 *       Filename:  DataGenerator.cpp
 *
 *        Version:  1.0
 *        Created:  19.11.2009 05:47:18
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
 * Implementácia generátora náhodných hospitalizácií.
 */

#include "DataGenerator.h"
#include "AVLTree.h"
#include "Nemocnica.h"
#include "Pacient.h"

#include <iostream>

const QChar DataGenerator::spoluhlasky[PocetSpoluhlasok] = {
	0x0062, 0x0063, 0x010d, 0x0064, 0x010f, 0x0066,
	0x0067, 0x0068, 0x006a, 0x006b, 0x006c, 0x013e,
	0x006d, 0x006e, 0x0148, 0x0070, 0x0072, 0x0073,
	0x0161, 0x0074, 0x0165, 0x0076, 0x007a, 0x017e
};
const QChar DataGenerator::samohlasky[PocetSamohlasok] = {
	0x0061, 0x00e1, 0x0065, 0x00e9, 0x0069, 0x00ed,
	0x006f, 0x00f3, 0x0075, 0x00fa, 0x0079, 0x00fd
};

QVector<Nemocnica *> DataGenerator::generujNahodneNemocnice(int pocet)
{
	typedef AVLTree<Nemocnica *, QString, NemocnicaNazovComparator> Nemocnice;
	Nemocnice nemocnice;
	for (int i = 0; i < pocet; ++i) {
		Nemocnica *nemocnica = new Nemocnica(nahodnyText(3, 10));
		try {
			nemocnice.insert(nemocnica);
		}
		catch (Nemocnice::DuplicateDataException &) {
		}
	}
	Nemocnice::Iterator it = nemocnice.iterator();
	QVector<Nemocnica *> zoznamNemocnic;
	while (it.hasNext()) {
		zoznamNemocnic.append(it.next());
	}
	return zoznamNemocnic;
}


QVector<Pacient *> DataGenerator::generujPacientov(int pocet)
{
	typedef AVLTree<Pacient *, RodCis, PacientRodCisComparator> Pacienti;
	Pacienti pacienti;

	for (int i = 0; i < pocet; ++i) {
		Pacient *pacient = new Pacient(nahodneRodCis(), nahodneMeno());
		pacient->setDatumNarodenia(nahodnyDatumNar());
		pacient->setPoistovna(nahodnaPoistovna());
		try {
			pacienti.insert(pacient);
		}
		catch (Pacienti::DuplicateDataException &) {
		}
	}

	Pacienti::Iterator it = pacienti.iterator();
	QVector<Pacient *> zoznamPacientov;
	while (it.hasNext()) {
		zoznamPacientov.append(it.next());
	}
	return zoznamPacientov;
}


QVector<QPair<Pacient *, Hospitalizacia> > DataGenerator::generujHospitalizacie(const QVector<Nemocnica *> &nemocnice, const QVector<Pacient *> &pacienti)
{
	QVector<QPair<Pacient *, Hospitalizacia> > zoznamHospitalizacii;
	foreach (Pacient *pacient, pacienti) {
		int zaciatok = 5000;
		Nemocnica *nemocnica = nemocnice[qrand() % nemocnice.count()];
		while (1) {
			if (zaciatok < 2) {
				break;
			}
			zaciatok = qrand() % zaciatok;
			int koniec = qMax(qrand() % (zaciatok + 1), zaciatok - qrand() % 15);
			QDate zaciatokDat = QDate::currentDate().addDays(-zaciatok);
			QDate koniecDat = QDate::currentDate().addDays(-koniec);
			zaciatok = koniec;
			QString diagnoza = nahodnyText(2, 10);
			if (qrand() % 8 > 0) {
				if (zaciatok < 30 && qrand() % 2 == 0) {
					zoznamHospitalizacii.append(QPair<Pacient *, Hospitalizacia>(pacient, Hospitalizacia(nemocnica, diagnoza, zaciatokDat, QDate())));
				}
				else {
					zoznamHospitalizacii.append(QPair<Pacient *, Hospitalizacia>(pacient, Hospitalizacia(nemocnica, diagnoza, zaciatokDat, koniecDat)));
				}
				break;
			}
			else {
				zoznamHospitalizacii.append(QPair<Pacient *, Hospitalizacia>(pacient, Hospitalizacia(nemocnica, diagnoza, zaciatokDat, koniecDat)));
			}
		}
	}
	return zoznamHospitalizacii;
}


QString DataGenerator::nahodnyText(int min, int max)
{
	QString out;
	int dlzka = min + qrand() % (max - min + 1);
	out.fill(' ', dlzka);
	bool samohlaska = qrand() % 2;
	for (int i = 0; i < dlzka; ++i) {
		QChar znak;
		if (samohlaska) {
			znak = samohlasky[qrand() % PocetSamohlasok];
		}
		else {
			znak = spoluhlasky[qrand() % PocetSpoluhlasok];
		}
		if (i == 0) {
			znak = znak.toUpper();
		}
		out[i] = znak;
		samohlaska = !samohlaska;
	}
	return out;
}


Meno DataGenerator::nahodneMeno()
{
	return Meno(nahodnyText(3, 7), nahodnyText(3, 8));
}


RodCis DataGenerator::nahodneRodCis()
{
	char rc[11];
	rc[10] = '\0';
	for (int i = 0; i < 10; ++i) {
		rc[i] = '0' + qrand() % 10;
	}
	return RodCis(rc);
}


QDate DataGenerator::nahodnyDatumNar()
{
	return QDate::currentDate().addDays(-(qrand() % 40000));
}


int DataGenerator::nahodnaPoistovna()
{
	return qrand() % 10;
}

