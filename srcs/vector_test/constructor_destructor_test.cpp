//
// Created by amyroshn on 19/06/22.
//
#include "ft_containers_test.hpp"

using namespace ft;

void fill_and_copy_constructor() {
	vector<LeakTest> b(500, 42);
	test_vector_print(b);
	vector<int>a(500);
	test_vector_print(a);
	vector<vector<LeakTest> > c(3000, b);
	std::cout << "size " << c.size() << " capacity " << c.capacity() << std::endl;
	vector<LeakTest> bb(b);
	test_vector_print(bb);
	vector<int>aa(a);
	test_vector_print(aa);
	vector<vector<LeakTest> > cc(c);
	std::cout << "size " << cc.size() << " capacity " << cc.capacity() << std::endl;

}

void default_constructor() {
	vector<LeakTest> b;
	std::cout << "size " << b.size() << " capacity " << b.capacity() << std::endl;
	vector<int>a;
	std::cout << "size " << a.size() << " capacity " << a.capacity() << std::endl;
	vector<vector<LeakTest> > c;
	std::cout << "size " << c.size() << " capacity " << c.capacity() << std::endl;
}
#include <ctime>

void constructor_destructor_test() {
	default_constructor();
	fill_and_copy_constructor();
	/*
	time_t now = time(0);
	char* dt = ctime(&now);
	std::cout << "The local date and time is: " << dt << std::endl;
	 */
}