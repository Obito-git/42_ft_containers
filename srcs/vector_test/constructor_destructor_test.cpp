//
// Created by amyroshn on 19/06/22.
//
#include "ft_containers_test.hpp"

using namespace ft;

void fill_and_copy_constructor() {
	vector<LeakTest> b(1000, 42);
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
	test_vector_print(b);
	vector<int>a;
	test_vector_print(a);
	vector<vector<LeakTest> > c;
	std::cout << "size " << c.size() << " capacity " << c.capacity() << std::endl;
}

void fill_range_constructor_and_assign_operator() {
	vector<int> a(1000);
	for (int i = 0; i < 1000; i++)
		a.push_back(i);
	vector<int> tested(a.begin() + 111, a.begin() + 777);
	test_vector_print(tested);
	vector<int> tested2(a.begin(), a.begin());
	test_vector_print(tested2);
	vector<int> tested3(a.end(), a.end());
	test_vector_print(tested3);
	vector<int> tested4(a.begin(), a.end());
	test_vector_print(tested4);
	vector<LeakTest> l(1000, 42);
	vector<LeakTest> tested5 = l;
	vector<int> tested6;
	vector<int> tested7;
	vector<int> tested8;
	tested6 = tested;
	tested7 = tested2;
	tested8 = tested3;
	test_vector_print(l);
	test_vector_print(tested6);
	test_vector_print(tested7);
	test_vector_print(tested8);
}

void constructor_destructor_test() {
	default_constructor();
	fill_and_copy_constructor();
	fill_range_constructor_and_assign_operator();
	/*
	time_t now = time(0);
	char* dt = ctime(&now);
	std::cout << "The local date and time is: " << dt << std::endl;
	 */
}