#include <vector>
#include <iostream>
#include <string>
#include "containers/vector.hpp"

class Test {
public:
	int i;
	int *a;
	Test() {
		a = new int;
	}
	Test(const Test& t) {
		std::cout << "cpy" << std::endl;
		a = new int;
		(void) t;
	}
	Test(int ii) : i(ii){
		std::cout << "const" << std::endl;
		a = new int;
	}

	virtual ~Test() {
		std::cout << "dest" << std::endl;
		delete a;
	}
};

class foo;
class bar;

template<class T>
struct is_bar
{
	template<class Q>
	typename ft::enable_if<std::is_same<Q, bar>::value>::type check()
	{
		return true;
	}

	template<class Q>
	typename ft::enable_if<!std::is_same<Q, bar>::value>::type check()
	{
		return false;
	}
};

int main()
{
	is_bar<foo> foo_is_bar;
	is_bar<bar> bar_is_bar;
	if (!foo_is_bar.check() && bar_is_bar.check())
		std::cout << "It works!" << std::endl;

	return 0;
}