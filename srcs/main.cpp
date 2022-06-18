#include <vector>
#include <iostream>
#include <string>
#include "containers/vector.hpp"

class Test {
public:
	int i;
	int *a;
	Test() {
		a = new int;
	}
	Test(const Test& t) {
		std::cout << "cpy" << std::endl;
		a = new int;
		(void) t;
	}
	Test(int ii) : i(ii){
		std::cout << "const" << std::endl;
		a = new int;
	}

	virtual ~Test() {
		std::cout << "dest" << std::endl;
		delete a;
	}
};

using namespace ft;
template <typename T>
void test_print(T t) {
	(void) t;
	//std::cout << t << std::endl;
}

int main1() {
	vector<int> a(100, 100);
	vector<int> b(100, 222);
	vector<int>::iterator it = b.begin();
	a.assign(it, it + 5);
	std::cout << "!!!!!!!!!!!! " << it - b.begin() << std::endl;
	return (0);
}

int main()
{
	/***************** RANDOM ACCESS OPERATOR *************************************/
	/******************************************************************************/
	vector<int> a(5);
	for (int i = 0; i < 10; i++)
		a.push_back(i);
	vector<int>::iterator beg = a.begin();
	vector<int>::const_iterator const_beg = a.begin();
	vector<int>::iterator end = a.end() - 1;
	vector<int>::const_iterator const_end = a.end() - 1;

	//equality operators:
	test_print(beg == const_beg);
	test_print(beg != const_beg);
	test_print(beg > const_beg);
	test_print(beg < const_beg);
	test_print(beg >= const_beg);
	test_print(beg <= const_beg);


	test_print(end == const_end);
	test_print(end != const_end);
	test_print(end > const_end);
	test_print(end < const_end);
	test_print(end >= const_end);
	test_print(end <= const_end);


	test_print(beg == const_end);
	test_print(beg != const_end);
	test_print(beg > const_end);
	test_print(beg < const_end);
	test_print(beg >= const_end);
	test_print(beg <= const_end);


	test_print(end == const_beg);
	test_print(end != const_beg);
	test_print(end > const_beg);
	test_print(end < const_beg);
	test_print(end >= const_beg);
	test_print(end <= const_beg);


	//addition / subtraction
	test_print(*(end - 5));
	test_print(*beg++);
	test_print(*const_beg++);
	test_print(*beg);
	*(beg -1) = 42;
	test_print(*const_beg);
	test_print(*--beg);
	test_print(*--const_beg);
	test_print(*end);
	test_print(*(const_beg + 1));
	test_print(const_end - const_beg);
	test_print(const_end - const_beg - 3);
	test_print(const_end - const_beg + 32);
	*(beg + 4) = 999;
	beg += 4;
	test_print(*beg);
	beg[const_end - const_beg] = 222;
	test_print(beg[const_end - const_beg]);

	/******************* VECTOR ************************/
	vector<int> vect(5, 2);
	vect.assign(10, 1);
	std::cout << vect.capacity() << std::endl;
	vector<int>::const_iterator i1 = vect.begin();
	for (; i1 != vect.end(); i1++)
		std::cout << *i1 << std::endl;


	// errors
	//test(const_beg + const_end);
	//test(10 - const_beg);
	// *const_beg = 10;
	//const_beg[0] = 10;


	/************************ INSERT ********************/
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

	return 0;
}