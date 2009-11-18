/*
 * =====================================================================================
 *
 *       Filename:  PacientiInfoModel.h
 *
 *        Version:  1.0
 *        Created:  18.11.2009 09:55:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  PACIENTIINFOMODEL_H
#define  PACIENTIINFOMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class Pacient;
typedef QVector<Pacient *> PacientiZoznam;

class PacientiInfoModel: public QAbstractTableModel
{
Q_OBJECT
public:
	enum Sekcie {
		RodneCislo = 0,
		Meno = 1
	};
	PacientiInfoModel(const PacientiZoznam &zoznam, QObject *parent = 0);
	~PacientiInfoModel();
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;
	Pacient *pacient(int row) const;
private:
	PacientiZoznam m_zoznam;
};

#endif   /* ----- #ifndef PACIENTIINFOMODEL_H  ----- */

