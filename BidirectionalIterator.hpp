//
// Created by Freely Kathryne on 1/23/21.
//

#ifndef FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
#define FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP

#include <iterator>
#include "List.hpp"

template <class T, class Alloc = std::allocator<T> >
		class list;

template <class T, class Alloc = std::allocator<T> >
class BDIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	// types:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef value_type*									pointer;
	typedef size_t										size_type;


public:
	explicit BDIterator(pointer it = nullptr) : _it(it) {};
	BDIterator(const BDIterator & it) { *this = it; }
	BDIterator& operator=(const BDIterator& it) {
		this->_it = it._it;
		return *this;
	}
	~BDIterator() {}

	pointer getIt() const { return this->_it; }

	reference operator*() { return *this->_it; }
	pointer operator->() { return this->_it; }

	BDIterator& operator++() {
		this->_it++;
		return *this;
	}
	BDIterator operator++(int) {
		BDIterator tmp(getIt());
		this->_it = _it + 1;
		return tmp;
	}
	BDIterator& operator--() {
		this->_it--;
		return *this;
	}
	BDIterator operator--(int) {
		BDIterator tmp(getIt());
		this->_it = _it - 1;
		return tmp;
	}

	bool operator==(const BDIterator &other) const { return this->_it == other.getIt(); };
	bool operator!=(const BDIterator &other) const { return this->_it != other.getIt(); };


private:
	pointer _it;
};

template <class T, class Alloc = std::allocator<T> >
class ConstBDIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	// types:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef value_type*									pointer;
	typedef size_t										size_type;

public:
	explicit ConstBDIterator(pointer it = nullptr) : _it(it) {};
	ConstBDIterator(const ConstBDIterator & it) { *this = it; }
	ConstBDIterator& operator=(const ConstBDIterator& it) { this->_it = it._it; return *this; }
	~ConstBDIterator() {}

	pointer getIt() const { return this->_it; }

	reference operator*() { return *this->_it; }
	pointer operator->() { return this->_it; }

	ConstBDIterator& operator++() {
		this->_it++;
		return *this;
	}
	ConstBDIterator operator++(int) {
		ConstBDIterator tmp(getIt());
		this->_it = _it + 1;
		return tmp;
	}
	ConstBDIterator& operator--() {
		this->_it--;
		return *this;
	}
	ConstBDIterator operator--(int) {
		ConstBDIterator tmp(getIt());
		this->_it = _it - 1;
		return tmp;
	}

	bool operator==(const ConstBDIterator &other) const { return this->_it == other.getIt(); };
	bool operator!=(const ConstBDIterator &other) const { return this->_it != other.getIt(); };

private:
	pointer _it;
};

#endif //FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
