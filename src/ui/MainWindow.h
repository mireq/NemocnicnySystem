/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.h
 *
 *        Version:  1.0
 *        Created:  14.11.2009 20:35:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  MAINWINDOW_H
#define  MAINWINDOW_H

#include "ui_MainWindow.h"
#include "NemocnicnySystem.h"

#include <QMainWindow>

class QActionGroup;
class NemocnicaVyber;

class MainWindow: public QMainWindow, private Ui::MainWindow
{
Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void aktualizujTitulokOkna(bool zmenene, const QString &nazovSuboru);
	void aktualizujNemocnice();
	void otvor();
	void uloz();
	void ulozAko(const QString &fileName = QString());
	void generuj();
	void about();
	void aboutQt();
	void rezimHladaniePacienta();
	void rezimHospitalizovaniPacienti();
	void rezimPodklady();
	void vykonanieHospitalizacie();
	void vytvoreniePacienta();
	void vytvorenieNemocnice();
	void zrusenieNemocnice(const QString &nazov = QString());
	void zmenAktualnuNemocnicu(const QString &nazov);
	void prepniAktualnyPohlad();
	void updateHladanieButton();
	void hladajPacienta();
	void zobrazHospitalizacie();
	void zobrazPodklady();
	void nastavDoMin(const QDate &date);

private:
	void setupActions();
	void connectActions();

	void resetHladatPohlad();
	void resetHospitalizaciePohlad();
	void resetPodkladyPohlad();

	bool zatvorSubor();

private:
	enum PohladIndex {
		Desktop        = 0,
		Hladat         = 1,
		Hospitalizacie = 2,
		Podklady       = 3
	};
	NemocnicnySystem m_nemocnicnySystem;
	NemocnicaVyber *m_nemocnicaVyber;
	QActionGroup *m_toolBarActions;
};

#endif   /* ----- #ifndef MAINWINDOW_H  ----- */

