//
// Created by Anton on 09/06/2022.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP
#include <memory>
#include <stdexcept>
#include "inc/utils/utils.hpp"
#include "inc/iterator/random_access_iterator.hpp"
#include "inc/iterator/reverse_iterator.hpp"
#include "inc/utils/algorithm.hpp"


namespace ft {
	template<typename T, class Alloc = std::allocator<T> >
	class vector {
	public:
		/***************************** TYPEDEFS *********************************/
		typedef				T									value_type;
		typedef				Alloc								allocator_type;
		typedef typename	allocator_type::reference			reference;
		typedef typename	allocator_type::const_reference		const_reference;
		typedef typename	allocator_type::pointer    			pointer;
		typedef typename	allocator_type::const_pointer		const_pointer;
		typedef				size_t  							size_type;
		typedef				ptrdiff_t							difference_type;

		typedef	ft::random_access_iterator<value_type>			iterator;
		typedef	ft::random_access_iterator<const value_type>	const_iterator;
		typedef	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

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
		explicit vector (const allocator_type& alloc = allocator_type()) :  _alloc(alloc), _size(0), _capacity(0) {
			_data = _alloc.allocate(_capacity);
		}

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
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0):
				_data(null_pointer), _alloc(alloc), _size(0), _capacity(0) {
			assign(first, last);
		}

		/* Copy constructor *
		Constructs a container with a copy of each of the elements in x, in the same order. */
		vector (const vector& x): _data(null_pointer), _alloc(x._alloc), _size(0), _capacity(0) {
			this->insert(this->begin(), x.begin(), x.end());
		}

		/*	Assigment operator overloading */
		vector& operator=(const vector& x) {
			if (this != &x) {
				clear();
				insert(begin(), x.begin(), x.end());
			}
			return *this;
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
	public:
		size_type size() const {
			return _size;
		}

		/*  Return maximum size *
		* Returns the maximum number of elements that the vector can hold.
		* This is the maximum potential size the container can reach due to known system or library implementation limitations,
		* but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate
		* storage at any point before that size is reached.*/
	public:
		size_type max_size () const {
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
	public:
		void resize (size_type n, value_type val = value_type()) {
			for (; _size > n; _size--) { _alloc.destroy(&_data[_size - 1]); }
			for (; _size < n && n <= _capacity; _size++) { _alloc.construct(&_data[_size], val); }
			if (n > capacity()) {
				reserve(n > capacity() * 2 ? n : capacity() * 2);
				for(; _size < n; _size++) { _alloc.construct(_data + _size, val); }
				_size = n ;
			}
		}

		/* Return size of allocated storage capacity *
		Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space
		allowing to accommodate for growth without the need to reallocate on each insertion.*/
	public:
		size_type capacity() const {
			return _capacity;
		}

		/*  Test whether vector is empty *
		 * Returns whether the vector is empty (i.e. whether its size is 0). */
	public:
		bool empty() const {
			return _size == 0;
		}

		/*  Request a change in capacity *
		* Requests that the vector capacity be at least enough to contain n elements.
		*   If n is greater than the current vector capacity, the function causes the container
		* to reallocate its storage increasing its capacity to n (or greater).
		*   In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
		* This function has no effect on the vector size and cannot alter its elements.*/
	public:
		void reserve (size_type n) {
			if (n + _capacity > max_size()) { throw std::length_error("vector::reserve"); }
			if (n > capacity()) {
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size && i < n; i++) { _alloc.construct(tmp + i, _data[i]); }
				this->~vector();
				_capacity = n;
				_data = tmp;
			}
		}

		/*	Reserve memory, but not saving old content */
	private:
		void reserve_cleanly (size_type n) {
			if (n > max_size()) { throw std::length_error("vector::reserve"); }
			if (n > capacity()) {
				pointer tmp = _alloc.allocate(n);
				clear();
				_alloc.deallocate(_data, _capacity);
				_capacity = n;
				_data = tmp;
			}
		}

	public:
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
	public:
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
	public:
		reference at (size_type n) {
			if (n >= size()) { throw std::out_of_range("Out of array's bound"); }
			return (_data[n]);
		}
		const_reference at (size_type n) const {
			if (n >= size()) { throw std::out_of_range("Out of array's bound"); }
			return (_data[n]);
		}

		/*  Access first element *
		* Returns a reference to the first element in the vector.
		* Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
		* Calling this function on an empty container causes undefined behavior.*/
	public:
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
	public:
		reference back() {
			return _data[_size - 1];
		}
		const_reference back() const {
			return _data[_size - 1];		}

		/********
		 ********	MODIFIERS:
		 ********/

		/*  Assign vector content *
		* Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		*   The new contents are elements constructed from each of the elements
		* in the range between first and last, in the same order.*/
	public:
		//random access iterator version, guarantees that size will be checked before change vector
		void assign (iterator first, iterator last){
			if (last < first)
				throw std::length_error("Vector range constructor iterator error");
			size_type n = last - first;
			if (n > capacity())
				reserve_cleanly(n);
			clear();
			while (first != last)
				push_back(*first++);
		}

	public:
		/*	If InputIterator is not at least of a forward iterator category
		* (i.e., it is just an input iterator) the new capacity cannot be determined beforehand and the operation
		* incurs in additional logarithmic complexity in the new size*/
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			clear();
			while (first != last)
				push_back(*first++);
		}

	public:
		/*  The new contents are n elements, each initialized to a copy of val. */
		void assign (size_type n, const value_type& val) {
			if (n > capacity())
				reserve(n);
			clear();
			while (_size < n) { _alloc.construct(&_data[_size++], val) ;}
		}

		/*  Add element at the end *
		*   Adds a new element at the end of the vector, after its current last element.
		* The content of val is copied (or moved) to the new element.
		* This effectively increases the container size by one, which causes an automatic reallocation of the
		* allocated storage space if -and only if- the new vector size surpasses the current vector capacity.*/
	public:
		void push_back (const value_type& val) {
			if (_size == _capacity) { _capacity ? reserve(_capacity * 2) : reserve(1) ;}
			_alloc.construct(_data + _size, val);
			_size++;
		}

		/*  Delete last element. *
		* Removes the last element in the vector, effectively reducing the container size by one.
		* This destroys the removed element.*/
	public:
		void pop_back() {
			_alloc.destroy(&back());
			_size--;
		}

		/*	Insert elements *
		* The vector is extended by inserting new elements before the element at the specified position,
		* effectively increasing the container size by the number of elements inserted.
		* This causes an automatic reallocation of the allocated storage space if -and only if-
		* the new vector size surpasses the current vector capacity. */

		/*	single element */
	public:
		iterator insert (iterator position, const value_type& val) {
			difference_type ind = position - begin();
			insert(position, 1, val);
			return _data + ind;
		}

		/* fill */
	public:
		void insert (iterator position, size_type n, const value_type& val) {
			size_type start_pos = position - begin();
			// not using reserve for not iterate 2 times on data
			pointer tmp_data;
			size_type copied_elem = 0;
			if (_size + n > _capacity)
			{
				if (_size + n > _size * 2)
					_capacity = _size + n;
				else if (_capacity == 0)
					_capacity = 1;
				else
					_capacity = _size * 2;
			}
			tmp_data = _alloc.allocate(_capacity);
			for (; copied_elem < start_pos; copied_elem++)
				_alloc.construct(tmp_data + copied_elem, _data[copied_elem]);
			for (; copied_elem - start_pos < n; copied_elem++)
				_alloc.construct(tmp_data + copied_elem, val);
			for (; copied_elem < _size + n; copied_elem++)
				_alloc.construct(tmp_data + copied_elem, _data[copied_elem - n]);
			this->~vector();
			_data = tmp_data;
			_size += n;
		}

		/* range (3) for random_access_operator */
	public:
		void insert(iterator position, iterator first, iterator last) {
			size_type start_pos = position - begin();
			size_type n = last - first;
			if (n + _capacity > max_size()) { throw std::length_error("vector::reserve"); }
			pointer tmp_data;
			size_type copied_elem = 0;
			size_type new_capacity = _capacity;
			if (_size + n > _capacity)
			{
				if (_size + n > _size * 2)
					new_capacity = _size + n;
				else if (_size == 0)
					new_capacity = 1;
				else
					new_capacity *= 2;
			}
			tmp_data = _alloc.allocate(new_capacity);
			for (; copied_elem < start_pos; copied_elem++)
				_alloc.construct(tmp_data + copied_elem, _data[copied_elem]);
			for (iterator it = first; it != last; it++, copied_elem++)
				_alloc.construct(tmp_data + copied_elem, *it);
			for (; copied_elem < _size + n; copied_elem++)
				_alloc.construct(tmp_data + copied_elem, _data[copied_elem - n]);
			this->~vector();
			_capacity = new_capacity;
			_data = tmp_data;
			_size += n;
		}

		/* range (3) for all iterators type, can't guarantee that they are enough memory for all elements  */
	public:
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
			vector tmp;
			for (; first != last; first++)
				tmp.push_back(*first);
			insert(position, tmp.begin(), tmp.end());
		}

		/*	Erase elements *
		* Removes from the vector either a single element (position) or a range of elements ([first,last)).
		* This effectively reduces the container size by the number of elements removed, which are destroyed.*/
	public:
		iterator erase (iterator position) {
			return erase(position, position + 1);
		}

	public:
		iterator erase (iterator first, iterator last) {
			if (last - first == static_cast<difference_type>(size())) { clear(); return begin(); }
			int first_pos = first - begin();
			size_type elem_to_del = size() - (last - first);
			size_type i;
			for (i = 0; (last + i) != end(); i++, first++) {
				*first = *(last + i);
			};
			while (size() > elem_to_del)
				pop_back();
			return (_data + first_pos);
		}

		/*	Swap content *
		* Exchanges the content of the container by the content of x, which is another vector object of the same type.
		* Sizes may differ.*/
	public:
		void swap (vector<T, Alloc>& x) {
			allocator_type tmp_alloc = _alloc;
			pointer tmp_data = _data;
			size_type tmp_size = _size;
			size_type tmp_capac = _capacity;

			_alloc = x._alloc;
			_data = x._data;
			_size = x._size;
			_capacity = x._capacity;

			x._alloc = tmp_alloc;
			x._data = tmp_data;
			x._size = tmp_size;
			x._capacity = tmp_capac;
		}

		/* Clear content	*
		* Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		* A reallocation is not guaranteed to happen. */
	public:
		void clear() {
			while (!empty()) { pop_back(); }
		}

		/**************************************** ALLOCATOR ************************************************/
	public:
		/*	Get allocator *
		* Returns a copy of the allocator object associated with the vector. */
		allocator_type get_allocator() const {
			return _alloc;
		}

		/*************************************** ITERATORS *************************************************/

		/*	Return iterator to beginning
		* Returns an iterator pointing to the first element in the vector.
		* Notice that, unlike member vector::front, which returns a reference to the first element,
		* this function returns a random access iterator pointing to it.*/
	public:
		iterator begin() {return _data;}
		const_iterator begin() const { return _data; }

		/*	Return iterator to end
		* Returns an iterator referring to the past-the-end element in the vector container. */
	public:
		iterator end() {return _data + _size; }
		const_iterator end() const { return _data + _size; }

		/*	Return reverse iterator to reverse beginning
		* Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning). */
	public:
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

		/*	Return reverse iterator to reverse end
		* Returns a reverse iterator pointing to the theoretical element preceding
		* the first element in the vector (which is considered its reverse end).*/
	public:
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	};

	/*	The equality comparison (operator==) is performed by first comparing sizes, and if they match,
	* the elements are compared sequentially using operator==,
	* stopping at the first mismatch (as if using algorithm equal).*/
	template <class T, class Alloc>
	bool operator ==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator !=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	/*	The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare,
	* which compares the elements sequentially using operator< in a reciprocal manner
	* (i.e., checking both a<b and b<a) and stopping at the first occurrence.*/
	template <class T, class Alloc>
	bool operator <(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator <=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator >(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator >=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
	{
		x.swap(y);
	}
}

#endif //CONTAINERS_VECTOR_HPP
