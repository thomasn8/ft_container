#include <iostream>
#include <map>
#include "../map.hpp"
#include "../pair.hpp"
#include "../container_details.hpp"


int main()
{
	// // ************************************************************
	// // ********************** TESTS FT::PAIR **********************

	// ft::pair<int, char> p1;
	// std::cout << "Paire1 ";
	// std::cout << "	#1 = " << p1.first << "	";
	// std::cout << "	#2 = " << p1.second << std::endl;
	// ft::pair<int, float> p3(1, 4.31f);
	// std::cout << "Paire3 ";
	// std::cout << "	#1 = " << p3.first << "	";
	// std::cout << "	#2 = " << p3.second << std::endl;
	// ft::pair<float, char> p6 = p3;
	// std::cout << "Paire6 ";
	// std::cout << "	#1 = " << p6.first << "	";
	// std::cout << "	#2 = " << p6.second << std::endl;
	// ft::pair<float, float> p7 = ft::make_pair<float,float>(1.1f,2.2f);
	// std::cout << "Paire7 ";
	// std::cout << "	#1 = " << p7.first << "	";
	// std::cout << "#2 = " << p7.second << std::endl;
	// ft::make_pair<float,float>(1.1f,2.2f);

	// std::cout << std::endl;
	// ft::pair<int,char> foo2(10,'z');
	// ft::pair<int,char> bar2(90,'a');
	// if (foo2==bar2) std::cout << "foo and bar are equal\n";
	// if (foo2!=bar2) std::cout << "foo and bar are not equal\n";
	// if (foo2< bar2) std::cout << "foo is less than bar\n";
	// if (foo2> bar2) std::cout << "foo is greater than bar\n";
	// if (foo2<=bar2) std::cout << "foo is less than or equal to bar\n";
	// if (foo2>=bar2) std::cout << "foo is greater than or equal to bar\n";

	// // ************************************************************
	// // ********************** TESTS FT::MAP ***********************
	// ft::map<char,int> ft1;
	// ft1['c'] = 3;
	// ft1['b'] = 2;
	// ft1['a'] = 1;
	// ft1.erase('b');
	// ft1.erase('c');
	// ft1.erase('a');
	// ft::map_details(ft1);

	// ft::map<char,int> ft2;
	// ft2['a'] = 17;
	// ft2['b'] = 7;
	// ft2['c'] = 5;
	// ft2['d'] = 8;
	// ft2['e'] = 9;
	// ft2['f'] = 9;
	// ft2['g'] = 9;
	// ft2['h'] = 9;
	// ft2['i'] = 9;
	// ft2['j'] = 9;
	// ft2['k'] = 9;
	// ft2['l'] = 9;
	// ft2['m'] = 9;
	// ft2['n'] = 9;
	// ft2['o'] = 9;
	// ft2['p'] = 9;
	// ft2['q'] = 9;
	// ft2['r'] = 9;
	// ft2['s'] = 9;
	// ft2.erase(ft2.find('a'));
	// ft2.erase(ft2.find('c'));
	// ft2.erase(ft2.find('g'));
	// ft2.erase(ft2.find('r'));
	// ft2.erase(ft2.find('n'));
	// ft2.erase(ft2.find('d'));
	// ft::map_details(ft2);

	// ft::map<char,int> ft3;
	// ft3.insert(ft2.begin(), ft2.end());
	// ft3.erase(ft3.begin(), ft3.end());
	// ft::map_details(ft3);

	// ft::map<char,int> ft4 = ft2;
	// ft::map_details(ft4);
	// ft::pair<char,int> pr1;
	// ft::pair<char,int> pr2;
	// ft4.insert(pr1);
	// ft4.insert(pr2);
	// ft4.insert(ft::make_pair<char,int>('y',1));
	// ft4.insert(ft::make_pair<char,int>('z',1000));
	// ft::map_details(ft4);
	// ft4.at('z') = 77777;
	// // ft4.at('w');					// OUT OF RANGE
	// // ft4.at('v');					// OUT OF RANGE
	// ft::map_details(ft4);
	// ft4.clear();
	// ft4.swap(ft2);
	// ft::map_details(ft2);
	// ft::map_details(ft4);
	// ft::map<char,int>::iterator a = ft4.find('a');
	// std::cout << a->first << std::endl;
	// for (ft::map<char,int>::const_reverse_iterator it = ft4.crbegin(); it != ft4.crend(); ++it)
    // 	std::cout << it->first << " => " << it->second << std::endl;

	// ft::map<char,int> ft5;
	// ft5['m'] = 17;
	// ft5['c'] = 7;
	// ft5['p'] = 8;
	// ft5['a'] = 5;
	// ft5['h'] = 9;
	// ft5['e'] = 19;
	// ft5['n'] = 19;
	// ft5['t'] = 19;
	// ft5['s'] = 19;
	// ft5['y'] = 19;
	// ft::map_details(ft5);
	// (*ft5.upper_bound('f')).second = 1;
	// (*ft5.lower_bound('n')).second = 1;
	// ft::map_details(ft5);

	ft::map<char,int> ft6;
	ft6['a'] = 5;
	ft6['b'] = 10;
	ft6['c'] = 15;
	ft6['d'] = 20;
	ft6['e'] = 25;
	ft::map_details(ft6);
	// ft6.print_tree();
	ft::map<char,int>::iterator it = ft6.find('d');
	std::cout << it->first << " => " << it->second << std::endl;
	ft6.erase('b');
	ft::map_details(ft6);
	// ft6.print_tree();
	std::cout << it->first << " => " << it->second << std::endl;
	ft6.erase('d');
	std::cout << it->first << " => " << it->second << std::endl;
	return 0;
}
