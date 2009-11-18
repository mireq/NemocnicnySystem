/*
 * =====================================================================================
 *
 *       Filename:  PacientInfo.h
 *
 *        Version:  1.0
 *        Created:  18.11.2009 11:23:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  PACIENTINFO_H
#define  PACIENTINFO_H

#include "ui_PacientInfo.h"

#include <QWidget>

class Pacient;

class PacientInfo: public QWidget, private Ui::PacientInfo
{
Q_OBJECT
public:
	PacientInfo(QWidget *parent = 0);
	~PacientInfo();
	void setPacient(Pacient *pacient);
	void reset();
};

#endif   /* ----- #ifndef PACIENTINFO_H  ----- */

