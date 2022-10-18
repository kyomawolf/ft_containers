#pragma once

#include <memory>
#include "pair.hpp"
#include "swap.hpp"
#include "iterator.hpp"
#include <iostream>


namespace ft {

    typedef enum E_Color { RED, BLACK }  E_Color;

    template<typename node_ptr>
    node_ptr    lowest_tree_node(node_ptr node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    template<typename node_ptr>
    node_ptr    highest_tree_node(node_ptr node) {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }


    template <class node_ptr>
    node_ptr prev_tree_node(node_ptr node)
    {
        if (node->left != nullptr)
            return highest_tree_node(node->left);

        while (node == node->parent->left)
            node = node->parent;
        return node->parent;
    }

    template <class node_ptr>
    node_ptr next_tree_node(node_ptr node)
    {
        if (node->right != nullptr)
            return lowest_tree_node(node->right);

        while (node == node->parent->right)
            node = node->parent;
        return node->parent;
    }


    template <typename T>
    class tree_node {
    public:
        typedef       tree_node<T>*    pointer;
        typedef const tree_node<T>*    const_pointer;

        tree_node() : value(T()), parent(nullptr), left(nullptr), right(nullptr) {}

        T       value;
        pointer parent;
        pointer left;
        pointer right;
        E_Color color;
    };

    template<typename T, typename diff>
    class const_tree_iterator;

    template <typename T, typename diff>
    class tree_iterator {
    public:
        typedef          std::bidirectional_iterator_tag         iterator_category;
        typedef          T                                       value_type;
        typedef          value_type*                             pointer;
        typedef          value_type&                             reference;
        typedef          diff                                    difference_type;
        typedef          const_tree_iterator<T, diff>            const_iterator;
    private:
        typedef typename tree_node<value_type>::pointer          node_pointer;
        typedef typename tree_node<value_type>::const_pointer    const_node_pointer;

        node_pointer    _ptr;
    public:
        node_pointer base() const { return _ptr; }

        tree_iterator() : _ptr() {}
        tree_iterator(const tree_iterator& other) : _ptr(other._ptr) {}
        tree_iterator(node_pointer other) : _ptr(other) {}

        reference operator*() const {return _ptr->value; }

        pointer  operator->() const { return &(operator*()); }

        tree_iterator&  operator++() {
            _ptr = next_tree_node(_ptr);
            return *this;
        }

        tree_iterator   operator++(int) {
            node_pointer tmp = _ptr;
            ++(*this);
            return tmp;
        }

        tree_iterator&  operator--() {
            _ptr = prev_tree_node(_ptr);
            return *this;
        }

        tree_iterator   operator--(int) {
            node_pointer tmp = _ptr;
            --(*this);
            return tmp;
        }

        bool    operator==(const tree_iterator& other) const {
            return other.base() == _ptr;
        }

        bool    operator!=(const tree_iterator& other) const {
            return !(*this == other);
        }

        bool    operator==(const const_iterator& other) const {
            return other.base() == _ptr;
        }

        bool    operator!=(const const_iterator & other) const {
            return !(*this == other);
        }


    };

    template <typename T, typename diff>
    class const_tree_iterator {
    public:
        typedef          std::bidirectional_iterator_tag         iterator_category;
        typedef          T                                       value_type;
        typedef          value_type*                             pointer;
        typedef          value_type&                             reference;
        typedef          diff                                    difference_type;
        typedef          tree_iterator<T, diff>                  tree_iterator;
    private:
        typedef typename tree_node<value_type>::pointer          node_pointer;
        typedef typename tree_node<value_type>::const_pointer    const_node_pointer;

        node_pointer    _ptr;
    public:
        node_pointer base() const { return _ptr; }

        const_tree_iterator() : _ptr() {}
        const_tree_iterator(const tree_iterator& other) : _ptr(other.base()) {}
        const_tree_iterator(const const_tree_iterator& other) : _ptr(other._ptr) {}
        const_tree_iterator(node_pointer other) : _ptr(other) {}

        reference operator*() const {return _ptr->value; }

        pointer  operator->() const { return &(operator*()); }

        const_tree_iterator&  operator++() {
            _ptr = next_tree_node(_ptr);
            return *this;
        }

        const_tree_iterator   operator++(int) {
            node_pointer tmp = _ptr;
            ++(*this);
            return tmp;
        }

        const_tree_iterator&  operator--() {
            _ptr = prev_tree_node(_ptr);
            return *this;
        }

        const_tree_iterator   operator--(int) {
            node_pointer tmp = _ptr;
            --(*this);
            return tmp;
        }

        bool    operator==(const tree_iterator& other) const {
            return other.base() == _ptr;
        }

        bool    operator!=(const tree_iterator& other) const {
            return !(*this == other);
        }

        bool    operator==(const const_tree_iterator& other) const {
            return other.base() == _ptr;
        }

        bool    operator!=(const const_tree_iterator & other) const {
            return !(*this == other);
        }

    };

    template <typename T, typename Compare, typename Allocator>
    class tree {
    public:
        typedef          T                                                 value_type;
        typedef          Compare                                           value_compare;
        typedef          Allocator                                         allocator_type;
        typedef          tree_node<value_type>                             node_type; //NODE
        typedef typename node_type::pointer                                node_pointer;
        typedef typename node_type::const_pointer                          const_node_pointer;


        typedef typename allocator_type::template rebind<node_type>::other node_allocator_type;
        typedef typename allocator_type::pointer                           pointer;
        typedef typename allocator_type::const_pointer                     const_pointer;
        typedef typename allocator_type::size_type                         size_type;
        typedef typename allocator_type::difference_type                   difference_type;


        typedef ft::tree_iterator<value_type, difference_type>             iterator; //ITERATORS
        typedef ft::const_tree_iterator<value_type, difference_type>       const_iterator;
        typedef ft::reverse_iterator<iterator>                             reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                       const_reverse_iterator;
    protected:
        value_compare       _comp;
        allocator_type      _alloc;
        node_allocator_type _node_alloc;
        node_pointer        _head;
        node_pointer        _left_outer;
        size_type           _count;
    public:
        explicit tree(const value_compare& compare, const allocator_type& allocator) : _comp(compare), _alloc(allocator), _node_alloc(allocator), _head(nullptr), _left_outer(nullptr), _count(0) {
            _head = _new_node(value_type(), BLACK);
            _head->parent = _head;
            _left_outer = _head;
        };
        tree(const tree& other) :_comp(other._comp), _alloc(other._alloc), _node_alloc(other._node_alloc) {
            _head = _new_node(value_type(), BLACK);
            _head->parent = _head;
            _left_outer = _head;

            *this = other;
        }

        ~tree() { _destroy_rec(_head); }



        tree& operator=(const tree& other) {
            if (this != &other) {
                clear();
                _comp = other._comp;
                if (other._root() != nullptr) {
                    _root() = _copy_rec(other._root());
                    _root()->parent = _head;
                    _left_outer = lowest_tree_node(_root());
                    _count = other._count;
                }
            }
            return *this;
        }

        void clear()
        {
            if (_root() == nullptr)
                return;
            _destroy_rec(_root());
            _root() = nullptr;
            _left_outer = _head;
            _count = 0;
        }

        template <typename Key>
        iterator find(const Key& key)
        {
            node_pointer tmp = _root();
            while (tmp != nullptr) {
                if (_comp(key, tmp->value))
                    tmp = tmp->left;
                else if (_comp(tmp->value, key))
                    tmp = tmp->right;
                else
                    return iterator(tmp);
            }
            return end();
        }

        template <typename Key>
        const_iterator find(const Key& key) const
        {
            node_pointer tmp = _root();
            while (tmp != nullptr) {
                if (_comp(key, tmp->value))
                    tmp = tmp->left;
                else if (_comp(tmp->value, key))
                    tmp = tmp->right;
                else
                    return const_iterator(tmp);
            }
            return end();
        }

        template <typename Key>
        iterator lower_bound(const Key& key)
        {
            node_pointer result = _head;
            node_pointer iter = _root();
            while (iter != nullptr) {
                if (!_comp(iter->value, key)) {
                    result = iter;
                    iter = iter->left;
                } else
                    iter = iter->right;
            }
            return iterator(result);
        }

        template <typename Key>
        const_iterator lower_bound(const Key& key) const
        {
            node_pointer result = _head;
            node_pointer iter = _root();
            while (iter != nullptr) {
                if (!_comp(iter->value, key)) {
                    result = iter;
                    iter = iter->left;
                } else
                    iter = iter->right;
            }
            return const_iterator(result);
        }

        template <typename Key>
        iterator upper_bound(const Key& key)
        {
            node_pointer result = _head;
            node_pointer iter = _root();
            while (iter != nullptr) {
                if (_comp(key, iter->value)) {
                    result = iter;
                    iter = iter->left;
                } else
                    iter = iter->right;
            }
            return iterator(result);
        }

        template <typename Key>
        const_iterator upper_bound(const Key& key) const
        {
            node_pointer result = _head;
            node_pointer iter = _root();
            while (iter != nullptr) {
                if (_comp(key, iter->value)) {
                    result = iter;
                    iter = iter->left;
                } else
                    iter = iter->right;
            }
            return const_iterator(result);
        }

        allocator_type get_allocator()  const { return _alloc; }
        size_type      max_size()       const { return _node_alloc.max_size(); }
        size_type      size()           const { return _count; }

        iterator       begin()                { return iterator(_left_outer); }
        const_iterator begin()          const { return const_iterator(_left_outer); }

        iterator       end()                  { return iterator(_head); }
        const_iterator end()            const { return const_iterator(_head); }

        void swap(tree& other)
        {
            ft::swap(_comp, other._comp);
            ft::swap(_alloc, other._alloc);
            ft::swap(_node_alloc, other._node_alloc);
            ft::swap(_head, other._head);
            ft::swap(_left_outer, other._left_outer);
            ft::swap(_count, other._count);
        }

        template <typename Key>
        ft::pair<iterator, iterator> equal_range(const Key& key)
        {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        template <typename Key>
        ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
        {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }


        iterator erase_node(iterator node)
        {
            node_pointer node_ptr = const_cast<node_pointer>(node.base());
            node_pointer next_node_ptr = next_tree_node(node_ptr);
            if (node_ptr == _left_outer)
                _left_outer = next_node_ptr;
            _remove_node(_root(), node_ptr);
            _alloc.destroy(&node_ptr->value);
            _node_alloc.deallocate(node_ptr, 1);
            --_count;
            return iterator(next_node_ptr);
        }

        void erase_range(iterator first, iterator last)
        {
            while (first != last)
                first = erase_node(first);
        }

        template <typename Key>
        size_type erase_key(const Key& key)
        {
            iterator node = find(key);
            if (node == end())
                return 0;
            erase_node(node);
            return 1;
        }

    private:

        node_pointer _root() const { return _head->left; }
        node_pointer& _root() { return _head->left; }

        ///node creation and deletion
        void    _delete_node(node_pointer node) {
            _alloc.destroy(&node->value);
            _node_alloc.deallocate(node, 1);
        }

        void _destroy_rec(node_pointer node) {
            if (node == nullptr)
                return;
            _destroy_rec(node->left);
            _destroy_rec(node->right);
            _delete_node(node);
        }

        node_pointer _copy_rec(const node_pointer node) {
            if (node == nullptr)
                return nullptr;
            node_pointer ret_node = _new_node(node);
            ret_node->left = _copy_rec(node->left);
            ret_node->right = _copy_rec(node->right);
            if (ret_node->left)
                ret_node->left->parent = ret_node;
            if (ret_node->right)
                ret_node->right->parent = ret_node;
            return ret_node;
        }

        node_pointer _new_node(const node_pointer& node) {
            return _new_node(node->value, node->color);
        }

        node_pointer _new_node(const value_type& val, E_Color color) {
            node_pointer node = _node_alloc.allocate(1);
            _alloc.construct(&node->value, val);
            node->color = color;
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }

        /// rotation

        void _left_rotation(node_pointer init)
        {
            node_pointer tmp = init->right;
            init->right = tmp->left;
            if (init->right != nullptr)
                init->right->parent = init;
            tmp->parent = init->parent;
            if (init == init->parent->left)
                init->parent->left = tmp;
            else
                init->parent->right = tmp;

            tmp->left = init;
            init->parent = tmp;
        }

        void _right_rotation(node_pointer init)
        {
            node_pointer tmp = init->left;
            init->left = tmp->right;
            if (init->left != nullptr)
                init->left->parent = init;
            tmp->parent = init->parent;
            if (init == init->parent->left)
                init->parent->left = tmp;
            else
                init->parent->right = tmp;

            tmp->right = init;
            init->parent = tmp;
        }

    public:

        iterator insert(const_iterator hint, const value_type& val)
        {
            node_pointer  parent;
            node_pointer& pos_ptr_ref = find_pos(hint, parent, val);
            node_pointer  pos_ptr = pos_ptr_ref;
            if (pos_ptr_ref == nullptr) {
                node_pointer new_node = _new_node(val, RED);
                insert_node(new_node, pos_ptr_ref, parent);
                pos_ptr = new_node;
            }
            return iterator(pos_ptr);
        }

        template <class InputIt>
        void    insert_range(InputIt first, InputIt last) {
            for (; first != last; ++first)
                insert(*first);
        }

        ft::pair<iterator, bool> insert(const value_type& val)
        {
            node_pointer  parent;
            node_pointer& pos_ptr_ref = find_pos(parent, val);
            node_pointer  pos_ptr = pos_ptr_ref;
            bool          inserted = false;
            if (pos_ptr_ref == nullptr) {
                node_pointer new_node = _new_node(val, RED);
                insert_node(new_node, pos_ptr_ref, parent);
                inserted = true;
                pos_ptr = new_node;
            }
            return ft::make_pair(iterator(pos_ptr), inserted);
        }

        void insert_node(node_pointer& node, node_pointer& pos, node_pointer origin) {
            node->parent = origin;
            pos = node;
            if (_left_outer->left != nullptr)
                _left_outer = _left_outer->left;
            _insert_balance(_root(), node);
            ++_count;
        }

    private:
        void _insert_balance(node_pointer root, node_pointer key) {
            if (key == root)
            key->color = BLACK;
            else
                key->color = RED;
            while (key != root && key->parent->color == RED) {
                if (key->parent == key->parent->parent->left) {
                    node_pointer uncle = key->parent->parent->right;
                    if (uncle && uncle->color == RED) {
                        uncle->color = BLACK;
                        key->parent->color = BLACK;
                        key = key->parent->parent;
                        if (key == root)
                            key->color = BLACK;
                        else
                            key->color = RED;
                    } else {
                        if (key == key->parent->right) {
                        key = key->parent;
                        _left_rotation(key);
                        }
                        key->parent->color = BLACK;
                        key->parent->parent->color = RED;
                        _right_rotation(key->parent->parent);
                        break;
                    }
                } else {
                    node_pointer uncle = key->parent->parent->left;
                    if (uncle != nullptr && uncle->color == RED) {
                        uncle->color = BLACK;
                        key->parent->color = BLACK;
                        key = key->parent->parent;
                        if (key == root)
                            key->color = BLACK;
                        else
                            key->color = RED;
                    } else {
                        if (key == key->parent->left) {
                            key = key->parent;
                            _right_rotation(key);
                        }
                        key->parent->color = BLACK;
                        key->parent->parent->color = RED;
                        _left_rotation(key->parent->parent);
                        break;
                    }
                }
            }
        }

        void _remove_node(node_pointer root, node_pointer node) {
            node_pointer replace;
            node_pointer child_replace;
            node_pointer sibling = nullptr;
            if (node->left == nullptr || node->right == nullptr)
                replace = node;
            else
                replace = next_tree_node(node);
            if (replace->left != nullptr)
                child_replace = replace->left;
            else
                child_replace = replace->right;
            if (child_replace != nullptr)
                child_replace->parent = replace->parent;
            if (replace == replace->parent->left) {
                replace->parent->left = child_replace;
                if (replace == root)
                    root = child_replace;
                else
                    sibling = replace->parent->right;
            } else {
                replace->parent->right = child_replace;
                sibling = replace->parent->left;
            }

            bool set_red = (replace->color == BLACK);
            if (replace != node) {
                if (node == root)
                    root = replace;
                replace->parent = node->parent;
                if (node == node->parent->left)
                    replace->parent->left = replace;
                else
                    replace->parent->right = replace;
                replace->left = node->left;
                replace->left->parent = replace;
                replace->right = node->right;
                if (replace->right != nullptr)
                    replace->right->parent = replace;
                replace->color = node->color;
            }
            if (set_red && root != nullptr) {
                if (child_replace != nullptr) {
                    child_replace->color = BLACK;
                } else
                    _remove_balance(root, sibling);
            }
        }

        void _remove_balance(node_pointer root, node_pointer sibling) {
            node_pointer tmp = nullptr;
            while (true) {
                if (sibling == sibling->parent->right) {
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        sibling->parent->color = RED;
                        _left_rotation(sibling->parent);
                        if (root == sibling->left)
                            root = sibling;
                        sibling = sibling->left->right;
                    }
                    if ((sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                        sibling->color = RED;
                        tmp = sibling->parent;
                        if (tmp == root || tmp->color == RED) {
                            tmp->color = BLACK;
                            break;
                        }
                        if (tmp == tmp->parent->left)
                            sibling = tmp->parent->right;
                        else
                            sibling = tmp->parent->left;
                    } else {
                        if (sibling->right == nullptr || sibling->right->color == BLACK) {
                            sibling->left->color = BLACK;
                            sibling->color = RED;
                            _right_rotation(sibling);
                            sibling = sibling->parent;
                        }
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    _left_rotation(sibling->parent);
                    break;
                    }
                } else {
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        sibling->parent->color = RED;
                        _right_rotation(sibling->parent);
                        if (root == sibling->right)
                            root = sibling;
                        sibling = sibling->right->left;
                    }
                    if ((sibling->left == nullptr || sibling->left->color == BLACK) && (sibling->right == nullptr || sibling->right->color == BLACK)) {
                        sibling->color = RED;
                        tmp = sibling->parent;
                        if (tmp == root || tmp->color == RED) {
                            tmp->color = BLACK;
                            break;
                        }
                        if (tmp == tmp->parent->left)
                            sibling = tmp->parent->right;
                        else
                            sibling = tmp->parent->left;
                    } else {
                        if (sibling->left == nullptr || sibling->left->color == BLACK) {
                            sibling->right->color = BLACK;
                            sibling->color = RED;
                            _left_rotation(sibling);
                            sibling = sibling->parent;
                        }
                        sibling->color = sibling->parent->color;
                        sibling->parent->color = BLACK;
                        sibling->left->color = BLACK;
                        _right_rotation(sibling->parent);
                        break;
                    }
                }
            }
        }

        template <typename Key>
        node_pointer& find_pos(node_pointer& parent, const Key& key) {
            node_pointer iter = _root();
            if (iter != nullptr) {
                while (true) {
                    if (_comp(key, iter->value)) {
                        if (iter->left != nullptr)
                            iter = iter->left;
                        else {
                            parent = iter;
                            return parent->left;
                        }
                    } else if (_comp(iter->value, key)) {
                        if (iter->right != nullptr)
                            iter = iter->right;
                        else {
                            parent = iter;
                            return parent->right;
                        }
                    } else {
                        parent = iter;
                        return parent;
                    }
                }
            }
            parent = _head;
            return parent->left;
        }

        template <typename Key>
        node_pointer& find_pos(const_iterator hint, node_pointer & parent, const Key& key) {
            if (hint == end() || _comp(key, *hint)) {
                const_iterator prev = hint;
                if (prev == begin() || _comp(*(--prev), key)) {
                    if (hint.base()->left == nullptr) {
                        parent = const_cast<node_pointer>(hint.base());
                        return parent->left;
                    } else {
                        parent = const_cast<node_pointer>(prev.base());
                        return parent->right;
                    }
                }
                return find_pos(parent, key);
            } else if (_comp(*hint, key)) {
                const_iterator next = std::next(hint);
                if (next == end() || _comp(key, *next)) {
                    if (hint.base()->right == nullptr) {
                        parent = const_cast<node_pointer>(hint.base());
                        return parent->right;
                    } else {
                        parent = const_cast<node_pointer>(next.base());
                        return parent->left;
                    }
                }
                return find_pos(parent, key);
            }
            parent = const_cast<node_pointer>(hint.base());
            return parent;
        }
    };
};