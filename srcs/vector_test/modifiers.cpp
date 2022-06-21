//
// Created by Anton on 19/06/2022.
//

#include "ft_containers_test.hpp"

using namespace ft;
void erase_test() {
	vector<int> test;
	for (int i = 0; i < 100; i++)
		test.push_back(i);
	std::cout << *test.erase(test.begin(), test.begin() + 5) << std::endl;
	test_vector_print(test);
	std::cout << *test.erase(test.begin() + 50, test.end()) << std::endl;
	test_vector_print(test);
	test.erase(test.begin(), test.end());
	test_vector_print(test);

	vector<LeakTest> test2(100, 123);
	std::cout << *test2.erase(test2.begin()) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 22) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 42) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 11) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 71) << std::endl;;
	test_vector_print(test2);
}