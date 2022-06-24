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
		typedef ft::pair<key_type, mapped_type> value_type;
		typedef Compare key_compare;
		//typedef Compare value_compare;
		typedef		typename Alloc::template rebind<RB_node<Key, T> >::other	allocator_type;
		typedef RB_node<Key, T> node;
		typedef typename	allocator_type::reference		reference;
		typedef typename	allocator_type::const_reference	const_reference;
		typedef typename	allocator_type::pointer    		pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;
		typedef				size_t  						size_type;
		typedef				ptrdiff_t						difference_type;
		typedef 			RBT_iterator<node>				iterator;

	private:
		node* root;
		allocator_type _alloc;
		key_compare _k_comp;

		node* create_root(const value_type& val, node* parent, bool red = true) {
			node *res = _alloc.allocate(1);
			_alloc.construct(res, val);
			res->parent = parent;
			res->is_red = red;
			create_null_leafs(res);

			return res;
		}

		void create_null_leafs(node* parent) {
			if (!parent->left) {
				parent->left = _alloc.allocate(1);
				_alloc.construct(parent->left, parent);
			}
			if (!parent->right){
				parent->right = _alloc.allocate(1);
				_alloc.construct(parent->right, parent);
			}
		}

		/*
		void left_turn(node* child) {
			node* grandfather = child->parent->parent;
			child->is_red = false;
			child->parent->is_red = true;
			if (!grandfather)
				root = child;
			else if (grandfather->left == child->parent)
				grandfather->left = child;
			else
				grandfather->right = child;
			child->parent->right = child->left;
			child->left->parent = child->parent;
			child->left = child->parent;
			child->parent->parent = child;
			child->parent = grandfather;
		}

		void right_turn(node* child) {
			node* grandfather = child->parent->parent;
			child->is_red = false;
			child->parent->is_red = true;
			if (!grandfather)
				root = child;
			else if (grandfather->left == child->parent)
				grandfather->left = child;
			else
				grandfather->right = child;
			child->parent->left = child->right;
			child->right->parent = child->parent;
			child->right = child->parent;
			child->parent->parent = child;
			child->parent = grandfather;
		}
		 */



		void left_right_rotation(node* cur) {
			std::cout << "lrr" << std::endl;
			if (cur->get_gparent_node() == root)
				root = cur;
			node* cur_tmp_left = cur->left;
			node* cur_tmp_right = cur->right;
			node* tmp_par = cur->get_gparent_node(); //simplify without var
			if (tmp_par->parent) {
				if (tmp_par->parent->left == tmp_par)
					tmp_par->parent->left = cur;
				else if (tmp_par->parent->right == tmp_par)
					tmp_par->parent->right = cur;
			}

			cur->left = cur->parent;
			cur->left->right = cur_tmp_right;
			cur->left->right = cur->left->right->parent = cur->left;
			cur->left->parent = cur;

			cur->right = tmp_par;
			cur->right->left = cur_tmp_left; //leaf
			cur->right->left->parent = cur->right; //leaf
			cur->parent = tmp_par->parent;

			cur->right->parent = cur;
			cur->is_red = false;
			cur->left->is_red = true;
			cur->right->is_red = true;
		}




		void color_swap(node* current) {
			std::cout << "color swap" << std::endl;
			current->left->is_red = false;
			current->right->is_red = false;
			if (current != root)
				current->is_red = true;

		}
	public:
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : root(null_pointer),
					  _alloc(alloc), _k_comp(comp) {}
		~map() {}

		void balance(node *current) {
			while (current) {
				//if (current->get_gparent_node() && current->get_aunt_node()->is_red && current->is_red && current->parent->is_red)
				//	color_swap(current->get_gparent_node());
				if ((current->get_gparent_node()) && (current->is_red && current->parent->left == current)
						&& (current->parent->is_red && current->get_gparent_node()->left == current->parent))
					current->right_rotation(&root); //FIXME maybe need to return new pointer to update current;
				else if ((current->get_gparent_node()) && (current->is_red && current->parent->right == current)
					    && (current->parent->is_red && current->get_gparent_node()->left == current->parent)
						&& (!current->parent->left->is_red))
					current->left_right_rotation(&root);
				else if ((current->get_gparent_node()) && (current->is_red && current->parent->right == current)
				        && (current->parent->is_red && current->get_gparent_node()->right == current->parent))
					current->left_rotation(&root);
				else if ((current->get_gparent_node()) && (current->is_red && current->parent->left == current)
				        && (current->parent->is_red && current->get_gparent_node()->right == current->parent)
				        && (!current->parent->right->is_red))
					current->right_left_rotation(&root);
				current = current->parent;
			}
		}


		void insert(const value_type& val) {
			node tmp(val);
			if (!root) { root = create_root(val, null_pointer, false); return; }
			node *current = root;
			while (true) {
				if (val.first < current->node_data.first) {
					if (!current->left->is_nullLeaf()) { current = current->left; continue; }
					else {
						*(current->left) = tmp;
						create_null_leafs(current->left);
						balance(current->left);
						break; }
				}
				if (!current->right->is_nullLeaf()) { current = current->right; continue; }
				*(current->right) = tmp;
				create_null_leafs(current->right);
				balance(current->right);
				break;
			}
		}

		iterator begin(){
			node* tmp = root;
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return iterator(tmp);
		}

		iterator end(){
			node* tmp = root;
			while (tmp->right)
				tmp = tmp->right;
			return iterator(tmp);
		}



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
	};

}

#endif //CONTAINERS_MAP_HPP
