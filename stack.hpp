//
// Created by Anton on 21/06/2022.
//

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP
#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> > class stack {
		/***************************** TYPEDEFS *********************************/
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	protected:
		container_type c;
	public:
		/*	Construct stack *
		* Constructs a stack container adaptor object. */
		explicit stack (const container_type& ctnr = container_type()): c(ctnr){}

		/*********************************** Member functions *********************************************/
		/*	Test whether container is empty *
		* Returns whether the stack is empty: i.e. whether its size is zero.
		* This member function effectively calls member empty of the underlying container object. */
	public:
		bool empty() const {
			return c.empty();
		}

		/*	Return size *
		* Returns the number of elements in the stack.
		* This member function effectively calls member size of the underlying container object.*/
	public:
		size_type size() const {
			return c.size();
		}

		/*	Access next element *
		* Returns a reference to the top element in the stack.
		* Since stacks are last-in first-out containers, the top element is the last element inserted into the stack. */
	public:
		value_type& top() {
			return c.back();
		}

		const value_type& top() const {
			return c.back();
		}

		/*	Insert element *
		* Inserts a new element at the top of the stack, above its current top element.
		* The content of this new element is initialized to a copy of val. */
	public:
		void push(const value_type& val) {
			c.push_back(val);
		}

		/*	Remove top element *
		* Removes the element on top of the stack, effectively reducing its size by one.
		* The element removed is the latest element inserted into the stack,
		* whose value can be retrieved by calling member stack::top. */
	public:
		void pop() {
			c.pop_back();
		}

		/******************************* Relational Operators *************************************/

		friend bool operator ==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c == rhs.c);
		}

		friend bool operator >(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c > rhs.c;
		}

		friend bool operator !=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c != rhs.c;
		}

		friend bool operator <(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c < rhs.c;
		}

		friend bool operator <=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c <= rhs.c;
		}

		friend bool operator >=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c >= rhs.c;
		}
	};



}

#endif //CONTAINERS_STACK_HPP
