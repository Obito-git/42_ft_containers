//
// Created by Anton on 20/06/2022.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP
#include "null_pointer.hpp"

namespace ft {
template <class Iterator>
class reverse_iterator {
public:
	typedef Iterator											iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type      value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer     pointer;
	typedef typename ft::iterator_traits<Iterator>::reference   reference;

private:
	iterator_type _ptr;
public:
	/********************************* CONSTRUCTORS *****************************************/
	/*	default constructor *
	* Constructs a reverse iterator that points to no object.
	* The internal base iterator is value-initialized.*/
	reverse_iterator(): _ptr(null_pointer) {}
	/*	initalization constructor *
	* Constructs a reverse iterator from some original iterator it. The behavior of the constructed object
	* replicates the original, except that it iterates through its pointed elements in the reverse order.*/
	explicit reverse_iterator (iterator_type it): _ptr(it) {}
	/*	copy / type-cast constructor *
	* Constructs a reverse iterator from some other reverse iterator. The constructed object keeps the same sense of iteration as rev_it*/
	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it): _ptr(rev_it.base()) {}

	iterator_type base() const { return _ptr; }

	/* dereferences */

	/* increment / decrement */
	reverse_iterator& operator++() { --_ptr; return *this; }
	reverse_iterator operator++(int) {
		reverse_iterator<iterator_type> temp(*this);
		--_ptr;
		return temp;
	}
	reverse_iterator& operator--() { ++_ptr; return *this; }
	reverse_iterator operator--(int) {
		reverse_iterator<iterator_type> temp(*this);
		++_ptr;
		return temp;
	}


	/* arithmetic operators +- */
	reverse_iterator operator+(difference_type n) const { return reverse_iterator(_ptr - n); }
	reverse_iterator operator-(difference_type other) const { return reverse_iterator(_ptr + other) ; }

	/* compound assignment operations */
	reverse_iterator& operator+=(difference_type n) { _ptr -= n; return *this; }
	reverse_iterator& operator-=(difference_type n) { _ptr += n; return *this; }

	/*********************************** MEMBER FUNCTION *********************************************/

	reference operator[](difference_type pos) {return *(_ptr - pos - 1); }
	reference operator*() const {
		iterator_type tmp = _ptr;
		return (*(--tmp)); }
	pointer operator->() const {
		return &(operator*());
	}


	/* convertion from const */
	//operator reverse_iterator<const Iterator>() const {
	//	return (reverse_iterator<const Iterator>)(this->_ptr);
	//}
};
	template <class T1, class T2>
	bool operator== (const reverse_iterator<T1>& lhs,
					 const reverse_iterator<T2>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <class T1, class T2>
	bool operator!= (const reverse_iterator<T1>& lhs,
					 const reverse_iterator<T2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <class T1, class T2>
	bool operator<  (const reverse_iterator<T1>& lhs,
					 const reverse_iterator<T2>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class T1, class T2>
	bool operator<= (const reverse_iterator<T1>& lhs,
					 const reverse_iterator<T2>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <class T1, class T2>
	bool operator>  (const reverse_iterator<T1>& lhs,
					 const reverse_iterator<T2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class T1, class T2>
	bool operator>= (const reverse_iterator<T1>& lhs,
					 const reverse_iterator<T2>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return rev_it + n;
	}

	template <class T1, class T2>
	typename reverse_iterator<T1>::difference_type operator- (
			const reverse_iterator<T1>& lhs,
			const reverse_iterator<T2>& rhs) {
		return (rhs.base() - lhs.base());
	}
}

#endif //CONTAINERS_REVERSE_ITERATOR_HPP
