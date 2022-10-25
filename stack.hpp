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
