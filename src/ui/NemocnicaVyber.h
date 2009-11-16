/*
 * =====================================================================================
 *
 *       Filename:  NemocnicaVyber.h
 *
 *        Version:  1.0
 *        Created:  15.11.2009 15:05:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  NEMOCNICAVYBER_H
#define  NEMOCNICAVYBER_H

#include "ui_NemocnicaVyber.h"

#include "NemocnicnySystem.h"

#include <QWidget>

class NemocnicaVyber: public QWidget, private Ui::NemocnicaVyber
{
Q_OBJECT
public:
	NemocnicaVyber(QWidget *parent = 0);
	~NemocnicaVyber();
	void aktualizujNemocnice(NemocnicnySystem::Nemocnice::Iterator it);
signals:
	void pridajNemocnicuClicked();
	void zrusNemocnicuClicked(const QString &nazov);
private slots:
	void updateRemoveButton();
	void pridajNemocnicu();
	void zrusNemocnicu();
};

#endif   /* ----- #ifndef NEMOCNICAVYBER_H  ----- */

