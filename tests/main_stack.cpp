// --------------------------------------------------------------------------
// -------------------------------- FT TESTS -------------------------------- 

#include <iostream>
#include "../vector.hpp"
#include "../stack.hpp"
#include "../container_details.hpp"
#include <vector>

int main()
{
	ft::vector<int> v1(5, 999);
	ft::vector_details(v1);
	
	ft::stack<int> s1;
	std::cout << "size: " << s1.size() << std::endl;
	std::cout << "empty: " << s1.empty() << std::endl;
	
	std::cout << std::endl;

	ft::stack<int> s2(v1);
	std::cout << "size: " << s2.size() << std::endl;
	std::cout << "empty: " << s2.empty() << std::endl;
	std::cout << "top: " << s2.top() << std::endl;
	s2.top() -= 333;
	std::cout << "top: " << s2.top() << std::endl;
	s2.push(4);
	std::cout << "top: " << s2.top() << std::endl;
	s2.push(v1.front());
	std::cout << "top: " << s2.top() << std::endl;
	s2.pop();
	std::cout << "top: " << s2.top() << std::endl;

	std::cout << std::endl;

	std::cout << "size: " << s1.size() << std::endl;
	std::cout << "size: " << s2.size() << std::endl;
	s2.swap(s1);
	std::cout << "size: " << s1.size() << std::endl;
	std::cout << "size: " << s2.size() << std::endl;
	ft::swap(s1, s2);
	std::cout << "size: " << s1.size() << std::endl;
	std::cout << "size: " << s2.size() << std::endl;

	std::cout << std::endl;

	ft::vector<int> foo_v (3,100);   // three ints with a value of 100
	ft::vector<int> bar_v (2,200);   // two ints with a value of 200
	ft::stack<int> foo(foo_v);
	ft::stack<int> bar( bar_v);
	if (foo == bar) std::cout << "foo and bar are equal\n";
	if (foo != bar) std::cout << "foo and bar are not equal\n";
	if (foo  < bar) std::cout << "foo is less than bar\n";
	if (foo  > bar) std::cout << "foo is greater than bar\n";
	if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";

	return 0;
}