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

#include "DataGenerator.h"
#include "HospitalizaciaWizard.h"
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
#include <QCloseEvent>
#include <QFileDialog>
#include <QDate>
#include <QTextDocument>
#include <Qt>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupUi(this);
	aktualizujTitulokOkna(m_nemocnicnySystem.zmenene(), m_nemocnicnySystem.nazovSuboru());
	m_nemocnicaVyber = new NemocnicaVyber;
	nemocnicaToolBar->addWidget(m_nemocnicaVyber);

	setupActions();
	connectActions();

	actionDesktop->setChecked(true);
	hladatStack->setEnabled(false);
	hospitalizacieStack->setEnabled(false);

	odEdit->setDate(QDate::currentDate());
	doEdit->setDate(QDate::currentDate());
	mesiacEdit->setDate(QDate::currentDate());
}


MainWindow::~MainWindow()
{
}


void MainWindow::closeEvent(QCloseEvent *event)
{
	if (zatvorSubor()) {
		event->accept();
	}
	else {
		event->ignore();
	}
}


void MainWindow::aktualizujTitulokOkna(bool zmenene, const QString &nazovSuboru)
{
	QString zmeneneStr = "";
	QString nazovSuboruStr = "";
	if (zmenene) {
		zmeneneStr = QString::fromUtf8(" [zmenené]");
	}
	if (!nazovSuboru.isNull()) {
		nazovSuboruStr = QString(" - ") + nazovSuboru;
	}
	QString titulok = QString::fromUtf8("Nemocničný informačný systém%1%2").arg(zmeneneStr).arg(nazovSuboruStr);
	setWindowTitle(titulok);
}


void MainWindow::aktualizujNemocnice()
{
	m_nemocnicaVyber->aktualizujNemocnice(m_nemocnicnySystem.nemocnice());
}


void MainWindow::otvor()
{
	if (!zatvorSubor()) {
		return;
	}

	QFileDialog dlg(this, QString::fromUtf8("Vyberte súboru"));
	dlg.setFileMode(QFileDialog::ExistingFile);
	dlg.setDirectory(QDir::home());
	if (dlg.exec() == QDialog::Accepted) {
		QStringList files = dlg.selectedFiles();
		if (files.length() > 0) {
			QString fileName = files.takeFirst();
			try {
				m_nemocnicnySystem.otvor(fileName);
			}
			catch (NemocnicnySystem::SuborException &e) {
				if (e.type() == NemocnicnySystem::SuborException::Access) {
					QMessageBox warn(QMessageBox::Warning,
						QString::fromUtf8("Nepodarilo sa otvoriť súbor"),
						QString::fromUtf8("Súbor sa nepodarilo otvoriť pre čítanie."),
						QMessageBox::NoButton,
						this);
					warn.exec();
				}
				else if (e.type() == NemocnicnySystem::SuborException::Format) {
					QMessageBox warn(QMessageBox::Warning,
						QString::fromUtf8("Nepodarilo sa otvoriť súbor"),
						QString::fromUtf8("Súbor má nesprávny formát."),
						QMessageBox::NoButton,
						this);
					warn.exec();
				}
			}
		}
	}
}


void MainWindow::uloz()
{
	ulozAko(m_nemocnicnySystem.nazovSuboru());
}


void MainWindow::ulozAko(const QString &fileName)
{
	QString subor = fileName;
	if (subor.isNull()) {
		QFileDialog dlg(this, QString::fromUtf8("Uloženie súboru"));
		dlg.setConfirmOverwrite(true);
		dlg.setFileMode(QFileDialog::AnyFile);
		dlg.setDirectory(QDir::home());
		if (dlg.exec() == QDialog::Accepted) {
			QStringList files = dlg.selectedFiles();
			if (files.length() > 0) {
				subor = files.takeFirst();
			}
		}
		else {
			return;
		}
	}

	try {
		m_nemocnicnySystem.uloz(subor);
	}
	catch (NemocnicnySystem::SuborException &e) {
		QMessageBox warn(QMessageBox::Warning,
			QString::fromUtf8("Nepodarilo sa uložiť súbor"),
			QString::fromUtf8("Súbor sa nepodarilo otvoriť pre zápis."),
			QMessageBox::NoButton,
			this);
		warn.exec();
	}
}


void MainWindow::generuj()
{
	if (!zatvorSubor()) {
		return;
	}

	actionDesktop->setChecked(true);
	prepniAktualnyPohlad();

	setUpdatesEnabled(false);
	/*try {
	}
	catch (...) {
	}*/
	const QVector<Pacient *> pacienti = DataGenerator::generujPacientov(1000);
	foreach (Pacient *pacient, pacienti) {
		m_nemocnicnySystem.pridajPacienta(pacient);
	}
	const QVector<Nemocnica *> nemocnice = DataGenerator::generujNahodneNemocnice(10);
	foreach (Nemocnica *nemocnica, nemocnice) {
		m_nemocnicnySystem.pridajNemocnicu(nemocnica);
	}
	const QVector<QPair<Pacient *, Hospitalizacia> > hospitalizacie = DataGenerator::generujHospitalizacie(nemocnice, pacienti);
	for (QVector<QPair<Pacient *, Hospitalizacia> >::const_iterator it = hospitalizacie.begin(); it != hospitalizacie.end(); ++it) {
		m_nemocnicnySystem.hospitalizuj(it->second.nemocnica(), it->first, it->second);
	}
	setUpdatesEnabled(true);
	aktualizujNemocnice();
}

void MainWindow::about()
{
	QMessageBox::about(this, QString::fromUtf8("O aplikácii"), QString::fromUtf8("<b>Autor:</b><br />Miroslav Bendík"));
}


void MainWindow::aboutQt()
{
	QMessageBox::aboutQt(this, QString::fromUtf8("O Qt"));
}


void MainWindow::rezimHladaniePacienta()
{
	actionHladat->setChecked(true);
	prepniAktualnyPohlad();
}


void MainWindow::rezimHospitalizovaniPacienti()
{
	actionHospitalizacie->setChecked(true);
	prepniAktualnyPohlad();
}


void MainWindow::rezimPodklady()
{
	actionPodklady->setChecked(true);
	prepniAktualnyPohlad();
}


void MainWindow::vykonanieHospitalizacie()
{
	HospitalizaciaWizard hospitalizaciaWizard(&m_nemocnicnySystem, this);
	hospitalizaciaWizard.setWindowTitle(QString::fromUtf8("Pridanie hospitalizácie"));
	if (hospitalizaciaWizard.exec() == QDialog::Accepted) {
		Nemocnica *nemocnica = hospitalizaciaWizard.nemocnica();
		Pacient *pacient = hospitalizaciaWizard.pacient();
		if (pacient == NULL) {
			pacient = new Pacient(hospitalizaciaWizard.newPacient());
			m_nemocnicnySystem.pridajPacienta(pacient);
		}
		m_nemocnicnySystem.hospitalizuj(nemocnica, pacient, hospitalizaciaWizard.hospitalizacia());
	}
}


void MainWindow::vytvoreniePacienta()
{
	QWizard vytvoreniePacientaWizard(this);
	vytvoreniePacientaWizard.setPixmap(QWizard::LogoPixmap, QPixmap(":/icons/user-properties.png"));
	vytvoreniePacientaWizard.setWindowIcon(QIcon(":/icons/user-properties.png"));
	vytvoreniePacientaWizard.setWindowTitle(QString::fromUtf8("Vytvorenie nového pacienta"));
	vytvoreniePacientaWizard.setOption(QWizard::NoBackButtonOnLastPage);
	vytvoreniePacientaWizard.setButtonText(QWizard::FinishButton, QString::fromUtf8("Vytvoriť"));
	PacientEdit *edt = new PacientEdit;
	edt->setFinalPage(true);
	edt->setSubTitle(QString::fromUtf8("Vyplňte prosím údaje o novom pacientovi."));
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
}


void MainWindow::zmenAktualnuNemocnicu(const QString &nazov)
{
	if (nazov.isNull()) {
		hladatStack->setEnabled(false);
		hospitalizacieStack->setEnabled(false);
	}
	else {
		hladatStack->setEnabled(true);
		hospitalizacieStack->setEnabled(true);
	}

	if (pohladStack->currentIndex() == Hospitalizacie) {
		zobrazHospitalizacie();
	}
	else if (pohladStack->currentIndex() == Podklady) {
		zobrazPodklady();
	}
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
		resetHladatPohlad();
	}
	else if (checked == actionHospitalizacie) {
		pohladStack->setCurrentIndex(Hospitalizacie);
		zobrazHospitalizacie();
	}
	else if (checked == actionPodklady) {
		pohladStack->setCurrentIndex(Podklady);
		zobrazPodklady();
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

	QString nemocnicaNazov = m_nemocnicaVyber->aktualnaNemocnica();
	if (nemocnicaNazov.isNull()) {
		return;
	}

	Nemocnica *nemocnica = m_nemocnicnySystem.najdiNemocnicu(nemocnicaNazov).next();
	PacientiZoznam zoz;
	// Hľadanie podľa rodného čísla
	if (hladanieEdit->rodCisZapisane()) {
		Nemocnica::PacientiRC::Iterator it = nemocnica->hladajPacienta(hladanieEdit->toRodCis());
		while (it.hasNext()) {
			zoz.append(it.next());
		}
		PacientiInfoModel *model = new PacientiInfoModel(zoz);
		pacientiHladanieList->setModel(model);
	}
	// Hľadanie podľa mena
	else {
		Nemocnica::PacientiMeno::Iterator it = nemocnica->hladajPacienta(hladanieEdit->toMeno());
		while (it.hasNext()) {
			zoz.append(it.next());
		}
		PacientiInfoModel *model = new PacientiInfoModel(zoz);
		pacientiHladanieList->setModel(model);
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
	// Zmena stavu modelu
	connect(&m_nemocnicnySystem, SIGNAL(zmenaStavuSuboru(bool,QString)), SLOT(aktualizujTitulokOkna(bool,QString)));
	connect(&m_nemocnicnySystem, SIGNAL(zmenaNemocnic()), SLOT(aktualizujNemocnice()));

	// Menu
	connect(actionOpen,      SIGNAL(triggered()), SLOT(otvor()));
	connect(actionSave,      SIGNAL(triggered()), SLOT(uloz()));
	connect(actionSaveAs,    SIGNAL(triggered()), SLOT(ulozAko()));
	connect(actionGenerovat, SIGNAL(triggered()), SLOT(generuj()));
	connect(actionAbout,     SIGNAL(triggered()), SLOT(about()));
	connect(actionAboutQt,   SIGNAL(triggered()), SLOT(aboutQt()));

	// Zmena pohľadu
	connect(actionDesktop,        SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));
	connect(actionHladat,         SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));
	connect(actionHospitalizacie, SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));
	connect(actionPodklady,       SIGNAL(triggered()), SLOT(prepniAktualnyPohlad()));

	// Akcie na hlavnom paneli (rampa :P)
	connect(hladaniePacientaButton,        SIGNAL(clicked()), SLOT(rezimHladaniePacienta()));;
	connect(vykonajHospitalizaciuButton,   SIGNAL(clicked()), SLOT(vykonanieHospitalizacie()));
	connect(hospitalizovaniPacientiButton, SIGNAL(clicked()), SLOT(rezimHospitalizovaniPacienti()));
	connect(podkladyButton,                SIGNAL(clicked()), SLOT(rezimPodklady()));
	connect(vytvorPacientaButton,          SIGNAL(clicked()), SLOT(vytvoreniePacienta()));
	connect(vytvorenieNemocniceButton,     SIGNAL(clicked()), SLOT(vytvorenieNemocnice()));
	connect(zrusenieNemocniceButton,       SIGNAL(clicked()), SLOT(zrusenieNemocnice()));

	// Panel pre výber nemocníc
	connect(m_nemocnicaVyber, SIGNAL(pridajNemocnicuClicked()),        SLOT(vytvorenieNemocnice()));
	connect(m_nemocnicaVyber, SIGNAL(zrusNemocnicuClicked(QString)),   SLOT(zrusenieNemocnice(QString)));
	connect(m_nemocnicaVyber, SIGNAL(aktualnaNemocnicaZmena(QString)), SLOT(zmenAktualnuNemocnicu(QString)));

	// Hľadanie pacienta
	connect(hladanieEdit,   SIGNAL(textChanged(QString)), SLOT(updateHladanieButton()));
	connect(hladanieEdit,   SIGNAL(returnPressed()),      SLOT(hladajPacienta()));
	connect(hladanieButton, SIGNAL(clicked()),            SLOT(hladajPacienta()));

	// Zobrazenie hospitalizácii
	connect(filterButton,  SIGNAL(clicked()),           SLOT(zobrazHospitalizacie()));
	connect(filterTab,     SIGNAL(currentChanged(int)), SLOT(zobrazHospitalizacie()));
	connect(poistovnaSpin, SIGNAL(valueChanged(int)),   SLOT(zobrazHospitalizacie()));
	connect(odEdit,        SIGNAL(dateChanged(QDate)),  SLOT(zobrazHospitalizacie()));
	connect(doEdit,        SIGNAL(dateChanged(QDate)),  SLOT(zobrazHospitalizacie()));
	connect(odEdit,        SIGNAL(dateChanged(QDate)),  SLOT(nastavDoMin(QDate)));

	connect(mesiacEdit, SIGNAL(dateChanged(QDate)), SLOT(zobrazPodklady()));
}


void MainWindow::resetHladatPohlad()
{
	hladanieEdit->setText(QString());
	PacientiZoznam zoz;
	PacientiInfoModel *model = new PacientiInfoModel(zoz);
	pacientiHladanieList->setModel(model);
}


void MainWindow::resetHospitalizaciePohlad()
{
	zobrazHospitalizacie();
}


void MainWindow::resetPodkladyPohlad()
{
	podkladyDisplay->setText(QString());
}


bool MainWindow::zatvorSubor()
{
	if (m_nemocnicnySystem.zmenene()) {
		QMessageBox msg(QMessageBox::Information,
			QString::fromUtf8("Uložiť zmeny?"),
			QString::fromUtf8("Chcete uložiť zmeny pred zatvorením súboru?"),
			QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Save,
			this
		);
		msg.setInformativeText(QString::fromUtf8("Pri neuložení budú zmeny stratené."));
		msg.setDefaultButton(QMessageBox::Save);

		switch (msg.exec()) {
			case QMessageBox::Save:
				uloz();
				m_nemocnicnySystem.zatvor();
				break;
			case QMessageBox::Cancel:
				return false;
			case QMessageBox::Discard:
				m_nemocnicnySystem.zatvor();
				break;
			default:
				return false;
		}
	}
	return true;
}


void MainWindow::zobrazHospitalizacie()
{
	QString nemocnicaNazov = m_nemocnicaVyber->aktualnaNemocnica();
	if (nemocnicaNazov.isNull()) {
		PacientiZoznam zoz;
		PacientiInfoModel *model = new PacientiInfoModel(zoz);
		pacientiHospitalizacieList->setModel(model);
		return;
	}

	Nemocnica *nemocnica = m_nemocnicnySystem.najdiNemocnicu(nemocnicaNazov).next();
	PacientiZoznam zoz;
	if (!filterButton->isChecked()) {
		Nemocnica::PacientiPoistovna::Iterator it = nemocnica->hospitalizovaniPacienti();
		while (it.hasNext()) {
			zoz.append(it.next());
		}
	}
	else {
		// Filtrujeme podľa poisťovne
		if (filterTab->currentWidget() == filterPoistovna) {
			Nemocnica::PacientiPoistovna::Iterator it = nemocnica->hospitalizovaniPacientiPoistovna(poistovnaSpin->value());
			while (it.hasNext()) {
				zoz.append(it.next());
			}
		}
		// Filtrujeme podľa času hospitalizácie od-do
		else {
			Nemocnica::PacientiRC::Iterator it = nemocnica->pacienti();
			while (it.hasNext()) {
				Pacient *pacient = it.next();
				if (pacient->hospitalizovanyVCase(odEdit->date(), doEdit->date(), nemocnica)) {
					zoz.append(pacient);
				}
			}
		}
	}
	PacientiInfoModel *model = new PacientiInfoModel(zoz);
	pacientiHospitalizacieList->setModel(model);
}


void MainWindow::zobrazPodklady()
{
	podkladyDisplay->setText("");

	QDate zac = mesiacEdit->date().addDays(-mesiacEdit->date().day() + 1);
	QDate kon = zac.addDays(zac.daysInMonth() - 1);

	int poistovneDni[100];
	for (int i = 0; i < 100; ++i) {
		poistovneDni[i] = 0;
	}

	QList<Pacient *> pacienti;
	NemocnicnySystem::Pacienti::Iterator pacientiIterator = m_nemocnicnySystem.pacienti();
	while (pacientiIterator.hasNext()) {
		Pacient *pacient = pacientiIterator.next();
		int dni = pacient->dniHospitalizacieVCase(zac, kon);
		if (dni > 0) {
			poistovneDni[pacient->poistovna()] += dni;
			pacienti.append(pacient);
		}
	}

	QString text = QString::fromUtf8("<h2>Poisťovne</h2><table border=1 cellspacing=0><tr><th>Kód poisťovne</th><th>Dní hospitalizácie</th></tr>");
	for (int i = 0; i < 100; ++i) {
		if (poistovneDni[i] == 0) {
			continue;
		}
		text += QString::fromUtf8("<tr><td>%1</td><td>%2</td></tr>").arg(i).arg(poistovneDni[i]);
	}
	text += QString::fromUtf8("</table><hr />");
	text += QString::fromUtf8("<h2>Hospitalizovaní pacienti</h2><table border=1 cellspacing=0><tr><th>Rodné číslo</th><th>Meno</th></tr>");
	foreach (Pacient *pacient, pacienti) {
		text += QString::fromUtf8("<tr><td>%1</td><td>%2</td></tr>").arg(Qt::escape(pacient->rodCislo().toString())).arg(pacient->meno().toString());
	}
	text += QString::fromUtf8("</table>");
	podkladyDisplay->setText(text);
}


void MainWindow::nastavDoMin(const QDate &date)
{
	doEdit->setMinimumDate(date);
}

