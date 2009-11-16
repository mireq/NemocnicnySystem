/*
 * =====================================================================================
 *
 *       Filename:  PacientEdit.cpp
 *
 *        Version:  1.0
 *        Created:  11.11.2009 19:05:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "PacientEdit.h"

#include "Pacient.h"

#include <QStringListModel>
#include <QInputDialog>

PacientEdit::PacientEdit(QWidget *parent)
	: QWizardPage(parent),
	  m_valid(false)
{
	m_pacient = new Pacient;
	m_alergieModel = new QStringListModel;
	setupUi(this);

	menoEdit->setRezim(MenoRCEdit::Meno);
	rodneCisloEdit->setRezim(MenoRCEdit::RodneCislo);

	zoznamAlergiiList->setModel(m_alergieModel);

	connect(pridajAlergiuButton, SIGNAL(clicked()), SLOT(pridajAlergiu()));
	connect(odoberAlergiuButton, SIGNAL(clicked()), SLOT(odoberAlergiu()));

	connect(menoEdit,       SIGNAL(textChanged(QString)), SLOT(aktualizujPacient()));
	connect(rodneCisloEdit, SIGNAL(textChanged(QString)), SLOT(aktualizujPacient()));
}


PacientEdit::~PacientEdit()
{
	delete m_pacient;
	delete m_alergieModel;
}


const Pacient &PacientEdit::pacient() const
{
	return *m_pacient;
}


bool PacientEdit::isComplete() const
{
	return m_valid;
}


void PacientEdit::aktualizujPacient()
{
	m_pacient->setMeno(menoEdit->toMeno());
	m_pacient->setRodCislo(rodneCisloEdit->toRodCis());
	m_pacient->setDatumNarodenia(datumNarodeniaEdit->dateTime().date());
	m_pacient->setPoistovna(cisloPoistovneEdit->value());
	m_pacient->setAdresa(adresaEdit->toPlainText());
	m_pacient->setAlergie(m_alergieModel->stringList());

	bool newValid = m_pacient->isValid();
	if (newValid != m_valid) {
		m_valid = newValid;
		emit completeChanged();
	}
}


void PacientEdit::pridajAlergiu()
{
	QModelIndex alergiaIndex = zoznamAlergiiList->currentIndex();
	int row = 0;
	if (alergiaIndex.isValid()) {
		row = alergiaIndex.row() + 1;
	}
	m_alergieModel->insertRows(row, 1);

	QModelIndex index = m_alergieModel->index(row);
	zoznamAlergiiList->setCurrentIndex(index);
	zoznamAlergiiList->edit(index);
}


void PacientEdit::odoberAlergiu()
{
	QModelIndex idx = zoznamAlergiiList->currentIndex();
	if (idx.isValid()) {
		m_alergieModel->removeRows(idx.row(), 1);
	}
}

