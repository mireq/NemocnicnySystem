/*
 * =====================================================================================
 *
 *       Filename:  HospitalizaciaEdit.cpp
 *
 *        Version:  1.0
 *        Created:  17.11.2009 19:23:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "HospitalizaciaEdit.h"
#include "Hospitalizacia.h"
#include "Nemocnica.h"

HospitalizaciaEdit::HospitalizaciaEdit(QWidget *parent)
	: QWizardPage(parent),
	  m_nemocnica(NULL)
{
	setupUi(this);
	odEdit->setDate(QDate::currentDate());
	doEdit->setDate(QDate::currentDate());

	connect(odEdit, SIGNAL(dateChanged(QDate)), SLOT(setMinDo(QDate)));
}


HospitalizaciaEdit::~HospitalizaciaEdit()
{
}


void HospitalizaciaEdit::setHospitalizacia(const Hospitalizacia &hospitalizacia)
{
	m_nemocnica = hospitalizacia.nemocnica();

	if (hospitalizacia.zaciatok().isValid()) {
		odEdit->setDate(hospitalizacia.zaciatok());
		odEdit->setEnabled(false);
	}
	else {
		odEdit->setEnabled(true);
		odEdit->setDate(QDate::currentDate());
	}

	if (hospitalizacia.koniec().isValid()) {
		doEdit->setDate(hospitalizacia.koniec());
		doEdit->setEnabled(false);
		ukoncenieCheckBox->setEnabled(false);
	}
	else {
		ukoncenieCheckBox->setEnabled(true);
		if (ukoncenieCheckBox->isChecked()) {
			doEdit->setEnabled(true);
		}
		doEdit->setDate(QDate::currentDate());
	}

	diagnozaEdit->setPlainText(hospitalizacia.diagnoza());

	if (hospitalizacia.nemocnica() != NULL) {
		nemocnicaDisplay->setText(hospitalizacia.nemocnica()->nazov());
	}
	else {
		nemocnicaDisplay->setText(QString());
	}
}


Hospitalizacia HospitalizaciaEdit::hospitalizacia() const
{
	Nemocnica *nemocnica = m_nemocnica;
	QString diagnoza = diagnozaEdit->toPlainText();
	QDate zaciatok = odEdit->date();
	QDate koniec;
	if (ukoncenieCheckBox->isChecked()) {
		koniec = doEdit->date();
	}
	return Hospitalizacia(nemocnica, diagnoza, zaciatok, koniec);
}


void HospitalizaciaEdit::setMinDo(const QDate &min)
{
	doEdit->setMinimumDate(min);
}

