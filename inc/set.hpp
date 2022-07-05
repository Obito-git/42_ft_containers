//
// Created by Anton on 21/06/2022.
//

#ifndef CONTAINERS_SET_HPP
#define CONTAINERS_SET_HPP

#include <ostream>
#include "pair.hpp"
#include "null_pointer.hpp"
#include "utils.hpp"
#include "RBT_iterator.hpp"
#include "RB_tree.hpp"
#include "ft_containers_test.hpp"
#include <vector>


namespace ft {
	template < class T,   	                                   // set::mapped_type
			class Compare = std::less<T>,                     // set::key_compare
			class Alloc = std::allocator<T>    // set::allocator_type
	> class set {
	/****************************************** Member types *******************************************************/
	public:
		typedef 	T							value_type;
		typedef RB_tree<value_type, value_type, const value_type, Compare, Alloc>	MapTree;
		typedef typename	MapTree::key_compare							key_compare;
		typedef typename 	MapTree::value_compare							value_compare;
		typedef typename	MapTree::node_allocator_type					allocator_type;
		typedef typename	allocator_type::reference		reference;
		typedef typename	allocator_type::const_reference	const_reference;
		typedef typename	allocator_type::pointer    		pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;
		//reverse iterator
		//const reverse iterator
		typedef typename	MapTree::iterator				iterator;
		typedef typename	MapTree::const_iterator		const_iterator;
		typedef typename	MapTree::reverse_iterator 		reverse_iterator;
		typedef typename	MapTree::const_reverse_iterator 		const_reverse_iterator;
		typedef				ptrdiff_t						difference_type;
		typedef				size_t  						size_type;

	private:
		/* Red black tree variable*/
		MapTree _data;
	public:
		/***************************************** CONSTRUCTORS ****************************************/
		/*	Empty container constructor (default constructor)
		* Constructs an empty container, with no elements.*/

		explicit set (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _data(comp, alloc) {}

		/*	Range constructor
		* Constructs a container with as many elements as the range [first,last),
		* with each element constructed from its corresponding element in that range*/
		template <class InputIterator>
		set (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()): _data(comp, alloc) {
			insert(first, last);
		}
		/*	Copy constructor
		* Constructs a container with a copy of each of the elements in x.*/
		set (const set& x): _data(x.key_comp(), x.get_allocator()) {
			insert(x.begin(), x.end());
		}

		/*	Copy container content
		* Assigns new contents to the container, replacing its current content.*/
		set& operator= (const set& x) {
			if (&x != this) {
				clear();
				insert(x.begin(), x.end());
			}
			return *this;
		}

		~set() {}

		/*************************************** ITERATORS *********************************************/

		/*	Return iterator to beginning
		* Returns an iterator referring to the first element in the set container. */
		iterator begin(){
			return _data.begin();
		}

		const_iterator begin() const {
			return _data.begin();
		}

		/*	Return iterator to end
		* Returns an iterator referring to the past-the-end element in the set container.*/

		iterator end(){
			return _data.end();
		}

		const_iterator end() const{
			return _data.end();
		}


		//FIXME DESCRIBE
		reverse_iterator rbegin() {
			return _data.rbegin();
		}

		const_reverse_iterator rbegin() const {
			return _data.rbegin();
		}

		reverse_iterator rend() {
			return _data.rend();
		}
		const_reverse_iterator rend() const {
			return _data.rend();
		}

		/****************************************** MODIFIERS ***********************************************/

		/*	Insert elements *
		* Extends the container by inserting new elements,
		* effectively increasing the container size by the number of elements inserted.*/

		/*	The single element versions return a pair, with its member pair::first set to an iterator pointing
		* to either the newly inserted element or to the element with an equivalent key in the set.
		* The pair::second element in the pair is set to true if a new element was inserted
		* or false if an equivalent key already existed.*/

		pair<iterator,bool> insert (const value_type& val) {
			return _data.insert_element(val);
		}

		/*	The versions with a hint return an iterator pointing to either the newly inserted element
		* or to the element that already had an equivalent key in the set.*/

		iterator insert (iterator position, const value_type& val) {
			(void) position; //FIXME test
			ft::pair<iterator, bool> ret = _data.insert_element(val);
			return ret.first;
		}


		/* Iterators specifying a range of elements. Copies of the elements in the range [first,last)
		* are inserted in the container. Notice that the range includes all the elements between first and last,
		* including the element pointed by first but not the one pointed by last.*/

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			while (first != last) {
				_data.insert_element(*first);
				first++;
			}
		}

		/*	Erase elements *
		* Removes from the set container either a single element or a range of elements ([first,last)).
		* This effectively reduces the container size by the number of elements removed, which are destroyed.*/

		void erase (iterator position) {
			_data.erase(position);
		}

		/* For the key-based version the function returns the number of elements erased. */

		size_type erase (const value_type& k) {
			iterator it = find(k);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}
		/*	Iterators specifying a range within the set container to be removed: [first,last). i.e.,
		* the range includes all the elements between first and last, including the element
		* pointed by first but not the one pointed by last.
		* Member types iterator and const_iterator are bidirectional iterator types that point to elements. */

		void erase (iterator first, iterator last) {
			for (; first != last; first++)
				erase(first);
		}

		/*	Swap content
		* Exchanges the content of the container by the content of x, which is another set of the same type. */

		void swap (set& x) {
			_data.swap(x._data);
		}

		/*	Clear content *
		* Removes all elements from the set container (which are destroyed), leaving the container with a size of 0.*/

		void clear() {
			_data.clear();
		}

		/****************************************** OPERATIONS ***********************************************/

		/*	Return iterator to lower bound *
		* Returns an iterator pointing to the first element in the container whose key is not considered
		* to go before k (i.e., either it is equivalent or goes after).*/

		iterator lower_bound (const value_type& k) {
			return _data.lower_bound(k);
		}

		const_iterator lower_bound (const value_type& k) const {
			return _data.lower_bound(k);
		}

		/*	Return iterator to upper bound
		* Returns an iterator pointing to the first element in the container whose key is considered to go after k. */

		iterator upper_bound (const value_type& k) {
			return _data.upper_bound(k);
		}
		const_iterator upper_bound (const value_type& k) const {
			return _data.upper_bound(k);
		}

		/*	Get iterator to element *
		* Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
		* otherwise it returns an iterator to set::end.
		* Two keys are considered equivalent if the container's comparison object returns false reflexively
		* (i.e., no matter the order in which the elements are passed as arguments).*/

		iterator find (const value_type& k) {
			return _data.find(k);
		}

		const_iterator find (const value_type& k) const {
			return _data.find(k);
		}

		/*	Count elements with a specific key
		* Searches the container for elements with a key equivalent to k and returns the number of matches.
		* Because all elements in a set container are unique, the function can only return 1
		* (if the element is found) or zero (otherwise).*/
		size_type count (const value_type& k) const {
			return _data.count(k);
		}

		/*	Get range of equal elements *
		* Returns the bounds of a range that includes all the elements in the container which have a key
		* equivalent to k. Because the elements in a set container have unique keys,
		* the range returned will contain a single element at most.
		*	If no matches are found, the range returned has a length of zero, with both iterators pointing to the first
		* element that has a key considered to go after k according to the container's internal comparison object (key_comp).*/

		pair<const_iterator,const_iterator> equal_range (const value_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		pair<iterator,iterator> equal_range (const value_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		/****************************************** CAPACITY ************************************************/
		/*	Return container size *
		* Returns the number of elements in the set container.*/
		size_type size() const {
			return _data.getSize();
		}

		/*	Test whether container is empty *
		* Returns whether the set container is empty (i.e. whether its size is 0).*/
		bool empty() const {
			return (!size());
		}

		/*	Return maximum size *
		* Returns the maximum number of elements that the set container can hold*/
		size_type max_size() const {
			return _data.getAlloc().max_size();
		}

		/****************************************** CAPACITY ************************************************/
		/*	Access element *
		* If k matches the key of an element in the container,
		* the function returns a reference to its mapped value.

		* If k does not match the key of any element in the container, the function inserts a new element with
		* that key and returns a reference to its mapped value. Notice that this always increases the container
		* size by one, even if no mapped value is assigned to the element
		* (the element is constructed using its default constructor).*/

		/**************************************** OBSERVERS ***************************************************/

	public:
		/*	Return key comparison object *
		* Returns a copy of the comparison object used by the container to compare keys.*/

		key_compare key_comp() const {
			return _data.key_comp();
		}

		/*	Return value comparison object *
		* Returns a comparison object that can be used to compare two elements
		* to get whether the key of the first one goes before the second.*/

		value_compare value_comp() const {
			return _data.value_comp();
		}


		/****************************** ALLOCATOR ****************************************/
		/*	Get allocator *
		* Returns a copy of the allocator object associated with the set.*/
		allocator_type get_allocator() const {
			return _data.getAlloc();
		}
	};

	/*	The equality comparison (operator==) is performed by first comparing sizes, and if they match,
* the elements are compared sequentially using operator==,
* stopping at the first mismatch (as if using algorithm equal).*/
	template <class T, class Compare, class Alloc>
	bool operator ==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool operator !=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	/*	The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare,
	* which compares the elements sequentially using operator< in a reciprocal manner
	* (i.e., checking both a<b and b<a) and stopping at the first occurrence.*/
	template <class T, class Compare, class Alloc>
	bool operator <(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator <=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class T, class Compare, class Alloc>
	bool operator >(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Compare, class Alloc>
	bool operator >=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Compare, class Alloc>
	void swap (set<T, Compare, Alloc>& x, set<T, Compare, Alloc>&y)
	{
		x.swap(y);
	}

}

#endif //CONTAINERS_SET_HPP
