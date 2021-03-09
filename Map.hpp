//
// Created by Freely Kathryne on 3/4/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

namespace ft {
	template < class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T>> >
	class map {
	public:
		class iterator;
		class const_iterator;

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef value_type &								reference;
		typedef const value_type &							const_reference;
		typedef value_type *								pointer;
		typedef const value_type *							const_pointer;
		typedef size_t 										size_type;
		typedef ptrdiff_t 									difference_type;

		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
	};
}

#endif //FT_CONTAINERS_MAP_HPP
