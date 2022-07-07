//
// Created by amyroshn on 06/07/22.
//
#include "../../inc/ft_containers_test.hpp"

using namespace ft;

void stack_test() {
	stack<LeakTest> leak;
	type_print(leak.empty());
	type_print(leak.size());
	{
		for (int i = 0; i < 100000; i++) {
			LeakTest l(i);
			leak.push(l);
		}
		type_print(leak.empty());
		type_print(leak.size());
	}
	while  (!leak.empty()) {
		if (leak.size() > 99000)
			std::cout << *leak.top().a << std::endl;
		leak.pop();
	}
	type_print(leak.empty());
	type_print(leak.size());
	stack<std::string> test;
	type_print(test.empty());
	type_print(test.size());
	test.push("evaluator");
	test.push("dear");
	test.push("my");
	test.push("Hello");
	type_print(test.empty());
	type_print(test.size());
	while (!test.empty()) {
		type_print(test.top());
		test.pop();
	}
}