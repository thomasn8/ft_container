// --------------------------------------------------------------------------
// -------------------------------- STD TESTS -------------------------------- 

#include <iostream>
#include <vector>
#include "../container_details.hpp"

int main()
{
	// ************************************************************
	// ******************** TESTS CONSTRUCTORS ********************
	std::vector<int> v1;
	vector_details(v1);
	std::vector<int> v2(5, 999);
	vector_details(v2);
	std::vector<int> v3(v2.begin(), v2.end());
	vector_details(v3);
	std::vector<int> v4(3);
	vector_details(v4);
	std::vector<int> v5 = v4;
	vector_details(v5);
	std::vector<int> v6(3, 333);
	vector_details(v6);
	v5 = v6;
	vector_details(v5);
	v5 = v1;
	vector_details(v5);
	v1 = v6;
	vector_details(v1);

	// ************************************************************
	// ******************* TESTS ELEMENT ACCESS *******************
	std::vector<int> v10;
	for (int i = 0; i < 10; i++)
		v10.push_back(i);
	vector_details(v10);
	std::cout << "v10[0] = " << v10[0] << std::endl;
	std::cout << "v10[9] = " << v10[9] << std::endl;
	std::cout << "front() = " << v10.front() << std::endl;
	std::cout << "back() = " << v10.back() << std::endl;
	std::cout << "data() = " << &*v10.data() << " = " << *v10.data() << std::endl;
	std::cout << "at(0) = " << v10.at(0) << std::endl;
	std::cout << "at(1) = " << v10.at(1) << std::endl;

	// ************************************************************
	// ************************* CAPACITY *************************
	std::vector<int> v20;
	vector_details(v20);
	std::cout << "size = " << v20.size() << std::endl;
	std::cout << "empty ? " << v20.empty() << std::endl;
	std::cout << "capacity = " << v20.capacity() << std::endl;
	std::cout << "max size = " << v20.max_size() << std::endl;
	std::vector<int> v21;
	for (int i = 0; i < 10; i++)
		v21.push_back(i);
	vector_details(v21);
	std::cout << "size = " << v21.size() << std::endl;
	std::cout << "empty ? " << v21.empty() << std::endl;
	std::cout << "capacity = " << v21.capacity() << std::endl;
	std::cout << "max size = " << v21.max_size() << std::endl;

	v20.shrink_to_fit();
	vector_details(v20);
	v21.shrink_to_fit();
	vector_details(v21);
	std::vector<int> v30;
	std::vector<int> v40(4,10);
	std::vector<int> v50(40,10);
	
	v30.reserve(10);
	v40.reserve(10);
	v50.reserve(10);
	vector_details(v30);
	vector_details(v40);
	vector_details(v50);
	std::vector<int> v60(4,10);
	vector_details(v60);
	v60.reserve(4);
	vector_details(v60);

	std::vector<int> v70;
	v70.resize(1, 1);
	v70.resize(10, 10);
	v70.resize(5, 5);
	vector_details(v70);
	std::vector<int> v80(5,10);
	v80.resize(0, 9);
	v80.resize(100, 9);
	v80.resize(50, 9);
	vector_details(v80);

	std::vector<int> v81(5,10);
	v81.resize(4, 9);
	vector_details(v81);
	v81.resize(0, 9);
	vector_details(v81);
	v81.resize(100, 9);
	vector_details(v81);
	v81.resize(50, 9);
	vector_details(v81);

	// ************************************************************
	// ************************ MODIFIERS *************************
	// 1. clear (used in partout)
	std::vector<int> v100;
	std::vector<int> v110(1000, 110);
	std::vector<int> v120(v110);
	v100.clear();
	v110.clear();
	v120.clear();
	std::vector<int> v130(v110);
	v130.clear();
	vector_details(v100);
	vector_details(v110);
	vector_details(v120);
	vector_details(v130);

	// 2. assign (used in operator=, insert)
	std::vector<int> v200;
	v200.assign(10,200);
	vector_details(v200);
	std::vector<int> v210(10,210);
	v210.assign(5,9);
	vector_details(v210);
	v210.assign(25,9);
	vector_details(v210);
	v210.clear();
	vector_details(v210);
	v210.assign(v200.begin(),v200.end());
	vector_details(v210);
	v210.clear();
	std::vector<int> v220;
	v220.assign(v210.begin(),v210.end());
	vector_details(v220);
	std::vector<int> v230;
	std::vector<int> v240;
	v240.assign(v230.begin(),v230.end());
	vector_details(v240);

	// 3. erase (used in resize)
	std::vector<int> v300;
	v300.assign(5,5);
	vector_details(v300);
	v300.erase(v300.end() - 2);
	vector_details(v300);
	v300.erase(v300.begin());
	vector_details(v300);
	v300.erase(v300.begin(), v300.end());
	vector_details(v300);
	v300.assign(5,5);
	v300.erase(v300.begin()+1, v300.end()-1);
	vector_details(v300);
	v300.assign(5,5);
	std::cout << &*v300.erase(v300.begin()+2, v300.end()-2)<< std::endl;
	vector_details(v300);
	std::cout << &*v300.erase(v300.begin(), v300.end())<< std::endl;
	vector_details(v300);
	std::cout << &*v300.erase(v300.begin(), v300.end())<< std::endl;
	vector_details(v300);

	// 4. insert (used in resize)
	// #1
	std::vector<int> v400;
	v400.insert(v400.begin(),2);
	v400.insert(v400.begin(),1);
	v400.insert(v400.end(),3);
	v400.insert(v400.end(),4);
	vector_details(v400);
	v400.clear();
	v400.insert(v400.begin(),1);
	v400.insert(v400.end(),2);
	vector_details(v400);
	// #2
	std::vector<int> v401;
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
	std::vector<int> v402;
	std::vector<int> v403;
	v402.insert(v402.begin(),v401.begin()+1, v401.end()-3);
	v403.insert(v403.end(),v401.begin()+1, v401.end()-3);
	vector_details(v402);
	vector_details(v403);
	v402.clear();
	v403.clear();
	v402.insert(v402.begin(),v401.begin()+1, v401.end()-3);
	v403.insert(v403.end(),v401.begin()+1, v401.end()-3);
	vector_details(v402);
	vector_details(v403);
	v402.insert(v402.begin(),v401.begin()+1, v401.end()-3);
	v403.insert(v403.end(),v401.begin()+1, v401.end()-3);
	vector_details(v402);
	vector_details(v403);
	std::vector<int> v404;
	v404.insert(v404.begin(),v401.begin(), v401.begin());
	v404.insert(v404.begin(),v401.end(), v401.end());
	vector_details(v404);

	// 5. push_back et pop_back
	std::vector<int> v500;
	std::vector<int> v501(30, 0);
	std::vector<int> v502(30, 0);
	v502.clear();
	for (int i = 0; i<12; i++)
		v500.push_back(i);
	for (int i = 0; i<12; i++)
		v501.push_back(i);
	for (int i = 0; i<12; i++)
		v502.push_back(i);
	vector_details(v500);
	vector_details(v501);
	vector_details(v502);

	v502.pop_back();
	vector_details(v502);
	/* 	// Undefined behavior in std::vector
		// v502.clear();
		// v502.pop_back();
		// vector_details(v502);
		// std::vector<int> v503;
		// v503.pop_back();
		// vector_details(v503);
	*/
	
	// 6. swap
	std::vector<int> v600;
	std::vector<int> v601;
	std::swap(v600, v601);
	std::swap(v601, v600);
	vector_details(v600);
	vector_details(v601);
	std::vector<int> v602(5,1);
	std::vector<int> v603(3,9);
	std::swap(v602, v603);
	std::swap(v603, v602);
	vector_details(v602);
	vector_details(v603);
	std::vector<int> v604;
	std::vector<int> v605(3,5);
	std::swap(v604, v605);
	std::swap(v605, v604);
	vector_details(v604);
	vector_details(v605);
	std::vector<int> v606;
	v606.clear();
	std::vector<int> v607(20,10);
	std::swap(v606, v607);
	std::swap(v607, v606);
	vector_details(v606);
	vector_details(v607);

	// ************************************************************
	// **************** TESTS RELATIONAL OPERATORS ****************
	std::vector<int> foo (3,100);   // three ints with a value of 100
	std::vector<int> bar (2,200);   // two ints with a value of 200
	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	return 0;
}
