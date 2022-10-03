#ifndef VECTOR_HPP
#define VECTOR_HPP

#ifndef null_ptr
#define  null_ptr NULL
#endif /*null_ptr*/
#include <memory>
#include "iterator.hpp"
#include <iostream>

namespace ft {
    template <class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T                                          value_type;
        typedef Allocator                                  allocator_type;
        typedef typename allocator_type::size_type         size_type;
        typedef typename allocator_type::difference_type   difference_type;
        typedef typename allocator_type::reference         reference;
        typedef typename allocator_type::const_reference   const_reference;
        typedef typename allocator_type::pointer           pointer;
        typedef typename allocator_type::const_pointer     const_pointer;
        typedef ft::normal_iterator<pointer, vector>       iterator;
        typedef ft::normal_iterator<const_pointer, vector> const_iterator;
        typedef ft::reverse_iterator<iterator>             reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;
    private:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _finish;
        pointer         _eos;

        ///ALLOCATOR



        inline void    _allocate_n(size_type n) {
//            if (n > max_size())
//                throw std::length_error("vector");
            _start = _alloc.allocate(n);
            _finish = _start;
            _eos = _start + n;
        }

        inline void    _build(size_type n, value_type val) {
            //debug
            if (n > capacity()) {
                std::cerr << "_build: bad capacity" << std::endl;
                return;
            } //debug
            for (size_type i = 0; i < n; i++) {
                _alloc.construct(_finish, val);
                ++_finish;
            }
        }
        template <typename ForwardIter>
        inline void    _build(ForwardIter first, ForwardIter last) {
            for (; first != last; first++) {
                _alloc.construct(_finish, *first);
                ++_finish;
            }
        }

        inline void    _destroy(pointer dest, size_type n) {
            for (size_type i = 0; i < n; i++)
                _alloc.destroy(dest + i);
        }

        inline void    _delete() {
            if (_start == null_ptr)
                return;
            clear();
            _alloc.deallocate(_start, capacity());
        }

    public:
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc),
        _start(null_ptr), _finish(null_ptr), _eos(null_ptr) { }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() ) :
        _alloc(alloc), _start(null_ptr), _finish(null_ptr), _eos(null_ptr) {
            _allocate_n(n);
            _build(n, val);
        }
        template <typename InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
                : _alloc(alloc), _start(null_ptr), _finish(null_ptr), _eos(null_ptr) {
            assign(first, last);
        }

        vector(const vector& x)
                : _alloc(x.get_allocator()), _start(null_ptr), _finish(nullptr), _eos(null_ptr)
        {
            size_type n = x.size();
            if (n > 0) {
                _allocate_n(n);
                _build(x.begin(), x.end(), ft::iterator_category(x.begin()));
            }
        }

        ~vector() { _delete(); }

        vector& operator=(const vector& other)
        {
            if (this != &other) {
                _alloc = other.get_allocator();
                assign(other.begin(), other.end());
            }
            return *this;
        }

        ///easy stuff

        void clear() { _destroy(_start, size()); }

        allocator_type  get_allocator() const { return _alloc; }

        reference       operator[](size_type n) { return _start[n]; }

        const_reference operator[](size_type n) const { return _start[n]; }

        reference       front() { return *_start; }

        const_reference front() const { return *_start; }

        reference       back() { return *(_finish - 1); }

        const_reference back() const { return *(_finish - 1); }

        iterator        begin() { return iterator(_start); }

        const_iterator  begin() const { return const_iterator(_start); }

        iterator        end() { return iterator(_finish); }

        const_iterator  end() const { return const_iterator(_finish); }

        reverse_iterator        rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator  rbegin() const { return const_reverse_iterator(end()); }

        reverse_iterator        rend() { return reverse_iterator(begin()); }

        const_reverse_iterator  rend() const { return const_reverse_iterator(begin()); }

        bool            empty() { return !size(); }

        size_type size() const { return _finish - _start; }

        size_type capacity() const { return _eos - _start; }

        
    };
};

#endif /*VECTOR_HPP*/