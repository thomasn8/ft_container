#ifndef CONTAINER_DETAILS_HPP
# define CONTAINER_DETAILS_HPP

#include <iostream>
#include <vector>
#include <map>
#include "vector.hpp"
#include "map.hpp"

namespace ft
{
// AFFICHE LE DETAIL D'UN FT::VECTOR CONTAINER
	template<class T>
	void vector_details(const ft::vector<T> & v)
	{
		std::cout << std::endl << "----------------------- DETAILS ------------------------" << std::endl;
		std::cout << "Size = " << v.size() << " | Capacity = " << v.capacity() << std::endl << std::endl;
		if (v.size())
		{
			typename ft::vector<T>::const_iterator it = v.begin();
			typename ft::vector<T>::const_iterator ite = v.end();
			int i = 0;
			while (it != ite)
			{
				std::cout << i << ": " << *it << std::endl;
				it++;
				i++;
			}
		}
		else
			std::cout << "vector container is empty" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}

// AFFICHE LE DETAIL D'UN FT::MAP CONTAINER
	template<class T1, class T2>
	void map_details(const ft::map<T1,T2> & m)
	{
		std::cout << std::endl << "----------------------- DETAILS ------------------------" << std::endl;
		std::cout << "Size = " << m.size() << std::endl << std::endl;
		if (m.size())
		{
			typename ft::map<T1,T2>::const_iterator it = m.begin();
			typename ft::map<T1,T2>::const_iterator ite = m.end();
			while (it != ite)
			{
				std::cout << "It  " << &*it << ": " << it->first << " -> " << it->second << std::endl;
				it++;
			}
			std::cout << "Ite " << &*ite << std::endl;
		}
		else
			std::cout << "map container is empty" << std::endl << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}
}


// AFFICHE LE DETAIL D'UN STD::VECTOR CONTAINER COMME ft::vector_details()
template<class T>
void vector_details(const std::vector<T> & v)
{
	std::cout << std::endl << "----------------------- DETAILS ------------------------" << std::endl;
	std::cout << "Size = " << v.size() << " | Capacity = " << v.capacity() << std::endl << std::endl;
	if (v.size())
	{
		typename std::vector<T>::const_iterator it = v.begin();
		typename std::vector<T>::const_iterator ite = v.end();
		int i = 0;
		while (it != ite)
		{
			std::cout << i << ": " << *it << std::endl;
			it++;
			i++;
		}
		// std::cout << "Ite " << &*ite << std::endl;
	}
	else
	{
		std::cout << "vector container is empty" << std::endl;
		// std::cout << "_first  " << &v.front() << std::endl;
		// std::cout << "_last   " << &v.back() << std::endl << std::endl;
	}
	std::cout << "--------------------------------------------------------" << std::endl;
}

// AFFICHE LE DETAIL D'UN STD::MAP CONTAINER COMME ft::map_details()
template<class T1, class T2>
void map_details(std::map<T1,T2> m)
{
	std::cout << std::endl << "----------------------- DETAILS ------------------------" << std::endl;
	std::cout << "Size = " << m.size() << std::endl << std::endl;
	if (m.size())
	{
		typename std::map<T1,T2>::iterator it = m.begin();
		typename std::map<T1,T2>::iterator ite = m.end();
		while (it != ite)
		{
			std::cout << "It  " << &*it << ": " << it->first << " | " << it->second << std::endl;
			it++;
		}
		std::cout << "Ite " << &*ite << std::endl;
	}
	else
		std::cout << "container is empty" << std::endl << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

#endif