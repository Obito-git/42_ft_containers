#include <string>
#include <stack>
#include "../inc/ft_containers_test.hpp"
#include <string>
#include <map>
#include <iterator>
#include <sys/time.h>
using namespace ft;

#define T_SIZE_TYPE typename vector<T>::size_type

template <typename T>
void	printSize(vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename vector<T>::const_iterator it = vct.begin();
		typename vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


#define TESTED_TYPE std::string

void	checkErase(vector<TESTED_TYPE> const &vct,
vector<TESTED_TYPE>::const_iterator const &it)
{
static int i = 0;
std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
printSize(vct);
}

int		main1(void)
{
	vector<TESTED_TYPE> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));
	return (0);
}


int main()
{
	long seconds;
	long microseconds;
	double elapsed;
	struct timeval begin, end;
	gettimeofday(&begin, 0);
	/******************* VECTOR ************************/
	random_access_iterator_test();
	constructor_destructor_test();
	capacity_test();
	access_test();
	modifiers_test();
	vector_benchmark();

	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	std::cout << "vector " << elapsed << " seconds" << std::endl;
	/******************* STACK ************************/
	gettimeofday(&begin, 0);

	stack_test();
	stack_bench();

	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	std::cout << "stack " << elapsed << " seconds" << std::endl;
	/******************* MAP ************************/

	gettimeofday(&begin, 0);

	map_iter_cap_access();
	map_bench();

	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	std::cout << "map " << elapsed << " seconds" << std::endl;

	return 0;
}
