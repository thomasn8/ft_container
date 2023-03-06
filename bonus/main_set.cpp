#include <iostream>
#include "set.hpp"
#include "container_details.hpp"

int main()
{
	ft::set<char> ft1;
	ft1.insert('c');
	ft1.insert('b');
	ft1.insert('a');
	ft1.erase('b');
	ft1.erase('c');
	ft1.erase('a');
	ft::set_details(ft1);

	ft::set<char> ft2;
	ft2.insert('a');
	ft2.insert('b');
	ft2.insert('c');
	ft2.insert('d');
	ft2.insert('e');
	ft2.insert('f');
	ft2.insert('g');
	ft2.insert('h');
	ft2.insert('i');
	ft2.insert('j');
	ft2.insert('k');
	ft2.insert('l');
	ft2.insert('m');
	ft2.insert('n');
	ft2.insert('o');
	ft2.insert('p');
	ft2.insert('q');
	ft2.insert('r');
	ft2.insert('s');
	ft2.erase(ft2.find('a'));
	ft2.erase(ft2.find('c'));
	ft2.erase(ft2.find('g'));
	ft2.erase(ft2.find('r'));
	ft2.erase(ft2.find('n'));
	ft2.erase(ft2.find('d'));
	ft::set_details(ft2);

	ft::set<char> ft3;
	ft3.insert(ft2.begin(), ft2.end());
	ft3.erase(ft3.begin(), ft3.end());
	ft::set_details(ft3);

	ft::set<char> ft4 = ft2;
	ft::set_details(ft4);
	char c1;
	char c2;
	ft4.insert(c1);
	ft4.insert(c2);
	ft4.insert('y');
	ft4.insert('z');
	ft::set_details(ft4);

	ft4.clear();
	ft4.swap(ft2);
	ft::set_details(ft2);
	ft::set_details(ft4);
	ft::set<char>::iterator a = ft4.find('a');
	std::cout << *a << std::endl;
	for (ft::set<char>::const_reverse_iterator it = ft4.crbegin(); it != ft4.crend(); ++it)
    	std::cout << *it << std::endl;

	ft::set<char> ft5;
	ft5.insert('m');
	ft5.insert('c');
	ft5.insert('p');
	ft5.insert('a');
	ft5.insert('h');
	ft5.insert('e');
	ft5.insert('n');
	ft5.insert('t');
	ft5.insert('s');
	ft5.insert('y');
	ft::set_details(ft5);
	std::cout << "upper_bound: " << *ft5.upper_bound('f') << std::endl;
	std::cout << "lower_bound: " << *ft5.lower_bound('n') << std::endl;

	return 0;
}
