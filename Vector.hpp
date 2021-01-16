//
// Created by Freely Kathryne on 1/15/21.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "VectorIterator.hpp"

namespace ft {
	template<class T, class Alloc = std::allocator<T> >
	class vector {
		// types:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef VectorIterator<value_type,allocator_type>	iterator;
		typedef VectorConstIterator<value_type,allocator_type>	const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	public:
		//iterators:
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		//capacity:
		size_type size() const { return this->_size; }
		size_type max_size() const { return std::numeric_limits<size_type>::max(); }
		void resize(size_type n, value_type val = value_type());
		size_type  capacity() const;
		bool empty() const;
		void reserve(size_type n);

		//element access:
		reference operator[](size_type n);
		const_reference  operator[](size_type n) const;
		reference at(size_type n);
		const_reference at(size_type n) const;
		reference  front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		//modifiers:
		template<class InputIterator>
				void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const value_type& val);
		void push_back(const value_type& val);
		void pop_back();
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const value_type& val);

		template<class InputIterator>
				void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector& x);
		void clear();

		//constructor
		explicit vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const value_type & val = value_type(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type());
		vector(const vector& x);
		vector& operator=(const vector& x);
		~vector();


	private:
		size_type	_size;
		pointer		_array;

	};
	template <class T, class Alloc>
		bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template<class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif //VECTOR_HPP
