/*
 * =====================================================================================
 *
 *       Filename:  MenoRCEdit.h
 *
 *        Version:  1.0
 *        Created:  16.11.2009 12:55:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  MENORCEDIT_H
#define  MENORCEDIT_H


#include <QLineEdit>
#include <QValidator>

#include "Meno.h"
#include "RodCis.h"

class MenoRCEdit : public QLineEdit
{
Q_OBJECT
public:
	enum Rezim {
		Auto = 0,
		Meno = 1,
		RodneCislo = 2
	};
	MenoRCEdit(QWidget *parent = 0);
	~MenoRCEdit();

	void setRezim(Rezim rezim);
	Rezim rezim() const;

	bool rodCisZapisane() const;
	bool menoZapisane() const;

	void setMeno(const ::Meno &meno);
	void setRodCis(const ::RodCis &rodCis);

	::RodCis toRodCis() const;
	::Meno toMeno() const;

private slots:
	void aktualizujRezim(const QString &input);

private:
	void setInternRezim(Rezim rezim);

	class MenoRCValidator: public QValidator
	{
	public:
		MenoRCValidator(MenoRCEdit *edit): m_edit(edit) {};
	public:
		State validate(QString &input, int &pos) const;
	private:
		MenoRCEdit *m_edit;
	};
	friend class MenoRCValidator;

private:
	Rezim m_rezim;
	Rezim m_internRezim;
	MenoRCValidator *m_validator;
};

#endif   /* ----- #ifndef MENORCEDIT_H  ----- */

