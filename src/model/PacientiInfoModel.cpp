/*
 * =====================================================================================
 *
 *       Filename:  PacientiInfoModel.cpp
 *
 *        Version:  1.0
 *        Created:  18.11.2009 09:55:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "PacientiInfoModel.h"
#include "Pacient.h"


PacientiInfoModel::PacientiInfoModel(const PacientiZoznam &zoznam, QObject *parent)
	: QAbstractTableModel(parent),
	  m_zoznam(zoznam)
{
}


PacientiInfoModel::~PacientiInfoModel()
{
}


int PacientiInfoModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid()) {
		return 0;
	}
	return m_zoznam.count();
}


int PacientiInfoModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid()) {
		return 0;
	}
	return 2;
}


QVariant PacientiInfoModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	int row = index.row();
	if (row < 0 || row >= m_zoznam.count()) {
		return QVariant();
	}

	switch (index.column()) {
		case RodneCislo: return QVariant(QVariant(m_zoznam[row]->rodCislo().toString()));
		case Meno: return QVariant(QVariant(m_zoznam[row]->meno().toString()));
		default: return QVariant();
	}
}


QVariant PacientiInfoModel::headerData(int section, Qt::Orientation orientation,int role) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	if (orientation != Qt::Horizontal) {
		return QVariant();
	}

	switch (section) {
		case RodneCislo: return QVariant(QString::fromUtf8("Rodné číslo"));
		case Meno: return QVariant(QString::fromUtf8("Meno a priezvisko"));
		default: return QVariant();
	}
}


Pacient *PacientiInfoModel::pacient(int row) const
{
	return m_zoznam[row];
}

