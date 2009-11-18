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

class QSplitter;
class QTreeView;

class PacientInfoWidget: public QWidget
{
Q_OBJECT
public:
	PacientInfoWidget(QWidget *parent = 0);
	~PacientInfoWidget();
	void setModel(PacientiInfoModel *model);
private:
	PacientiInfoModel *m_model;
	QSplitter *m_splitter;
	QTreeView *m_pacientiList;
};

#endif   /* ----- #ifndef PACIENTINFOWIDGET_H  ----- */

