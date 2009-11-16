/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.cpp
 *
 *        Version:  1.0
 *        Created:  14.11.2009 20:36:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "MainWindow.h"
#include "NemocnicaVyber.h"
#include "NemocniceList.h"
#include "PacientEdit.h"

#include <QVBoxLayout>
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QWizard>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);
	m_nemocnicaVyber = new NemocnicaVyber;
	nemocnicaToolBar->addWidget(m_nemocnicaVyber);

	setupActions();
	connectActions();

	actionDesktop->setChecked(true);
}


MainWindow::~MainWindow()
{
}


void MainWindow::vytvoreniePacienta()
{
	QWizard vytvoreniePacientaWizard(this);
	vytvoreniePacientaWizard.setWindowTitle(QString::fromUtf8("Vytvorenie nového pacienta"));
	vytvoreniePacientaWizard.setOption(QWizard::NoBackButtonOnLastPage);
	vytvoreniePacientaWizard.setButtonText(QWizard::FinishButton, QString::fromUtf8("Vytvoriť"));
	PacientEdit *edt = new PacientEdit;
	edt->setFinalPage(true);
	vytvoreniePacientaWizard.addPage(edt);
	if (vytvoreniePacientaWizard.exec() == QDialog::Accepted) {
		try {
			m_nemocnicnySystem.pridajPacienta(edt->pacient());
		}
		catch (NemocnicnySystem::PacientDuplicitaException &e) {
			QMessageBox warn(QMessageBox::Warning,
				QString::fromUtf8("Pacient už existuje"),
				QString::fromUtf8("Pacient s rodným číslom '%1' už bol vložený.").arg(e.pacient().rodCislo().toString()),
				QMessageBox::NoButton,
				this);
			warn.exec();
		}
	}
}


void MainWindow::vytvorenieNemocnice()
{
	QInputDialog nazovDialog(this);
	nazovDialog.setWindowTitle(QString::fromUtf8("Zadajte názov nemocnice"));
	nazovDialog.setLabelText(QString::fromUtf8("Názov novej nemocnice"));

	if (nazovDialog.exec() == QDialog::Rejected) {
		return;
	}
	QString nazov = nazovDialog.textValue().trimmed();
	if (nazov.isEmpty()) {
		QMessageBox warn(QMessageBox::Warning,
			QString::fromUtf8("Nezadaný názov nemocnice"),
			QString::fromUtf8("Nebol zadaný názov nemocnice"),
			QMessageBox::NoButton,
			this);
		warn.exec();
		return;
	}

	try {
		m_nemocnicnySystem.pridajNemocnicu(nazov);
		m_nemocnicaVyber->aktualizujNemocnice(m_nemocnicnySystem.nemocnice());
	}
	catch (NemocnicnySystem::NemocnicaDuplicitaException &e) {
		QMessageBox warn(QMessageBox::Warning,
			QString::fromUtf8("Nemocnica už existuje"),
			QString::fromUtf8("Nemocnica s názvom '%1' už bola vložená do systému.").arg(e.nazov()),
			QMessageBox::NoButton,
			this);
		warn.exec();
	}
}


void MainWindow::zrusenieNemocnice(const QString &nazov)
{
	QString nazovNemocnice = nazov;
	if (nazovNemocnice.isNull()) {
		QWizard zrusenieNemocniceWizard(this);
		zrusenieNemocniceWizard.setWindowTitle(QString::fromUtf8("Zrušenie nemocnice"));
		QList<QWizard::WizardButton> buttons;
		zrusenieNemocniceWizard.setOption(QWizard::NoBackButtonOnLastPage);
		zrusenieNemocniceWizard.setButtonText(QWizard::FinishButton, QString::fromUtf8("Odstrániť"));
		NemocniceList *nemocniceList = new NemocniceList(m_nemocnicnySystem.nemocnice());
		nemocniceList->setFinalPage(true);
		zrusenieNemocniceWizard.addPage(nemocniceList);

		if (zrusenieNemocniceWizard.exec() == QDialog::Accepted) {
			nazovNemocnice = nemocniceList->vybranaNemocnica();
		}
		else {
			return;
		}
	}
	m_nemocnicnySystem.zrusNemocnicu(nazovNemocnice);
	m_nemocnicaVyber->aktualizujNemocnice(m_nemocnicnySystem.nemocnice());
}


void MainWindow::prepniAktualnyPohlad()
{
	switch (pohladStack->currentIndex())
	{
		case Hladat:         resetHladatPohlad();         break;
		case Hospitalizacie: resetHospitalizaciePohlad(); break;
		case Podklady:       resetPodkladyPohlad();       break;
		default: break;
	}

	QAction *checked = m_toolBarActions->checkedAction();
	if (checked == NULL) {
		pohladStack->setCurrentIndex(Desktop);
	}
	else if (checked == actionDesktop) {
		pohladStack->setCurrentIndex(Desktop);
	}
	else if (checked == actionHladat) {
		pohladStack->setCurrentIndex(Hladat);
	}
	else if (checked == actionHospitalizacie) {
		pohladStack->setCurrentIndex(Hospitalizacie);
	}
	else if (checked == actionPodklady) {
		pohladStack->setCurrentIndex(Podklady);
	}
}


void MainWindow::updateHladanieButton()
{
	if (hladanieEdit->hasAcceptableInput()) {
		hladanieButton->setEnabled(true);
	}
	else {
		hladanieButton->setEnabled(false);
	}
}


void MainWindow::hladajPacienta()
{
	if (!hladanieEdit->hasAcceptableInput()) {
		return;
	}
}


void MainWindow::setupActions()
{
	m_toolBarActions = new QActionGroup(this);
	m_toolBarActions->setExclusive(true);
	m_toolBarActions->addAction(actionDesktop);
	m_toolBarActions->addAction(actionHladat);
	m_toolBarActions->addAction(actionHospitalizacie);
	m_toolBarActions->addAction(actionPodklady);
}


void MainWindow::connectActions()
{
	connect(actionDesktop,        SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));
	connect(actionHladat,         SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));
	connect(actionHospitalizacie, SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));
	connect(actionPodklady,       SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));

	connect(vytvorPacientaButton,      SIGNAL(clicked()), SLOT(vytvoreniePacienta()));
	connect(vytvorenieNemocniceButton, SIGNAL(clicked()), SLOT(vytvorenieNemocnice()));
	connect(zrusenieNemocniceButton,   SIGNAL(clicked()), SLOT(zrusenieNemocnice()));

	connect(m_nemocnicaVyber, SIGNAL(pridajNemocnicuClicked()),      SLOT(vytvorenieNemocnice()));
	connect(m_nemocnicaVyber, SIGNAL(zrusNemocnicuClicked(QString)), SLOT(zrusenieNemocnice(QString)));

	/* ----- Hľadanie pacienta ----- */
	connect(hladanieEdit,   SIGNAL(textChanged(QString)), SLOT(updateHladanieButton()));
	connect(hladanieEdit,   SIGNAL(returnPressed()),      SLOT(hladajPacienta()));
	connect(hladanieButton, SIGNAL(clicked()),            SLOT(hladajPacienta()));
}


void MainWindow::resetHladatPohlad()
{
	hladanieEdit->setText(QString());
}


void MainWindow::resetHospitalizaciePohlad()
{
}


void MainWindow::resetPodkladyPohlad()
{
}

