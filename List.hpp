//
// Created by Freely Kathryne on 1/11/21.
//

#ifndef LIST_HPP
#define LIST_HPP



#include <iostream>
#include "BidirectionalIterator.hpp"


namespace ft {

	template <class T, class Alloc = std::allocator<T> >
	class list {
	public:

		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef value_type*									pointer;
		typedef size_t										size_type;

		typedef BDIterator<value_type,allocator_type>		iterator;
		typedef ConstBDIterator<value_type,allocator_type>	const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		//iterators:
		iterator begin() { return iterator(this->_endNode->next); }
		const_iterator  begin() const { return const_iterator(this->_endNode->next); }
		iterator end() { return iterator(this->_endNode); }
		const_iterator end() const { return const_iterator(this->_endNode); }
		reverse_iterator rbegin() { return reverse_iterator(this->_endNode->prev); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_endNode->prev); }
		reverse_iterator rend() { return reverse_iterator(this->_endNode); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->_endNode); }

		//capacity:
		bool empty() const { return size() == 0; }
		size_type size() const { return this->_size; }
		size_type  max_size() const { return std::numeric_limits<size_type>::max() / sizeof(List); }

		//element access:
		reference front() { return *this->_endNode->next->value; }
		const_reference front() const { return *this->_endNode->next->value; }
		reference back() { return *this->_endNode->prev->value; }
		const_reference back() const { return *this->_endNode->prev->value; }

		//modifiers:
		template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const value_type & val);
		void push_front(const value_type & val);
		void pop_front();
		void push_back(const value_type & val) {
			//create node
			List* node = this->_allocRebind.allocate(1);
			node->value = this->_alloc.allocate(1);
			this->_alloc.construct(node->value, val);
			this->_size++;
			//link
			node->prev = this->_endNode->prev;
			node->next = this->_endNode;

		}
		void pop_back();
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
		explicit list(const allocator_type & alloc = allocator_type()) : _size(0), _alloc(alloc) {
			this->_endNode = this->_allocRebind.allocate(1);
			this->_endNode->value = this->_alloc.allocate(1);
			this->_endNode->prev = this->_endNode;
			this->_endNode->next = this->_endNode;
		}
		explicit list(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()) : _size(0), _alloc(alloc) {
			createList();
			while (n--)
				push_back(val);
		}
		template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				 typename std::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _size(0), _alloc(alloc) {
			createList();
			for (; first != last; first++)
				push_back(*first);
		}
		list(const list & x) { *this = x; }
		list & operator=(const list & x);
		~list() {}

	private:
		typedef struct		Node {
			value_type* 	value;
			Node* 			prev;
			Node* 			next;
		}					List;

		typedef typename allocator_type::template rebind<List>::other allocator_rebind_type;

		allocator_type			_alloc;
		allocator_rebind_type 	_allocRebind;
		size_type				_size;
		List*					_endNode;

		void createList() {
			this->_endNode = this->_allocRebind.allocate(1);
			this->_endNode->value = this->_alloc.allocate(1);
			this->_endNode->prev = this->_endNode;
			this->_endNode->next = this->_endNode;
		}
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
