#pragma once

#ifndef null_ptr
#define  null_ptr NULL
#endif /*null_ptr*/


namespace ft {

    typedef enum E_Color { RED, BLACK }  E_Color;

    template<typename node_ptr>
    node_ptr    lowest_tree_node(node_ptr node) {
        while (node->left != null_ptr)
            node = node->left;
        return node;
    }

    template<typename node_ptr>
    node_ptr    highest_tree_node(node_ptr node) {
        while (node->right != null_ptr)
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

        tree_node() : value(T()), parent(null_ptr), left(null_ptr), right(null_ptr) {}

        T       value;
        pointer parent;
        pointer left;
        pointer right;
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
        node_pointer base() { return _ptr; }

        tree_iterator() : _ptr() {}
        tree_iterator(const tree_iterator& other) : _ptr(other._ptr) {}
        explicit tree_iterator(node_pointer other) : _ptr(other) {}

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
        node_pointer base() { return _ptr; }

        const_tree_iterator() : _ptr() {}
        explicit const_tree_iterator(const tree_iterator& other) : _ptr(other.base()) {}
        const_tree_iterator(const const_tree_iterator& other) : _ptr(other._ptr) {}
        explicit const_tree_iterator(node_pointer other) : _ptr(other) {}

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
        explicit tree(const value_compare& compare, const allocator_type& allocator) : _comp(compare), _alloc(allocator), _node_alloc(allocator), _count(0), _head(null_ptr), _left_outer(null_ptr) { };
        tree(const tree& other) :_comp(other._comp), _alloc(other._alloc), _node_alloc(other._node_alloc) {
            //todo
        }

        ~tree() { destroy_(_head); }

        tree& operator=(const tree& other)
    };
};