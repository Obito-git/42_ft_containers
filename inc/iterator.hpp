//
// Created by Anton on 10/06/2022.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP
#include <cstddef>
#include "null_pointer.hpp"

namespace ft {
	/* Iterator category's */
	struct input_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	/*Template parameters
	* @Category		- the category of the iterator. Must be one of iterator category tags.
	* @T			- the type of the values that can be obtained by dereferencing the iterator. This type should be void for output iterators.
	* @Distance		- a type that can be used to identify distance between iterators
	* @Pointer		- defines a pointer to the type iterated over (T)
	* @Reference	- defines a reference to the type iterated over (T)*/

	template<class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	/*  Iterator traits *
	* Traits class defining properties of iterators.
	* Standard algorithms determine certain properties of the iterators passed to them and the range they represent
	* by using the members of the corresponding iterator_traits instantiation.
	*   For every iterator type, a corresponding specialization of iterator_traits class template shall be defined,
	* with at least the following member types defined:
*/
	/*  Member types *
	* @difference_type	- Type to express the result of subtracting one iterator from another.
	* @value_type		- The type of the element the iterator can point to.
	* @pointer			- The type of a pointer to an element the iterator can point to.
	* @reference		- The type of a reference to an element the iterator can point to.
	* @iterator_category- The iterator category. It can be one of these:
		*input_iterator_tag
		*output_iterator_tag
		*forward_iterator_tag
		*bidirectional_iterator_tag
		*random_access_iterator_tag */

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};

	/*fundamental integral types
	* bool
	* char
	* char16_t
	* char32_t
	* wchar_t
	* signed char
	* short int
	* int
	* long int
	* long long int
	* unsigned char
	* unsigned short int
	* unsigned int
	* unsigned long int
	* unsigned long long int
*/


}
#endif //CONTAINERS_ITERATOR_HPP
