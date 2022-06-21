#include <string>
#include "ft_containers_test.hpp"

using namespace ft;

int main()
{
	/******************* VECTOR ************************/
	//random_access_iterator_test();
	//constructor_destructor_test();
	//capacity_test();
	//access_test();
	//erase_test();

	vector<int> test;
	test.reserve(10);
	for (int i = 100; i < 110; i++)
		test.push_back(i);
	vector<int>::reverse_iterator rit = test.rbegin();
	vector<int>::const_reverse_iterator rit_const = test.rbegin();
	//vector<int>::iterator it = test.begin();
	//vector<int>::const_iterator it_const = test.begin();
	if (rit_const == rit_const)
		std::cout << "hello" << std::endl;



	// errors
	//test(const_beg + const_end);
	//test(10 - const_beg);
	// *const_beg = 10;
	//const_beg[0] = 10;


	/************************ INSERT ********************
	vector<int> test(10, 1);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	vector<int>::iterator it = test.end();
	test.insert(it, 42);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;
	test.insert(test.begin(), 25);
	test.insert(test.begin() + 4, 244);
	test.insert(test.begin() + 10, 211);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;
	test.insert(test.end(), 243, 999);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;
	test.insert(test.begin(), 421, 512);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;
	test.insert(test.begin() + 4, 332, 816);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;
	//insert iterator test
	vector<int> tmp;
	for (int i = 0; i < 1000000; i++)
		tmp.push_back(i);
	std::cout << "size: " << tmp.size() << " capacity: " << tmp.capacity() << std::endl;
	test.insert(test.begin(), tmp.begin(), tmp.begin() + 3000);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;
	test.insert(test.begin() + 1777, tmp.begin() + 3000 , tmp.begin() + 6000);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;
	test.insert(test.end(), tmp.begin() + 6000 , tmp.begin() + 66666);
	std::cout << "size: " << test.size() << " capacity: " << test.capacity() << std::endl;
	for (it = test.begin(); it != test.end(); it++)
		std::cout << *it << std::endl;

*/
	return 0;
}