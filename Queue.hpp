//
// Created by Freely Kathryne on 1/16/21.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "Vector.hpp"

namespace ft {
	 template<class T, class Container = ft::list<T> >
	class queue {
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	public:
		//member function:
		bool empty() const { return this->_container.empty(); }
		size_type size() const { return this->_container.size(); }
		value_type& front() { return this->_container.front(); };
		const value_type& front() const { return this->_container.front(); };
		value_type& back() { return this->_container.back(); };
		const value_type& back() const { return this->_container.back(); };
		void push(const value_type& val) { return this->_container.push_back(val); };
		void pop() { this->_container.pop_back(); };

		//constructor
		explicit queue(const container_type& containerType = container_type()) : _container(containerType) {}
		~queue() {};
	private:
		container_type _container;
	};
	template <class T, class Container>
	bool operator==(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {return lhs._container == rhs._container; };
	template <class T, class Container>
	bool operator!=(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {return lhs._container != rhs._container; };
	template <class T, class Container>
	bool operator<(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {return lhs._container < rhs._container; };
	template <class T, class Container>
	bool operator<=(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {return lhs._container <= rhs._container; };
	template <class T, class Container>
	bool operator>(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {return lhs._container > rhs._container; };
	template <class T, class Container>
	bool operator>=(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {return lhs._container >= rhs._container; };
}

#endif //QUEUE_HPP
