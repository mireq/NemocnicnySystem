/*
 * =====================================================================================
 *
 *       Filename:  PacientInfoWidget.h
 *
 *        Version:  1.0
 *        Created:  18.11.2009 09:23:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  PACIENTINFOWIDGET_H
#define  PACIENTINFOWIDGET_H

#include <QWidget>

#include "PacientiInfoModel.h"

class QGroupBox;
class QSplitter;
class QTreeView;
class PacientInfo;

class PacientInfoWidget: public QWidget
{
Q_OBJECT
public:
	PacientInfoWidget(QWidget *parent = 0);
	~PacientInfoWidget();
	void setModel(PacientiInfoModel *model);

private slots:
	void aktualizujPacienta(const QModelIndex &index);

private:
	void zobrazPacienta(int row);

private:
	PacientiInfoModel *m_model;
	QSplitter *m_splitter;
	QTreeView *m_pacientiList;
	QGroupBox *m_pacientInfoGroup;
	PacientInfo *m_pacientInfo;
};

#endif   /* ----- #ifndef PACIENTINFOWIDGET_H  ----- */

