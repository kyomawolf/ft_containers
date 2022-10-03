#ifndef VECTOR_HPP
#define VECTOR_HPP

#ifndef null_ptr
#define  null_ptr NULL
#endif /*null_ptr*/
#include <memory>
#include <iostream>
#include "iterator.hpp"
#include "compare.hpp"

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

        reference at( size_type pos ) { if (pos < size()) return _start[pos]; throw std::out_of_range("vector"); }

        const_reference at( size_type pos ) const { if (pos < size()) return _start[pos]; throw std::out_of_range("vector"); }

        size_type   max_size() const { return static_cast<size_type>(_alloc.max_size() < std::numeric_limits<difference_type>::max() ? _alloc.max_size() : std::numeric_limits<difference_type>::max()); }

        ///assign

        void    assign(size_type n, value_type& val) {
            if (_start != null_ptr && !empty())
                clear();
            resize(n, val);
        }

        template <typename InputIterator>
        void    assign(InputIterator first, InputIterator last,
                       typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
            if (_start != null_ptr && !empty())
                clear();
            for (; first != last; first++)
                push_back(*first);
        }

        ///data

        value_type* data() { return _start; }

        const value_type* data() const { return _start; }

        ///manipulation

        void    push_back(value_type& val) {
            reserve(size() + 1);
            _build(1, val);
        }

        void    pop_back() {
            if (empty())
                return;
            _destroy(_finish - 1);
            --_finish;
        }

        iterator erase(iterator pos) {
            if (pos + 1 == end()) {
                pop_back();
            } else {
                iterator cp = pos;
                for (iterator first = pos + 1; first != end(); first++) {
                    *cp = *first;
                    ++cp;
                }
            }
            return pos;
        }

        iterator erase(iterator first, iterator last) {
            if (last + 1 == end()) {
                _destroy(pointer(*first), last - first);
                _finish -= last - first;
            } else {
                for (iterator cp = first, cp_l = last + 1; cp_l != end(); cp++, cp_l++) {
                    *cp = *cp_l;
                }
                _destroy(pointer(*(first + (end() - last))), end() - last);
                _finish -= end() - last;
            }
            return first;
        }



        //TODO insert
        //TODO swap
        ///sizestuff

        void    resize(size_type n, value_type val = value_type()) {
            reserve(n);
            _build(n - size(), val);
        }

        void reserve(size_type n) {
            if (n <= capacity())
                return;
            if (n > max_size())
                throw std::length_error("vector");
            pointer old_start = _start;
            pointer old_finish = _finish;
            pointer old_eos = _eos;
            _allocate_n(n);
            _build(pointer(old_start), old_finish);
            _destroy(old_start, old_finish - old_start);
            _alloc.deallocate(old_start, old_eos - old_start);
        }

        /// comparison

    };
    template <typename T, typename Allocator>
    inline bool    operator==(const vector<T, Allocator>& first, const vector<T, Allocator>& sec) {
        if (first.size() == sec.size() && ft::equal(first.begin(), first.end(), sec.begin()))
            return true;
        return false;
    }
    template <typename T, typename Allocator>
    inline bool    operator!=(const vector<T, Allocator>& first, const vector<T, Allocator>& sec) {
        if (!(first == sec))
            return true;
        return false;
    }
    template <typename T, typename Allocator>
    inline bool    operator<(const vector<T, Allocator>& first, const vector<T, Allocator>& sec) {
        return ft::lexicographical_compare(first.begin(), first.end(), sec.begin(), sec.end());
    }
    template <typename T, typename Allocator>
    inline bool    operator>(const vector<T, Allocator>& first, const vector<T, Allocator>& sec) {
        return sec < first;
    }
    template <typename T, typename Allocator>
    inline bool    operator<=(const vector<T, Allocator>& first, const vector<T, Allocator>& sec) {
        return !(sec < first);
    }
    template <typename T, typename Allocator>
    inline bool    operator>=(const vector<T, Allocator>& first, const vector<T, Allocator>& sec) {
        return !(first < sec);
    }

    template <typename T, typename Allocator>
    inline void swap(vector<T, Allocator>& first, vector<T, Allocator>& sec) {
        first.swap(sec);
    }
};

#endif /*VECTOR_HPP*/