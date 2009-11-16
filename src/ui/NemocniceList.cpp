/*
 * =====================================================================================
 *
 *       Filename:  NemocniceList.cpp
 *
 *        Version:  1.0
 *        Created:  15.11.2009 19:43:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "NemocniceList.h"

#include <QVBoxLayout>
#include <QStringList>
#include <QListWidget>

NemocniceList::NemocniceList(NemocnicnySystem::Nemocnice::Iterator it, QWidget *parent)
	: QWizardPage(parent),
	  m_complete(false)
{
	setTitle(QString::fromUtf8("Výber nemocnice"));
	setSubTitle(QString::fromUtf8("Vyberte prosím nemocnicu zo zoznamu nemocníc."));

	QStringList nemocnice;
	while (it.hasNext()) {
		Nemocnica *nemocnica = it.next();
		if (!nemocnica->zrusena()) {
			nemocnice.append(nemocnica->nazov());
		}
	}

	QVBoxLayout *layout = new QVBoxLayout;
	setLayout(layout);

	m_nemocniceList = new QListWidget;
	layout->addWidget(m_nemocniceList);
	connect(m_nemocniceList, SIGNAL(itemSelectionChanged()), SLOT(changeComplete()));

	m_nemocniceList->addItems(nemocnice);
}


NemocniceList::~NemocniceList()
{
}


bool NemocniceList::isComplete() const
{
	return m_complete;
}


const QString &NemocniceList::vybranaNemocnica() const
{
	return m_vybranaNemocnica;
}


void NemocniceList::changeComplete()
{
	bool complete = true;

	QList<QListWidgetItem *> selected = m_nemocniceList->selectedItems();
	if (selected.count() == 0) {
		complete = false;
		m_vybranaNemocnica = QString();
	}
	else {
		QListWidgetItem *item = selected.first();
		m_vybranaNemocnica = item->data(Qt::DisplayRole).toString();
	}

	if (complete != m_complete) {
		m_complete = complete;
		emit completeChanged();
	}
}

