//
// Created by Anton on 19/06/2022.
//
#include "../inc/ft_containers_test.hpp"

using namespace ft;
void capacity_test() {
	vector<int> test;
	print_vector(test); //showing capacity and size inside
	std::cout << test.max_size() << std::endl;
	std::cout << (test.empty() ? "empty" : "not empty") << std::endl;
	try {
		test.reserve(test.max_size() + 1);
	} catch (std::length_error& err) {
		std::cout << "exception catched" << std::endl;
		std::cout << err.what() << std::endl;
	}
	test.reserve(10);
	print_vector(test); //showing capacity and size inside
	std::cout << (test.empty() ? "empty" : "not empty") << std::endl;
	for (int i = 0; i < 50; i++)
		test.push_back(i);
	std::cout << (test.empty() ? "empty" : "not empty") << std::endl;
	print_vector(test); //showing capacity and size inside
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

void fill_and_copy_constructor() {
	vector<LeakTest<int> > b(100, 42);
	print_vector_size(b);
	vector<int>a;
	print_vector(a);
	vector<vector<LeakTest<int> > > c(1000, b);
	vector<LeakTest<int> > bb(b);
	print_vector(bb);
	vector<int>aa(a);
	print_vector(aa);
	vector<vector<LeakTest<int> > > cc(c);
}

void default_constructor() {
	vector<LeakTest<int> > b;
	print_vector(b);
	vector<int>a;
	print_vector(a);
	vector<vector<LeakTest<int> > > c;
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
	vector<LeakTest<int> > l(1000, 42);
	vector<LeakTest<int> > tested5 = l;
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

	vector<LeakTest<int> > test2(100, 123);
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

void random_access_iterator_test() {
	{
		vector<int> a(5);
		for (int i = 0; i < 10; i++)
			a.push_back(i);
		vector<int>::iterator beg = a.begin();
		vector<int>::const_iterator const_beg = a.begin();
		vector<int>::iterator end = a.end() - 1;
		vector<int>::const_iterator const_end = a.end() - 1;

		//equality operators const vs non const:
		type_print(beg == const_beg);
		type_print(beg != const_beg);
		type_print(beg > const_beg);
		type_print(beg < const_beg);
		type_print(beg >= const_beg);
		type_print(beg <= const_beg);


		type_print(end == const_end);
		type_print(end != const_end);
		type_print(end > const_end);
		type_print(end < const_end);
		type_print(end >= const_end);
		type_print(end <= const_end);


		type_print(beg == const_end);
		type_print(beg != const_end);
		type_print(beg > const_end);
		type_print(beg < const_end);
		type_print(beg >= const_end);
		type_print(beg <= const_end);


		type_print(end == const_beg);
		type_print(end != const_beg);
		type_print(end > const_beg);
		type_print(end < const_beg);
		type_print(end >= const_beg);
		type_print(end <= const_beg);

		//equality operator non const vs non const
		type_print(beg == end);
		type_print(beg != end);
		type_print(beg > end);
		type_print(beg < end);
		type_print(beg >= end);
		type_print(beg <= end);


		type_print(end == beg);
		type_print(end != beg);
		type_print(end > beg);
		type_print(end < beg);
		type_print(end >= beg);
		type_print(end <= beg);



		//addition / subtraction
		type_print(*(end - 5));
		type_print(*beg++);
		type_print(*const_beg++);
		type_print(*beg);
		*(beg - 1) = 42;
		type_print(*const_beg);
		type_print(*--beg);
		type_print(*--const_beg);
		type_print(*end);
		type_print(*(const_beg + 1));
		type_print(*(1 + const_beg + 1));
		type_print(*(1 + const_beg));
		type_print(end - const_beg);
		type_print(const_end - const_beg - 3);
		type_print(const_end - const_beg + 32);
		*(beg + 4) = 999;
		beg += 4;
		type_print(*beg);
		beg[const_end - const_beg] = 222;
		type_print(beg[const_end - const_beg]);


		//OTHER

		beg++;
		const_end--;

		//equality operators const vs non const:
		type_print(beg == const_beg);
		type_print(beg != const_beg);
		type_print(beg > const_beg);
		type_print(beg < const_beg);
		type_print(beg >= const_beg);
		type_print(beg <= const_beg);


		type_print(end == const_end);
		type_print(end != const_end);
		type_print(end > const_end);
		type_print(end < const_end);
		type_print(end >= const_end);
		type_print(end <= const_end);


		type_print(beg == const_end);
		type_print(beg != const_end);
		type_print(beg > const_end);
		type_print(beg < const_end);
		type_print(beg >= const_end);
		type_print(beg <= const_end);


		type_print(end == const_beg);
		type_print(end != const_beg);
		type_print(end > const_beg);
		type_print(end < const_beg);
		type_print(end >= const_beg);
		type_print(end <= const_beg);

		//equality operator non const vs non const
		type_print(beg == end);
		type_print(beg != end);
		type_print(beg > end);
		type_print(beg < end);
		type_print(beg >= end);
		type_print(beg <= end);


		type_print(end == beg);
		type_print(end != beg);
		type_print(end > beg);
		type_print(end < beg);
		type_print(end >= beg);
		type_print(end <= beg);



		//addition / subtraction
		type_print(*(end - 5));
		type_print(*beg++);
		type_print(*const_beg++);
		type_print(*beg);
		*(beg - 1) = 42;
		type_print(*const_beg);
		type_print(*--beg);
		type_print(*--const_beg);
		type_print(*end);
		type_print(*(const_beg + 1));
		type_print(*(1 + const_beg + 1));
		type_print(*(1 + const_beg));
		type_print(end - const_beg);
		type_print(const_end - const_beg - 3);
		type_print(const_end - const_beg + 32);
		*(beg + 4) = 999;
		beg += 4;
		type_print(*beg);
	}

	/********************* REVERSE ***************************/
	{
		vector<char> test;
		test.push_back('q');
		test.push_back('w');
		test.push_back('e');
		test.push_back('r');
		test.push_back('t');
		test.push_back('y');
		test.push_back('u');
		test.push_back('i');
		test.push_back('o');
		test.push_back('p');
		test.push_back('[');
		test.push_back(']');
		test.push_back('a');
		test.push_back('s');
		test.push_back('d');
		test.push_back('f');
		test.push_back('g');
		test.push_back('h');
		test.push_back('j');
		test.push_back('k');
		test.push_back('l');
		test.push_back(';');
		test.push_back('z');
		test.push_back('x');
		test.push_back('c');
		test.push_back('v');
		test.push_back('b');
		test.push_back('n');
		test.push_back('m');
		test.push_back(',');
		test.push_back('.');
		print_vector(test);
		vector<char>::reverse_iterator start = test.rbegin();
		while (start != test.rend()) {
			std::cout << *start;
			start++;
		}
		std::cout << std::endl;
		type_print(*(--test.rend()));
	}
}