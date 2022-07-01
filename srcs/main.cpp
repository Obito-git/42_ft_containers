#include <string>
#include <stack>
#include "../inc/ft_containers_test.hpp"
#include "../inc/stack.hpp"
#include "../inc/map.hpp"
#include "../inc/RBT_iterator.hpp"
#include <string>
#include <map>
using namespace ft;

void print(map<int, int>& test) {
	map<int, int>::iterator it1 = test.begin();

	while (it1 != test.end()) {
		std::cout << it1->first  << std::endl;
		it1++;
	}
}
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
	for (int i = 0; i < 1000; i++) {
		test.insert(make_pair(i, i));
	}
	/*
	test.erase(1);
	test.erase(10);
	test.erase(321);
	test.erase(54);
	test.erase(991);
	test.erase(500);
	test.erase(325);
	test.erase(666);
	test.erase(763);
	test.erase(3);
	test.erase(123);
	test.erase(432);
	test.erase(111);
	test.erase(19);
	test.erase(79);
	test.erase(86);
	test.erase(754);
*/

	for (int i = 0; i < 1000; i++)
		if ((i % 2 == 1 || i % 10 == 0) && (i > 300))
			test.erase(i);
	print(test);
	for (int i = 0; i < 30; i++)
		test.erase(i);
	print(test);
	for (int i = 40; i < 50; i++)
		test.erase(i);
	print(test);
	for (int i = 70; i < 100; i++)
		test.erase(i);
	print(test);
	for (int i = 150; i < 200; i++)
		test.erase(i);
	print(test);
	for (int i = 233; i < 277; i++)
		test.erase(i);
	print(test);
	/*§
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
