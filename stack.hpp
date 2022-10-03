#include "vector.hpp"

namespace ft {
	template <class T, class Container = vector<T> >
	class stack {
	private:
		Container	cont;
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef typename vector<T>::size_type size_type;

		explicit stack (const Container& ctnr = container_type()) {
			cont = ctnr;
		}
		bool				empty()								const {
			return cont.empty();
		}
		size_type			size()								const {
			return cont.size();
		}
		value_type&			top() {
			return cont.back();
		}
		const value_type&	top() 								const{
			return cont.back();
		}
		void				push(const value_type& val) {
			cont.push_back(val);
		}
		void				pop() {
			cont.pop_back();
		}

		//OPERATOR OVERLOADS
		bool operator== (const stack<T, Container>& rhs) {
			return (cont == rhs.cont);
		}
		bool operator!= (const stack<T, Container>& rhs) {
			return (cont != rhs.cont);
		}
		bool operator<  (const stack<T, Container>& rhs) {
			return (cont < rhs.cont);
		}
		bool operator<= (const stack<T, Container>& rhs) {
			return (cont <= rhs.cont);
		}
		bool operator>  (const stack<T, Container>& rhs) {
			return (cont > rhs.cont);
		}
		bool operator>= (const stack<T, Container>& rhs) {
			return (cont >= rhs.cont);
		}
	};
}