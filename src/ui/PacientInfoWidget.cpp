/*
 * =====================================================================================
 *
 *       Filename:  PacientInfoWidget.cpp
 *
 *        Version:  1.0
 *        Created:  18.11.2009 09:23:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "PacientInfoWidget.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QTreeView>

PacientInfoWidget::PacientInfoWidget(QWidget *parent)
	: QWidget(parent),
	  m_model(NULL)
{
	QVBoxLayout *layout = new QVBoxLayout;
	setLayout(layout);

	m_splitter = new QSplitter(Qt::Vertical);
	layout->addWidget(m_splitter);

	m_pacientiList = new QTreeView;
	m_pacientiList->setRootIsDecorated(false);
	m_splitter->addWidget(m_pacientiList);
}


PacientInfoWidget::~PacientInfoWidget()
{
}


void PacientInfoWidget::setModel(PacientiInfoModel *model)
{
	m_model = model;
	m_pacientiList->setModel(m_model);
}


