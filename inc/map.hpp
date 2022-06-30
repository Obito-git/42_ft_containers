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
	private:

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef typename ft::pair<const Key, T> value_type;


		//Red black tree typedefs
		typedef RB_tree<key_type, mapped_type, value_type, Compare, Alloc>	MapTree;
		typedef typename	MapTree::node_allocator_type				allocator_type;
		typedef typename	MapTree::key_compare					key_compare;

		//typedef Compare value_compare;

		typedef typename	allocator_type::reference		reference;
		typedef typename	allocator_type::const_reference	const_reference;
		typedef typename	allocator_type::pointer    		pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;
		typedef				size_t  						size_type;
		typedef				ptrdiff_t						difference_type;
		typedef typename	MapTree::iterator				iterator;
		typedef typename	MapTree::const_iterator		const_iterator;


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
		map (const map& x) {
			(void) x;

		}
		~map() {}

		/*************************************** ITERATORS *********************************************/

		iterator begin(){
			return _data.begin();
		}

		iterator end(){
			return _data.end();
		}

		const_iterator begin() const {
			return _data.begin();
		}

		const_iterator end() const{
			return _data.end();
		}

		iterator upper_bound (const key_type& k) {
			return _data.upper_bound(k);
		}

		const_iterator upper_bound (const key_type& k) const {
			return _data.upper_bound(k);
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		pair<iterator,iterator> equal_range (const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		/****************************************** MODIFIERS ***********************************************/

		pair<iterator,bool> insert (const value_type& val) {
			return _data.insert_element(val);
		}

		iterator insert (iterator position, const value_type& val) {
			(void) position; //FIXME test
			ft::pair<iterator, bool> ret = _data.insert_element(val);
			return ret.first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			while (first != last)
				_data.insert_element(*first++);
		}

		void erase (iterator position) {
			_data.erase(position);
		}

		size_type erase (const key_type& k) {
			iterator it = find(k);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}
		//void erase (iterator first, iterator last);

		/****************************************** OPERATIONS ***********************************************/

		iterator lower_bound (const key_type& k) {
			return _data.lower_bound(k);
		}

		const_iterator lower_bound (const key_type& k) const {
			return _data.lower_bound(k);
		}

		iterator find (const key_type& k) {
			return _data.find(k);
		}
		//const_iterator find (const key_type& k) const;

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

		void clear() {
			int i = 1;
			while (!empty()) {
				//std::cout << "element " << i++ << ", key " << begin()->first << std::endl; FIXME
				_data.erase(begin());
			}
		}


		/****************************** ALLOCATOR ****************************************/
		/*	Get allocator *
		* Returns a copy of the allocator object associated with the map.*/
		allocator_type get_allocator() const {
			return _data.getAlloc();
		}



		/*
		friend std::ostream &operator<<(std::ostream &os, const map &map) {
			int current_lvl = 0;
			int depth = 0;
			std::vector<node *> parents;
			std::vector<node *> tmp_par;

			parents.push_back(map.root);
			for (; !parents.empty(); depth++) {
				for (typename std::vector<node *>::iterator it = parents.begin(); it != parents.end(); it++) {
					if (!(*it)->left->is_nullLeaf()) { tmp_par.push_back((*it)->left); }
					if (!(*it)->right->is_nullLeaf()) { tmp_par.push_back((*it)->right); }
				}
				parents.swap(tmp_par);
				tmp_par.clear();
			}
			os << "current level: " << current_lvl++ << ".";
			for (int i = 0; i < depth; i++) { os << "    "; }
			depth--;
			os<< *map.root << std::endl;
			parents.push_back(map.root);
			for (;!parents.empty(); current_lvl++) {
				os << "current level: " << current_lvl << ". ";
				for (int i = 0; i < depth; i++) { os << "   "; }
				depth--;
				for (typename std::vector<node *>::iterator it = parents.begin(); it != parents.end(); it++) {
					if ((*it)->left)
						os << *(*it)->left << "L  ";
					else os << "       ";
					if ((*it)->right)
						os << *(*it)->right << "R   ";
					else
						os << "    ";
					if (!(*it)->is_nullLeaf()) {
						tmp_par.push_back((*it)->left);
						tmp_par.push_back((*it)->right);
					}
				}
				os << std::endl;
				parents.swap(tmp_par);
				tmp_par.clear();
			}
			return os;
		}
		 */
	};

}

#endif //CONTAINERS_MAP_HPP
