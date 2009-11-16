/*
 * =====================================================================================
 *
 *       Filename:  NemocnicaVyber.cpp
 *
 *        Version:  1.0
 *        Created:  15.11.2009 15:05:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "NemocnicaVyber.h"

NemocnicaVyber::NemocnicaVyber(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	updateRemoveButton();

	connect(nemocniceCombo, SIGNAL(currentIndexChanged(int)), SLOT(updateRemoveButton()));
	connect(pridajButton, SIGNAL(clicked()), SLOT(pridajNemocnicu()));
	connect(zrusButton, SIGNAL(clicked()), SLOT(zrusNemocnicu()));
}


NemocnicaVyber::~NemocnicaVyber()
{
}


void NemocnicaVyber::aktualizujNemocnice(NemocnicnySystem::Nemocnice::Iterator it)
{
	nemocniceCombo->clear();
	QStringList zoznamNemocnic;
	int cisloNemocnice = 0;
	while (it.hasNext()) {
		Nemocnica *nemocnica = it.next();
		if (nemocnica->zrusena()) {
			continue;
		}
		if (cisloNemocnice == 0) {
			zoznamNemocnic.append(QString());
		}
		zoznamNemocnic.append(nemocnica->nazov());
		cisloNemocnice++;
	}
	nemocniceCombo->addItems(zoznamNemocnic);
}


void NemocnicaVyber::updateRemoveButton()
{
	bool enabled = false;
	int idx = nemocniceCombo->currentIndex();
	if (idx != -1) {
		if (!nemocniceCombo->itemText(idx).isNull()) {
			enabled = true;
		}
	}
	zrusButton->setEnabled(enabled);
}


void NemocnicaVyber::pridajNemocnicu()
{
	emit pridajNemocnicuClicked();
}


void NemocnicaVyber::zrusNemocnicu()
{
	int idx = nemocniceCombo->currentIndex();
	if (idx != -1) {
		if (!nemocniceCombo->itemText(idx).isNull()) {
			emit zrusNemocnicuClicked(nemocniceCombo->itemText(idx));
		}
	}
}

