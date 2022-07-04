//
// Created by Anton on 21/06/2022.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include <ostream>
#include "pair.hpp"
#include "null_pointer.hpp"
#include "utils.hpp"
#include "RBT_iterator.hpp"
#include "RB_tree.hpp"
#include "ft_containers_test.hpp"
#include <vector>


namespace ft {
	template < class Key,                                     // map::key_type
			class T,   	                                   // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
	> class map {
	/****************************************** Member types *******************************************************/
	public:
		typedef				Key												key_type;
		typedef				T												mapped_type;
		typedef typename	ft::pair<const Key, T>							value_type;
		typedef RB_tree<key_type, mapped_type, value_type, Compare, Alloc>	MapTree;
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
		typedef				ptrdiff_t						difference_type;
		typedef				size_t  						size_type;

	private:
		/* Red black tree variable*/
		MapTree _data;
	public:
		/***************************************** CONSTRUCTORS ****************************************/
		/*	Empty container constructor (default constructor)
		* Constructs an empty container, with no elements.*/

		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _data(comp, alloc) {}

		/*	Range constructor
		* Constructs a container with as many elements as the range [first,last),
		* with each element constructed from its corresponding element in that range*/
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()): _data(comp, alloc) {
			insert(first, last);
		}
		/*	Copy constructor
		* Constructs a container with a copy of each of the elements in x.*/
		map (const map& x): _data(x.key_compare, x.allocator_type) {
			insert(x.begin(), x.end());
		}

		/*	Copy container content
		* Assigns new contents to the container, replacing its current content.*/
		map& operator= (const map& x) {
			if (&x != this) {
				clear();
				insert(x.begin(), x.end());
			}
			return *this;
		}

		~map() {}

		/*************************************** ITERATORS *********************************************/

		/*	Return iterator to beginning
		* Returns an iterator referring to the first element in the map container. */
		iterator begin(){
			return _data.begin();
		}

		const_iterator begin() const {
			return _data.begin();
		}

		/*	Return iterator to end
		* Returns an iterator referring to the past-the-end element in the map container.*/

		iterator end(){
			return _data.end();
		}

		const_iterator end() const{
			return _data.end();
		}

		/****************************************** MODIFIERS ***********************************************/

		/*	Insert elements *
		* Extends the container by inserting new elements,
		* effectively increasing the container size by the number of elements inserted.*/

		/*	The single element versions return a pair, with its member pair::first set to an iterator pointing
		* to either the newly inserted element or to the element with an equivalent key in the map.
		* The pair::second element in the pair is set to true if a new element was inserted
		* or false if an equivalent key already existed.*/

		pair<iterator,bool> insert (const value_type& val) {
			return _data.insert_element(val);
		}

		/*	The versions with a hint return an iterator pointing to either the newly inserted element
		* or to the element that already had an equivalent key in the map.*/

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
			while (first != last)
				_data.insert_element(*first++);
		}

		/*	Erase elements *
		* Removes from the map container either a single element or a range of elements ([first,last)).
		* This effectively reduces the container size by the number of elements removed, which are destroyed.*/

		void erase (iterator position) {
			_data.erase(position);
		}

		/* For the key-based version the function returns the number of elements erased. */

		size_type erase (const key_type& k) {
			iterator it = find(k);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}
		/*	Iterators specifying a range within the map container to be removed: [first,last). i.e.,
		* the range includes all the elements between first and last, including the element
		* pointed by first but not the one pointed by last.
		* Member types iterator and const_iterator are bidirectional iterator types that point to elements. */

		void erase (iterator first, iterator last) {
			for (iterator it = first; it != last; it++)
				erase(it);
		}

		/*	Swap content
		* Exchanges the content of the container by the content of x, which is another map of the same type. */

		void swap (map& x) {
			map<key_type, mapped_type, key_compare, allocator_type> tmp(x);
			x = *this;
			*this = tmp;
		}

		/*	Clear content *
		* Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.*/

		void clear() {
			_data.clear();
		}

		/****************************************** OPERATIONS ***********************************************/

		/*	Return iterator to lower bound *
		* Returns an iterator pointing to the first element in the container whose key is not considered
		* to go before k (i.e., either it is equivalent or goes after).*/

		iterator lower_bound (const key_type& k) {
			return _data.lower_bound(k);
		}

		const_iterator lower_bound (const key_type& k) const {
			return _data.lower_bound(k);
		}

		/*	Return iterator to upper bound
		* Returns an iterator pointing to the first element in the container whose key is considered to go after k. */

		iterator upper_bound (const key_type& k) {
			return _data.upper_bound(k);
		}
		const_iterator upper_bound (const key_type& k) const {
			return _data.upper_bound(k);
		}

		/*	Get iterator to element *
		* Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
		* otherwise it returns an iterator to map::end.
		* Two keys are considered equivalent if the container's comparison object returns false reflexively
		* (i.e., no matter the order in which the elements are passed as arguments).*/

		iterator find (const key_type& k) {
			return _data.find(k);
		}

		const_iterator find (const key_type& k) const {
			return _data.find(k);
		}

		/*	Count elements with a specific key
		* Searches the container for elements with a key equivalent to k and returns the number of matches.
		* Because all elements in a map container are unique, the function can only return 1
		* (if the element is found) or zero (otherwise).*/
		size_type count (const key_type& k) const {
			return _data.count(k);
		}

		/*	Get range of equal elements *
		* Returns the bounds of a range that includes all the elements in the container which have a key
		* equivalent to k. Because the elements in a map container have unique keys,
		* the range returned will contain a single element at most.
		*	If no matches are found, the range returned has a length of zero, with both iterators pointing to the first
		* element that has a key considered to go after k according to the container's internal comparison object (key_comp).*/

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		pair<iterator,iterator> equal_range (const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		/****************************************** CAPACITY ************************************************/
		/*	Return container size *
		* Returns the number of elements in the map container.*/
		size_type size() const {
			return _data.getSize();
		}

		/*	Test whether container is empty *
		* Returns whether the map container is empty (i.e. whether its size is 0).*/
		bool empty() const {
			return (!size());
		}

		/*	Return maximum size *
		* Returns the maximum number of elements that the map container can hold*/
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

		mapped_type& operator[] (const key_type& k) {
			insert(ft::make_pair(k, mapped_type()));
			return find(k)->second;
		}


		/****************************** ALLOCATOR ****************************************/
		/*	Get allocator *
		* Returns a copy of the allocator object associated with the map.*/
		allocator_type get_allocator() const {
			return _data.getAlloc();
		}
	};

}

#endif //CONTAINERS_MAP_HPP
