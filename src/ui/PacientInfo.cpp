/*
 * =====================================================================================
 *
 *       Filename:  PacientInfo.cpp
 *
 *        Version:  1.0
 *        Created:  18.11.2009 11:23:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "PacientInfo.h"
#include "Pacient.h"
#include "Nemocnica.h"

#include <QTextDocument>
#include <Qt>
#include <iostream>

PacientInfo::PacientInfo(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}


PacientInfo::~PacientInfo()
{
}


void PacientInfo::setPacient(Pacient *pacient)
{
	reset();
	if (pacient != NULL) {
		menoDisplay->setText(pacient->meno().toString());
		rodneCisloDisplay->setText(pacient->rodCislo().toString());
		datumNarodeniaDisplay->setText(pacient->datumNarodenia().toString(Qt::SystemLocaleShortDate));
		poistovnaDisplay->setText(QString("%1").arg(pacient->poistovna()));
		adresaDisplay->setText(pacient->adresa());
		foreach (const QString &alergia, pacient->alergie()) {
			alergieDisplay->setText(alergieDisplay->text() + alergia + QString("\n"));
		}
		foreach (const Hospitalizacia &hospitalizacia, pacient->hospitalizacie()) {
			QString zaciatok = "--";
			QString koniec = "--";
			QString nemocnica = "NULL";
			QString diagnoza = hospitalizacia.diagnoza();
			if (hospitalizacia.zaciatok().isValid()) {
				zaciatok = hospitalizacia.zaciatok().toString(Qt::SystemLocaleShortDate);
			}
			if (hospitalizacia.koniec().isValid()) {
				koniec = hospitalizacia.koniec().toString(Qt::SystemLocaleShortDate);
			}
			if (hospitalizacia.nemocnica() != NULL) {
				nemocnica = hospitalizacia.nemocnica()->nazov();
			}
			QString text = QString::fromUtf8("%1 - %2<br /><b>Nemocnica:</b> %3<br /><b>Diagnóza: </b><br />%4<hr />").arg(Qt::escape(zaciatok)).arg(Qt::escape(koniec)).arg(Qt::escape(nemocnica)).arg(Qt::escape(diagnoza));
			hospitalizacieDisplay->setText(hospitalizacieDisplay->text() + text);
		}
	}
}


void PacientInfo::reset()
{
	menoDisplay->setText(QString());
	rodneCisloDisplay->setText(QString());
	datumNarodeniaDisplay->setText(QString());
	poistovnaDisplay->setText(QString());
	adresaDisplay->setText(QString());
	alergieDisplay->setText(QString());
	hospitalizacieDisplay->setText(QString());
}

