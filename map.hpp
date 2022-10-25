#pragma once

#include "tree.hpp"
#include "pair.hpp"
#include "compare.hpp"
#include <functional>
#include <iostream>

namespace ft {
    template <typename Key, typename T, typename Compare>
    class map_value_type_compare : public std::binary_function<Key, Key, bool>
    {
    public:
        typedef Key  first_argument_type;
        typedef Key  second_argument_type;
        typedef bool result_type;

    public:
        map_value_type_compare() : _comp() {}

        map_value_type_compare(const Compare& c) : _comp(c) {}

    public:
        const Compare& key_comp() const { return _comp; }

        bool operator()(const T& x, const T& y) const { return _comp(x.first, y.first); }

        bool operator()(const Key& x, const T& y) const { return _comp(x, y.first); }

        bool operator()(const T& x, const Key& y) const { return _comp(x.first, y); }

        void swap(map_value_type_compare& other) { std::swap(_comp, other._comp); }

    protected:
        Compare _comp;
    };

    template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {
    public:
		typedef					Key													key_type;
		typedef					T   												mapped_type;
		typedef					pair<const key_type, mapped_type>					value_type;
		typedef					Compare												key_compare;
		typedef					Alloc												allocator_type;
		typedef typename		allocator_type::reference							reference;
		typedef typename		allocator_type::const_reference						const_reference;
		typedef typename		allocator_type::pointer								pointer;
		typedef typename		allocator_type::const_pointer						const_pointer;
        typedef					size_t                                              size_type;

    private:
        typedef map_value_type_compare<key_type, value_type, key_compare>  value_type_compare;
        typedef ft::tree<value_type, value_type_compare, allocator_type>   tree_type;
        tree_type _container;
    public:
		typedef typename        tree_type::iterator               iterator;
		typedef typename        tree_type::const_iterator         const_iterator;
		typedef typename        tree_type::reverse_iterator       reverse_iterator;
		typedef typename        tree_type::const_reverse_iterator const_reverse_iterator;
		typedef typename        tree_type::difference_type        difference_type;


        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class map<Key, T, Compare>;
        protected :
            Compare _comp;
        public:
            value_compare(Compare c) : _comp(c) {}
            bool operator()(const value_type& x, const value_type& y) const {
                return _comp(x.first, y.first);
            }
        };
        explicit map( const Compare& comp = key_compare(), const Alloc& alloc = Alloc() ) :
        _container(comp, alloc) { }
        template< class InputIt >
        map( InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc() ) :
        _container(comp, alloc) {
            _container.insert_range(first, last);
        }

        map( const map& other ) : _container(other._container) {}

        ~map() {}

        map& operator=(const map& other) {
            _container = other._container;
            return *this;
        }

        iterator        begin()       { return _container.begin(); }
        const_iterator  begin() const { return _container.begin(); }
        iterator        end()         { return _container.end(); }
        const_iterator  end()   const { return _container.end(); }

        reverse_iterator        rbegin()       { return reverse_iterator(end()); }
        const_reverse_iterator  rbegin() const { return const_reverse_iterator(end()); }
        reverse_iterator        rend()         { return reverse_iterator(begin()); }
        const_reverse_iterator  rend()   const { return const_reverse_iterator(begin()); }

        allocator_type  get_allocator() const { return _container.get_allocator(); }
        bool            empty()  const { return _container.size() == 0; }
        size_type       size()   const { return _container.size(); }
        size_type       max_size() const { return _container.max_size(); }

        void            clear()        { _container.clear(); }
        key_compare     key_comp()     { return key_compare(); }
        value_compare   value_comp()     { return value_compare(key_comp()); }

        iterator        find(const Key& key) { return _container.find(key); }
        const_iterator  find(const Key& key) const { return _container.find(key); }
        size_type       count(const Key& key) const { return _container.find(key) != end(); }

        ft::pair<iterator, iterator> equal_range(const Key& key) { return _container.equal_range(key); }
        ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const { return _container.equal_range(key); }

        iterator        lower_bound(const Key& key) { return _container.lower_bound(key); }
        const_iterator  lower_bound(const Key& key) const { return _container.lower_bound(key); }
        iterator        upper_bound(const Key& key) { return _container.upper_bound(key); }
        const_iterator  upper_bound(const Key& key) const { return _container.upper_bound(key); }

        mapped_type& operator[](const key_type& key) {
            return (*((insert(value_type(key, T()))).first)).second;
        }

        mapped_type& at(const key_type& key)
        {
            iterator it = _container.find(key);
            if (it == end())
                throw std::out_of_range("map::at:  key not found");
            return it->second;
        }

        const mapped_type& at(const key_type& key) const
        {
            const_iterator it = _container.find(key);
            if (it == end())
                throw std::out_of_range("map::at:  key not found");
            return it->second;
        }

        ft::pair<iterator, bool>  insert( const value_type& value ) { return _container.insert(value); }
        iterator                  insert(iterator pos, const value_type& value) { return _container.insert(const_iterator(pos), value); }
        template <class InputIt>
        void                      insert(InputIt first, InputIt last) { _container.insert_range(first, last); }

        void                      erase(iterator pos) { _container.erase_node(pos); }
        void                      erase(iterator first, iterator last) { _container.erase_range(first, last); }
        size_type                 erase(const Key& key) { return _container.erase_key(key); }

        void swap(map& other) { _container.swap(other._container); }
    };

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline bool operator==(const map<Key, T, Compare, Allocator>& lhs,
                           const map<Key, T, Compare, Allocator>& rhs)
    {
        return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
                           const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline bool operator<(const map<Key, T, Compare, Allocator>& lhs,
                          const map<Key, T, Compare, Allocator>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
                           const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline bool operator>(const map<Key, T, Compare, Allocator>& lhs,
                          const map<Key, T, Compare, Allocator>& rhs)
    {
        return rhs < lhs;
    }

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
                           const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(lhs < rhs);
    }

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline void swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
    {
        x.swap(y);
    }
}