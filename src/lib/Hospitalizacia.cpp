/*
 * =====================================================================================
 *
 *       Filename:  Hospitalizacia.cpp
 *
 *        Version:  1.0
 *        Created:  17.11.2009 15:20:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "Hospitalizacia.h"
#include "Nemocnica.h"

Hospitalizacia::Hospitalizacia()
	: m_nemocnica(NULL),
	  m_diagnoza(QString()),
	  m_zaciatok(QDate()),
	  m_koniec(QDate())
{
}


Hospitalizacia::Hospitalizacia(Nemocnica *nemocnica, const QString &diagnoza, const QDate &zaciatok, const QDate &koniec)
	: m_nemocnica(nemocnica),
	  m_diagnoza(diagnoza),
	  m_zaciatok(zaciatok),
	  m_koniec(koniec)
{
}


Nemocnica *Hospitalizacia::nemocnica() const
{
	return m_nemocnica;
}


void Hospitalizacia::setNemocnica(Nemocnica *nemocnica)
{
	m_nemocnica = nemocnica;
}


const QString &Hospitalizacia::diagnoza() const
{
	return m_diagnoza;
}


const QDate &Hospitalizacia::zaciatok() const
{
	return m_zaciatok;
}


const QDate &Hospitalizacia::koniec() const
{
	return m_koniec;
}


bool Hospitalizacia::ukoncena() const
{
	return m_koniec.isNull();
}


bool Hospitalizacia::isValid() const
{
	if (m_nemocnica != NULL && m_zaciatok.isValid()) {
		return true;
	}
	else {
		return false;
	}
}


std::ostream &operator << (std::ostream &os, Hospitalizacia &hospitalizacia)
{
	os << "Hospitalizacia" << std::endl;
	if (hospitalizacia.m_nemocnica != NULL) {
		os << "Nemocnica: " << hospitalizacia.m_nemocnica->nazov().toUtf8().constData() << std::endl;
	}
	if (hospitalizacia.m_diagnoza != NULL) {
		os << "Diagnoza: " << hospitalizacia.m_diagnoza.toUtf8().constData() << std::endl;
	}
	if (!hospitalizacia.m_zaciatok.isNull()) {
		os << "Zaciatok: " <<  hospitalizacia.m_zaciatok.toString(Qt::SystemLocaleShortDate).toUtf8().constData() << std::endl;
	}
	if (!hospitalizacia.m_koniec.isNull()) {
		os << "Koniec: " <<  hospitalizacia.m_koniec.toString(Qt::SystemLocaleShortDate).toUtf8().constData() << std::endl;
	}
	return os;
}

