#include <string>
#include <stack>
#include "../inc/ft_containers_test.hpp"
#include "../inc/stack.hpp"
#include "../inc/map.hpp"
#include "../inc/RBT_iterator.hpp"
#include <string>
#include <map>
using namespace std;

int main()
{
	/******************* VECTOR ************************/
	//random_access_iterator_test();
	//constructor_destructor_test();
	//capacity_test();
	//access_test();
	//erase_test();

	/******************* STACK ************************/
	//vector<int> test;
	//stack<int, vector<int> > a(test);
	//std::cout << (a.empty() ? "true" : "false") << std::endl;
	//std::cout << (a.top()) << std::endl;

	/****************** MAP **********************/
	map<int, int> test;
	test.insert(make_pair(155, 100));
	test.insert(make_pair(133, 600));
	test.insert(make_pair(177, 100));
	test.insert(make_pair(166, 100));
	test.insert(make_pair(167, 600));
	test.insert(make_pair(200, 600));
	test.insert(make_pair(300, 600));
	test.insert(make_pair(180, 600));
	test.insert(make_pair(179, 600));
	test.insert(make_pair(181, 600));
	test.insert(make_pair(182, 600));
	test.insert(make_pair(183, 600));
	for (int i = 400; i < 500; i++)
		test.insert(make_pair(i, i));
	for (int i = -5; i > -200; i--)
		test.insert(make_pair(i, i));

	map<int, int>::iterator it = test.begin();
	while (it != test.end()) {
		std::cout << (*it).first << std::endl;
		++it;
	}
	/*
	test.insert(make_pair(15, 600));
	std::cout << (test) << std::endl;
	test.insert(make_pair(30, 600));
	std::cout << (test) << std::endl;
	test.insert(make_pair(31, 600));
	std::cout << (test) << std::endl;
	test.insert(make_pair(32, 600));
	std::cout << (test) << std::endl;
	test.insert(make_pair(33, 600));

	std::cout << (test) << std::endl;
	std::cout << (*test.begin()).first << std::endl;
*/
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
