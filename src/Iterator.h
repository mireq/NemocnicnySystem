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
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
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
	DataT next();
	bool hasNext() const;
	DataT previous();
	bool hasPrevious() const;
	void toFirst();
	void toLast();
	int currentItem() const;

private:
	Iterator(AVLTree *tree);

private:
	AVLTree *m_tree;
	AVLNode *m_next;
	AVLNode *m_previous;
	int m_count;
	std::list<AVLNode *> m_stack;
	int m_currentItem;

friend class AVLTree;
};

/* ----- Implementácia ----- */

template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
AVLTree<DataT, KeyT, ComparatorT >::Iterator::Iterator(AVLTree<DataT, KeyT, ComparatorT> *tree)
{
	m_tree = tree;
	m_count = tree->count();

	toFirst();
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
DataT AVLTree<DataT, KeyT, ComparatorT >::Iterator::next()
{
	AVLNode *ret = m_next;
	if (m_next->right != NULL) {
		m_stack.push_back(m_next);
		m_next = m_next->right;
		while (m_next->left != NULL) {
			m_stack.push_back(m_next);
			m_next = m_next->left;
		}
	}
	else {
		AVLNode *node = ret;
		while (!m_stack.empty()) {
			AVLNode *parent = m_stack.back();
			if (node == parent->right) {
				node = parent;
				m_stack.pop_back();
			}
			else {
				break;
			}
		}
		if (m_stack.empty()) {
			node = NULL;
		}
		else {
			node = m_stack.back();
			m_stack.pop_back();
		}
		m_next = node;
	}
	m_previous = ret;
	m_currentItem++;
	if (m_next == NULL) {
		toLast();
	}
	return ret->data;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::Iterator::hasNext() const
{
	if (m_next != NULL) {
		return true;
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
	AVLNode *ret = m_previous;
	if (m_previous->left != NULL) {
		m_stack.push_back(m_previous);
		m_previous = m_previous->left;
		while (m_previous->right != NULL) {
			m_stack.push_back(m_previous);
			m_previous = m_previous->right;
		}
	}
	else {
		AVLNode *node = ret;
		while (!m_stack.empty()) {
			AVLNode *parent = m_stack.back();
			if (node == parent->left) {
				node = parent;
				m_stack.pop_back();
			}
			else {
				break;
			}
		}
		if (m_stack.empty()) {
			node = NULL;
		}
		else {
			node = m_stack.back();
			m_stack.pop_back();
		}
		m_previous = node;
	}
	m_next = ret;
	m_currentItem--;
	if (m_previous == NULL) {
		toFirst();
	}
	return ret->data;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<DataT, KeyT, ComparatorT >::Iterator::hasPrevious() const
{
	if (m_previous != NULL) {
		return true;
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
	AVLNode *next = m_tree->m_rootNode;
	while (next != NULL && next->left != NULL) {
		m_stack.push_back(next);
		next = next->left;
	}
	m_next = next;
	m_previous = NULL;
	m_currentItem = 0;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<DataT, KeyT, ComparatorT >::Iterator::toLast()
{
	m_stack.erase(m_stack.begin(), m_stack.end());
	AVLNode *previous = m_tree->m_rootNode;
	while (previous != NULL && previous->right != NULL) {
		m_stack.push_back(previous);
		previous = previous->right;
	}
	m_previous = previous;
	m_next = NULL;
	m_currentItem = -1;
}


template < typename DataT,
 typename KeyT,
	template < typename T, typename U > class ComparatorT >
int AVLTree<DataT, KeyT, ComparatorT >::Iterator::currentItem() const
{
	return m_currentItem;
}

#endif   /* ----- #ifndef ITERATOR_H  ----- */

