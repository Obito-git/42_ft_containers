//
// Created by Anton on 19/06/2022.
//

#include "../../inc/ft_containers_test.hpp"

using namespace ft;
void modifiers_test() {
	/***************************** ERASE ********************************/
	vector<int> test;
	for (int i = 0; i < 100; i++)
		test.push_back(i);
	std::cout << *test.erase(test.begin(), test.begin() + 5) << std::endl;
	print_vector(test);
	std::cout << *test.erase(test.begin() + 50, test.end()) << std::endl;
	print_vector(test);
	test.erase(test.begin(), test.end());
	print_vector(test);

	vector<LeakTest> test2(100, 123);
	std::cout << *test2.erase(test2.begin()) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 22) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 42) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 11) << std::endl;;
	std::cout << *test2.erase(test2.begin() + 71) << std::endl;;
	print_vector(test2);

	vector<int>::iterator test_it = test.begin();
	while (test_it++ != test.end())
		if (*test_it % 2 == 0)
			test.erase(test_it);
	print_vector(test);

	/************************* ASSIGN ************************************/
	std::list<char> test_list;
	char i = 40;
	while (i < 126)
		test_list.push_back(i++);
	vector<char> test_other_iter;
	for (int ia = 0; ia < 100; ia++)
		test_other_iter.push_back(static_cast<char>(ia));
	test_other_iter.assign(test_list.begin(), test_list.end());
	print_vector(test_other_iter);
	test_other_iter.assign(10, 'a');
	print_vector(test_other_iter);
	test_other_iter.assign(133, 'o');
	print_vector(test_other_iter);


	/************************* INSERT *******************************/
	test_other_iter.insert(test_other_iter.begin(), 'a');
	print_vector(test_other_iter);
	test_other_iter.insert(test_other_iter.begin() + 100, 42, 'h');
	print_vector(test_other_iter);
	test_other_iter.insert(test_other_iter.end() - 1, test_list.begin(), test_list.end());
	print_vector(test_other_iter);



	/************************* SWAP *******************************/
	vector<char> empty;
	empty.swap(test_other_iter);
	print_vector(empty);
	print_vector(test_other_iter);
	test_other_iter = empty;

	/************************* clear *******************************/
	print_vector(empty);
	empty.clear();
	print_vector(empty);
	empty.clear();
	print_vector(empty);

}