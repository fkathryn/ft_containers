//
// Created by Freely Kathryne on 1/11/21.
//

#ifndef FT_HPP
#define FT_HPP

#include <List>
#include <iostream>


namespace ft {

	template <class T, class Alloc = std::allocator<T> >
	class List {
		// types:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
	public:
		List();
		~List();
		List(const List & otherElem);
		List &operator=(const List & otherElem);
	};
}


#endif //FT_HPP
