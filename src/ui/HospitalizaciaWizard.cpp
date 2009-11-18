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
	  m_nemocnicnySystem(system),
	  m_nemocnica(NULL),
	  m_pacient(NULL)
{
	m_nemocniceList = new NemocniceList(m_nemocnicnySystem->nemocnice());
	m_pacientEdit = new PacientEdit();
	m_hospitalizaciaEdit = new HospitalizaciaEdit();

	connect(m_pacientEdit, SIGNAL(rcAcceptableChanged()), SLOT(updatePacientEdit()));
	connect(this, SIGNAL(currentIdChanged(int)), SLOT(updateData()));

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


Pacient *HospitalizaciaWizard::pacient() const
{
	return m_pacient;
}


Pacient HospitalizaciaWizard::newPacient() const
{
	return m_pacientEdit->pacient();
}


Nemocnica *HospitalizaciaWizard::nemocnica() const
{
	return m_nemocnica;
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

			// Kontrola, či je hospitalizovaný v správnej nemocnici
			Nemocnica *nemocnica = m_pacient->hospitalizovanyV();
			if (nemocnica != NULL) {
				if (nemocnica != m_nemocnica) {
					m_pacientEdit->setErrorMessage(QString::fromUtf8("Pacient je už hospitalizovaný v nemocnici '%1'").arg(nemocnica->nazov()));
				}
				else {
					m_pacientEdit->setErrorMessage(QString());
					m_hospitalizaciaEdit->setHospitalizacia(m_pacient->poslednaHospitalizacia());
				}
			}
			else {
				m_pacientEdit->setErrorMessage(QString());
			}
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
		m_hospitalizaciaEdit->setNemocnica(m_nemocnica->nazov());
	}
	else {
		m_nemocnica = NULL;
		m_hospitalizaciaEdit->setNemocnica(QString());
	}
	
	// Už je hospitalizovaný môžeme maximálne ukončiť hospitalizáziu
	if (m_pacient != NULL && m_pacient->hospitalizovanyV() != NULL) {
		// Kontrola, či je hospitalizovaný v správnej nemocnici
		Nemocnica *nemocnica = m_pacient->hospitalizovanyV();
		if (nemocnica != m_nemocnica) {
			m_pacientEdit->setErrorMessage(QString::fromUtf8("Pacient je už hospitalizovaný v nemocnici '%1'").arg(nemocnica->nazov()));
		}
		else {
			m_pacientEdit->setErrorMessage(QString());
			m_hospitalizaciaEdit->setHospitalizacia(m_pacient->poslednaHospitalizacia());
		}
	}
	// Nie je hospitalizovaný
	else {
		m_pacientEdit->setErrorMessage(QString());
		m_hospitalizaciaEdit->setHospitalizacia(Hospitalizacia(NULL, QString(), QDate(), QDate()));
	}
}

