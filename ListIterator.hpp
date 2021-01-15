//
// Created by Freely Kathryne on 1/15/21.
//

#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include <iterator>
#include "List.hpp"

template <class T, class Alloc = std::allocator<T> >
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
	ListIterator() { this->_it = nullptr; };
	ListIterator(const ListIterator &it) { *this = it; }
	ListIterator &operator=(const ListIterator &it) {};
	~ListIterator() {};

	ListIterator(T *it) { this->_it = it; }
	bool operator==(const ListIterator &it) { return this->_it == it._it; };
	bool operator!=(const ListIterator &it) { return this->_it != it._it; };
	T &operator*() { return *(this->_it); }
private:

};

#endif //LISTITERATOR_HPP
