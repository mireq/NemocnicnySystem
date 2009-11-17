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
	  m_valid(false),
	  m_rcValid(false),
	  m_enabled(true)
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


void PacientEdit::setPacient(Pacient *pacient)
{
	Q_UNUSED(pacient);
	if (pacient == NULL) {
		setWidgetEnabled(true);
	}
	else {
		setWidgetEnabled(false);
		menoEdit->setMeno(pacient->meno());
		datumNarodeniaEdit->setDate(pacient->datumNarodenia());
		cisloPoistovneEdit->setValue(pacient->poistovna());
		adresaEdit->setPlainText(pacient->adresa());
		m_alergieModel->setStringList(pacient->alergie());
	}
}


bool PacientEdit::rcAcceptable() const
{
	return rodneCisloEdit->hasAcceptableInput();
}


void PacientEdit::setErrorMessage(const QString &message)
{
	m_errorMessage = message;
	errorMessage->setText(m_errorMessage);
	aktualizujPacient();
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
	if (!m_errorMessage.isNull()) {
		newValid = false;
	}

	if (newValid != m_valid) {
		m_valid = newValid;
		emit completeChanged();
	}

	bool newRCValid = rodneCisloEdit->hasAcceptableInput();
	if (newRCValid != m_rcValid) {
		m_rcValid = newRCValid;
		emit rcAcceptableChanged();
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


void PacientEdit::setWidgetEnabled(bool enabled)
{
	if (m_enabled != enabled) {
		m_enabled = enabled;

		if (m_enabled) {
			menoEdit->setEnabled(true);
			datumNarodeniaEdit->setEnabled(true);
			cisloPoistovneEdit->setEnabled(true);
			adresaEdit->setEnabled(true);
			zoznamAlergiiList->setEnabled(true);
			odoberAlergiuButton->setEnabled(true);
			pridajAlergiuButton->setEnabled(true);
		}
		else {
			menoEdit->setEnabled(false);
			datumNarodeniaEdit->setEnabled(false);
			cisloPoistovneEdit->setEnabled(false);
			adresaEdit->setEnabled(false);
			zoznamAlergiiList->setEnabled(false);
			odoberAlergiuButton->setEnabled(false);
			pridajAlergiuButton->setEnabled(false);
		}
	}
}

