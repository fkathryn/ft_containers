//
// Created by Freely Kathryne on 1/15/21.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "Iterator.hpp"

namespace ft {

	template<bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if <true, T> { typedef T type; };

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

		typedef Iterator<value_type, allocator_type> iterator;
		typedef ConstIterator<value_type, allocator_type> const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	public:
		//iterators:
		iterator begin() { return iterator(this->_array); }
		const_iterator begin() const { return const_iterator(this->_array); }
		iterator end()  { return iterator(&this->_array[this->_size - 1]); }
		const_iterator end() const { return const_iterator(&this->_array[this->_size - 1]); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reference_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const {return const_reference_iterator(begin()); }


//		void printVector() {
//			for (iterator it = begin(), ite = end(); it != ite; ++it)
//				std::cout << *it << " ";
//			std::cout << std::endl;
//		}


		//capacity:
		size_type size() const { return this->_size; }
		size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(*this->_array); }
		void resize(size_type n, value_type val = value_type()) {
			for (; size() < n; this->_size++) {
				push_back(val);
			}
			for (; size() > n; this->_size--) {
				pop_back();
			}
		}
		size_type capacity() const { return this->_capacity; }
		bool empty() const { return size() == 0; }
		void reserve(size_type n) {
			if (n >= capacity()) {
				pointer tmp = this->_alloc.allocate(n);
				for (size_type i = 0; i < size(); ++i) {
					tmp[i] = this->_array[i];
				}
				this->_alloc.deallocate(this->_array, capacity());
				this->_array = tmp;
				this->_capacity = n;
			}
		}

		//element access:
		reference operator[](size_type n) { return this->_array[n]; }
		const_reference operator[](size_type n) const { return this->_array[n]; }
		reference at(size_type n) {
			if (size() <= n)
				throw std::out_of_range("out of range");
			return this->_array[n];
		}
		const_reference at(size_type n) const {
			if (size() <= n)
				throw std::out_of_range("out of range");
			return this->_array[n];
		}
		reference front() { return this->_array[0]; }
		const_reference front() const { return this->_array[0]; }
		reference back() { return this->_array[size() - 1]; }
		const_reference back() const { return this->_array[size() - 1]; }

		//modifiers:
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last,
			  typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			clear();
			this->_array = createArray(last - first + 1);
			for (; first != last; first++) {
				push_back(*first);
			}
		}
		void assign(size_type n, const value_type &val) {
			clear();
			this->_array = createArray(n);
			for (size_type i = 0; i != n; ++i) {
				push_back(val);
			}
		}
		void push_back(const value_type &val) {
			if (size() + 1 > capacity()) {
				reserve((size() + 1) * 2);
			}
			this->_array[size()] = val;
			this->_size++;
		}
		void pop_back() {
			if (capacity() > size()) {
				pointer tmp = this->_alloc.allocate(size());
				for (size_type i = 0; i != size() - 1; ++i) {
					tmp[i] = this->_array[i];
				}
				this->_alloc.deallocate(this->_array, capacity());
				this->_array = tmp;
				this->_capacity = size() - 1;
				this->_size--;
				return ;
			}
			this->_alloc.destroy(&this->_array[size() - 1]);
			this->_size--;
		}

		iterator insert(iterator position, const value_type &val);

		void insert(iterator position, size_type n, const value_type &val);

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
			  typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);

		iterator erase(iterator position) {
			iterator last = end();
			ptrdiff_t elem = position.getIt() - begin().getIt();
			for (ptrdiff_t i = elem; position != last; position++, ++i) {
				this->_array[i] = this->_array[i + 1];
			}
			this->_size--;
			return iterator(this->_array + elem);
		}
		iterator erase(iterator first, iterator last) {
			for (; last != first; last--)
				erase(last);
			return last;
		}
		void swap(vector &x) {
			pointer tmpArray = x._array;
			allocator_type tmpAlloc = x._alloc;
			size_type tmpSize = x._size;
			size_type tmpCapacity = x._capacity;

			x._array = this->_array;
			x._alloc = this->_alloc;
			x._size = this->_size;
			x._capacity = this->_capacity;

			this->_array = tmpArray;
			this->_alloc = tmpAlloc;
			this->_size = tmpSize;
			this->_capacity = tmpCapacity;
		}
		void clear() {
			if (size()) {
				this->_alloc.deallocate(this->_array, capacity());
				this->_array = nullptr;
				this->_capacity = 0;
				this->_size = 0;
			}
		}

		//constructs:
		explicit vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(nullptr) {}

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0){
			this->_array = createArray(n);
			for (size_type i = 0; i < n; ++i) {
				this->_array[i] = val;
				this->_size++;
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
		 typename enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _size(0),_capacity(0),_alloc(alloc),_array(nullptr) {
			size_type n = last - first + 1;
			this->_array = createArray(n);
			for (; first != last; first++) {
				push_back(*first);
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

		pointer createArray(size_type n) {
			pointer tmp = this->_alloc.allocate(n * 2);
			this->_capacity = n * 2;
			return tmp;
		}
	};

	template <class T, class Alloc>
		bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs.size() == 0 && rhs.size() == 0)
				return true;

			typename ft::vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
			typename ft::vector<T, Alloc>::const_iterator lhs_ite = lhs.end();
			typename ft::vector<T, Alloc>::const_iterator rhs_it = rhs.begin();
			typename ft::vector<T, Alloc>::const_iterator rhs_ite = rhs.end();

			if (lhs.size() != rhs.size())
				return false;
			for (; lhs_it != lhs_ite; ++lhs_it, ++rhs_it) {
				if (*lhs_it != *rhs_it)
					return false;
			}
			return true;
	}

	template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs == rhs); }
	template <class T, class Alloc>
		bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			typename ft::vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
			typename ft::vector<T, Alloc>::const_iterator lhs_ite = lhs.end();
			typename ft::vector<T, Alloc>::const_iterator rhs_it = rhs.begin();
			typename ft::vector<T, Alloc>::const_iterator rhs_ite = rhs.end();

			for (; lhs_it != lhs_ite && rhs_it != rhs_ite; ++lhs_it, ++rhs_it) {
				if (*lhs_it < *rhs_it)
					return true;
			}
			if (lhs_it != lhs_ite && rhs_it == rhs_ite)
				return false;
			if (lhs_it == lhs_ite && rhs_it == rhs_ite)
				return false;
			return true;
		}
	template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs < rhs || lhs == rhs); }
	template <class T, class Alloc>
			bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			typename ft::vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
			typename ft::vector<T, Alloc>::const_iterator lhs_ite = lhs.end();
			typename ft::vector<T, Alloc>::const_iterator rhs_it = rhs.begin();
			typename ft::vector<T, Alloc>::const_iterator rhs_ite = rhs.end();

			for (; lhs_it != lhs_ite && rhs_it != rhs_ite; ++lhs_it, ++rhs_it) {
				if (*lhs_it > *rhs_it)
					return true;
			}
			if (lhs_it != lhs_ite && rhs_it == rhs_ite)
				return true;
			if (lhs_it == lhs_ite && rhs_it == rhs_ite)
				return false;
			return true;
		}
	template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs > rhs || lhs == rhs); }

	template<class T, class Alloc>
		void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }
}

#endif //VECTOR_HPP