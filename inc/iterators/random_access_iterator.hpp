//
// Created by Anton on 11/06/2022.
//

#ifndef CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#define CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#include "iterators/iterator.hpp"

//https://m.cplusplus.com/reference/iterator/RandomAccessIterator/

#include <iostream>
namespace ft {
	template <typename T>
	class random_access_iterator : public iterator<ft::random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<random_access_iterator_tag, T>					iterator_category;
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef T& reference;
		typedef T*	pointer;
		typedef const T& const_reference;

		/* Is default-constructible, copy-constructible, copy-assignable and destructible */
		random_access_iterator() : _ptr(null_pointer) {}
		random_access_iterator(const random_access_iterator<T>& other) :_ptr(other._ptr){}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator &operator=(const random_access_iterator<T>& other) {
				 if (this == &other) { return *this; }
				 _ptr = other._ptr;
				 return *this;
		}
		virtual ~random_access_iterator() {}

		/*	Can be compared for equivalence using the equality/inequality operators
			(meaningful when both iterator values iterate over the same underlying sequence).*/
		bool operator==(const_reference other) const { return _ptr == other._ptr; }
		bool operator!=(const_reference other) const { return _ptr == other._ptr; }

		/* Put simply, an lvalue is an object reference and an rvalue is a value.
		* The difference between lvalues and rvalues plays a role in the writing and understanding of expressions.
		**********************************************************************************************************
		* Can be dereferenced as an rvalue (if in a dereferenceable state).
		* For mutable iterators (non-constant iterators):
		* Can be dereferenced as an lvalue (if in a dereferenceable state).*/
		reference operator*() { return *_ptr; }
		const_reference operator*() const { return *_ptr; }
		pointer operator->() { return _ptr; }

		/*	Can be incremented (if in a dereferenceable state).
		* The result is either also dereferenceable or a past-the-end iterator.
		* Two iterators that compare equal, keep comparing equal after being both increased. */
		random_access_iterator& operator++() { _ptr++; return *this; }
		random_access_iterator operator++(int) { random_access_iterator old(*this); _ptr++; return old; }

		/* Can be decremented (if a dereferenceable iterator value precedes it). */
		random_access_iterator& operator--() { _ptr--; return *this; }
		random_access_iterator operator--(int) { random_access_iterator old(*this); _ptr--; return old; }

		/*	Supports the arithmetic operators + and - between an iterator and an integer value,
		* or subtracting an iterator from another.	*/
		random_access_iterator operator+(difference_type n) { return _ptr + n; }
		random_access_iterator operator-(difference_type other) { return _ptr - other; }


		/*	No member operator overload */
		friend random_access_iterator operator+(difference_type n, const random_access_iterator& other) {
			return other._ptr + n;
		}
		friend difference_type operator-(const random_access_iterator& a, const random_access_iterator& b) {
			return a._ptr - b._ptr;
		}

		/*	Can be compared with inequality relational operators (<, >, <= and >=). */
		bool operator<(const random_access_iterator &other) const {_ptr < other._ptr; }
		bool operator>(const random_access_iterator &other) const {_ptr > other._ptr; }
		bool operator<=(const random_access_iterator &other) const {_ptr <= other._ptr; }
		bool operator>=(const random_access_iterator &other) const {_ptr >= other._ptr; }

		/*	Supports compound assignment operations += and -= */
		void operator+=(difference_type n) { _ptr += n; }
		void operator-=(difference_type n) { _ptr -= n; }

		/*	Supports the offset dereference operator ([])	*/
		reference operator[](difference_type pos) {return *(_ptr + pos); }
	private:
		pointer _ptr;
	};
}

#endif //CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
