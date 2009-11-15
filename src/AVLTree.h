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
 * \file Deklarácia a definícia AVL stromu.
 */

#ifndef  AVLTREE_H
#define  AVLTREE_H


#include <cstdlib>
#include <iostream>
#include <list>
#include <algorithm>

#include "Comparator.h"
#include "serialization.h"

template < typename DataT,
	typename KeyT,
	template < typename T, typename U > class ComparatorT >
class AVLTree
{
public:
	// -------------------------------- Iterator --------------------------------
	class Iterator;

	AVLTree(): m_rootNode(NULL), m_count(0) {};
	~AVLTree()                      { deleteSubTree(m_rootNode);           };
	void insert(const DataT &data)  { insertIntoSubTree(m_rootNode, data); };
	Iterator find(const KeyT &key)  { return Iterator(this, key);          };
	Iterator iterator()             { return Iterator(this);               };
	bool remove(const DataT &data);
	bool hasKey(const KeyT &key);
	int count() {return m_count;};
	template <class Archive>
	void serialize(Archive &ar, const unsigned int &)
	{
		ar & boost::serialization::make_nvp("root", m_rootNode);
		ar & boost::serialization::make_nvp("count", m_count);
	}
	// -------------------------------- DuplicateDataException --------------------------------
	class DuplicateDataException
	{
	public:
		DataT data() const                        { return m_data; };
	private:
		DuplicateDataException(const DataT &data) { m_data = data; };
		DataT m_data;
	friend class AVLTree;
	};

private:
	// -------------------------------- AVLNode --------------------------------
	struct AVLNode
	{
		DataT data;
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

		AVLNode()
		{
		}

		template <class Archive>
		void serialize(Archive &ar, const unsigned int &)
		{
			ar & boost::serialization::make_nvp("data", data);
			ar & boost::serialization::make_nvp("left", left);
			ar & boost::serialization::make_nvp("right", right);
		}
	};

	typedef AVLNode * AVLNodePtr;

	enum Balanced {
		BalancedDoubleLeft  = -2,
		BalancedLeft        = -1,
		Balanced            = 0,
		BalancedRight       = 1,
		BalancedDoubleRight = 2
	};

private:
	bool rebalance(AVLNodePtr &root);
	bool rotateL(AVLNodePtr &root);
	bool rotateR(AVLNodePtr &root);
	bool rotateRL(AVLNodePtr &root);
	bool rotateLR(AVLNodePtr &root);
	bool insertIntoSubTree(AVLNode * &node, const DataT &data);
	std::pair<bool, DataT *> removeFromSubTree(AVLNode * &node, const DataT &data, bool &changeHeight, ComparatorBase::ComparisonType sType);
	void deleteSubTree(AVLNode * &node);

private:
	AVLNode *m_rootNode;
	ComparatorT<DataT, KeyT> m_comp;
	int m_count;
};

#include "Iterator.h"

/* ----- Implementácia ----- */


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::remove(const DataT &data)
{
	bool changeHeight = false;
	std::pair<bool, DataT *> deleted = removeFromSubTree(m_rootNode, data, changeHeight, ComparatorBase::ExactEql);
	// Uvoľnenie pamäte prvku, ak už nebol uvoľnený
	if (deleted.first) {
		delete deleted.second;
	}
	deleted.first = false;

	if (deleted.second != NULL) {
		return true;
	}
	else {
		return false;
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::hasKey(const KeyT &key)
{
	AVLNode *node = m_rootNode;
	while (node != NULL) {
		ComparatorBase::ComparisonType comp_val = m_comp(node->data, key, ComparatorBase::ExactEql);
		switch (comp_val) {
			case ComparatorBase::Gt: node = node->left; break;
			case ComparatorBase::Lt: node = node->right; break;
			default: return true;
		}
	}
	return false;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::rebalance(AVLNodePtr &root)
{
	bool changeHeight = false;
	if (root->balance == BalancedDoubleRight) {
		if (root->right->balance == BalancedLeft) {
			changeHeight = rotateLR(root);
		}
		else {
			changeHeight = rotateL(root);
		}
	}
	else if (root->balance == BalancedDoubleLeft) {
		if (root->left->balance == BalancedRight) {
			changeHeight = rotateRL(root);
		}
		else {
			changeHeight = rotateR(root);
		}
	}
	return changeHeight;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::rotateL(AVLNodePtr &root)
{
	AVLNodePtr pivot = root->right;
	bool changeHeight = false;
	// Ak nebol uzol vyvážený vždy nastane zmena výšky
	if (root->right->balance != Balanced) {
		changeHeight = true;
	}

	// Rotácia prvkov
	root->right = pivot->left;
	pivot->left = root;

	// Zmena vyváženia
	pivot->balance--;
	root->balance = -(pivot->balance);

	root = pivot;
	return changeHeight;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::rotateR(AVLNodePtr &root)
{
	AVLNodePtr pivot = root->left;
	bool changeHeight = false;
	if (root->left->balance != Balanced) {
		changeHeight = true;
	}

	pivot->balance++;
	root->balance = -(pivot->balance);

	root->left = pivot->right;
	pivot->right = root;

	root = pivot;
	return changeHeight;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::rotateRL(AVLNodePtr &root)
{
	AVLNodePtr leftChild = root->left;
	AVLNodePtr successor = leftChild->right;

	// Rotácie
	root->left = successor->right;
	successor->right = root;

	leftChild->right = successor->left;
	successor->left = leftChild;

	// Zmena vyváženia
	successor->left->balance = -std::max<signed char>(successor->balance, 0);
	successor->right->balance = -std::min<signed char>(successor->balance, 0);
	successor->balance = Balanced;

	root = successor;

	// Pri dvojitej rotácii vždy dôjde k zmene výšky
	return true;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::rotateLR(AVLNodePtr &root)
{
	AVLNodePtr rightChild = root->right;
	AVLNodePtr successor = rightChild->left;

	root->right = successor->left;
	successor->left = root;

	rightChild->left = successor->right;
	successor->right = rightChild;

	successor->left->balance = -std::max<signed char>(successor->balance, 0);
	successor->right->balance = -std::min<signed char>(successor->balance, 0);
	successor->balance = Balanced;

	root = successor;

	return true;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT>::insertIntoSubTree(AVLNode * &node, const DataT &data)
{
	if (node == NULL) {
		node = new AVLNode(data);
		m_count++;
		return true;
	}

	ComparatorBase::ComparisonType comp_val = m_comp(data, node->data, ComparatorBase::ExactEql);
	int direction;
	// Skúsime vložiť vľavo
	if (comp_val == ComparatorBase::Lt) {
		direction = -1;
	}
	// Vpravo
	else if (comp_val == ComparatorBase::Gt) {
		direction = 1;
	}
	// Prvky sú rovnaké
	else {
		throw new DuplicateDataException(data);
	}

	signed char oldBalance = node->balance;

	// Vloženie do ľavého / pravého podstromu
	bool balanceUp;
	if (direction == -1) {
		balanceUp = insertIntoSubTree(node->left, data);
	}
	else {
		balanceUp = insertIntoSubTree(node->right, data);
	}

	// Zmena vyváženia
	if (balanceUp) {
		node->balance += direction;
	}

	// Vyváženie stromu v prípade, že je nevyvážený
	if (node->balance == BalancedDoubleRight || node->balance == BalancedDoubleLeft) {
		rebalance(node);
		return false;
	}
	else {
		// Ak sa zväčšilo nevyváženie pošleme to vyššie
		if (abs(oldBalance) < abs(node->balance)) {
			return true;
		}
		else {
			return false;
		}
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
std::pair<bool, DataT *> AVLTree<DataT, KeyT, ComparatorT>::removeFromSubTree(
	AVLNode * &node,
	const DataT &data,
	bool &changeHeight,
	ComparatorBase::ComparisonType sType)
{
	// Nenašiel sa prvok
	if (node == NULL) {
		changeHeight = false;
		return std::pair<bool, DataT *>(true, NULL);
	}

	std::pair<bool, DataT *> found(true, NULL);
	int balanceChange = 0;

	ComparatorBase::ComparisonType comp = m_comp(data, node->data, sType);

	// Ak hľadáme nasledovníka v in order a ľavý prvok nie je NULL, potom
	// hľadáme ďalej vľavo kým nebude NULL.
	if (comp == ComparatorBase::Eql && sType == ComparatorBase::Lt && node->left != NULL) {
		comp = ComparatorBase::Lt;
	}

	// Odstránenie v ľavom / pravom podstrome
	if (comp == ComparatorBase::Lt) {
		found = removeFromSubTree(node->left, data, changeHeight, sType);
	}
	else if (comp == ComparatorBase::Gt) {
		found = removeFromSubTree(node->right, data, changeHeight, sType);
	}

	// Prvok neexistuje
	if (comp != ComparatorBase::Eql) {
		if (found.second == NULL) {
			return found;
		}
		if (changeHeight) {
			if (comp == ComparatorBase::Gt) {
				balanceChange = 1;
			}
			else {
				balanceChange = -1;
			}
		}
	}
	// Odstránenie prvku
	else {
		m_count--;
		// Prvok je listom
		if (node->left == NULL && node->right == NULL) {
			found = std::pair<bool, DataT *>(true, new DataT(node->data));
			changeHeight = true;

			delete node;
			node = NULL;

			return found;
		}
		// Prvok má oboch synov - vymazávaný prvok sa nahradí nasledovníkom v
		// in-order poradí.
		else if (node->left != NULL && node->right != NULL) {
			found = std::pair<bool, DataT *>(false, &node->data);
			bool subHeightChanged = false;

			std::pair<bool, DataT *> subDeleted = removeFromSubTree(node->right, data, subHeightChanged, ComparatorBase::Lt);
			DataT *newData = subDeleted.second;
			node->data = *newData;
			delete newData;

			if (subHeightChanged) {
				balanceChange = 1;
			}
		}
		// Prvok má jediného syna - vymazávaný p rvok bude nahradený synom
		else {
			found = std::pair<bool, DataT *>(true, new DataT(node->data));
			AVLNode *delNode = node;
			if (node->left == NULL) {
				node = node->right;
			}
			else {
				node = node->left;
			}

			delete delNode;
			changeHeight = true;
			return found;
		}
	}

	node->balance -= balanceChange;

	// Indikujeme zmenu výšky podstromu
	if (balanceChange != 0) {
		if (node->balance != Balanced) {
			changeHeight = rebalance(node);
		}
		else {
			changeHeight = true;
		}
	}
	else {
		changeHeight = false;
	}

	return found;
}



template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<DataT, KeyT, ComparatorT >::deleteSubTree(AVLNode * &node)
{
	if (node == NULL) {
		return;
	}
	deleteSubTree(node->left);
	deleteSubTree(node->right);
	delete node;
}

#endif   /* ----- #ifndef AVLTREE_H  ----- */

