//
// Created by Freely Kathryne on 1/15/21.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "Iterator.hpp"

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

		typedef Iterator<value_type,allocator_type>	iterator;
		typedef ConstIterator<value_type,allocator_type>	const_iterator;
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
		size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(size_type); }
		void resize(size_type n, value_type val = value_type()) {
			for (; this->_size < n; this->_size++) {
				push_back(val);
			}
			for (; this->_size > n; this->size--) {
				pop_back();
			}
		};
		size_type  capacity() const { return this->_capacity; }
		bool empty() const { return this->_size == 0; }
		void reserve(size_type n) {
			pointer tmp = this->_alloc.allocate(this->_capacity + n);
			for (size_type i = 0; i < this->_size; ++i) {
				tmp[i] = this->_array[i];
			}
			this->_array.deallocate(this->_array, this->_capacity);
			this->_array = tmp;
			this->_capacity += n;
		}

		//element access:
		reference operator[](size_type n) { return this->_array[n]; }
		const_reference  operator[](size_type n) const { return this->_array[n]; }
		reference at(size_type n) {
			if (this->_size < n)
				throw std::out_of_range("out of range");
			return this->_array[n];
		}
		const_reference at(size_type n) const {
			if (this->_size < n)
				throw std::out_of_range("out of range");
			return this->_array[n];
		}
		reference  front() { return this->_array[0]; }
		const_reference front() const { return this->_array[0]; }
		reference back() {return this->_array[this->_size - 1];}
		const_reference back() const { return this->_array[this->_size - 1]; }

		//modifiers:
		template<class InputIterator>
				void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const value_type& val);
		void push_back(const value_type& val) {
			if (this->_size + 1 > this->_capacity) {
				this->_array.reserve(20);
			}
			this->_array[this->_size] = val;
			this->_size++;
		}
		void pop_back() {
			this->_alloc.destroy(this->_array[this->_size - 1]);
			this->_size--;
		};
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const value_type& val);
		template<class InputIterator>
				void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector& x);
		void clear() {
			for (size_type i = 0; i != this->_size; ++i) {
				this->_alloc.destroy(this->_array[i]);
			}
			this->_size = 0;
		};

		//constructor
		explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _array(nullptr) {}
		explicit vector(size_type n, const value_type & val = value_type(), const allocator_type& alloc = allocator_type()) {
			this->_array = this->_alloc.allocate(n);
			this->_capacity = n;
			for (size_type i = 0; i < n; ++i) {
				this->_array[i] = val;
				this->_size++;
			}
		}
		template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type()) : _size(0), _capacity(0), _array(nullptr) {
				if (this->_array.empty) {
					this->_array = this->_alloc.allocate(20);
					this->_capacity = 20;
				}
				for(; first != last; first++) {
					this->_array.push_back(*first);
				}
			}
		vector(const vector& x) { *this = x; }
		vector& operator=(const vector& x) {
			if (this != &x) {
				this->_size = x._size;
				this->_array = x._array;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
			}
			return *this;
		}
		~vector() {}


	private:
		size_type		_size;
		size_type		_capacity;
		pointer			_array;
		allocator_type  _alloc;
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
