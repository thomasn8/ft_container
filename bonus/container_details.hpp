#ifndef CONTAINER_DETAILS_HPP
# define CONTAINER_DETAILS_HPP

#include <iostream>
#include "set.hpp"

namespace ft
{
// AFFICHE LE DETAIL D'UN FT::SET CONTAINER
	template<class T>
	void set_details(const ft::set<T> & s)
	{
		std::cout << std::endl << "----------------------- DETAILS ------------------------" << std::endl;
		std::cout << "Size = " << s.size() << std::endl << std::endl;
		if (s.size())
		{
			typename ft::set<T>::const_iterator it = s.cbegin();
			typename ft::set<T>::const_iterator ite = s.cend();
			while (it != ite)
			{
				std::cout << "It  " << it.getNode() << ": " << *it << std::endl;
				it++;
			}
			std::cout << "Ite " << ite.getNode() << std::endl;
		}
		else
			std::cout << "set container is empty" << std::endl << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}
	template<class T>
	void set_rev_details(const ft::set<T> & s)
	{
		std::cout << std::endl << "----------------------- DETAILS ------------------------" << std::endl;
		std::cout << "Size = " << s.size() << std::endl << std::endl;
		if (s.size())
		{
			typename ft::set<T>::const_reverse_iterator it = s.crbegin();
			typename ft::set<T>::const_reverse_iterator ite = s.crend();
			while (it != ite)
			{
				std::cout << "It  " << it.base().getNode() << ": " << *it << std::endl;
				it++;
			}
			std::cout << "Its " << ite.base().getNode() << std::endl;
		}
		else
			std::cout << "set container is empty" << std::endl << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
	}
}

#endif
