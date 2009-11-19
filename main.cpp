/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Nemocničný informačný systém
 *
 *        Version:  1.0
 *        Created:  24.10.2009 13:43:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include <QApplication>
#include <ctime>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qsrand(std::time(NULL));
	MainWindow win;
	win.show();
	return app.exec();
}

