//#include "vector.hpp"
//#include <iostream>
//#include <vector>
////#include "map.hpp"
//
//void	vector_test_original() {
//	std::cout << "testing constructors...\n";
//	std::vector<int>	def_const;
//	std::vector<int>	fill(12, 1);
//	std::vector<int>	range(fill.begin(), fill.begin() + 6);
//	std::vector<int>	copy(fill);
//
//	std::cout << "default constructor: ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "fill constructor: 12, 1";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "range constructor: 6";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "copy constructor: copying fill";
//	for (auto i = copy.begin(); i != copy.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n\n";
//	std::cout << "testing modifiers...\n";
//	int j = 0;
//	for (auto	it = fill.begin(); it != fill.end(); it++) {
//		*it = j;
//		j++;
//	}
//	std::cout << "insert single value: \n";
//	std::cout << "	pre:	";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	fill.insert(fill.begin() + 7, 999);
//	std::cout << "	after:  ";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "insert fill, single value:\n";
//	std::cout << "	pre:	";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	def_const.insert(def_const.begin(), 4, 42);
//	std::cout << "\n";
//	std::cout << "	after:  ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "insert copy, iterator range:\n";
//	std::cout << "	pre:	";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	range.insert(range.begin() + 1, fill.begin() + 2, fill.begin() + 5);
//	std::cout << "\n";
//	std::cout << "	after:  ";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n\n";
//	std::cout << "erase range:\n";
//	std::cout << "	pre:	";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	range.erase(range.begin() + 5, range.end() - 2);
//	std::cout << "\n";
//	std::cout << "	after:  ";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "erase single value: \n";
//	std::cout << "	pre:	";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	fill.erase(fill.begin() + 7);
//	std::cout << "	after:  ";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n\n";
//	std::cout << "push back: \n";
//	std::cout << "	pre:	";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	def_const.push_back(420);
//	std::cout << "	after:  ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "pop back: \n";
//	std::cout << "	pre:	";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	def_const.pop_back();
//	std::cout << "	after:  ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "testing element access...\n";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\nfront: " << fill.front() << "\n";
//	std::cout << "back: " << fill.back() << "\n";
//	std::cout << "\n\"at\" operator " << fill.at(1) << " " << fill.at(2) << "\n";
//	std::cout << "\"at\" operator that will fail, because out of range, but an exception can be caught: \n";
//	try {
//		std::cout << fill.at(45678);
//	} catch (std::out_of_range &e) {
//		std::cout << "WARNING: EXCEPTION CAUGHT IN: " << e.what() << "\n";
//	}
//	std::cout << "[] operator: " << fill[1] << " " << fill[2] << "\n";
//	std::cout << "[] operator that will fail, because out of range: \n";
//	//std::cout << fill[100897350] << " " << fill[324534200] << "\n";
//}
//
//void	vector_test() {
//	std::cout << "testing constructors...\n";
//	ft::vector<int>	def_const;
//	ft::vector<int>	fill(12, 1);
//	ft::vector<int>	range(fill.begin(), fill.begin() + 6);
//	ft::vector<int>	copy(fill);
//
//	std::cout << "default constructor: ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "fill constructor 12, 1: ";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "range constructor 6: ";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "copy constructor copying fill: ";
//	for (auto i = copy.begin(); i != copy.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n\n";
//	std::cout << "testing modifiers...\n";
//	int j = 0;
//	for (auto	it = fill.begin(); it != fill.end(); it++) {
//		*it = j;
//		j++;
//	}
//	std::cout << "insert single value: \n";
//	std::cout << "	pre:	";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	fill.insert(fill.begin() + 7, 999);
//	fill.insert(fill.end(), 999);
//	std::cout << "	after:  ";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "insert fill, single value:\n";
//	std::cout << "	pre:	";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	size_t var = 4;
//	int num = 42;
//	def_const.insert(def_const.begin(), var, num);
//	std::cout << "\n";
//	std::cout << "	after:  ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	for (size_t i = 0; i != range.size(); i++)
//		range.at(i) = i % 12;
//	std::cout << "insert copy, iterator range:\n";
//	std::cout << "	pre:	";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//	std::cout << *i << " ";
//	range.insert(range.begin() + 1, fill.begin() + 2, fill.begin() + 5);
//	std::cout << "\n";
//	std::cout << "	after:  ";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
////	for (int i = 0; i < 12; i++)
////		std::cout << range[i] << "  ";
////	exit(0);
//	std::cout << "\n\n";
//	std::cout << "erase range:\n";
//	std::cout << "	pre:	";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "  " << range.end() - 2 - range.begin() + 5;
//	range.erase(range.begin() + 5, range.end() - 2);
//	std::cout << "\n";
//	std::cout << "	after:  ";
//	for (auto i = range.begin(); i != range.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "erase single value: \n";
//	std::cout << "	pre:	";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	fill.erase(fill.begin() + 7);
//	fill.erase(fill.end() - 1);
//	std::cout << "	after:  ";
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n\n";
//	std::cout << "push back: \n";
//	std::cout << "	pre:	";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	def_const.push_back(420);
//	std::cout << "	after:  ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "pop back: \n";
//	std::cout << "	pre:	";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	def_const.pop_back();
//	std::cout << "	after:  ";
//	for (auto i = def_const.begin(); i != def_const.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\n";
//	std::cout << "testing element access...\n";
//	fill.push_back(10);
//	for (auto i = fill.begin(); i != fill.end(); i++)
//		std::cout << *i << " ";
//	std::cout << "\nfront: " << fill.front() << "\n";
//	std::cout << "back: " << fill.back() << "\n";
//	std::cout << "\n\"at\" operator " << fill.at(1) << " " << fill.at(2) << "\n";
//	std::cout << "\"at\" operator that will fail, because out of range, but an exception can be caught: \n";
//	try {
//		std::cout << fill.at(45678);
//	} catch (std::out_of_range &e) {
//		std::cout << "WARNING: EXCEPTION CAUGHT IN: " << e.what() << "\n";
//	}
//	std::cout << "[] operator: " << fill[1] << " " << fill[2] << "\n";
////	std::cout << "[] operator that will fail, because out of range: \n"
////			 << fill[100897350] << " " << fill[324534200] << "\n";
//
//	std::cout << "testing resizing... (smaller)\n";
//	fill.resize(11);
//	std::cout << "testing resizing...(bigger)\n";
//	fill.resize(17);
//}
//
//void	rb_tree_test() {
//
//}
//
//#include "integral.hpp"
//void integral () {
//	std::cout << std::boolalpha;
//	std::cout << "is_integral:" << std::endl;
//	std::cout << "char: " << std::is_integral<char>::value << std::endl;
//	std::cout << "int: " << std::is_integral<int>::value << std::endl;
//	std::cout << "float: " << std::is_integral<float>::value << std::endl;
//
//	std::cout << "FT_is_integral:" << std::endl;
//	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
//	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
//	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
//}
//
//#include "stack.hpp"
//#include "map.hpp"
//#include "pair.hpp"
//void	stack_test() {
//	ft::vector<int> v1(12, 1);
//	ft::stack<int> st1(v1);
//
//	std::cout << "stack: empty():\n" << st1.empty() << std::endl;
//	std::cout << "stack: top():\n" << st1.top() << std::endl;
//	std::cout << "stack: push(5):" << std::endl;
//	st1.push(5);
//	std::cout << st1.top() << std::endl;
//	std::cout << "stack: pop():" << std::endl;
//	st1.pop();
//	std::cout << st1.top() << std::endl;
//}
//
//void tree_test() {
//	std::string			temp = "first";
//	ft::pair<int, std::string> somepair(1, "hi");
//	ft::map<int, std::string> test;
//	test.insert(somepair);
//	somepair.first = -12;
//	somepair.second = "hello";
//	test.insert(somepair);
//	test.print_map();
//	std::cout << "\n\n";
//	somepair.first = 132;
//	somepair.second = "good day";
//	test.insert(somepair);
//	test.print_map();
//	std::cout << "\n\n";
//	somepair.first = -1231;
//	somepair.second = "another";
//	test.insert(somepair);
//	test.print_map();
//	std::cout << "\n\n";
//	somepair.first = -132;
//	somepair.second = "one";
//	test.insert(somepair);
//	test.print_map();
//	std::cout << "\n\n";
//	somepair.first = -1234;
//	somepair.second = "or";
//	test.insert(somepair);
//	test.print_map();
//	somepair.first = 12;
//	somepair.second = "something";
//	test.insert(somepair);
//	somepair.first = 2346789;
//	somepair.second = "else";
//	test.insert(somepair);
//	somepair.first = 91;
//	somepair.second = "string";
//	test.insert(somepair);
//	somepair.first = 2;
//	somepair.second = "no idea";
//	test.insert(somepair);
//	somepair.first = -9999;
//	somepair.second = "lowest";
//	test.insert(somepair);
//	somepair.first = -99999;
//	somepair.second = "for real lowest";
//	test.insert(somepair);
//}

#include "vector.hpp"
int main() {

//	ft::vector<int> tst(12, 1);
//	for (ft::vector<int>::iterator it = tst.begin(); it != tst.end(); it++)
//		std::cout << " " << *it;

//	ft::vector<int>	test(12, 1);
//	test.push_back(12);
//	std::cout << test.size() << "resize" << std::endl;
//	for (int i = 0; i < 22; i++ )
//		test.erase(test.begin());
//	try {
//	test.resize(12, 1);
//	std::cout << test.size() << "resize" << std::endl;
//	} catch (...) {
//
//	std::cout << "stuck" << std::endl;
//	}
//	std::cout << "STACK TEST: \n";
//	stack_test();
//	std::cout << "TREE TEST: \n";
//	tree_test();
//	std::cout << "INTEGRAL TEST: \n";
//	integral();
//	std::cout << "MAP TEST: \n";
//	rb_tree_test();
//	std::cout << "ORIGINAL FUNCTIONS TEST OUTPUT: \n";
//	vector_test_original();
//	std::cout << "FT_CONTAINERS FUNCTIONS TEST OUTPUT: \n";
//	vector_test();
    ft::vector<std::string> v;
    auto it = v.insert(v.end(), "a");
    std::cout << *it << std::endl;

	return 0;
}
