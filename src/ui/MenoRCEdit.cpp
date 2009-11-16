/*
 * =====================================================================================
 *
 *       Filename:  MenoRCEdit.cpp
 *
 *        Version:  1.0
 *        Created:  16.11.2009 12:55:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "MenoRCEdit.h"

#include <QStringList>

MenoRCEdit::MenoRCEdit(QWidget *parent)
	: QLineEdit(parent),
	  m_rezim(Auto),
	  m_internRezim(Auto)
{
	m_validator = new MenoRCValidator(this);
	setValidator(m_validator);

	connect(this, SIGNAL(textChanged(QString)), SLOT(aktualizujRezim(QString)));
}


MenoRCEdit::~MenoRCEdit()
{
	delete m_validator;
}


void MenoRCEdit::setRezim(MenoRCEdit::Rezim rezim)
{
	m_rezim = rezim;
	if (m_rezim != Auto) {
		setInternRezim(m_rezim);
	}
}


MenoRCEdit::Rezim MenoRCEdit::rezim() const
{
	return m_rezim;
}


bool MenoRCEdit::rodCisZapisane() const
{
	if (m_internRezim == RodneCislo && hasAcceptableInput()) {
		return true;
	}
	else {
		return false;
	}
}


bool MenoRCEdit::menoZapisane() const
{
	if (m_internRezim == Meno && hasAcceptableInput()) {
		return true;
	}
	else {
		return false;
	}
}


RodCis MenoRCEdit::toRodCis() const
{
	if (m_internRezim == RodneCislo && hasAcceptableInput()) {
		return RodCis(text().toUtf8().data());
	}
	else {
		return RodCis();
	}
}


::Meno MenoRCEdit::toMeno() const
{
	if (m_internRezim == Meno && hasAcceptableInput()) {
		QStringList txt = text().split(" ");
		return ::Meno(txt.first(), txt.last());
	}
	else {
		return ::Meno();
	}
}


void MenoRCEdit::aktualizujRezim(const QString &input)
{
	if (m_rezim == Auto) {
		if (input.length() != 0) {
			QChar firstChar = input[0];
			if (firstChar.isDigit()) {
				setInternRezim(RodneCislo);
			}
			else {
				setInternRezim(Meno);
			}
		}
	}
}


void MenoRCEdit::setInternRezim(Rezim rezim)
{
	if (rezim == Meno && m_internRezim != Meno) {
		setInputMask(QString());
		m_internRezim = Meno;
	}
	else if (rezim == RodneCislo && m_internRezim != RodneCislo) {
		setInputMask("999999/9999");
		m_internRezim = RodneCislo;
		cursorForward(false);
	}
	else if (rezim == Auto) {
		setInputMask(QString());
		m_internRezim = Auto;
	}
}


QValidator::State MenoRCEdit::MenoRCValidator::validate(QString &input, int &pos) const
{
	if (input.length() == 0) {
		return QValidator::Intermediate;
	}

	QChar firstChar = input[0];
	// Rodné číslo
	if (m_edit->m_internRezim == MenoRCEdit::RodneCislo) {
		if (input.length() > 11) {
			return QValidator::Invalid;
		}
		else {
			// Počet číslic
			int num = 0;
			for (int i = 0; i < input.length(); ++i) {
				if (i != 6) {
					if (!input[i].isDigit()) {
						if (input[i] != ' ') {
							return QValidator::Invalid;
						}
					}
					else {
						num++;
					}
				}
				else { // i == 6
					if (input[i] != '/') {
						return QValidator::Invalid;
					}
				}
			}
			if (num == 10) {
				return QValidator::Acceptable;
			}
			else {
				return QValidator::Intermediate;
			}
		}
	}
	// Meno
	else if (m_edit->m_internRezim == MenoRCEdit::Meno) {
		if (m_edit->m_rezim == MenoRCEdit::Auto && firstChar.isDigit()) {
			return QValidator::Intermediate;
		}
		if (!firstChar.isLetter()) {
			if (input == "      /    ") {
				pos = 0;
				return QValidator::Intermediate;
			}
			else {
				return QValidator::Invalid;
			}
		}
		int medzier = 0;
		int dlzkaMena = 0;
		for (int i = 1; i < input.length(); ++i) {
			QChar znak = input[i];
			if (znak.isLetter()) {
				dlzkaMena++;
			}
			else if (znak == ' ') {
				medzier++;
				if (medzier > 1) {
					input = input.left(i);
					return QValidator::Acceptable;
				}
				dlzkaMena = 0;
			}
			else {
				return QValidator::Invalid;
			}
		}
		if (medzier == 0 || dlzkaMena == 0) {
			return QValidator::Intermediate;
		}
		else {
			return QValidator::Acceptable;
		}
	}
	return QValidator::Intermediate;
}


