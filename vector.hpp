#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#ifndef NULL && null_ptr
#define null_ptr nullptr
#elifndef null_ptr
#define  null_ptr NULL
#endif /*null_ptr*/
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
        typedef ft::random_iterator<pointer, vector>       iterator;
        typedef ft::random_iterator<const_pointer, vector> const_iterator;
        typedef ft::reverse_iterator<iterator>             reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;
    private:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _finish;
        pointer         _eos;
        bool            _has_allocated;

        ///ALLOCATOR



        inline void    _allocate_n(size_type n) {
//            if (n > max_size())
//                throw std::length_error("vector");
            _start = _alloc.allocate(n);
            _has_allocated = true;
            _finish = _start;
            _eos = _start + n;
        }

        inline void    _construct(pointer target, const_reference val) {_alloc.construct(target, val); }

        inline void    _build(size_type n, value_type val) {
            //debug
            if (n > capacity()) {
                std::cerr << "_build: bad capacity" << std::endl;
                return;
            } //debug
            for (size_type i = 0; i < n; i++) {
                _construct(_finish, val);
                ++_finish;
            }
        }
        template <typename ForwardIter>
        inline void    _build(ForwardIter first, ForwardIter last, size_type dummy) {
            (void) dummy;
            for (; first != last; first++) {
                _construct(_finish, *first);
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
            if (_has_allocated) {
                if (size() != 0)
                    _destroy(_start, size());
                _alloc.deallocate(_start, capacity());
                _has_allocated = false;
            }
        }

    public:
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc),
        _start(null_ptr), _finish(null_ptr), _eos(null_ptr), _has_allocated(false) { }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() ) :
        _alloc(alloc), _start(null_ptr), _finish(null_ptr), _eos(null_ptr) {
            _allocate_n(n);
            _build(n, val);
        }
        template <typename InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
                : _alloc(alloc), _start(null_ptr), _finish(null_ptr), _eos(null_ptr), _has_allocated(false) {
            assign(first, last);
        }

        vector(const vector& x)
                : _alloc(x.get_allocator()), _start(null_ptr), _finish(nullptr), _eos(null_ptr), _has_allocated(false)
        {
            size_type n = x.size();
            if (n > 0) {
                _allocate_n(n);
                _build(x.begin(), x.end(), 0);
            }
        }

        vector& operator=(const vector& other)
        {
            if (this != &other) {
                _alloc = other.get_allocator();
                assign(other.begin(), other.end());
            }
            return *this;
        }

        ~vector() { _delete(); }

        ///easy stuff

        void clear() { _destroy(_start, size()); _finish = _start; }

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

        size_type max_size() const {
            if (static_cast<long long>(_alloc.max_size()) < static_cast<long long>(std::numeric_limits<difference_type>::max()))
                return _alloc.max_size();
            return std::numeric_limits<difference_type>::max();
        }
        ///assign

        void    assign(size_type n, const value_type& val) {
            if (size())
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

        void    push_back(const value_type& val) {
            reserve(size() + 1);
            _build(1, val);
        }

        void    pop_back() {
            if (empty())
                return;
            _destroy(_finish - 1, 1);
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
                _destroy(_finish - 1, 1);
                --_finish;
            }
            return pos;
        }

        iterator erase(iterator first, iterator last) {
            if (last == first)
                return last;
            if (last == end()) {
                _destroy(&(*first), last - first);
                _finish -= last - first;
            } else {
                iterator cp = first, cp_l = last;
                for (; cp_l != end(); cp++, cp_l++) {
                    *cp = *cp_l;
                }
                --cp_l;
                for (difference_type i = 0; i < (last - first); i++, --cp_l) {
                    _destroy(&*cp_l, 1);
                    --_finish;
                }
            }
            return first;
        }

        void    _move_end_n(size_type pos, size_type n) {
            reserve(size() + n);
            pointer last = _finish - 1;
            size_type diff = size() - pos;
            _build(n, value_type());
            for (size_type i = 0; i < diff; i++)
                *(_finish - 1 - i) = *(last - i);
        }

        iterator insert( const_iterator pos, const T& value ) {
            size_type x = pos - begin();
            _move_end_n(x, 1);
            *(_start + x) = value;
            return iterator(_start + x);
        }

        iterator insert( const_iterator pos, size_type count, const T& value ) {
            size_type x = pos - begin();
            _move_end_n(x, count);
            pointer p = _start + x;
            for (size_type i = 0; i < count; ++i, ++p)
                *p = value;
            return iterator(_start + x);
        }

        template< class InputIterator >
        iterator insert( const_iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
            size_type x = pos - begin();
            pointer tmp = const_cast<pointer>(&*pos);
            iterator ins = tmp;
            for (; first != last; ++first, ++ins)
                ins = insert(ins, *first);
            return iterator(_start + x);
        }

        ///sizestuff

        void    resize(size_type n, value_type val = value_type()) {
            if (n < size()) {
                for (size_type i = size(); i > n; --i)
                    pop_back();
            } else {
                reserve(n);
                _build(n - size(), val);
            }
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
            if (old_finish - old_start > 0)
                _build(pointer(old_start), old_finish, 0);
            if (old_eos - old_start != 0) {
                _destroy(old_start, old_finish - old_start);
                _alloc.deallocate(old_start, old_eos - old_start);
            }
        }

        void    swap(vector& other) {
            ft::swap(_alloc, other._alloc);
            ft::swap(_start, other._start);
            ft::swap(_finish, other._finish);
            ft::swap(_eos, other._eos);
        }

    };
    /// comparison
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

//void remove_node_(node_pointer root, node_pointer node)
//{
//    node_pointer repl =
//            (node->left == nullptr || node->right == nullptr) ? node : RBTree_next(node);
//    node_pointer repl_child = repl->left != nullptr ? repl->left : repl->right;
//    node_pointer sibling = nullptr;
//    if (repl_child != nullptr)
//        repl_child->parent = repl->parent;
//    if (repl == repl->parent->left) {
//        repl->parent->left = repl_child;
//        if (repl == root)
//            root = repl_child;
//        else
//            sibling = repl->parent->right;
//    } else {
//        repl->parent->right = repl_child;
//        sibling = repl->parent->left;
//    }
//    bool removed_black = (repl->color == BLACK);
//    if (repl != node) {
//        if (node == root)
//            root = repl;
//        repl->parent = node->parent;
//        if (node == node->parent->left)
//            repl->parent->left = repl;
//        else
//            repl->parent->right = repl;
//        repl->left = node->left;
//        repl->left->parent = repl;
//        repl->right = node->right;
//        if (repl->right != nullptr)
//            repl->right->parent = repl;
//        repl->color = node->color;
//    }
//    if (removed_black && root != nullptr) {
//        if (repl_child != nullptr)
//            repl_child->color = BLACK;
//        else
//            balance_after_remove_(root, sibling);
//    }
//}

//void balance_after_remove_(node_pointer root, node_pointer sibling)
//{
//    node_pointer x = nullptr;
//    while (true) {
//        if (sibling == sibling->parent->right) {
//            if (sibling->color == RED) {
//                sibling->color = BLACK;
//                sibling->parent->color = RED;
//                rotate_left_(sibling->parent);
//                if (root == sibling->left)
//                    root = sibling;
//                sibling = sibling->left->right;
//            }
//            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
//                (sibling->right == nullptr || sibling->right->color == BLACK)) {
//                sibling->color = RED;
//                x = sibling->parent;
//                if (x == root || x->color == RED) {
//                    x->color = BLACK;
//                    break;
//                }
//                sibling = (x == x->parent->left) ? x->parent->right : x->parent->left;
//            } else {
//                if (sibling->right == nullptr || sibling->right->color == BLACK) {
//                    sibling->left->color = BLACK;
//                    sibling->color = RED;
//                    rotate_right_(sibling);
//                    sibling = sibling->parent;
//                }
//                sibling->color = sibling->parent->color;
//                sibling->parent->color = BLACK;
//                sibling->right->color = BLACK;
//                rotate_left_(sibling->parent);
//                break;
//            }
//        } else {
//            if (sibling->color == RED) {
//                sibling->color = BLACK;
//                sibling->parent->color = RED;
//                rotate_right_(sibling->parent);
//                if (root == sibling->right)
//                    root = sibling;
//                sibling = sibling->right->left;
//            }
//            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
//                (sibling->right == nullptr || sibling->right->color == BLACK)) {
//                sibling->color = RED;
//                x = sibling->parent;
//                if (x == root || x->color == RED) {
//                    x->color = BLACK;
//                    break;
//                }
//                sibling = (x == x->parent->left) ? x->parent->right : x->parent->left;
//            } else {
//                if (sibling->left == nullptr || sibling->left->color == BLACK) {
//                    sibling->right->color = BLACK;
//                    sibling->color = RED;
//                    rotate_left_(sibling);
//                    sibling = sibling->parent;
//                }
//                sibling->color = sibling->parent->color;
//                sibling->parent->color = BLACK;
//                sibling->left->color = BLACK;
//                rotate_right_(sibling->parent);
//                break;
//            }
//        }
//    }
//}

#endif /*VECTOR_HPP*/