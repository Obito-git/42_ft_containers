//
// Created by Anton on 19/06/2022.
//
#include "../../inc/ft_containers_test.hpp"

using namespace ft;
void capacity_test() {
	vector<int> test;
	test_vector_print(test); //showing capacity and size inside
	std::cout << test.max_size() << std::endl;
	std::cout << (test.empty() ? "empty" : "not empty") << std::endl;
	try {
		test.reserve(test.max_size() + 1);
	} catch (std::length_error& err) {
		std::cout << "exception catched" << std::endl;
		std::cout << err.what() << std::endl;
	}
	test.reserve(10);
	test_vector_print(test); //showing capacity and size inside
	std::cout << (test.empty() ? "empty" : "not empty") << std::endl;
	for (int i = 0; i < 5000; i++)
		test.push_back(i);
	std::cout << (test.empty() ? "empty" : "not empty") << std::endl;
	test_vector_print(test); //showing capacity and size inside
}

void access_test() {
	vector<std::string> test;
	test.push_back("hello");
	test.push_back("hello1");
	test.push_back("hello2");
	test.push_back("hello3");
	try {
		test.at(1000);
	} catch (std::exception& e) {
		std::cout << "exception is catched" << std::endl;
	}
	std::cout << test[0] << std::endl;
	std::cout << test[1] << std::endl;
	std::cout << test[2] << std::endl;
	std::cout << test.front() << " " << test.back() << std::endl;
}
