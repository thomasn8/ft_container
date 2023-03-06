#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
// ENABLE_IF
	template<bool Cond, class T = void>
	struct enable_if {};
	template<class T>
	struct enable_if<true, T> { typedef T type; };

// IS_INTEGRAL
	template<typename T>
	struct is_integral { const static bool value = false; };
	template<>
	struct is_integral<int> { const static bool value = true; };
	template<>
	struct is_integral<char> { const static bool value = true; };
	template<>
	struct is_integral<unsigned int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned char> { const static bool value = true; };
	template<>
	struct is_integral<short unsigned int> { const static bool value = true; };
	template<>
	struct is_integral<short int> { const static bool value = true; };
	template<>
	struct is_integral<long unsigned int> { const static bool value = true; };
	template<>
	struct is_integral<long int> { const static bool value = true; };
	template<>
	struct is_integral<bool> { const static bool value = true; };
	template<>
	struct is_integral<wchar_t> { const static bool value = true; };

// EQUALITY COMPARE
	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2)
	{
		while (first1 != last1) 
		{
			if (!(*first1++ == *first2++))
				return false;
		}
		return true;
	}
	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1) 
		{
			if (!pred(*first1, *first2))
				return false;
			++first1; 
			++first2;
		}
		return true;
	}

// LEXICOGRAPHICAL COMPARE
	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;				
			else if (*first1 < *first2)
				return true;
			++first1; 
			++first2;
		}
		return (first2 != last2);
	}
	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; 
			++first2;
		}
		return (first2 != last2);
	}
}

#endif