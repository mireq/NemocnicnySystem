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

class NemocnicaVyber;

class MainWindow: public QMainWindow, private Ui::MainWindow
{
Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void vytvorenieNemocnice();
	void zrusenieNemocnice(const QString &nazov = QString());
private:
	NemocnicnySystem m_nemocnicnySystem;
	NemocnicaVyber *m_nemocnicaVyber;
};

#endif   /* ----- #ifndef MAINWINDOW_H  ----- */

