/*
 * =====================================================================================
 *
 *       Filename:  PacientEdit.h
 *
 *        Version:  1.0
 *        Created:  11.11.2009 19:06:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  PACIENTEDIT_H
#define  PACIENTEDIT_H

#include "ui_PacientEdit.h"
#include <QWizardPage>

class Pacient;
class QStringListModel;

class PacientEdit: public QWizardPage, private Ui::PacientEdit
{
Q_OBJECT
public:
	PacientEdit(QWidget *parent = 0);
	~PacientEdit();
	const Pacient &pacient() const;
	bool isComplete() const;

private slots:
	void aktualizujPacient();
	void pridajAlergiu();
	void odoberAlergiu();

private:
	QStringListModel *m_alergieModel;
	Pacient *m_pacient;
	bool m_valid;
};

#endif   /* ----- #ifndef PACIENTEDIT_H  ----- */

