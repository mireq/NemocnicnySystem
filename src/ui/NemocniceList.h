/*
 * =====================================================================================
 *
 *       Filename:  NemocniceList.h
 *
 *        Version:  1.0
 *        Created:  15.11.2009 19:43:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  NEMOCNICELIST_H
#define  NEMOCNICELIST_H

#include "NemocnicnySystem.h"

#include <QWizardPage>

class QListWidget;

class NemocniceList: public QWizardPage
{
Q_OBJECT
public:
	NemocniceList(NemocnicnySystem::Nemocnice::Iterator it, QWidget *parent = 0);
	~NemocniceList();
	bool isComplete() const;
	const QString &vybranaNemocnica() const;

private slots:
	void changeComplete();

private:
	QListWidget *m_nemocniceList;
	QString m_vybranaNemocnica;
	bool m_complete;
};

#endif   /* ----- #ifndef NEMOCNICELIST_H  ----- */

