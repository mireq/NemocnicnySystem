/*
 * =====================================================================================
 *
 *       Filename:  HospitalizaciaWizard.cpp
 *
 *        Version:  1.0
 *        Created:  17.11.2009 15:47:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "HospitalizaciaEdit.h"
#include "HospitalizaciaWizard.h"
#include "NemocniceList.h"
#include "PacientEdit.h"

#include "NemocnicnySystem.h"

HospitalizaciaWizard::HospitalizaciaWizard(NemocnicnySystem *system, QWidget *parent)
	: QWizard(parent),
	  m_nemocnicnySystem(system)
{
	m_nemocniceList = new NemocniceList(m_nemocnicnySystem->nemocnice());
	m_pacientEdit = new PacientEdit();
	m_hospitalizaciaEdit = new HospitalizaciaEdit();

	connect(m_pacientEdit, SIGNAL(rcAcceptableChanged()), SLOT(updatePacientEdit()));
	connect(this, SIGNAL(currentChanged(int)), SLOT(updateData()));

	addPage(m_nemocniceList);
	addPage(m_pacientEdit);
	addPage(m_hospitalizaciaEdit);
}


HospitalizaciaWizard::~HospitalizaciaWizard()
{
}


Hospitalizacia HospitalizaciaWizard::hospitalizacia() const
{
	return m_hospitalizaciaEdit->hospitalizacia();
}


void HospitalizaciaWizard::updatePacientEdit()
{
	// Zapísané údaje o pacientovi
	if (m_pacientEdit->rcAcceptable()) {
		RodCis rc = m_pacientEdit->pacient().rodCislo();
		NemocnicnySystem::Pacienti::Iterator it = m_nemocnicnySystem->najdiPacienta(rc);
		if (it.hasNext()) {
			Pacient *pacient = it.next();
			m_pacientEdit->setPacient(pacient);
			m_pacient = pacient;
			return;
		}
	}
	m_pacientEdit->setPacient(NULL);
	m_pacient = NULL;
	m_pacientEdit->setErrorMessage(QString());
}


void HospitalizaciaWizard::updateData()
{
	//m_nemocnica = m_nemocniceList->vybranaNemocnica();
	QString nemocnica = m_nemocniceList->vybranaNemocnica();
	NemocnicnySystem::Nemocnice::Iterator it = m_nemocnicnySystem->najdiNemocnicu(nemocnica);
	if (it.hasNext()) {
		m_nemocnica = it.next();
	}
	else {
		m_nemocnica = NULL;
	}
	
	// Už je hospitalizovaný môžeme maximálne ukončiť hospitalizáziu
	if (m_pacient != NULL && m_pacient->hospitalizovanyV() != NULL) {
		// Kontrola, či je hospitalizovaný v správnej nemocnici
		Nemocnica *nemocnica = m_pacient->hospitalizovanyV();
		if (nemocnica != NULL) {
			if (nemocnica != m_nemocnica) {
				m_pacientEdit->setErrorMessage(QString::fromUtf8("Pacient je už hospitalizovaný v nemocnici '%1'").arg(nemocnica->nazov()));
			}
			else {
				m_hospitalizaciaEdit->setHospitalizacia(m_pacient->poslednaHospitalizacia());
			}
		}
	}
	// Nie je hospitalizovaný
	else {
		m_hospitalizaciaEdit->setHospitalizacia(Hospitalizacia(m_nemocnica, QString(), QDate(), QDate()));
	}
}

