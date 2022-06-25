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
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
	> class map {
	private:

	public:
		typedef Key key_type;
		typedef T mapped_type;


		//Red black tree typedefs
		typedef RB_tree<key_type, mapped_type, Compare, Alloc> tree;
		typedef typename	tree::RB_node node;

		typedef typename	tree::allocator_type		allocator_type;

		typedef typename tree::key_compare key_compare;
		//typedef Compare value_compare;

		typedef typename	tree::value_type					value_type;
		typedef typename	allocator_type::reference		reference;
		typedef typename	allocator_type::const_reference	const_reference;
		typedef typename	allocator_type::pointer    		pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;
		typedef				size_t  						size_type;
		typedef				ptrdiff_t						difference_type;
		typedef 			RBT_iterator<node>				iterator;



		/* Red black tree variable*/
		tree _data;
	public:
		//constructors
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _data(comp, alloc) {}
		~map() {}

		/*************************************** ITERATORS *********************************************/

		iterator begin(){
			node* tmp = _data.getRoot();
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return iterator(tmp);
		}

		iterator end(){
			node* tmp = _data.getRoot();
			while (tmp->right)
				tmp = tmp->right;
			return iterator(tmp);
		}

		/****************************************** MODIFIERS ***********************************************/

		//pair<iterator,bool> insert (const value_type& val);
		void insert (const value_type& val) {
			_data.insert_element(val);
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
