//
// Created by Freely Kathryne on 1/11/21.
//

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "Iterator.hpp"


namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class list {
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
		//methods
		//iterators:
		iterator begin();
		const_iterator  begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		//capacity:
		bool empty() const {
			if (this->size() == 0)
				return true;
			return false;
		}
		size_type size() const { return this->_size; }
		size_type  max_size() const { return std::numeric_limits<size_type>::max(); }

		//element access:
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		//modifiers:
		template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const value_type & val);
		void push_front(const value_type & val);
		void pop_front();
		iterator insert(iterator position, const value_type & val);
		void insert(iterator position, size_type n, const value_type & val);
		template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(list & x);
		void resize(size_type n, value_type val = value_type());
		void clear();

		//operations:
		void splice(iterator position, list & x);
		void splice(iterator position, list & x, iterator i);
		void splice(iterator position, list & x, iterator first, iterator last);
		void remove(const value_type & val);
		template<class Predicate>
			void remove_if(Predicate pred);
		void unique();
		template <class BinaryPredicate>
			void unique(BinaryPredicate binary_pred);
		void merge(list & x);
		template <class Compare>
			void merge(list & x, Compare comp);
		void sort();
		template <class Compare>
			void sort (Compare comp);
		void reverse();

		//(constructor) destructor:
		explicit list(const allocator_type & alloc = allocator_type()); //default
		explicit list(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()); //fill
		template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		list(const list & x);
		list & operator=(const list & x);
		~list();

	private:
		typedef struct node {
			value_type* content;
			node* 	prev;
			node* 	next;
		}	List;
		allocator_type	_alloc;
		size_type		_size;
		List*			_endNode;
	};

	template <class T, class Alloc>
		bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	template <class T, class Alloc>
		void swap(list<T,Alloc>& x, list<T,Alloc>& y);
}

#endif //LIST_HPP
