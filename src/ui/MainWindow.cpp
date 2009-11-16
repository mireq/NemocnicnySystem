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

	connect(vytvorenieNemocniceButton, SIGNAL(clicked()), SLOT(vytvorenieNemocnice()));
	connect(zrusenieNemocniceButton, SIGNAL(clicked()), SLOT(zrusenieNemocnice()));
	connect(m_nemocnicaVyber, SIGNAL(pridajNemocnicuClicked()), SLOT(vytvorenieNemocnice()));
	connect(m_nemocnicaVyber, SIGNAL(zrusNemocnicuClicked(QString)), SLOT(zrusenieNemocnice(QString)));
}


MainWindow::~MainWindow()
{
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
			0,
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
			0,
			this);
		warn.exec();
	}
}


void MainWindow::zrusenieNemocnice(const QString &nazov)
{
	QString nazovNemocnice = nazov;
	if (nazovNemocnice.isNull()) {
		QWizard *zrusenieNemocniceWizard = new QWizard(this);
		zrusenieNemocniceWizard->setWindowTitle(QString::fromUtf8("Zrušenie nemocnice"));
		QList<QWizard::WizardButton> buttons;
		zrusenieNemocniceWizard->setOption(QWizard::NoBackButtonOnLastPage);
		zrusenieNemocniceWizard->setButtonText(QWizard::FinishButton, QString::fromUtf8("Odstrániť"));
		NemocniceList *nemocniceList = new NemocniceList(m_nemocnicnySystem.nemocnice());
		nemocniceList->setFinalPage(true);
		zrusenieNemocniceWizard->addPage(nemocniceList);

		if (zrusenieNemocniceWizard->exec() == QDialog::Accepted) {
			nazovNemocnice = nemocniceList->vybranaNemocnica();
		}
	}
	m_nemocnicnySystem.zrusNemocnicu(nazovNemocnice);
	m_nemocnicaVyber->aktualizujNemocnice(m_nemocnicnySystem.nemocnice());
}

