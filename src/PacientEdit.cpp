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
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "PacientEdit.h"

#include "Pacient.h"

#include <QStringListModel>
#include <QInputDialog>

PacientEdit::PacientEdit(QWidget *parent)
	: QWidget(parent)
{
	m_pacient = new Pacient;
	m_zoznamAlergii = new QStringList;
	m_alergieModel = new QStringListModel;
	setupUi(this);
	zoznamAlergiiList->setModel(m_alergieModel);

	connect(pridajAlergiuButton, SIGNAL(clicked()), SLOT(pridajAlergiu()));
	connect(odoberAlergiuButton, SIGNAL(clicked()), SLOT(odoberAlergiu()));
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


void PacientEdit::aktualizujPacient()
{
	Meno meno(menoEdit->text(), priezviskoEdit->text());
	m_pacient->setMeno(meno);
	m_pacient->setRodCislo(rodneCisloEdit->text());
	m_pacient->setDatumNarodenia(datumNarodeniaEdit->dateTime().date());
	m_pacient->setPoistovna(cisloPoistovneEdit->value());
	m_pacient->setAdresa(adresaEdit->toPlainText());
	m_pacient->setAlergie(*m_zoznamAlergii);
}


void PacientEdit::pridajAlergiu()
{
	QString alergia = QInputDialog::getText(this, QString::fromUtf8("Pridanie alergie"), QString::fromUtf8("Zadajte alergiu"));
	if (!alergia.isNull()) {
		m_zoznamAlergii->append(alergia);
		m_alergieModel->setStringList(*m_zoznamAlergii);
	}
}


void PacientEdit::odoberAlergiu()
{
	QModelIndex idx = zoznamAlergiiList->currentIndex();
	if (idx.isValid()) {
		m_zoznamAlergii->removeAt(idx.row());
		m_alergieModel->setStringList(*m_zoznamAlergii);
	}
}

