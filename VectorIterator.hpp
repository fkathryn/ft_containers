//
// Created by Freely Kathryne on 1/16/21.
//

#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

#include <iterator>

template <class T, class Alloc = std::allocator<T> >
class VectorIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
	explicit VectorIterator(pointer it = nullptr) : _it(it) {};
	VectorIterator(const VectorIterator & it) { *this = it; }
	VectorIterator& operator=(const VectorIterator& it) { this->_it = it._it; return *this; }
	~VectorIterator() {}

	pointer getIt() const { return this->_it; }

	VectorIterator& operator++() { this->_it++; return *this; }
	VectorIterator operator++(int) {
		VectorIterator tmp(getIt());
		this->_it = _it + 1;
		return tmp;
	}
	VectorIterator& operator--() { this->_it--; return *this; }
	VectorIterator operator--(int) {
		VectorIterator tmp(getIt());
		this->_it = _it - 1;
		return tmp;
	}
private:
	pointer _it;
};

template <class T, class Alloc = std::allocator<T> >
class VectorConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
	explicit VectorConstIterator(pointer it = nullptr) : _it(it) {};
	VectorConstIterator(const VectorConstIterator & it) { *this = it; }
	VectorConstIterator& operator=(const VectorConstIterator& it) { this->_it = it._it; return *this; }
	~VectorConstIterator() {}

	pointer getIt() const { return this->_it; }

	VectorConstIterator& operator++() { this->_it++; return *this; }
	VectorConstIterator operator++(int) {
		VectorConstIterator tmp(getIt());
		this->_it = _it + 1;
		return tmp;
	}
	VectorConstIterator& operator--() { this->_it--; return *this; }
	VectorConstIterator operator--(int) {
		VectorConstIterator tmp(getIt());
		this->_it = _it - 1;
		return tmp;
	}
private:
	pointer _it;
};


#endif //VECTORITERATOR_HPP
