#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2> 
	class pair
	{
		public : 
		typedef T1	first_type;
		typedef T2	second_type;
		
		first_type 	first;
		second_type	second;

		pair() : first(first_type()), second(second_type()) {}
		template<class U, class V> 
		pair(const pair<U, V> & pr) : first(pr.first), second(pr.second) {}
		pair(const first_type & a, const second_type & b) : first(a), second(b) {}
		pair & operator=(const pair & pr) { this->first = pr.first; this->second = pr.second; return *this; }
		~pair() {}

		void swap(pair & pr)
		{
			pair<first_type, second_type> tmp = pr;
			pr.first = this->first;
			pr.second = this->second;
			this->first = tmp.first;
			this->second = tmp.second;
		}
	};

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y) { return (pair<T1,T2>(x,y)); }

	template <class T1, class T2>
	void swap(pair<T1,T2> & x, pair<T1,T2> & y)
	{
		pair<T1, T2> tmp = x;
		x = y;
		y = tmp;
	}

	template<class T1, class T2>
	bool operator==(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs) 
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second); }

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
	{ return lhs.first <= rhs.first; }

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> & lhs, const pair<T1,T2> & rhs)
	{ return lhs.first > rhs.first || (lhs.first == rhs.first && lhs.second > rhs.second); }

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
	{ return lhs.first >= rhs.first; }
}

#endif
