//
// Created by Freely Kathryne on 1/15/21.
//

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "Vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	class stack {
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	public:
		//member function:
		bool empty() const { return this->_container.empty(); }
		size_type size() const { return this->_container.size(); }
		value_type & top() { return this->_container.back(); };
		const value_type & top() const { return this->_container.push_back(); };
		void push(const value_type& val) { return this->_container.push_back(val); };
		void pop() { this->_container.pop_back(); };

		explicit stack(const container_type & containerType = container_type()) : _container(containerType) {};
		~stack() {};
	private:
		container_type _container;
	};
	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._container == rhs._container; };
	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._container != rhs._container; };
	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._container < rhs._container; };
	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._container <= rhs._container; };
	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._container > rhs._container; };
	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._container >= rhs._container; };
}

#endif //STACK_HPP
