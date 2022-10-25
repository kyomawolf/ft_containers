#include "vector.hpp"

namespace ft {
    template <typename T, typename Container = ft::vector<T> >
    class stack {
    protected:
        Container c;
    public:
        typedef Container                           container_type;
        typedef typename Container::value_type      value_type;
        typedef typename Container::size_type       size_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;

        stack( const Container& cont = Container() ) : c(cont) { }
        stack( const stack& other ) : c(other.c) { }
        ~stack() {}

        stack& operator=( const stack& other ) {
            c = other.c;
            return *this;
        }

        reference top() {
            return c.back();
        }
        const_reference top() const {
            return c.back();
        }

        bool empty() const {
            return c.empty();
        }

        size_type size() const {
            return c.size();
        }

        void push( const value_type& value ) {
            c.push_back(value);
        }

        void pop() {
            c.pop_back();
        }
        bool operator==(const ft::stack<T, container_type> & rhs ) {
            return c == rhs.c;
        }
        bool operator!=(const ft::stack<T, container_type> & rhs ) {
            return c != rhs.c;
        }
        bool operator<( const ft::stack<T, container_type> & rhs ) {
            return c < rhs.c;
        }
        bool operator<=(const ft::stack<T, container_type> & rhs ) {
            return c <= rhs.c;
        }
        bool operator>(const  ft::stack<T, container_type> & rhs ) {
            return c > rhs.c;
        }
        bool operator>=(const ft::stack<T, container_type> & rhs ) {
            return c >= rhs.c;
        }
    };


};

//namespace ft {
//	template <class T, class Container = vector<T> >
//	class stack {
//	private:
//		Container	cont;
//	public:
//		typedef T value_type;
//		typedef Container container_type;
//		typedef typename vector<T>::size_type size_type;
//
//		explicit stack (const Container& ctnr = container_type()) {
//			cont = ctnr;
//		}
//		bool				empty()								const {
//			return cont.empty();
//		}
//		size_type			size()								const {
//			return cont.size();
//		}
//		value_type&			top() {
//			return cont.back();
//		}
//		const value_type&	top() 								const{
//			return cont.back();
//		}
//		void				push(const value_type& val) {
//			cont.push_back(val);
//		}
//		void				pop() {
//			cont.pop_back();
//		}
//
//		//OPERATOR OVERLOADS
//		bool operator== (const stack<T, Container>& rhs) {
//			return (cont == rhs.cont);
//		}
//		bool operator!= (const stack<T, Container>& rhs) {
//			return (cont != rhs.cont);
//		}
//		bool operator<  (const stack<T, Container>& rhs) {
//			return (cont < rhs.cont);
//		}
//		bool operator<= (const stack<T, Container>& rhs) {
//			return (cont <= rhs.cont);
//		}
//		bool operator>  (const stack<T, Container>& rhs) {
//			return (cont > rhs.cont);
//		}
//		bool operator>= (const stack<T, Container>& rhs) {
//			return (cont >= rhs.cont);
//		}
//	};
//}