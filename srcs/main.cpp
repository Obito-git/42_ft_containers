#include "vector.hpp"
#include <vector>
#include <iostream>
#include <string>

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

int main() {
	ft::vector<std::string> test(10, "1");
	test.resize(5);
	test.resize(10, "2");
	for (int i = 0; i < 10; i++)
		std::cout << test[i] << std::endl;
	std::vector<int> a(10);
	a.resize(21);
	std::cout << a.capacity() << std::endl;
}