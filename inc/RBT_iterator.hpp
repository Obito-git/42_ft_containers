//
// Created by Anton on 11/06/2022.
//

#ifndef CONTAINERS_RBT_ITERATOR_HPP
#define CONTAINERS_RBT_ITERATOR_HPP
#include "iterator.hpp"

//https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html

namespace ft {
	template <typename T, typename ValType>
	class RBT_iterator : public iterator<ft::bidirectional_iterator_tag, T> {
	public:
		typedef typename	ft::iterator<bidirectional_iterator_tag, ValType>			iterator_category;
		typedef typename	iterator_category::difference_type	difference_type;
		typedef typename 	iterator_category::value_type value_type;
		typedef typename 	iterator_category::pointer pointer;
		typedef typename 	iterator_category::reference reference;
		typedef				T														node;
		typedef				T*														node_pointer;
		//FIXME ??????????????? const ref??

		/*	Default constructor */
		RBT_iterator() : _ptr(null_pointer) {}

		/*	Copy constructor */
		RBT_iterator(const RBT_iterator& other) {
			_ptr = other._ptr;
		}

		/* Node pointer constructor */
		RBT_iterator(node_pointer ptr): _ptr(ptr) {}

		/* Copy assign operator */
		RBT_iterator &operator=(const RBT_iterator<T, ValType>& other) {
				 if (this == &other) { return *this; }
				 _ptr = other._ptr;
				 return *this;
		}

		/*	Default destructor */
		virtual ~RBT_iterator() {}

		node_pointer base() const {return _ptr;} //FIXME


		/*	Returns root pointer based of current element */
	private:
		node_pointer get_root() const {
			node_pointer tmp = _ptr;
			if (!tmp->parent)
				return tmp->right;
			while (tmp->parent && tmp->parent->parent)
				tmp = tmp->parent;
			return tmp;
		}

	private:
		/*	Returns last null leaf (right child of last element) */
		node_pointer get_last_nullLeaf() const {
			node_pointer tmp = get_root();
			while (tmp->right)
				tmp = tmp->right;
			return (tmp);
		}

	private:
		/*	Returns first null leaf (left child of left element) */
		node_pointer get_first_nullLeaf() const {
			node_pointer tmp = get_root();
			while (tmp->left)
				tmp = tmp->left;
			return (tmp);
		}

		/*************************** CONSTANT MEMBER FUNCTION ************************************/

	public:
		/* equality operators */
		bool operator==(const RBT_iterator &other) const { return _ptr == other._ptr; }
		bool operator!=(const RBT_iterator &other) const { return _ptr != other._ptr; }

		/* dereferences */
		reference operator*() const { return _ptr->node_data; }
		pointer operator->() const { return &_ptr->node_data; }

		/* increment / decrement */
		RBT_iterator& operator++() {
			node_pointer p;
			if (_ptr->right && !_ptr->right->is_nullLeaf()) {
				_ptr = _ptr->right;
				while (!_ptr->left->is_nullLeaf()) {
					_ptr = _ptr->left;
				}
			} else {
				if (_ptr == get_root()->parent || _ptr->right == get_last_nullLeaf()) {
					_ptr = get_root()->parent;
					return *this;
				}
				p = _ptr->parent;
				while (p && !p->is_nullLeaf() && _ptr == p->right) {
					_ptr = p;
					p = p->parent;
				}
				_ptr = p;
			}
			return *this;
		}

		RBT_iterator& operator--() {
			node_pointer p;
			if (_ptr == get_root()->parent) {
				_ptr = get_last_nullLeaf()->parent;
				return *this;
			}
			if (_ptr->left && !_ptr->left->is_nullLeaf()) {
				_ptr = _ptr->left;
				while (!_ptr->right->is_nullLeaf()) {
					_ptr = _ptr->right;
				}
			} else {
				if (_ptr == get_root()->parent || _ptr->left == get_first_nullLeaf()) {
					_ptr = get_root()->parent;
					return *this;
				}
				p = _ptr->parent;
				while (p && !p->is_nullLeaf() && _ptr == p->left) {
					_ptr = p;
					p = p->parent;
				}
				_ptr = p;
			}
			return *this;
		}

		RBT_iterator operator++(int) { RBT_iterator old(*this); operator++(); return old; }
		RBT_iterator operator--(int) { RBT_iterator old(*this); operator--(); return old; }

		/* const convertion */
		operator RBT_iterator<T, const ValType>() const {
			return (RBT_iterator<T, const ValType>)(this->_ptr);
		}
	private:
		node_pointer _ptr;
	};

	/*********************************** NOT MEMBER FUNCTION *********************************************/

/*
	 equality and relational operators
	template <typename T1, typename T2>
	bool operator==(const RBT_iterator<T1>& a, const RBT_iterator<T2>& b) {
		return &*a == &*b;
	}

	template <typename T1, typename T2>
	bool operator!=(const RBT_iterator<T1>& a, const RBT_iterator<T2>& b) {
		return &*a != &*b;
	}
	*/

}

#endif //CONTAINERS_RBT_ITERATOR_HPP
