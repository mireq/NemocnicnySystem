/*
 * =====================================================================================
 *
 *       Filename:  GeneratorSettings.h
 *
 *        Version:  1.0
 *        Created:  20.11.2009 10:06:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  GENERATORSETTINGS_H
#define  GENERATORSETTINGS_H

#include <QDialog>

class QSpinBox;
class QDialogButtonBox;

class GeneratorSettings: public QDialog
{
Q_OBJECT
public:
	GeneratorSettings(QWidget *parent = 0);
	~GeneratorSettings();
	int pacientov() const;
	int nemocnic() const;

private:
	QSpinBox *m_pocetNemocnicEdit;
	QSpinBox *m_pocetPacientovEdit;
	QDialogButtonBox *m_buttons;
};

#endif   /* ----- #ifndef GENERATORSETTINGS_H  ----- */

