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
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#include "src/AVLTree.h"

#include <QApplication>

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, const char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	srand(time(NULL));
	while (1) {
		AVLTree<int, int, Comparator> t;
		std::cout << "============================================================" << std::endl;
		for (int i = 0; i < 10000; ++i) {
			t.insert(rand() % 20);
		}
		for (int i = 0; i < 10000; ++i) {
			int val = rand() % 20;
			t.remove(val);
		}
		t.print();
		t.graphviz();
		return 0;
	}

	return 0;
}

