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
	std::pair<bool, DataT *> deleted = removeFromSubTree(m_rootNode, data, changeHeight, Eql);
	// Uvoľnenie pamäte prvku, ak už nebol uvoľnený
	if (deleted.first) {
		delete deleted.second;
	}
	deleted.first = false;
}


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rebalance(AVLNodePtr &root)
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


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rotateL(AVLNodePtr &root)
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


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rotateR(AVLNodePtr &root)
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


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
bool AVLTree<KeyT, DataT, ComparatorT >::rotateRL(AVLNodePtr &root)
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

	successor->left->balance = -std::max<signed char>(successor->balance, 0);
	successor->right->balance = -std::min<signed char>(successor->balance, 0);
	successor->balance = Balanced;

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

	ComparisonType comp_val = m_comp(data, node->data, Eql);
	int direction;
	// Skúsime vložiť vľavo
	if (comp_val == Lt) {
		direction = -1;
	}
	// Vpravo
	else if (comp_val == Gt) {
		direction = 1;
	}
	// Prvky sú rovnaké, pokúsime sa vložiť na voľné miesto
	else {
		if (node->right == NULL) {
			direction = 1;
		}
		else {
			direction = -1;
		}
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


template < typename KeyT,
	typename DataT,
	template < typename T, typename U > class ComparatorT >
std::pair<bool, DataT *> AVLTree<KeyT, DataT, ComparatorT>::removeFromSubTree(
	AVLNode * &node,
	const DataT &data,
	bool &changeHeight,
	ComparisonType sType)
{
	// Nenašiel sa prvok
	if (node == NULL) {
		changeHeight = false;
		return std::pair<bool, DataT *>(true, NULL);
	}

	std::pair<bool, DataT *> found(true, NULL);
	int balanceChange = 0;

	ComparisonType comp = m_comp(data, node->data, sType);

	// Ak hľadáme nasledovníka v in order a ľavý prvok nie je NULL, potom
	// hľadáme ďalej vľavo kým nebude NULL.
	if (comp == Eql && sType == Lt && node->left != NULL) {
		comp = Lt;
	}

	// Odstránenie v ľavom / pravom podstrome
	if (comp == Lt) {
		found = removeFromSubTree(node->left, data, changeHeight, sType);
	}
	else if (comp == Gt) {
		found = removeFromSubTree(node->right, data, changeHeight, sType);
	}

	// Prvok neexistuje
	if (comp != Eql) {
		if (found.second == NULL) {
			return found;
		}
		if (changeHeight) {
			if (comp == Gt) {
				balanceChange = 1;
			}
			else {
				balanceChange = -1;
			}
		}
	}
	// Odstránenie prvku
	else {
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

			std::pair<bool, DataT *> subDeleted = removeFromSubTree(node->right, data, subHeightChanged, Lt);
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
	ComparisonType compVal = m_comp(key, node->data, Eql);

	// Prvok je menší - hľadáme v ľavom podstrome
	if (compVal == Lt) {
		if (node->left != NULL) {
			std::list<DataT> sub = findSubTree(key, node->left);
			foundItems.splice(foundItems.end(), sub);
		}
	}
	// Prvok je väčší - hľadáme v pravom podstrome
	else if (compVal == Gt) {
		if (node->right != NULL) {
			std::list<DataT> sub = findSubTree(key, node->right);
			foundItems.splice(foundItems.end(), sub);
		}
	}
	// Prvok nájdený
	else {
		// Hľadáme ďalej v ľavom podstrome kvôli duplicitám
		if (node->left != NULL) {
			std::list<DataT> sub = findSubTree(key, node->left);
			foundItems.splice(foundItems.end(), sub);
		}
		// Vložíme prvok do zoznamu nájdených prvkov
		foundItems.push_back(node->data);
		// Pokračujeme v pravom podstrome
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
void AVLTree<KeyT, DataT, ComparatorT >::deleteSubTree(AVLNode * &node)
{
	if (node == NULL) {
		return;
	}
	deleteSubTree(node->left);
	deleteSubTree(node->right);
	delete node;
}


/* -------------------- Výpisy (kód na odstrel) -------------------- */


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

