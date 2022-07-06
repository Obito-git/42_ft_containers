//
// Created by Anton on 20/06/2022.
//

#ifndef CONTAINERS_PAIR_HPP
#define CONTAINERS_PAIR_HPP
namespace ft {
	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		/*	default constructor *
		* Constructs a pair object with its elements value-initialized.*/
		pair() :first(), second() {}

		/*	copy / move constructor (and implicit conversion) *
		* The object is initialized with the contents of the pr pair object.
		* The corresponding member of pr is passed to the constructor of each of its members.*/
		template<class U, class V>
		pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}

		/*	initialization constructor *
		* Member first is constructed with a and member second with b.*/
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr) {
			if (&pr != this) {
				first = pr.first;
				second = pr.second;
			}
			return *this;
		}

	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return ( pair<T1,T2>(x,y) );
	}

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }
}

#endif //CONTAINERS_PAIR_HPP
