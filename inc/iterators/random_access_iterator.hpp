//
// Created by Anton on 11/06/2022.
//

#ifndef CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#define CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#include "iterators/iterator.hpp"

//https://m.cplusplus.com/reference/iterator/RandomAccessIterator/

namespace ft {
	template <typename T>
	class random_access_iterator : public iterator<ft::random_access_iterator_tag, T> {
	public:
		typedef typename	ft::iterator<random_access_iterator_tag, T>						iterator_category;
		typedef typename	ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef				T&																reference;
		typedef 			T*																pointer;
		typedef 			const T&														const_reference;

		/* Is default-constructible, copy-constructible, copy-assignable and destructible */
		random_access_iterator() : _ptr(null_pointer) {}
		random_access_iterator(const random_access_iterator& other) {
			_ptr = other._ptr;
		}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator &operator=(const random_access_iterator<T>& other) {
				 if (this == &other) { return *this; }
				 _ptr = other._ptr;
				 return *this;
		}
		virtual ~random_access_iterator() {}

		/*************************** CONSTANT MEMBER FUNCTION ************************************/

		/* equality operators */
		bool operator==(const random_access_iterator &other) const { return _ptr == other._ptr; }
		bool operator!=(const random_access_iterator &other) const { return _ptr != other._ptr; }

		/* dereferences */
		const_reference operator*() const { return *_ptr; }

		/* increment / decrement */
		random_access_iterator& operator++() { _ptr++; return *this; }
		random_access_iterator operator++(int) { random_access_iterator old(*this); _ptr++; return old; }
		random_access_iterator& operator--() { _ptr--; return *this; }
		random_access_iterator operator--(int) { random_access_iterator old(*this); _ptr--; return old; }

		/* arithmetic operators +- */
		random_access_iterator operator+(difference_type n) const { return _ptr + n; }
		random_access_iterator operator-(difference_type other) const { return _ptr - other; }

		/* relational operators */
		bool operator<(const random_access_iterator &other) const { return _ptr < other._ptr; }
		bool operator>(const random_access_iterator &other) const { return _ptr > other._ptr; }
		bool operator<=(const random_access_iterator &other) const { return _ptr <= other._ptr; }
		bool operator>=(const random_access_iterator &other) const { return _ptr >= other._ptr; }

		/* compound assignment operations */
		void operator+=(difference_type n) { _ptr += n; }
		void operator-=(difference_type n) { _ptr -= n; }

		/* the offset dereference operator */
		const_reference operator[](difference_type pos) const {return *(_ptr + pos); }
		/*********************************** MEMBER FUNCTION *********************************************/

		reference operator[](difference_type pos) {return *(_ptr + pos); }
		reference operator*() { return *_ptr; }
		pointer operator->() { return _ptr; }


		/* convertion from const */
		operator random_access_iterator<const T>() const {
			return (random_access_iterator<const T>)(this->_ptr);
		}
	private:
		pointer _ptr;
	};

	/*********************************** NOT MEMBER FUNCTION *********************************************/


	template <typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n,
			const random_access_iterator<T>& other) {
		return other + n;
	}
	template <typename T1, typename T2>
	typename random_access_iterator<T1>::difference_type operator-(const ft::random_access_iterator<T1>& a,
			const random_access_iterator<T2>& b) {
		return &*a - &*b;
	}
	/* equality and relational operators */
	template <typename T1, typename T2>
	bool operator==(const random_access_iterator<T1>& a, const random_access_iterator<T2>& b) {
		return &*a == &*b;
	}

	template <typename T1, typename T2>
	bool operator!=(const random_access_iterator<T1>& a, const random_access_iterator<T2>& b) {
		return &*a != &*b;
	}

	template <typename T1, typename T2>
	bool operator>(const random_access_iterator<T1>& a, const random_access_iterator<T2>& b) {
	   return &*a > &*b;
   }

	template <typename T1, typename T2>
	bool operator<(const random_access_iterator<T1>& a, const random_access_iterator<T2>& b) {
	   return &*a < &*b;
   }
	template <typename T1, typename T2>
	bool operator>=(const random_access_iterator<T1>& a, const random_access_iterator<T2>& b) {
	   return &*a >= &*b;
   }
	template <typename T1, typename T2>
	bool operator<=(const random_access_iterator<T1>& a, const random_access_iterator<T2>& b) {
	   return &*a <= &*b;
   }

}

#endif //CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
