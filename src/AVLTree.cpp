/*
 * =====================================================================================
 *
 *       Filename:  AVLTree.cpp
 *
 *        Version:  1.0
 *        Created:  30.10.2009 10:18:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Implementácia AVL stromu.
 */


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
AVLTree<KeyT, DataT, ComparatorT >::AVLTree()
{
	m_rootNode = NULL;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
AVLTree<KeyT, DataT, ComparatorT >::~AVLTree()
{
	deleteSubTree(m_rootNode);
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<KeyT, DataT, ComparatorT >::insert(const DataT &data)
{
	insertIntoSubTree(m_rootNode, data);
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<KeyT, DataT, ComparatorT >::remove(const DataT &data)
{
	bool changeHeight = false;
	std::pair<bool, DataT *> deleted = removeFromSubTree(m_rootNode, data, changeHeight, EQL);
	if (deleted.first) {
		delete deleted.second;
	}
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rebalance(AVLNodePtr &root)
{
	bool changeHeight = false;
	if (root->balance == 2) {
		if (root->right->balance == -1) {
			changeHeight = rotateLR(root);
		}
		else {
			changeHeight = rotateL(root);
		}
	}
	else if (root->balance == -2) {
		if (root->left->balance == 1) {
			changeHeight = rotateRL(root);
		}
		else {
			changeHeight = rotateR(root);
		}
	}
	return changeHeight;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rotateL(AVLNodePtr &root)
{
	AVLNodePtr pivot = root->right;
	bool changeHeight = false;
	if (root->right->balance != 0) {
		changeHeight = true;
	}

	root->right = pivot->left;
	pivot->left = root;

	pivot->balance--;
	root->balance = -(pivot->balance);

	root = pivot;
	return changeHeight;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rotateR(AVLNodePtr &root)
{
	AVLNodePtr pivot = root->left;
	bool changeHeight = false;
	if (root->left->balance != 0) {
		changeHeight = true;
	}

	pivot->balance++;
	root->balance = -(pivot->balance);

	root->left = pivot->right;
	pivot->right = root;

	root = pivot;
	return changeHeight;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rotateRL(AVLNodePtr &root)
{
	AVLNodePtr leftChild = root->left;
	AVLNodePtr successor = leftChild->right;

	root->left = successor->right;
	successor->right = root;

	leftChild->right = successor->left;
	successor->left = leftChild;

	successor->left->balance = -std::max<int>(successor->balance, 0);
	successor->right->balance = -std::min<int>(successor->balance, 0);
	successor->balance = 0;

	root = successor;

	return true;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rotateLR(AVLNodePtr &root)
{
	AVLNodePtr rightChild = root->right;
	AVLNodePtr successor = rightChild->left;

	root->right = successor->left;
	successor->left = root;

	rightChild->left = successor->right;
	successor->right = rightChild;

	successor->left->balance = -std::max<int>(successor->balance, 0);
	successor->right->balance = -std::min<int>(successor->balance, 0);
	successor->balance = 0;

	root = successor;

	return true;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT>::insertIntoSubTree(AVLNode * &node, const DataT &data)
{
	if (node == NULL) {
		node = new AVLNode(data);
		return true;
	}

	int comp_val = m_comp(data, node->data);
	int direction;
	if (comp_val < 0) {
		direction = -1;
	}
	else if (comp_val > 0) {
		direction = 1;
	}
	else {
		if (node->right == NULL) {
			direction = 1;
		}
		else {
			direction = -1;
		}
	}

	signed char oldBalance = node->balance;
	bool balanceUp;
	if (direction == -1) {
		balanceUp = insertIntoSubTree(node->left, data);
	}
	else {
		balanceUp = insertIntoSubTree(node->right, data);
	}
	if (balanceUp) {
		node->balance += direction;
	}

	if (node->balance == 2 || node->balance == -2) {
		rebalance(node);
		return false;
	}
	else {
		if (abs(oldBalance) < abs(node->balance)) {
			return true;
		}
	}
	return false;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
std::pair<bool, DataT *> AVLTree<KeyT, DataT, ComparatorT>::removeFromSubTree(AVLNode * &node, const DataT &data, bool &changeHeight, int sType)
{
	if (node == NULL) {
		changeHeight = 0;
		return std::pair<bool, DataT *>(true, NULL);
	}

	std::pair<bool, DataT *> found(true, NULL);
	int balanceChange = 0;
	int comp = m_comp(data, node->data);

	if (comp < 0 && sType == LT && node->left == NULL) {
		comp = 0;
	}
	if (comp > 0 && sType == GT && node->right == NULL) {
		comp = 0;
	}
	if (comp == 0 && sType == LT && node->left != NULL) {
		comp = -1;
	}
	if (comp == 0 && sType == GT && node->left != NULL) {
		comp = 1;
	}

	if (comp < 0) {
		found = removeFromSubTree(node->left, data, changeHeight, sType);
	}
	else if (comp > 0) {
		found = removeFromSubTree(node->right, data, changeHeight, sType);
	}
	if (comp != 0) {
		if (found.second == NULL) {
			return found;
		}
		if (changeHeight) {
			if (comp > 0) {
				balanceChange = 1;
			}
			else {
				balanceChange = -1;
			}
		}
	}
	else {
		if (node->left == NULL && node->right == NULL) {
			found = std::pair<bool, DataT *>(true, new DataT(node->data));
			delete node;
			node = NULL;
			changeHeight = true;
			return found;
		}
		else if (node->left != NULL && node->right != NULL) {
			found = std::pair<bool, DataT *>(false, &node->data);
			bool subHeightChanged = false;
			std::pair<bool, DataT *> subDeleted = removeFromSubTree(node->right, data, subHeightChanged, LT);
			DataT *newData = subDeleted.second;
			node->data = *newData;
			delete newData;
			if (subHeightChanged) {
				balanceChange = 1;
			}
		}
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

	if (balanceChange != 0) {
		if (node->balance != 0) {
			changeHeight = rebalance(node);
		}
		else {
			changeHeight = 1;
		}
	}
	else {
		changeHeight = 0;
	}

	return found;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
std::list<DataT> AVLTree<KeyT, DataT, ComparatorT >::find(const KeyT &key)
{
	std::list<DataT> foundItems;
	if (m_rootNode != NULL) {
		foundItems = findSubTree(key, m_rootNode);
	}
	return foundItems;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
std::list<DataT> AVLTree<KeyT, DataT, ComparatorT >::findSubTree(const KeyT &key, AVLNode *node)
{
	std::list<DataT> foundItems;
	int compVal = m_comp(key, node->data);

	if (compVal < 0) {
		if (node->left != NULL) {
			std::list<DataT> sub = findSubTree(key, node->left);
			foundItems.splice(foundItems.end(), sub);
		}
	}
	else if (compVal > 0) {
		if (node->right != NULL) {
			std::list<DataT> sub = findSubTree(key, node->right);
			foundItems.splice(foundItems.end(), sub);
		}
	}
	else {
		if (node->left != NULL) {
			std::list<DataT> sub = findSubTree(key, node->left);
			foundItems.splice(foundItems.end(), sub);
		}
		foundItems.push_back(node->data);
		if (node->right != NULL) {
			std::list<DataT> sub = findSubTree(key, node->right);
			foundItems.splice(foundItems.end(), sub);
		}
	}
	return foundItems;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<KeyT, DataT, ComparatorT >::print()
{
	printSubTree(m_rootNode, 0);
	std::list<AVLNode *> nStack;
	std::list<AVLNode *> newStack;
	nStack.push_back(m_rootNode);
	int step = 120;
	for (int i = 1; i < 9; ++i) {
		for (int j = 0; j < step / 2; ++j) {
			std::cout << " ";
		}
		for (typename std::list<AVLNode *>::iterator it = nStack.begin(); it != nStack.end(); ++it) {
			if ((*it) == NULL) {
				std::cout << " ";
				for (int j = 0; j < step; ++j) {
					std::cout << " ";
				}
			}
			else {
				std::cout << std::setw(2) << int((*it)->balance);
				for (int j = 0; j < step; ++j) {
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
		for (int j = 0; j < step / 2; ++j) {
			std::cout << " ";
		}
		for (typename std::list<AVLNode *>::iterator it = nStack.begin(); it != nStack.end(); ++it) {
			if ((*it) == NULL) {
				newStack.push_back(NULL);
				newStack.push_back(NULL);
				std::cout << " ";
				for (int j = 0; j < step; ++j) {
					std::cout << " ";
				}
			}
			else {
				newStack.push_back((*it)->left);
				newStack.push_back((*it)->right);
				std::cout << LIGHT_WHITE << std::setw(2) << (*it)->data << WHITE;
				for (int j = 0; j < step; ++j) {
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
		nStack = newStack;
		newStack.erase(newStack.begin(), newStack.end());
		step = step / 2;
	}
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<KeyT, DataT, ComparatorT >::graphviz()
{
	using namespace std;
	filebuf fb;
	fb.open("diagram.dot", ios::out);
	ostream os(&fb);
	os << "digraph G"<<endl;
	os << "{" << endl;
	os << "node [shape = record];" << endl;
	graphvizNodes(os, m_rootNode, true);
	os << "}" << endl;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<KeyT, DataT, ComparatorT >::graphvizNodes(std::ostream &os, AVLNode *node, bool resetCounter, int parentId, bool left) {
	using namespace std;
	static int counter = 0;
	if (resetCounter) {
		counter = 0;
	}
	if (node == NULL) {
		return;
	}

	counter++;
	int id = counter;
	os << "node" << id << "[label = \"<f0>|<f1>"  << node->data << "|<f2>" << int(node->balance) << "\"];" << endl;
	if (parentId != 0) {
		os << "node" << parentId << ":f" << (left?0:2) << " -> " << "node" << id << ":f1;" << endl;
	}
	this->graphvizNodes(os, node->left, false, id, true);
	this->graphvizNodes(os, node->right, false, id, false);
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<KeyT, DataT, ComparatorT >::printSubTree(AVLNode *node, int depth)
{
	if (node == NULL) {
		return;
	}
	printSubTree(node->left, depth + 1);
	std::cout << node->data << std::endl;
	printSubTree(node->right, depth + 1);
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
void AVLTree<KeyT, DataT, ComparatorT >::deleteSubTree(AVLNode *node)
{
	if (node == NULL) {
		return;
	}
	deleteSubTree(node->left);
	deleteSubTree(node->right);
	delete node;
}

