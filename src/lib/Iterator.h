/*
 * =====================================================================================
 *
 *       Filename:  Iterator.h
 *     ______               __
 *    /  _/ /____ _______ _/ /____  ____
 *   _/ // __/ -_) __/ _ `/ __/ _ \/ __/
 *  /___/\__/\__/_/  \_,_/\__/\___/_/
 *
 *        Version:  1.0
 *        Created:  11.11.2009 11:20:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

#ifndef  ITERATOR_H
#define  ITERATOR_H

#include <list>

template <typename DataT,
	typename KeyT,
	template < typename T, typename U > class ComparatorT >
class AVLTree<DataT, KeyT, ComparatorT>::Iterator
{
public:
	~Iterator();
	DataT next();
	bool hasNext();
	DataT previous();
	bool hasPrevious();
	void toFirst();
	void toLast();
	int currentItem() const;

private:
	enum Position {
		Invalid = 0
	};
	Iterator(AVLTree *tree);
	Iterator(AVLTree *tree, const KeyT &key);
	void moveNext();
	void movePrevious();
	void moveTo(int index);

private:
	ComparatorT<DataT, KeyT> m_comp;
	AVLTree *m_tree;
	AVLNode *m_node;
	int m_count;
	std::list<AVLNode *> m_stack;
	int m_currentItem;
	int m_internalCounter;
	KeyT *m_key;

friend class AVLTree;
};

/* ----- Implementácia ----- */

template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
AVLTree<DataT, KeyT, ComparatorT >::Iterator::Iterator(AVLTree<DataT, KeyT, ComparatorT> *tree)
{
	m_key = NULL;
	m_tree = tree;
	m_count = tree->count();
	m_node = NULL;
	m_currentItem = 0;
	m_internalCounter = 0;

	toFirst();
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
AVLTree<DataT, KeyT, ComparatorT >::Iterator::Iterator(AVLTree<DataT, KeyT, ComparatorT> *tree, const KeyT &key)
{
	m_key = new KeyT(key);
	m_tree = tree;
	m_count = -1;
	m_node = NULL;
	m_currentItem = 0;
	m_internalCounter = 0;

	toFirst();
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
AVLTree<DataT, KeyT, ComparatorT >::Iterator::~Iterator()
{
	if (m_key != NULL) {
		delete m_key;
		m_key = NULL;
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
DataT AVLTree<DataT, KeyT, ComparatorT >::Iterator::next()
{
	m_currentItem++;
	moveTo(m_currentItem);
	return m_node->data;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::Iterator::hasNext()
{
	moveTo(m_currentItem + 1);
	if (m_node != NULL) {
		if (m_key == NULL) {
			return true;
		}
		else if (m_comp(m_node->data, *m_key, ComparatorBase::Eql) == ComparatorBase::Eql) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
DataT AVLTree<DataT, KeyT, ComparatorT >::Iterator::previous()
{
	m_currentItem--;
	moveTo(m_currentItem);
	return m_node->data;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::Iterator::hasPrevious()
{
	moveTo(m_currentItem - 1);
	if (m_node != NULL) {
		if (m_key == NULL) {
			return true;
		}
		else if (m_comp(m_node->data, *m_key, ComparatorBase::Eql) == ComparatorBase::Eql) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<DataT, KeyT, ComparatorT >::Iterator::toFirst()
{
	m_stack.erase(m_stack.begin(), m_stack.end());
	m_node = m_tree->m_rootNode;
	if (m_key == NULL) {
		while (m_node != NULL && m_node->left != NULL) {
			m_stack.push_back(m_node);
			m_node = m_node->left;
		}
	}
	else {
		while (m_node != NULL) {
			ComparatorBase::ComparisonType comp = m_comp(m_node->data, *m_key, ComparatorBase::Eql);
			if ((comp == ComparatorBase::Gt || comp == ComparatorBase::Eql) && m_node->left != NULL) {
				m_stack.push_back(m_node);
				m_node = m_node->left;
			}
			else if (comp == ComparatorBase::Lt && m_node->right != NULL) {
				m_stack.push_back(m_node);
				m_node = m_node->right;
			}
			else {
				break;
			}
		}
		if (m_comp(m_node->data, *m_key, ComparatorBase::Eql) != ComparatorBase::Eql) {
			moveNext();
		}
	}

	if (m_node == NULL) {
		m_internalCounter = Invalid;
	}
	else {
		m_internalCounter = 1;
		m_currentItem = 0;
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<DataT, KeyT, ComparatorT >::Iterator::toLast()
{
	m_stack.erase(m_stack.begin(), m_stack.end());
	m_node = m_tree->m_rootNode;
	if (m_key == NULL) {
		while (m_node != NULL && m_node->right != NULL) {
			m_stack.push_back(m_node);
			m_node = m_node->right;
		}
	}
	else {
		while (m_node != NULL) {
			ComparatorBase::ComparisonType comp = m_comp(m_node->data, *m_key, ComparatorBase::Eql);
			if ((comp == ComparatorBase::Lt || comp == ComparatorBase::Eql) && m_node->right != NULL) {
				m_stack.push_back(m_node);
				m_node = m_node->right;
			}
			else if (comp == ComparatorBase::Gt && m_node->left != NULL) {
				m_stack.push_back(m_node);
				m_node = m_node->left;
			}
			else {
				break;
			}
		}
		if (m_comp(m_node->data, *m_key, ComparatorBase::Eql) != ComparatorBase::Eql) {
			movePrevious();
		}
	}

	if (m_node == NULL) {
		m_internalCounter = Invalid;
	}
	else {
		m_internalCounter = -1;
		m_currentItem = 0;
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
int AVLTree<DataT, KeyT, ComparatorT >::Iterator::currentItem() const
{
	return m_currentItem;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<DataT, KeyT, ComparatorT >::Iterator::moveNext()
{
	/**
	 * @bug Pri použití nelineárneho prístupu treba vždy volať toFirst/toLast.
	 * Problém sa vyskytuje kvôli konfliktu s premennými m_internalCounter a
	 * m_currentItem.
	 */
	if (m_node == NULL) {
		toFirst();
		// Žiaden prvok nie je v strome
		if (m_node == NULL) {
			return;
		}
	}

	if (m_node->right != NULL) {
		m_stack.push_back(m_node);
		m_node = m_node->right;
		while (m_node->left != NULL) {
			m_stack.push_back(m_node);
			m_node = m_node->left;
		}
	}
	else {
		while (!m_stack.empty() && m_node == m_stack.back()->right) {
			m_node = m_stack.back();
			m_stack.pop_back();
		}
		if (m_stack.empty()) {
			m_node = NULL;
		}
		else {
			m_node = m_stack.back();
			m_stack.pop_back();
		}
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<DataT, KeyT, ComparatorT >::Iterator::movePrevious()
{
	if (m_node == NULL) {
		toLast();
		// Žiaden prvok nie je v strome
		if (m_node == NULL) {
			return;
		}
	}
	if (m_node->left != NULL) {
		m_stack.push_back(m_node);
		m_node = m_node->left;
		while (m_node->right != NULL) {
			m_stack.push_back(m_node);
			m_node = m_node->right;
		}
	}
	else {
		while (!m_stack.empty() && m_node == m_stack.back()->left) {
			m_node = m_stack.back();
			m_stack.pop_back();
		}
		if (m_stack.empty()) {
			m_node = NULL;
		}
		else {
			m_node = m_stack.back();
			m_stack.pop_back();
		}
	}
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<DataT, KeyT, ComparatorT >::Iterator::moveTo(int index)
{
	int intCtr = m_internalCounter;
	if (index > intCtr) {
		for (int i = intCtr; i < index; ++i) {
			moveNext();
		}
		m_internalCounter = index;
	}
	else if (index < intCtr) {
		for (int i = index; i < intCtr; ++i) {
			movePrevious();
		}
		m_internalCounter = index;
	}
}

#endif   /* ----- #ifndef ITERATOR_H  ----- */

