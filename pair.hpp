#pragma once

namespace ft {
	template <class T1, class T2>
	class pair {
	public:
		T1	first;
		T2	second;
		//assignment and construction
		pair() : first(), second() {};
		template <class U1, class U2>
		pair(const pair<U1, U2>& ori) : first(ori.first), second(ori.second) {}
		explicit pair(const T1& val_one, const T2& val_two) : first(val_one), second(val_two) {}
//		pair& operator=(const pair& ori) {this->first = ori.first; this->second = ori.second; return *this; }

		//operator overload
		bool operator== (const pair& sec) {
			if (first == sec.first && second == sec.second)
				return true;
			return false;
		}
		bool operator!= (const pair& sec) {
			if  (this == sec)
				return false;
			return true;
		}
		bool operator<  (const pair& sec) {
			if (first < sec.first)
				return true;
			else if (first == sec.first && second < sec.second)
				return true;
			return false;
		}
		bool operator<= (const pair& sec) {
			return !(sec < this);
		}
		bool operator>  (const pair& sec) {
			if (sec < this)
				return true;
			return false;
		}
		bool operator>= (const pair& sec) {
			return !(sec > this);
		}
	};
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 val_one, T2 val_two) {
			return pair<T1, T2>(val_one, val_two);
		}
}
