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

template <typename DataT, typename KeyT> inline int Comparator<DataT, KeyT>::operator()(DataT a, KeyT b) {
	if (a < b) {
		return -1;
	}
	else if (a == b) {
		return 0;
	}
	else {
		return 1;
	}
}

