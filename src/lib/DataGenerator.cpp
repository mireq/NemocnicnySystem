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

#include "DataGenerator.h"
#include "AVLTree.h"
#include "Nemocnica.h"
#include "Pacient.h"

#include <iostream>

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
		int zaciatok = 300;
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
			if (qrand() % 2 > 0) {
				if (zaciatok < 30 && qrand() % 4 == 0) {
					zoznamHospitalizacii.append(QPair<Pacient *, Hospitalizacia>(pacient, Hospitalizacia(nemocnica, diagnoza, zaciatokDat, QDate())));
				}
				else {
					zoznamHospitalizacii.append(QPair<Pacient *, Hospitalizacia>(pacient, Hospitalizacia(nemocnica, diagnoza, zaciatokDat, koniecDat)));
				}
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
	int dlzka = min + qrand() % (max - min + 1);
	char *text = new char[dlzka + 1];
	text[dlzka] = '\0';
	for (int i = 0; i < dlzka; ++i) {
		if (i == 0) {
			text[i] = 'A' + qrand() % 25;
		}
		else {
			text[i] = 'a' + qrand() % 25;
		}
	}
	QString out = text;
	delete[] text;
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

