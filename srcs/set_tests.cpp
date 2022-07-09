//
// Created by amyroshn on 09/07/22.
//

#include "../inc/ft_containers_test.hpp"

using namespace ft;

void set_iter() {
	set<int> test;
	print_map_size(test);
	for (int i = 0; i < 11; i++) {
		test.insert(i);
	}
	print_map_size(test);
	print_set(test);
	set<int>::iterator it = test.begin();
	set<int>::const_iterator itc = test.begin();
	set<int>::reverse_iterator rit(test.rbegin());
	set<int>::const_reverse_iterator ritc(test.rbegin());
	std::cout << "it" << std::endl;
	type_print(*it);
	it++;
	type_print(*it);
	++it;
	type_print(*it);
	it--;
	type_print(*it);
	--it;
	type_print(*it);

	std::cout << "rit" << std::endl;

	type_print(*rit);
	rit++;
	type_print(*rit);
	++rit;
	type_print(*rit);
	rit--;
	type_print(*rit);
	--rit;
	type_print(*rit);

	std::cout << "ritc" << std::endl;
	type_print(*ritc);
	ritc++;
	type_print(*ritc);
	++ritc;
	type_print(*ritc);
	ritc--;
	type_print(*ritc);
	--ritc;
	type_print(*ritc);

	std::cout << "itc" << std::endl;

	type_print(*itc);
	itc++;
	type_print(*itc);
	++itc;
	type_print(*itc);
	itc--;
	type_print(*itc);
	--itc;
	type_print(*itc);

	while (it != test.end())
		type_print(*it++);
	while (rit != test.rend())
		type_print(*rit++);
	while (ritc != test.rend())
		type_print(*ritc++);
	while (itc != test.end())
		type_print(*itc++);
	print_map_size(test);
}

void set_constructors() {
	//empty
	set<int> a;
	print_map_size(a);
	set<int, std::greater<int> > b;
	for (int i = 0; i < 10; i++)
		b.insert(i);
	print_set(b);

	//range
	set<int> c(b.begin(), b.end());
	print_set(c);

	std::list<int> lst;
	for (int i = 100; i < 50; i++)
		lst.push_back(i);

	set<int, std::greater<int> > d(lst.begin(), lst.end());
	print_set(d);

	//cpy
	set<int, std::greater<int> > e(d);
	e.insert(555);
	e.insert(5555);
	e.insert(53255);
	e.insert(5155);
	print_set(e);

	set<int> f(a);
	print_set(f);
}

void set_modifiers_tests() {
	// insert, erase, swap, clear
	//insert single
	set<std::string> a;
	a.insert("Hello");
	a.insert("world");
	pair<set<std::string>::iterator, bool> p = a.insert("Ecole");
	print_set(a);
	type_print(*p.first);
	type_print(p.second);
	p = a.insert("monde");
	print_set(a);
	type_print(*p.first);
	type_print(p.second);

	//with hint
	set<std::string>::iterator p2 = a.insert(a.begin(), "Khouribga");
	print_set(a);
	type_print(*p2);

	//range
	std::list<std::string> lst;
	lst.push_back("Bruxelles");
	lst.push_back("Seoul");
	lst.push_back("Tokyo");


	a.insert(lst.begin(), lst.end());
	print_set(a);

	//erase
	a.erase(a.begin());
	print_set(a);
	type_print(a.erase("Tokyo"));
	print_set(a);

	set<std::string> b;
	b.insert( "de Gea");
	b.insert( "Shaw");
	b.insert( "Fred");
	b.insert( "Ronaldo");
	b.insert( "Greenwood");
	b.insert( "Maguire");
	print_set(b);
	b.swap(a);
	print_set(a);
	print_set(b);
	b.clear();
	print_map_size(b);
	print_set(a);
}

void set_operations() {
	set<std::string> b;
	b.insert("de Gea");
	b.insert( "Shaw");
	b.insert( "Fred");
	b.insert("Ronaldo");
	b.insert( "Greenwood");
	b.insert("Maguire");

	set<std::string>::iterator it = b.find("Coca cola");
	std::cout << (it == b.end() ? "Found" : "Not found") << std::endl;
	it = b.find("Fred");
	std::cout << (it == b.end() ? "Found" : "Not found") << std::endl;
	type_print(b.count("Shaw"));
	type_print(b.count("Fred"));
	type_print(b.count("Dovbyk"));
	type_print(b.count("Yarmolenko"));
	type_print(b.count("Zinchenko"));

	it = b.lower_bound("Fred"); std::cout << *it << std::endl;
	it = b.lower_bound("Greenwood"); std::cout << *it << std::endl;

	it = b.upper_bound("Fred"); std::cout << *it << std::endl;
	it = b.upper_bound("Greenwood"); std::cout << *it << std::endl;
}
