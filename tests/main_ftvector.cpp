// --------------------------------------------------------------------------
// -------------------------------- FT TESTS -------------------------------- 

#include <iostream>
#include "../vector.hpp"
#include "../container_details.hpp"

int main()
{
	// ************************************************************
	// ******************** TESTS CONSTRUCTORS ********************
	ft::vector<int> v1;
	ft::vector_details(v1);
	ft::vector<int> v2(5, 999);
	ft::vector_details(v2);
	ft::vector<int> v3(v2.begin(), v2.end());
	ft::vector_details(v3);
	ft::vector<int> v4(3);
	ft::vector_details(v4);
	ft::vector<int> v5 = v4;
	ft::vector_details(v5);
	ft::vector<int> v6(3, 333);
	ft::vector_details(v6);
	v5 = v6;
	ft::vector_details(v5);
	v5 = v1;
	ft::vector_details(v5);
	v1 = v6;
	ft::vector_details(v1);

	// ************************************************************
	// ******************* TESTS ELEMENT ACCESS *******************
	ft::vector<int> v10;
	for (int i = 0; i < 10; i++)
		v10.push_back(i);
	ft::vector_details(v10);
	std::cout << "v10[0] = " << v10[0] << std::endl;
	std::cout << "v10[9] = " << v10[9] << std::endl;
	std::cout << "front() = " << v10.front() << std::endl;
	std::cout << "back() = " << v10.back() << std::endl;
	std::cout << "data() = " << &*v10.data() << " = " << *v10.data() << std::endl;
	std::cout << "at(0) = " << v10.at(0) << std::endl;
	std::cout << "at(1) = " << v10.at(1) << std::endl;

	// ************************************************************
	// ************************* CAPACITY *************************
	ft::vector<int> v20;
	ft::vector_details(v20);
	std::cout << "size = " << v20.size() << std::endl;
	std::cout << "empty ? " << v20.empty() << std::endl;
	std::cout << "capacity = " << v20.capacity() << std::endl;
	std::cout << "max size = " << v20.max_size() << std::endl;
	ft::vector<int> v21;
	for (int i = 0; i < 10; i++)
		v21.push_back(i);
	ft::vector_details(v21);
	std::cout << "size = " << v21.size() << std::endl;
	std::cout << "empty ? " << v21.empty() << std::endl;
	std::cout << "capacity = " << v21.capacity() << std::endl;
	std::cout << "max size = " << v21.max_size() << std::endl;
	
	v20.shrink_to_fit();
	ft::vector_details(v20);
	v21.shrink_to_fit();
	ft::vector_details(v21);
	ft::vector<int> v30;
	ft::vector<int> v40(4,10);
	ft::vector<int> v50(40,10);
	
	v30.reserve(10);
	v40.reserve(10);
	v50.reserve(10);
	ft::vector_details(v30);
	ft::vector_details(v40);
	ft::vector_details(v50);
	ft::vector<int> v60(4,10);
	ft::vector_details(v60);
	v60.reserve(4);
	ft::vector_details(v60);

	ft::vector<int> v70;
	v70.resize(1, 1);
	v70.resize(10, 10);
	v70.resize(5, 5);
	ft::vector_details(v70);
	ft::vector<int> v80(5,10);
	v80.resize(0, 9);
	v80.resize(100, 9);
	v80.resize(50, 9);
	ft::vector_details(v80);

	ft::vector<int> v81(5,10);
	v81.resize(4, 9);
	ft::vector_details(v81);
	v81.resize(0, 9);
	ft::vector_details(v81);
	v81.resize(100, 9);
	ft::vector_details(v81);
	v81.resize(50, 9);
	ft::vector_details(v81);

	// ************************************************************
	// ************************ MODIFIERS *************************
	// 1. clear (used in partout)
	ft::vector<int> v100;
	ft::vector<int> v110(1000, 110);
	ft::vector<int> v120(v110);
	v100.clear();
	v110.clear();
	v120.clear();
	ft::vector<int> v130(v110);
	v130.clear();
	ft::vector_details(v100);
	ft::vector_details(v110);
	ft::vector_details(v120);
	ft::vector_details(v130);

	// 2. assign (used in operator=, insert)
	ft::vector<int> v200;
	v200.assign(10,200);
	ft::vector_details(v200);
	ft::vector<int> v210(10,210);
	v210.assign(5,9);
	ft::vector_details(v210);
	v210.assign(25,9);
	ft::vector_details(v210);
	v210.clear();
	ft::vector_details(v210);
	v210.assign(v200.begin(),v200.end());
	ft::vector_details(v210);
	v210.clear();
	ft::vector<int> v220;
	v220.assign(v210.begin(),v210.end());
	ft::vector_details(v220);
	ft::vector<int> v230;
	ft::vector<int> v240;
	v240.assign(v230.begin(),v230.end());
	ft::vector_details(v240);

	// 3. erase (used in resize)
	ft::vector<int> v300;
	v300.assign(5,5);
	ft::vector_details(v300);
	v300.erase(v300.end() - 2);
	ft::vector_details(v300);
	v300.erase(v300.begin());
	ft::vector_details(v300);
	v300.erase(v300.begin(), v300.end());
	ft::vector_details(v300);
	v300.assign(5,5);
	v300.erase(v300.begin()+1, v300.end()-1);
	ft::vector_details(v300);
	v300.assign(5,5);
	std::cout << &*(v300.erase(v300.begin()+2, v300.end()-2)) << std::endl;
	ft::vector_details(v300);
	std::cout << &*(v300.erase(v300.begin(), v300.end()))<< std::endl;
	ft::vector_details(v300);
	std::cout << &*(v300.erase(v300.begin(), v300.end()))<< std::endl;
	ft::vector_details(v300);

	// 4. insert (used in resize)
	// #1
	ft::vector<int> v400;
	v400.insert(v400.begin(),2);
	v400.insert(v400.begin(),1);
	v400.insert(v400.end(),3);
	v400.insert(v400.end(),4);
	ft::vector_details(v400);
	v400.clear();
	v400.insert(v400.begin(),1);
	v400.insert(v400.end(),2);
	ft::vector_details(v400);
	// #2
	ft::vector<int> v401;
	v401.insert(v401.begin(),3,2);
	v401.insert(v401.begin(),3,1);
	v401.insert(v401.end(),3,3);
	v401.insert(v401.end(),4,4);
	vector_details(v401);
	v401.clear();
	v401.insert(v401.begin(),3,1);
	v401.insert(v401.end(),3,2);
	vector_details(v401);
	v401.insert(v401.begin()+3,3,5);
	vector_details(v401);
	v401.insert(v401.end() - 1,3,2);
	vector_details(v401); 
	// #3
	ft::vector<int> v402;
	ft::vector<int> v403;
	v402.insert(v402.begin(),v401.begin()+1, v401.end()-3);
	v403.insert(v403.end(),v401.begin()+1, v401.end()-3);
	ft::vector_details(v402);
	ft::vector_details(v403);
	v402.clear();
	v403.clear();
	v402.insert(v402.begin(),v401.begin()+1, v401.end()-3);
	v403.insert(v403.end(),v401.begin()+1, v401.end()-3);
	ft::vector_details(v402);
	ft::vector_details(v403);
	v402.insert(v402.begin(),v401.begin()+1, v401.end()-3);
	v403.insert(v403.end(),v401.begin()+1, v401.end()-3);
	ft::vector_details(v402);
	ft::vector_details(v403);
	ft::vector<int> v404;
	v404.insert(v404.begin(),v401.begin(), v401.begin());
	v404.insert(v404.begin(),v401.end(), v401.end());
	ft::vector_details(v404);

	// 5. push_back et pop_back
	ft::vector<int> v500;
	ft::vector<int> v501(30, 0);
	ft::vector<int> v502(30, 0);
	v502.clear();
	for (int i = 0; i<12; i++)
		v500.push_back(i);
	for (int i = 0; i<12; i++)
		v501.push_back(i);
	for (int i = 0; i<12; i++)
		v502.push_back(i);
	ft::vector_details(v500);
	ft::vector_details(v501);
	ft::vector_details(v502);
	
	v502.pop_back();
	ft::vector_details(v502);
	/*	// behavior in ft::vector is defined
		// v502.clear();
		// v502.pop_back();
		// ft::vector_details(v502);
		// ft::vector<int> v503;
		// v503.pop_back();
		// ft::vector_details(v503);
	*/

	// 6. swap
	ft::vector<int> v600;
	ft::vector<int> v601;
	ft::swap(v600, v601);
	ft::swap(v601, v600);
	ft::vector_details(v600);
	ft::vector_details(v601);
	ft::vector<int> v602(5,1);
	ft::vector<int> v603(3,9);
	ft::swap(v602, v603);
	ft::swap(v603, v602);
	ft::vector_details(v602);
	ft::vector_details(v603);
	ft::vector<int> v604;
	ft::vector<int> v605(3,5);
	ft::swap(v604, v605);
	ft::swap(v605, v604);
	ft::vector_details(v604);
	ft::vector_details(v605);
	ft::vector<int> v606;
	v606.clear();
	ft::vector<int> v607(20,10);
	ft::swap(v606, v607);
	ft::swap(v607, v606);
	ft::vector_details(v606);
	ft::vector_details(v607);

	// ************************************************************
	// **************** TESTS RELATIONAL OPERATORS ****************
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (2,200);   // two ints with a value of 200
	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	// ************************************************************
	// ****************** VECTOR ADVANCED (EVAL) ******************
	
	const ft::vector<int> bar2 (2,200);
	ft::vector<int>::iterator comp1 = foo.begin();
	ft::vector<int>::const_iterator comp2 = bar2.begin();
	
	if (comp2 > comp1)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	
	ft::vector<int> container1(5,5);
	ft::vector<int> container2(10,10);
	ft::vector<int>::iterator it1 = container1.begin();
	ft::vector<int>::iterator it2 = container2.begin();
	std::cout << "CONTAINER 1: " << &*container1.begin() << "->" << *container1.begin() << " = " << &*it1 << "->" << *it1 << std::endl;
	std::cout << "CONTAINER 2: "  << &*container2.begin() << "->" << *container2.begin() << " = " << &*it2 << "->" << *it2 << std::endl;
	std::cout << "swap " << std::endl;
	ft::swap(container1,container2);
	std::cout << "CONTAINER 1: " << &*container1.begin() << "->" << *container1.begin() << " = " << &*it2 << "->" << *it2 << std::endl;
	std::cout << "CONTAINER 2: " << &*container2.begin() << "->" << *container2.begin() << " = " << &*it1 << "->" << *it1 << std::endl;

	return 0;
}
