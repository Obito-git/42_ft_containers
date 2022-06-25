//
// Created by Anton on 11/06/2022.
//

#ifndef CONTAINERS_RBT_ITERATOR_HPP
#define CONTAINERS_RBT_ITERATOR_HPP
#include "iterator.hpp"

//https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html

namespace ft {
	template <typename T>
	class RBT_iterator : public iterator<ft::bidirectional_iterator_tag, T> {
	public:
		typedef typename	ft::iterator<bidirectional_iterator_tag, T>						iterator_category;
		typedef typename	ft::iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef	typename 	T::value_type&														value_reference;
		typedef typename	T::value_type*											value_pointer;
		typedef T* pointer;
		//FIXME ??????????????? const ref??

		/* Is default-constructible, copy-constructible, copy-assignable and destructible */
		RBT_iterator() : _ptr(null_pointer) {}
		RBT_iterator(const RBT_iterator& other) {
			_ptr = other._ptr;
		}
		RBT_iterator(pointer ptr): _ptr(ptr) {}
		RBT_iterator &operator=(const RBT_iterator<T>& other) {
				 if (this == &other) { return *this; }
				 _ptr = other._ptr;
				 return *this;
		}
		virtual ~RBT_iterator() {}

	private:
		pointer get_root() const {
			pointer tmp = _ptr;
			while (tmp->parent)
				tmp = tmp->parent;
			return tmp;
		}

		pointer get_last_nullLeaf() const {
			pointer tmp = get_root();
			while (tmp->right)
				tmp = tmp->right;
			return (tmp);
		}
	public:

		/*************************** CONSTANT MEMBER FUNCTION ************************************/

		/* equality operators */
		bool operator==(const RBT_iterator &other) const { return _ptr == other._ptr; }
		bool operator!=(const RBT_iterator &other) const { return _ptr != other._ptr; }

		/* dereferences */
		//const_reference operator*() const { return *_ptr; }

		/* increment / decrement */
		RBT_iterator& operator++() {
			pointer p;
			/*
			if (_ptr->is_nullLeaf())
			{
				// ++ from end(). get the root of the tree
				_ptr = tree->root;

				// error! ++ requested for an empty tree
				if (nodePtr == nullptr)
					throw UnderflowException { };

				// move to the smallest value in the tree,
				// which is the first node inorder
				while (nodePtr->left != nullptr) {
					nodePtr = nodePtr->left;
				}
			}
			else {
			 */
				if (!_ptr->right->is_nullLeaf()) {
					// successor is the farthest left node of
					// right subtree
					_ptr = _ptr->right;
					while (!_ptr->left->is_nullLeaf()) {
						_ptr = _ptr->left;
					}
				} else {
					if (_ptr->right == get_last_nullLeaf()) {
						_ptr = _ptr->right;
						return *this;
					}
					// have already processed the left subtree, and
					// there is no right subtree. move up the tree,
					// looking for a parent for which nodePtr is a left child,
					// stopping if the parent becomes NULL. a non-NULL parent
					// is the successor. if parent is NULL, the original node
					// was the last node inorder, and its successor
					// is the end of the list
					p = _ptr->parent;
					while (p && !p->is_nullLeaf() && _ptr == p->right) {
						_ptr = p;
						p = p->parent;
					}
					// if we were previously at the right-most node in
					// the tree, nodePtr = nullptr, and the iterator specifies
					// the end of the list
					_ptr = p;
				}
			//}
			return *this;
		}

		RBT_iterator operator++(int) { RBT_iterator old(*this); _ptr++; return old; }
		RBT_iterator& operator--() { _ptr--; return *this; }
		RBT_iterator operator--(int) { RBT_iterator old(*this); _ptr--; return old; }

		/* arithmetic operators +- */
		RBT_iterator operator+(difference_type n) const { return _ptr + n; }
		RBT_iterator operator-(difference_type other) const { return _ptr - other; }

		/* the offset dereference operator */
		//const_reference operator[](difference_type pos) const {return *(_ptr + pos); }
		/*********************************** MEMBER FUNCTION *********************************************/

		value_reference operator[](difference_type pos) {return *(_ptr + pos); }
		//FIXME
		value_reference operator*() const { return _ptr->node_data; }
		value_pointer operator->() { return (&_ptr->node_data); }


		/* convertion from const */
		operator RBT_iterator<const T>() const {
			return (RBT_iterator<const T>)(this->_ptr);
		}
	private:
		pointer _ptr;
	};

	/*********************************** NOT MEMBER FUNCTION *********************************************/


	template <typename T>
	RBT_iterator<T> operator+(typename RBT_iterator<T>::difference_type n,
			const RBT_iterator<T>& other) {
		return other + n;
	}
	template <typename T1, typename T2>
	typename RBT_iterator<T1>::difference_type operator-(const ft::RBT_iterator<T1>& a,
			const RBT_iterator<T2>& b) {
		return &*a - &*b;
	}
	/* equality and relational operators */
	template <typename T1, typename T2>
	bool operator==(const RBT_iterator<T1>& a, const RBT_iterator<T2>& b) {
		return &*a == &*b;
	}

	template <typename T1, typename T2>
	bool operator!=(const RBT_iterator<T1>& a, const RBT_iterator<T2>& b) {
		return &*a != &*b;
	}

}

#endif //CONTAINERS_RBT_ITERATOR_HPP
