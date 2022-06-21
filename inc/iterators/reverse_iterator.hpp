//
// Created by Anton on 20/06/2022.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP
#include "utils/null_pointer.hpp"

namespace ft {
template <class Iterator> class reverse_iterator {
	typedef Iterator											iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type      value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer     pointer;
	typedef typename ft::iterator_traits<Iterator>::reference   reference;

private:
	pointer _ptr;
public:
	/********************************* CONSTRUCTORS *****************************************/
	/*	default constructor *
	* Constructs a reverse iterator that points to no object.
	* The internal base iterator is value-initialized.*/
	reverse_iterator(): _ptr(null_pointer) {}
	/*	initalization constructor *
	* Constructs a reverse iterator from some original iterator it. The behavior of the constructed object
	* replicates the original, except that it iterates through its pointed elements in the reverse order.*/
	explicit reverse_iterator (iterator_type it): _ptr(&*it) {}
	/*	copy / type-cast constructor *
	* Constructs a reverse iterator from some other reverse iterator. The constructed object keeps the same sense of iteration as rev_it*/
//	template <class Iter>
//	reverse_iterator (const reverse_iterator<Iter>& rev_it);

	typename Iterator::pointer get_data() const { return &*_ptr; }

	/* dereferences */

	/* increment / decrement */
	reverse_iterator& operator++() { _ptr--; return *this; }
	reverse_iterator operator++(int) {
		reverse_iterator temp = *this;
		++(*this);
		return temp;
	}
	reverse_iterator& operator--() { _ptr++; return *this; }
	reverse_iterator operator--(int) {
		reverse_iterator temp = *this;
		--(*this);
		return temp;
	}

	/* arithmetic operators +- */
	reverse_iterator operator+(difference_type n) const { return reverse_iterator(_ptr - n); }
	reverse_iterator operator-(difference_type other) const { return reverse_iterator(_ptr + other) ; }

	/* compound assignment operations */
	void operator+=(difference_type n) { _ptr -= n; }
	void operator-=(difference_type n) { _ptr += n; }

	/*********************************** MEMBER FUNCTION *********************************************/

	reference operator[](difference_type pos) {return *(_ptr - pos - 1); }
	reference operator*() const {
		iterator_type tmp = _ptr;
		return (*(--tmp)); }
	pointer operator->() const {
		return &(operator*());
	}


	/* convertion from const */
	operator random_access_iterator<const Iterator>() const {
		return (random_access_iterator<const Iterator>)(this->_ptr);
	}
};
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.get_data() == rhs.get_data();
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.get_data() != rhs.get_data();
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.get_data() > rhs.get_data();
	}
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.get_data() >= rhs.get_data();
	}

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.get_data() < rhs.get_data();
	}
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					 const reverse_iterator<Iterator>& rhs) {
		return lhs.get_data() <= rhs.get_data();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return rev_it - n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
		lhs.get_data() - rhs.get_data();
	}
}

#endif //CONTAINERS_REVERSE_ITERATOR_HPP
