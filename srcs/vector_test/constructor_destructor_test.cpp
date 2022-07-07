//
// Created by amyroshn on 19/06/22.
//
#include "../../inc/ft_containers_test.hpp"

using namespace ft;

void fill_and_copy_constructor() {
	vector<LeakTest> b(100, 42);
	print_vector_size(b);
	vector<int>a;
	print_vector(a);
	vector<vector<LeakTest> > c(1000, b);
	vector<LeakTest> bb(b);
	print_vector(bb);
	vector<int>aa(a);
	print_vector(aa);
	vector<vector<LeakTest> > cc(c);
}

void default_constructor() {
	vector<LeakTest> b;
	print_vector(b);
	vector<int>a;
	print_vector(a);
	vector<vector<LeakTest> > c;
	std::cout << "size " << c.size() << " capacity " << c.capacity() << std::endl;
}

void fill_range_constructor_and_assign_operator() {
	vector<int> a(500);
	for (int i = 0; i < 500; i++)
		a.push_back(i);
	vector<int> tested(a.begin() + 111, a.begin() + 333);
	print_vector(tested);
	vector<int> tested2(a.begin(), a.begin());
	print_vector(tested2);
	vector<int> tested3(a.end(), a.end());
	print_vector(tested3);
	vector<int> tested4(a.begin(), a.end());
	print_vector(tested4);
	vector<LeakTest> l(1000, 42);
	vector<LeakTest> tested5 = l;
	vector<int> tested6;
	vector<int> tested7;
	vector<int> tested8;
	tested6 = tested;
	tested7 = tested2;
	tested8 = tested3;
	print_vector(l);
	print_vector(tested6);
	print_vector(tested7);
	print_vector(tested8);
}

void constructor_destructor_test() {
	default_constructor();
	fill_and_copy_constructor();
	fill_range_constructor_and_assign_operator();
}