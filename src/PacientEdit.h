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
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  PACIENTEDIT_H
#define  PACIENTEDIT_H

#include "ui_PacientEdit.h"

class Pacient;
class QStringListModel;

class PacientEdit: public QWidget, private Ui::PacientEdit
{
Q_OBJECT
public:
	PacientEdit(QWidget *parent = 0);
	~PacientEdit();
	const Pacient &pacient() const;

public slots:
	void aktualizujPacient();

private slots:
	void pridajAlergiu();
	void odoberAlergiu();

private:
	QStringListModel *m_alergieModel;
	Pacient *m_pacient;
};

#endif   /* ----- #ifndef PACIENTEDIT_H  ----- */

