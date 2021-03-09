//
// Created by Freely Kathryne on 1/11/21.
//

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <iterator>

namespace ft {

	template <class T, class Alloc = std::allocator<T> >
	class list {
	public:
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef value_type*									pointer;
		typedef size_t										size_type;

//		typedef std::reverse_iterator<iterator>				reverse_iterator;
//		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		//iterators:
		iterator				begin() { return iterator(this->_endNode->next); }
		const_iterator			begin() const { return const_iterator(this->_endNode->next); }
		iterator				end() { return iterator(this->_endNode); }
		const_iterator			end() const { return const_iterator(this->_endNode); }
		reverse_iterator		rbegin() { return reverse_iterator(this->_endNode->prev); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->_endNode->prev); }
		reverse_iterator		rend() { return reverse_iterator(this->_endNode); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(this->_endNode); }

		//capacity:
		bool					empty() const { return size() == 0; }
		size_type				size() const { return this->_size; }
		size_type				max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_List); }

		//element access:
		reference				front() { return *this->_endNode->next->value; }
		const_reference			front() const { return *this->_endNode->next->value; }
		reference				back() { return *this->_endNode->prev->value; }
		const_reference			back() const { return *this->_endNode->prev->value; }

		//modifiers:
		template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
			   typename std::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
				if (!empty()) {
					clear();
				}
				for (; first != last; first++) {
					push_back(*first);
				}
		}
		void assign(size_type n, const value_type & val) {
			if (!empty()) {
				clear();
			}
			while (n--) {
				push_back(val);
			}
		}
		void push_front(const value_type & val) {
			_List* node = createNode(val);
			linkNew(node, _endNode, _endNode->next);
			_endNode->next->prev = node;
			_endNode->next = node;
		}
		void pop_front() {
			if (size() == 0)
				return;
			_List *node = _endNode->next;
			_endNode->next = node->next;
			node->next->prev = _endNode;
			destroyNode(node);
		}
		void push_back(const value_type & val) {
			_List* node = createNode(val);
			linkNew(node, _endNode->prev, _endNode);
			_endNode->prev->next = node;
			_endNode->prev = node;
		}
		void pop_back() {
			if (size() == 0)
				return;
			_List* node = _endNode->prev;
			_endNode->prev = node->prev;
			node->prev->next = _endNode;
			destroyNode(node);
		}
		iterator insert(iterator position, const value_type & val) {
			_List* node = createNode(val);
			_List* list = position.getIt();
			linkNew(node, list->prev, list);
			list->prev->next = node;
			list->prev = node;
			return iterator(node);
		}
		void insert(iterator position, size_type n, const value_type & val) {
			while (n--) {
				insert(position, val);
			}
		}
		template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename std::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			for (; first != last; first++) {
				insert(position, *first);
			}
		}
		iterator erase(iterator position) {
			_List * node = position.getIt();
			_List * savePtrNode = node->next;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			destroyNode(node);
			return iterator(savePtrNode);
		}
		iterator erase(iterator first, iterator last) {
			for (; first != last; first++) {
				erase(first);
			}
			return last;
		}
		void swap(list & x) {
			_List * endTmp = _endNode;
			_endNode = x._endNode;
			x._endNode = endTmp;

			size_type sizeTmp = _size;
			_size = x._size;
			x._size = sizeTmp;
		}
		void resize(size_type n, value_type val = value_type()) {
			if (n < size()) {
				int i = size() - n;
				while (i--) {
					pop_back();
				}
			}
			else if (n > size()) {
				int i = n - size();
				while (i--) {
					push_back(val);
				}
			}
		}
		void clear() {
			while (size()) {
				pop_back();
			}
		}

		//operations:
		void splice(iterator position, list & x) {
			splice(position, x, x.begin(), x.end());
		}
		void splice(iterator position, list & x, iterator i) {
			_List * node = position.getIt();
			_List * newNode = i.getIt();
			linkNew(newNode, node->prev, node);
			node->prev->next = newNode;
			node->prev = newNode;
			x._size--;
			_size++;
		}
		void splice(iterator position, list & x, iterator first, iterator last) {
			_List * node = position.getIt();
			_List * newFirstNode = first.getIt();
			_List * newLastNode = last.getIt();
			newFirstNode->prev = node->prev;
			newLastNode->next = node;
			node->prev->next = newFirstNode;
			node->prev = newLastNode;
		}
		void remove(const value_type & val) {
			for (iterator it_b = begin(); it_b != end(); it_b++) {
				if (*it_b == val) {
					erase(it_b);
				}
			}
		}
		template<class Predicate>
			void remove_if(Predicate pred) {
			for (iterator it_b = begin(); it_b != end(); it_b++) {
				if (pred(*it_b)) {
					erase(it_b);
				}
			}
		}
		void unique() {
			unique(myPredicate);
		}
		template <class BinaryPredicate>
			void unique(BinaryPredicate binary_pred) {
			iterator it_b = begin();
			iterator nextIt = ++begin();
			while (nextIt != end()) {
				if (binary_pred(*it_b, *nextIt))
					nextIt = erase(nextIt);
				else {
					++it_b;
					++nextIt;
				}
			}
		}
		void merge(list & x) {
			merge(x, myCompare);
		}
		template <class Compare>
			void merge(list & x, Compare comp) {
				iterator it_begin = begin();
				iterator it_end = end();
				iterator x_begin = x.begin();
				iterator x_end = x.end();
				iterator next;

				while (x.size()) {
					if (comp(*x_begin, *it_begin) || it_begin == it_end) {
						next = x_begin;
						next++;
						splice(it_begin, x, x_begin);
						x_begin = next;
					} else {
						it_begin++;
					}
				}
				sort();
			}
		void sort() {
			sort(myCompare);
		}
		template <class Compare>
			void sort (Compare comp) {
				iterator it_begin = begin();
				iterator it_next = begin();
				iterator it_end = end();
				T* tmp;

				while(++it_next != it_end) {
					if (comp(*it_next, *it_begin)) {
						tmp = it_begin.getIt()->value;
						it_begin.getIt()->value = it_next.getIt()->value;
						it_next.getIt()->value = tmp;
						it_begin = begin();
						it_next = begin();
					} else {
						it_begin++;
					}
				}
			}
		void reverse() { myReverse(_endNode->next); }

		//constructor/destructor:
		explicit list(const allocator_type & alloc = allocator_type()) : _size(0), _alloc(alloc) {
			createList();
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
		list(const list & newList) : _size(newList._size), _alloc(newList._alloc) {
			createList();
			*this = newList;
		}
		list & operator=(const list & newList) {
			if (!empty()) {
				clear();
			}
			for (const_iterator it = newList.begin(); it != newList.end(); it++)
				push_back(*it);
			return *this;
		}
		~list() {
			if (!empty()) {
				clear();
			}
			_alloc.deallocate(_endNode->value, 1);
			_allocRebind.deallocate(_endNode, 1);
		}

	private:
		typedef struct		Node {
			value_type* 	value;
			Node* 			prev;
			Node* 			next;
		}					_List;
		_List*					_endNode;
		size_type				_size;

		allocator_type			_alloc;
		typedef typename allocator_type::template rebind<_List>::other allocator_rebind_type;
		allocator_rebind_type 	_allocRebind;

		void createList() {
			this->_endNode = this->_allocRebind.allocate(1);
			this->_endNode->value = this->_alloc.allocate(1);
			this->_endNode->prev = this->_endNode;
			this->_endNode->next = this->_endNode;
		}

		_List* createNode(const value_type & val) {
			_List *node = this->_allocRebind.allocate(1);
			node->value = this->_alloc.allocate(1);
			this->_alloc.construct(node->value, val);
			this->_size++;
			return node;
		}

		void linkNew(_List * newNode, _List * prev, _List * next) {
			newNode->prev = prev;
			newNode->next = next;
		}

		void destroyNode(_List* list) {
			this->_alloc.destroy(list->value);
//			this->_alloc.deallocate(list->value, 1);
//			this->_allocRebind.deallocate(list, 1);
			_size--;
		}

		void myReverse(_List* node) {
			_List * tmp = node->next;
			node->next = node->prev;
			node->prev = tmp;
			if (node == _endNode) {
				return;
			}
			myReverse(node->prev);
		}

		inline static bool myPredicate(const value_type & a, const value_type & b) { return a == b; }
		inline static bool myCompare(const value_type & a, const value_type & b) { return a < b; }

	public:
		class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			explicit iterator(_List* it = nullptr) : _it(it) {}
			iterator(const iterator & it) { *this = it; }
			iterator& operator=(const iterator & it) {
				this->_it = it._it;
				return *this;
			}
			~iterator() {}

			_List*  getIt() const { return this->_it; }

			reference operator*() { return *this->_it->value; }
			_List* operator->() { return this->_it->value; }

			iterator& operator++() {
				this->_it = _it->next;
				return *this;
			}
			iterator operator++(int) {
				iterator tmp(getIt());
				this->_it = _it->next;
				return tmp;
			}
			iterator& operator--() {
				this->_it = _it->prev;
				return *this;
			}
			iterator operator--(int) {
				iterator tmp(getIt());
				this->_it = _it->prev;
				return tmp;
			}

			bool operator==(const iterator &other) const { return this->_it->value == other.getIt()->value; };
			bool operator!=(const iterator &other) const { return this->_it->value != other.getIt()->value; };

		private:
			_List* _it;
		};

		class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			explicit reverse_iterator(_List* it = nullptr) : _it(it) {}
			reverse_iterator(const reverse_iterator & it) { *this = it; }
			reverse_iterator& operator=(const reverse_iterator & it) {
				this->_it = it._it;
				return *this;
			}
			~reverse_iterator() {}

			_List*  getIt() const { return this->_it; }

			reference operator*() { return *this->_it->value; }
			_List* operator->() { return this->_it->value; }

			reverse_iterator& operator++() {
				this->_it = _it->prev;
				return *this;
			}
			reverse_iterator operator++(int) {
				iterator tmp(getIt());
				this->_it = _it->prev;
				return tmp;
			}
			reverse_iterator& operator--() {
				this->_it = _it->next;
				return *this;
			}
			reverse_iterator operator--(int) {
				iterator tmp(getIt());
				this->_it = _it->next;
				return tmp;
			}

			bool operator==(const reverse_iterator &other) const { return this->_it->value == other.getIt()->value; };
			bool operator!=(const reverse_iterator &other) const { return this->_it->value != other.getIt()->value; };

		private:
			_List* _it;
		};

		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			explicit const_iterator(_List* it = nullptr) : _it(it) {}
			const_iterator(const const_iterator & it) { *this = it; }
			const_iterator& operator=(const const_iterator& it) {
				this->_it = it._it;
				return *this;
			}
			~const_iterator() {}

			_List*  getIt() const { return this->_it; }

			reference operator*() { return *this->_it->value; }
			_List* operator->() { return this->_it->value; }

			const_iterator& operator++() {
				this->_it = _it->next;
				return *this;
			}
			const_iterator operator++(int) {
				const_iterator tmp(getIt());
				this->_it = _it->next;
				return tmp;
			}
			const_iterator& operator--() {
				this->_it = _it->prev;
				return *this;
			}
			const_iterator operator--(int) {
				const_iterator tmp(getIt());
				this->_it = _it->prev;
				return tmp;
			}

			bool operator==(const const_iterator &other) const { return this->_it->value == other.getIt()->value; };
			bool operator!=(const const_iterator &other) const { return this->_it->value != other.getIt()->value; };

		private:
			_List* _it;
		};

		class const_reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			explicit const_reverse_iterator(_List* it = nullptr) : _it(it) {}
			const_reverse_iterator(const const_reverse_iterator & it) { *this = it; }
			const_reverse_iterator& operator=(const const_reverse_iterator & it) {
				this->_it = it._it;
				return *this;
			}
			~const_reverse_iterator() {}

			_List*  getIt() const { return this->_it; }

			reference operator*() { return *this->_it->value; }
			_List* operator->() { return this->_it->value; }

			const_reverse_iterator& operator++() {
				this->_it = _it->prev;
				return *this;
			}
			const_reverse_iterator operator++(int) {
				iterator tmp(getIt());
				this->_it = _it->prev;
				return tmp;
			}
			const_reverse_iterator& operator--() {
				this->_it = _it->next;
				return *this;
			}
			const_reverse_iterator operator--(int) {
				const_reverse_iterator tmp(getIt());
				this->_it = _it->next;
				return tmp;
			}

			bool operator==(const const_reverse_iterator &other) const { return this->_it->value == other.getIt()->value; };
			bool operator!=(const const_reverse_iterator &other) const { return this->_it->value != other.getIt()->value; };

		private:
			_List* _it;
		};
	};

	template <class T, class Alloc>
		bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
			typename ft::list<T, Alloc>::const_iterator lit_begin = lhs.begin();
			typename ft::list<T, Alloc>::const_iterator lit_end = lhs.end();
			typename ft::list<T, Alloc>::const_iterator rit_begin = rhs.begin();

			if (lhs.size() != rhs.size()) {
				return false;
			}
			for (; lit_begin != lit_end; ++lit_begin, ++rit_begin) {
				if (*lit_begin != *rit_begin) {
					return false;
				}
			}
			return true;
		}
	template <class T, class Alloc>
		bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs == rhs); }
	template <class T, class Alloc>
		bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
			typename ft::list<T, Alloc>::const_iterator lit_begin = lhs.begin();
			typename ft::list<T, Alloc>::const_iterator lit_end = lhs.end();
			typename ft::list<T, Alloc>::const_iterator rit_begin = rhs.begin();
			typename ft::list<T, Alloc>::const_iterator rit_end = rhs.end();

			for (; lit_begin != rit_end && rit_begin != rit_end; ++lit_begin, ++rit_begin) {
				if (*lit_begin < *rit_begin) {
					return true;
				}
			}
			if (lit_begin != rit_end) {
				return false;
			}
			return (rit_begin != rit_end);
		}
	template <class T, class Alloc>
		bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
			typename ft::list<T, Alloc>::const_iterator lit_begin = lhs.begin();
			typename ft::list<T, Alloc>::const_iterator lit_end = lhs.end();
			typename ft::list<T, Alloc>::const_iterator rit_begin = rhs.begin();
			typename ft::list<T, Alloc>::const_iterator rit_end = rhs.end();

			for (; lit_begin != rit_end && rit_begin != rit_end; ++lit_begin, ++rit_begin) {
				if (*lit_begin <= *rit_begin) {
					return true;
				}
			}
			if (lit_begin != rit_end) {
				return false;
			}
			return (rit_begin == rit_end);
		}
	template <class T, class Alloc>
		bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs < rhs); }
	template <class T, class Alloc>
		bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs <= rhs); }
	template <class T, class Alloc>
		void swap(list<T,Alloc>& x, list<T,Alloc>& y) {
			x.swap(y);
		}
}

#endif //LIST_HPP
