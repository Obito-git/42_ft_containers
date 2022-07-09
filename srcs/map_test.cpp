//
// Created by amyroshn on 06/07/22.
//

#include "../inc/ft_containers_test.hpp"

using namespace ft;

void map_iter() {
	map<const int, int> test;
	print_map_size(test);
	for (int i = 0; i < 11; i++) {
		test.insert(make_pair(i, i * 2));
	}
	print_map_size(test);
	print_map(test);
	map<const int, int>::iterator it = test.begin();
	map<const int, int>::const_iterator itc = test.begin();
	map<const int, int>::reverse_iterator rit(test.rbegin());
	map<const int, int>::const_reverse_iterator ritc(test.rbegin());
	std::cout << "it" << std::endl;
	pair_print(*it);
	it++;
	pair_print(*it);
	++it;
	pair_print(*it);
	it--;
	pair_print(*it);
	--it;
	pair_print(*it);

	std::cout << "rit" << std::endl;

	pair_print(*rit);
	rit++;
	pair_print(*rit);
	++rit;
	pair_print(*rit);
	rit--;
	pair_print(*rit);
	--rit;
	pair_print(*rit);

	std::cout << "ritc" << std::endl;
	pair_print(*ritc);
	ritc++;
	pair_print(*ritc);
	++ritc;
	pair_print(*ritc);
	ritc--;
	pair_print(*ritc);
	--ritc;
	pair_print(*ritc);

	std::cout << "itc" << std::endl;

	pair_print(*itc);
	itc++;
	pair_print(*itc);
	++itc;
	pair_print(*itc);
	itc--;
	pair_print(*itc);
	--itc;
	pair_print(*itc);

	while (it != test.end())
		pair_print(*it++);
	while (rit != test.rend())
		pair_print(*rit++);
	while (ritc != test.rend())
		pair_print(*ritc++);
	while (itc != test.end())
		pair_print(*itc++);
	print_map_size(test);
}

void map_access() {
	map<const std::string, int> test;
	print_map_size(test);
	test["cheese"] = 1;
	test["banana"] = 2;
	test["grape"] = 3;
	test["mangue"] = 4;
	test["coco"] = 5;
	test["orange"] = 6;
	test["fraise"] = 7;
	test["cerise"] = 8;
	print_map(test);
}

void map_constructors() {
	//empty
	map<const int, int> a;
	print_map_size(a);
	map<const int, int, std::greater<const int> > b;
	for (int i = 0; i < 10; i++)
		b.insert(make_pair(i, i * 2));
	print_map(b);

	//range
	map<const int, int> c(b.begin(), b.end());
	print_map(c);

	std::list<pair<const int, int> > lst;
	for (int i = 100; i < 50; i++)
		lst.push_back(make_pair(i, i * 2));

	map<const int, int, std::greater<const int> > d(lst.begin(), lst.end());
	print_map(d);

	//cpy
	map<const int, int, std::greater<const int> > e(d);
	e.insert(make_pair(555, 5431));
	e.insert(make_pair(5555, 54351));
	e.insert(make_pair(53255, 545531));
	e.insert(make_pair(5155, 54311));
	print_map(e);

	map<const int, int> f(a);
	print_map(f);
}

void map_leaks() {
	map<const int, LeakTest<int> > test;
	for (int i = 0; i < 100; i++) {
		LeakTest<int> a(i);
		test.insert(make_pair(i, a));
	}
	print_map_size(test);
	test.erase(test.begin(), test.find(30));
	print_map_size(test);
	test.erase(test.find(80), test.end());
	print_map_size(test);
	test.clear();
}

void map_modifiers_tests() {
	// insert, erase, swap, clear
	//insert single
	map<const int, std::string> a;
	a[1] = "Hello";
	a[44] = "world";
	pair<map<const int, std::string>::iterator, bool> p = a.insert(make_pair(42, "Ecole"));
	print_map(a);
	type_print(p.first->first);
	type_print(p.first->second);
	type_print(p.second);
	p = a.insert(make_pair(44, "monde"));
	print_map(a);
	type_print(p.first->first);
	type_print(p.first->second);
	type_print(p.second);

	//with hint
	map<const int, std::string>::iterator p2 = a.insert(a.begin(), make_pair(1337, "Khouribga"));
	print_map(a);
	type_print(p2->first);
	type_print(p2->second);

	//range
	std::list<pair<const int, std::string> > lst;
	lst.push_back(make_pair(19, "Bruxelles"));
	lst.push_back(make_pair(4242, "Seoul"));
	lst.push_back(make_pair(424242, "Tokyo"));


	a.insert(lst.begin(), lst.end());
	print_map(a);

	//erase
	a.erase(a.begin());
	print_map(a);
	type_print(a.erase(1337));
	a.erase(a.begin(), a.find(4242));
	print_map(a);

	map<const int, std::string> b;
	b.insert(make_pair(1, "de Gea"));
	b.insert(make_pair(23, "Shaw"));
	b.insert(make_pair(17, "Fred"));
	b.insert(make_pair(7, "Ronaldo"));
	b.insert(make_pair(11, "Greenwood"));
	b.insert(make_pair(5, "Maguire"));
	print_map(b);
	b.swap(a);
	print_map(a);
	print_map(b);
	b.clear();
	print_map_size(b);
	print_map(a);
}

void map_operations() {
	map<const int, std::string> b;
	b.insert(make_pair(1, "de Gea"));
	b.insert(make_pair(23, "Shaw"));
	b.insert(make_pair(17, "Fred"));
	b.insert(make_pair(7, "Ronaldo"));
	b.insert(make_pair(11, "Greenwood"));
	b.insert(make_pair(5, "Maguire"));

	map<const int, std::string>::iterator it = b.find(22);
	std::cout << (it == b.end() ? "Found" : "Not found") << std::endl;
	it = b.find(1);
	std::cout << (it == b.end() ? "Found" : "Not found") << std::endl;
	type_print(b.count(3));
	type_print(b.count(42));
	type_print(b.count(1));
	type_print(b.count(23));
	type_print(b.count(5));

	it = b.lower_bound(1); std::cout << it->first << " " << it->second << std::endl;
	it = b.lower_bound(22); std::cout << it->first << " " << it->second << std::endl;

	it = b.upper_bound(5); std::cout << it->first << " " << it->second << std::endl;
	it = b.upper_bound(1); std::cout << it->first << " " << it->second << std::endl;
}
