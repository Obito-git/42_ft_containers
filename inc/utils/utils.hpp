//
// Created by Anton on 13/06/2022.
//

#ifndef CONTAINERS_UTILS_HPP
#define CONTAINERS_UTILS_HPP
#include "null_pointer.hpp"
#include "pair.hpp"

namespace ft {
	template <bool B>
	struct enable_if {};

	template <>
	struct enable_if<true> { typedef int type; };

	template <class T> struct is_integral { static const bool value = false; };
	template<> struct is_integral<bool> { static const bool value = true; };
	template<> struct is_integral<char> { static const bool value = true; };
	template<> struct is_integral<wchar_t> { static const bool value = true; };
	template<> struct is_integral<signed char> { static const bool value = true; };
	template<> struct is_integral<short int> { static const bool value = true; };
	template<> struct is_integral<int> { static const bool value = true; };
	template<> struct is_integral<long int> { static const bool value = true; };
	template<> struct is_integral<long long int> { static const bool value = true; };
	template<> struct is_integral<unsigned char> { static const bool value = true; };
	template<> struct is_integral<unsigned short int> { static const bool value = true; };
	template<> struct is_integral<unsigned int> { static const bool value = true; };
	template<> struct is_integral<unsigned long int> { static const bool value = true; };
	template<> struct is_integral<unsigned long long int> { static const bool value = true; };

}
#endif //CONTAINERS_UTILS_HPP
