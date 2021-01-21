//
// Created by Freely Kathryne on 1/16/21.
//

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

template <class T, class Alloc = std::allocator<T> >
class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
	explicit Iterator(pointer it = nullptr) : _it(it) {};
	Iterator(const Iterator & it) { *this = it; }
	Iterator& operator=(const Iterator& it) { this->_it = it._it; return *this; }
	~Iterator() {}

	pointer getIt() const { return this->_it; }
	reference operator*() { return *this->_it; }

	Iterator& operator++() {
		this->_it++;
		return *this;
	}
	Iterator operator++(int) {
		Iterator tmp(getIt());
		this->_it = _it + 1;
		return tmp;
	}
	Iterator& operator--() {
		this->_it--;
		return *this;
	}
	Iterator operator--(int) {
		Iterator tmp(getIt());
		this->_it = _it - 1;
		return tmp;
	}
	Iterator operator+(difference_type val) const { return Iterator(this->_it + val); };
	Iterator operator-(difference_type val) const { return Iterator(this->_it - val); };
	difference_type operator+(Iterator &it) const { return this->_it + it._it; }
	difference_type operator-(Iterator &it) const { return this->_it - it._it; }
	Iterator &operator+=(difference_type val) { this->_it += val; return *this; };
	Iterator &operator-=(difference_type val) { this->_it -= val; return *this; };
	const_reference operator[](const_reference n) { return this->_it[n]; };
	pointer operator->() { return this->_it; }

	bool operator==(const Iterator &other) const { return this->_it == other.getIt(); };
	bool operator!=(const Iterator &other) const { return this->_it != other.getIt(); };
	bool operator<=(const Iterator &other) const { return this->_it <= other.getIt(); };
	bool operator>=(const Iterator &other) const { return this->_it >= other.getIt(); };
	bool operator<(const Iterator &other) const { return this->_it < other.getIt(); };
	bool operator>(const Iterator &other) const { return this->_it > other.getIt(); };
private:
	pointer _it;
};

template <class T, class Alloc = std::allocator<T> >
class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
	explicit ConstIterator(pointer it = nullptr) : _it(it) {};
	ConstIterator(const ConstIterator & it) { *this = it; }
	ConstIterator& operator=(const ConstIterator& it) { this->_it = it._it; return *this; }
	~ConstIterator() {}

	pointer getIt() const { return this->_it; }
	ConstIterator& operator++() {
		this->_it++;
		return *this;
	}
	ConstIterator operator++(int) {
		ConstIterator tmp(getIt());
		this->_it = _it + 1;
		return tmp;
	}
	ConstIterator& operator--() {
		this->_it--;
		return *this;
	}
	ConstIterator operator--(int) {
		ConstIterator tmp(getIt());
		this->_it = _it - 1;
		return tmp;
	}
	bool operator==(const ConstIterator &other) const { return _it == other.getElem(); };
	bool operator!=(const ConstIterator &other) const { return _it != other.getElem(); };
	bool operator<=(const ConstIterator &other) const { return _it <= other.getElem(); };
	bool operator>=(const ConstIterator &other) const { return this->_it >= other.getElem(); };
	bool operator<(const ConstIterator &other) const { return _it < other.getElem(); };
	bool operator>(const ConstIterator &other) const { return _it > other.getElem(); };
private:
	pointer _it;
};


#endif //ITERATOR_HPP
