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
#include <QGroupBox>
#include <QItemSelectionModel>

#include <QDebug>

#include "PacientInfo.h"

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
	m_pacientiList->setHidden(true);
	m_splitter->addWidget(m_pacientiList);

	m_pacientInfoGroup = new QGroupBox(QString::fromUtf8("Informácie o pacientovi"));
	QVBoxLayout *groupLayout = new QVBoxLayout();
	m_pacientInfoGroup->setLayout(groupLayout);
	m_splitter->addWidget(m_pacientInfoGroup);

	m_pacientInfo = new PacientInfo;
	groupLayout->addWidget(m_pacientInfo);
	m_pacientInfo->setHidden(true);
}


PacientInfoWidget::~PacientInfoWidget()
{
}


void PacientInfoWidget::setModel(PacientiInfoModel *model)
{
	zobrazPacienta(-1);
	m_pacientInfo->reset();
	m_model = model;
	m_pacientiList->setModel(m_model);
	if (m_model->rowCount() == 0) {
		m_pacientiList->setHidden(true);
		zobrazPacienta(-1);
		return;
	}
	if (m_model->rowCount() == 1) {
		m_pacientiList->setHidden(true);
		zobrazPacienta(0);
		return;
	}
	QItemSelectionModel *selectionModel = m_pacientiList->selectionModel();
	if (selectionModel != NULL) {
		connect(selectionModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(aktualizujPacienta(QModelIndex)));
	}
	m_pacientiList->setHidden(false);
}


void PacientInfoWidget::aktualizujPacienta(const QModelIndex &index)
{
	if (index.isValid()) {
		zobrazPacienta(index.row());
	}
	else {
		zobrazPacienta(-1);
	}
}


void PacientInfoWidget::zobrazPacienta(int row)
{
	if (row >= 0) {
		m_pacientInfo->setPacient(m_model->pacient(row));
		m_pacientInfo->setHidden(false);
	}
	else {
		m_pacientInfo->setPacient(NULL);
		m_pacientInfo->setHidden(true);
	}
}


