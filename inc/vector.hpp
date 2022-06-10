//
// Created by Anton on 09/06/2022.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP
#include "temp.hpp"
#include <iostream>
#include <memory>

namespace ft {
	template<typename T, class Alloc = std::allocator<T> >
	class vector {
	public:
		/******************** TYPEDEFS ***********************************/
		typedef				T								value_type;
		typedef				Alloc							allocator_type;
		typedef typename	allocator_type::reference		reference;
		typedef typename	allocator_type::const_reference	const_reference;
		typedef typename	allocator_type::pointer    		pointer;
		typedef typename	allocator_type::const_pointer	const_pointer;
		typedef				size_t  						size_type;
		typedef				ptrdiff_t						difference_type;

	private:
		pointer         _data;
		allocator_type  _alloc;
		size_type       _size;
		size_type       _capacity;
	public:
		/********************* CONSTRUCTORS ******************************/
		/* Default *
		Empty container constructor (default constructor)
		Constructs an empty container, with no elements. */
		explicit vector (const allocator_type& alloc = allocator_type()) :  _data(NULL), _alloc(alloc),
																			_size(0), _capacity(0) {}

		/* Fill constructor *
		Constructs a container with n elements. Each element is a copy of val. */
		explicit vector (size_type n, const value_type& val = value_type(),
		                 const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n) {
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _capacity; i++)
				_alloc.construct((_data + i), val);
		}

		/* Range constructor *
		Constructs a container with as many elements as the range [first,last),
		with each element constructed from its corresponding element in that range, in the same order. */
//		template <class InputIterator>
//		vector (InputIterator first, InputIterator last,
//		        const allocator_type& alloc = allocator_type());
		/* Copy constructor *
		Constructs a container with a copy of each of the elements in x, in the same order. */
		vector (const vector& x): _alloc(x._alloc), _size(x._size), _capacity(x._capacity) {
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _capacity; i++)
				_alloc.construct((_data + i), *(x._data + i));
		}

		/*  Vector destructor *
		* This destroys all container elements, and deallocates all the storage capacity allocated
		* by the vector using its allocator. */
		virtual ~vector() {
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
		}

		/********************* Member functions ***************************/

		/********
		 ********	CAPACITY:
		 ********/

		/*  Return size *
		* Returns the number of elements in the vector.
		* This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity. */
		size_type size() const {
			return _size;
		}

		/*  Return maximum size *
		* Returns the maximum number of elements that the vector can hold.
		* This is the maximum potential size the container can reach due to known system or library implementation limitations,
		* but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate
		* storage at any point before that size is reached.*/
		size_type max_size() {
			return _alloc.max_size();
		}

		/*  Change size *
		* Resizes the container so that it contains n elements.
		*	If n is smaller than the current container size, the content is reduced to its first n elements,
		* removing those beyond (and destroying them).
		*	If n is greater than the current container size, the content is expanded by inserting at the end as many
		* elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val,
		* otherwise, they are value-initialized.
		*	If n is also greater than the current container capacity,
		* an automatic reallocation of the allocated storage space takes place.
		* Notice that this function changes the actual content of the container by inserting or erasing elements from it. */
		void resize (size_type n, value_type val = value_type()) {
			for (; _size > n; _size--) { _alloc.destroy(&_data[_size - 1]); }
			for (; _size < n && n <= _capacity; _size++) { _alloc.construct(&_data[_size]); _data[_size] = val; } //need tests
			if (n > _capacity) {
				reallocate(n > _capacity * 2 ? n : _capacity * 2);
				while (_size <= n) { _alloc.construct(&_data[_size++], val); }
				_size = n;
			}
		}

		/* Return size of allocated storage capacity *
		Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space
		allowing to accommodate for growth without the need to reallocate on each insertion.*/
		size_type capacity() const {
			return _capacity;
		}

		/*  Test whether vector is empty *
		 * Returns whether the vector is empty (i.e. whether its size is 0). */
		bool empty() const {
			return _size == 0;
		}

		/*  Request a change in capacity *
		* Requests that the vector capacity be at least enough to contain n elements.
		*   If n is greater than the current vector capacity, the function causes the container
		* to reallocate its storage increasing its capacity to n (or greater).
		*   In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
		* This function has no effect on the vector size and cannot alter its elements.*/
		void reserve (size_type n) {
			if (n > max_size()) { throw std::length_error("Requested new size is greater than max size"); }
			if (n > _capacity) { reallocate(n); }
		}

		//custom member function
		void reallocate(size_type new_capacity) {
			pointer tmp = _alloc.allocate(new_capacity);
			for (size_type i = 0; i < _size; i++) { tmp[i] = _data[i]; }
			_alloc.deallocate(_data, _capacity);
			_capacity = new_capacity;
			_data = tmp;
		}

		/********
		 ********	ELEMENT ACCESS:
		 ********/

		/*  Access element *
		* Returns a reference to the element at position n in the vector container.
		* A similar member function, vector::at, has the same behavior as this operator function,
		* except that vector::at is bound-checked and signals if the requested position is out of range
		* by throwing an out_of_range exception.
		*   Portable programs should never call this function with an argument n
		* that is out of range, since this causes undefined behavior.*/
		reference operator[](size_type n) {
			return _data[n];
		}
		const_reference operator[](size_type n) const {
			return _data[n];
		}

		/*  Access element *
		* Returns a reference to the element at position n in the vector.
		* The function automatically checks whether n is within the bounds of valid elements in the vector,
		* throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
		* This is in contrast with member operator[], that does not check against bounds.*/
		reference at (size_type n) {
			if (n >= _size) { throw std::out_of_range("Out of array's bound"); }
			return (_data[n]);
		}
		const_reference at (size_type n) const {
			if (n >= _size) { throw std::out_of_range("Out of array's bound"); }
			return (_data[n]);
		}

		/*  Access first element *
		* Returns a reference to the first element in the vector.
		* Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
		* Calling this function on an empty container causes undefined behavior.*/
		reference front() {
			return _data[0];
		}
		const_reference front() const {
			return _data[0];
		}

		/*  Access last element *
		* Returns a reference to the last element in the vector.
		* Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
		* Calling this function on an empty container causes undefined behavior.*/
		reference back() {
			return _data[_size - 1];
		}
		const_reference back() const {
			return _data[_size - 1];
		}


	};
}

#endif //CONTAINERS_VECTOR_HPP
