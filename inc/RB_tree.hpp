//
// Created by Anton on 22/06/2022.
//

#ifndef CONTAINERS_RB_TREE_HPP
#define CONTAINERS_RB_TREE_HPP

#include <ostream>
#include "pair.hpp"
#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */

namespace ft {
	template<class Key, class T>
	struct RB_node {
		typedef ft::pair<Key, T> value_type;
		typedef void (*child_alloc)(RB_node *);

		value_type	node_data;
		RB_node*	left;
		RB_node*	right;
		RB_node*	parent;
		bool		is_red;

		RB_node(RB_node* par): left(null_pointer), right(null_pointer), parent(par), is_red(false) {}
		RB_node(const pair<Key, T> &nodeData) : node_data(nodeData), left(null_pointer),
												right(null_pointer), parent(null_pointer),
												is_red(true) {}

		RB_node& operator=(const RB_node& other) {
			if (this != &other) {
				node_data = other.node_data;
				is_red = true;
			}
			return *this;
		}


		RB_node* get_gparent_node() {
			if (!parent)
				return null_pointer;
			return parent->parent;
		}
		RB_node* get_aunt_node() {
			if (!get_gparent_node())
				return null_pointer;
			if (get_gparent_node()->right == parent)
				return get_gparent_node()->left;
			return get_gparent_node()->right;
		}

		Key &key() { return node_data.first; }

		T &val() { return node_data.second; }

		bool is_nullLeaf() const {
			return (!left && !right && !is_red);
		}

		friend std::ostream &operator<<(std::ostream &os, const RB_node &node) {
			if (node.is_nullLeaf())
				return os;
			else {
				os << (node.is_red ? RED : BOLDCYAN);
				os << "((K:[" << node.node_data.first << "]" << " P:[";
				if (node.parent)
					os << node.parent->node_data.first;
				else
					os << "ROOT";
				os << "]))"RESET;
			}
			return os;
		}

	};
}
#endif //CONTAINERS_RB_TREE_HPP
