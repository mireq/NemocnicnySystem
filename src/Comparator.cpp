/*
 * =====================================================================================
 *
 *       Filename:  Comparator.cpp
 *
 *        Version:  1.0
 *        Created:  30.10.2009 10:21:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik (), miroslav.bendik@gmail.com
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */

/**
 * \file Implementácia štandardného komparátora.
 */

template <typename DataT, typename KeyT>
inline typename AVLTree<KeyT, DataT, ::Comparator>::ComparisonType
	Comparator<DataT, KeyT>::operator()(
		DataT a,
		KeyT b,
		typename AVLTree<KeyT, DataT, ::Comparator>::ComparisonType type) 
{
	if (a == b) {
		return AVLTree<KeyT, DataT, ::Comparator>::Eql;
	}
	if (a < b && type == AVLTree<KeyT, DataT, ::Comparator>::Lt) {
		return AVLTree<KeyT, DataT, ::Comparator>::Eql;
	}
	if (a > b && type == AVLTree<KeyT, DataT, ::Comparator>::Gt) {
		return AVLTree<KeyT, DataT, ::Comparator>::Eql;
	}
	if (a < b) {
		return AVLTree<KeyT, DataT, ::Comparator>::Lt;
	}
	else {
		return AVLTree<KeyT, DataT, ::Comparator>::Gt;
	}
}

