/*
 * =====================================================================================
 *
 *       Filename:  HospitalizaciaEdit.h
 *
 *        Version:  1.0
 *        Created:  17.11.2009 19:23:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  HOSPITALIZACIAEDIT_H
#define  HOSPITALIZACIAEDIT_H

#include "ui_HospitalizaciaEdit.h"
#include <QWizardPage>

class Hospitalizacia;
class Nemocnica;

class HospitalizaciaEdit: public QWizardPage, private Ui::HospitalizaciaEdit
{
Q_OBJECT
public:
	HospitalizaciaEdit(QWidget *parent = 0);
	~HospitalizaciaEdit();
	void setHospitalizacia(const Hospitalizacia &hospitalizacia);
	Hospitalizacia hospitalizacia() const;

private slots:
	void setMinDo(const QDate &min);

private:
	Nemocnica *m_nemocnica;
};

#endif   /* ----- #ifndef HOSPITALIZACIAEDIT_H  ----- */

