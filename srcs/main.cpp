#include "../inc/ft_containers_test.hpp"

using namespace ft;


int main(int argc, char** argv) {
	if (argc != 2)
	{
		(void) argv;
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	struct timeval begin;
	gettimeofday(&begin, 0);
	std::string nmsp = "using namespace ft;";
	std::string name;
	name = nmsp.find("ft") != std::string::npos ? "[ft] " : "[std] ";

	std::cout << name << "Subject test: " << subject_test(argv[1]) << std::endl;

	bool bench = true;
	double vec = run_vector_tests(bench);
	double sta = run_stack_tests(bench);
	double mp = run_map_tests(bench);
	double st = run_set_tests(bench);
	std::cout << name << "vector: " << vec << ", stack: " << sta << ", map: " << mp << ", set: " << st;
	std::cout << "| total: " << print_used_time(begin) << std::endl;

	return (0);
}