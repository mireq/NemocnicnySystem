/*
 * =====================================================================================
 *
 *       Filename:  GeneratorSettings.cpp
 *
 *        Version:  1.0
 *        Created:  20.11.2009 10:06:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "GeneratorSettings.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDialogButtonBox>


GeneratorSettings::GeneratorSettings(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromUtf8("Nastavenia generátora"));
	QVBoxLayout *layout = new QVBoxLayout;
	setLayout(layout);

	QFormLayout *formLayout = new QFormLayout;
	layout->addLayout(formLayout);

	m_pocetNemocnicEdit = new QSpinBox;
	m_pocetPacientovEdit = new QSpinBox;

	m_pocetNemocnicEdit->setMinimum(1);
	m_pocetNemocnicEdit->setMaximum(50000);
	m_pocetNemocnicEdit->setValue(50);
	m_pocetPacientovEdit->setMinimum(1);
	m_pocetPacientovEdit->setMaximum(1000000);
	m_pocetPacientovEdit->setValue(50000);

	formLayout->addRow(QString::fromUtf8("&Nemocníc"), m_pocetNemocnicEdit);
	formLayout->addRow(QString::fromUtf8("&Pacientov"), m_pocetPacientovEdit);

	m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	layout->addWidget(m_buttons);
	connect(m_buttons, SIGNAL(accepted()), SLOT(accept()));
	connect(m_buttons, SIGNAL(rejected()), SLOT(reject()));
}


GeneratorSettings::~GeneratorSettings()
{
}


int GeneratorSettings::pacientov() const
{
	return m_pocetPacientovEdit->value();
}


int GeneratorSettings::nemocnic() const
{
	return m_pocetNemocnicEdit->value();
}

