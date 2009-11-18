/*
 * =====================================================================================
 *
 *       Filename:  HospitalizaciaWizard.h
 *
 *        Version:  1.0
 *        Created:  17.11.2009 15:47:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  HOSPITALIZACIAWIZARD_H
#define  HOSPITALIZACIAWIZARD_H

#include <QWizard>
#include <QString>

#include "Hospitalizacia.h"

class HospitalizaciaEdit;
class NemocnicnySystem;
class NemocniceList;
class PacientEdit;
class Pacient;
class Nemocnica;

class HospitalizaciaWizard: public QWizard
{
Q_OBJECT
public:
	HospitalizaciaWizard(NemocnicnySystem *system, QWidget *parent = 0);
	~HospitalizaciaWizard();
	Hospitalizacia hospitalizacia() const;
	Pacient *pacient() const;
	Pacient newPacient() const;
	Nemocnica *nemocnica() const;

private slots:
	void updatePacientEdit();
	void updateData();

private:
	NemocnicnySystem *m_nemocnicnySystem;
	NemocniceList *m_nemocniceList;
	PacientEdit *m_pacientEdit;
	HospitalizaciaEdit *m_hospitalizaciaEdit;

	Nemocnica *m_nemocnica;
	Pacient *m_pacient;
};

#endif   /* ----- #ifndef HOSPITALIZACIAWIZARD_H  ----- */

