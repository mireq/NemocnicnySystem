/*
 * =====================================================================================
 *      ___ _   ____ ______
 *     / _ | | / / //_  __/______ ___
 *    / __ | |/ / /__/ / / __/ -_) -_)
 *   /_/ |_|___/____/_/ /_/  \__/\__/
 *
 *       Filename:  AVLTree.h
 *
 *        Version:  1.0
 *        Created:  24.10.2009 14:04:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Deklarácia AVL stromu.
 */

#define RED     "\e[0;31m"
#define GREEN   "\e[0;32m"
#define YELLOW  "\e[0;33m"
#define BLUE    "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN    "\e[0;36m"
#define WHITE   "\e[0;37m"
#define LIGHT_RED     "\e[1;31m"
#define LIGHT_GREEN   "\e[1;32m"
#define LIGHT_YELLOW  "\e[1;33m"
#define LIGHT_BLUE    "\e[1;34m"
#define LIGHT_MAGENTA "\e[1;35m"
#define LIGHT_CYAN    "\e[1;36m"
#define LIGHT_WHITE   "\e[1;37m"


#ifndef  AVLTREE_H
#define  AVLTREE_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "Comparator.h"


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
class AVLTree
{
public:
	enum {
		LT = -1,
		EQL = 0,
		GT = 1
	} SearchType;

	AVLTree();
	~AVLTree();
	void insert(const DataT &data);
	void remove(const DataT &data);
	std::list<DataT> find(const KeyT &data);
	void print();
	void graphviz();
private:
	// -------------------------------- AVLNode --------------------------------
	struct AVLNode
	{
		KeyT data;
		AVLNode *left;
		AVLNode *right;
		signed char balance;

		AVLNode(const DataT &data)
		{
			this->data = data;
			this->left = NULL;
			this->right = NULL;
			this->balance = 0;
		}
	};

	typedef AVLNode * AVLNodePtr;

private:
	bool rebalance(AVLNodePtr &root);
	bool rotateL(AVLNodePtr &root);
	bool rotateR(AVLNodePtr &root);
	bool rotateRL(AVLNodePtr &root);
	bool rotateLR(AVLNodePtr &root);
	std::pair<bool, DataT *> removeFromSubTree(AVLNode * &node, const DataT &data, bool &changeHeight, int sType);

	void printSubTree(AVLNode *node, int depth);
	void graphvizNodes(std::ostream &os, AVLNode *node, bool resetCounter = false, int parentId = 0, bool left = true);
	void deleteSubTree(AVLNode *node);
	std::list<DataT> findSubTree(const KeyT &data, AVLNode *node);


private:
	AVLNode *m_rootNode;
	ComparatorT<DataT, KeyT> m_comp;
};

// Je potrebná aj implementácia
#include "AVLTree.cpp"

#endif   /* ----- #ifndef AVLTREE_H  ----- */

