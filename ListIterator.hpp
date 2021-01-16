//
// Created by Freely Kathryne on 1/15/21.
//

#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP

#include <iterator>
#include "List.hpp"

template <class T, class Alloc = std::allocator<T> >
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	// types:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
public:
	ListIterator();
	ListIterator(const ListIterator &it);
	ListIterator &operator=(const ListIterator &it);
	~ListIterator();

	bool operator==(const ListIterator &it);
	bool operator!=(const ListIterator &it);
	T & operator*() const;
private:
};

template <class T, class Alloc = std::allocator<T> >
class ListConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
	ListConstIterator();
	ListConstIterator(const ListConstIterator &it);
	ListConstIterator &operator=(const ListConstIterator &it);
	~ListConstIterator();

	bool operator==(const ListConstIterator &it);
	bool operator!=(const ListConstIterator &it);
	T & operator*() const;
private:

};

#endif //LISTITERATOR_HPP
