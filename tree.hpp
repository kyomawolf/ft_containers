#pragma once

#include <memory>
#ifndef NULL && null_ptr
#define null_ptr nullptr
#elifndef null_ptr
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
        if (node->left != null_ptr)
            return highest_tree_node(node->left);

        while (node == node->parent->left)
            node = node->parent;
        return node->parent;
    }

    template <class node_ptr>
    node_ptr next_tree_node(node_ptr node)
    {
        if (node->right != null_ptr)
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
            _head = construct_node_(value_type(), BLACK);
            _head->parent = _head;
            _left_outer = _head;

            *this = other;
        }

        ~tree() { destroy_(_head); }



        tree& operator=(const tree& other) {
            if (this != &other) {
                clear(); //todo
                _comp = other._comp;
                if (other._root() != nullptr) {
                    _root() = copy_(other._root()); //todo
                    _root()->parent = _head;
                    _left_outer = RBTree_min(_root());
                    _count = other.node_count_;
                }
            }
            return *this;
        }


        allocator_type get_allocator()  const { return _alloc; }
        size_type      max_size()       const { return _node_alloc.max_size(); }

        void clear() {
            _destroy_rec(_root());
            _root() = null_ptr;
            _left_outer = _head;
        }
    private:

        node_pointer _root() const { return _head->left; }
        node_pointer& _root() { return _head->left; }

        ///node creation and deletion
        void    _delete_node(node_pointer node) {
            _alloc.destroy(node->value);
            _node_alloc.deallocate(node, 1);
        }

        void _destroy_rec(node_pointer node) {
            if (!node)
                return;
            _destroy_rec(node->left);
            _destroy_rec(node->right);
            _delete_node(node);
        }

        node_pointer _copy_rec(const node_pointer node) {
            if (node == null_ptr)
                return null_ptr;
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
            _alloc.construct(&node->val, val);
            node->color = color;
            node->parent = null_ptr;
            node->left = null_ptr;
            node->right = null_ptr;
            return node;
        }

        /// rotation

        void _left_rotation(node_pointer init)
        {
            node_pointer tmp = init->right;
            init->right = tmp->left;
            if (init->right != null_ptr)
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
            if (init->left != null_ptr)
                init->left->parent = init;
            tmp->parent = init->parent;
            if (init == init->parent->left)
                init->parent->left = tmp;
            else
                init->parent->right = tmp;

            tmp->right = init;
            init->parent = tmp;
        }

        void insert_node(node_pointer& pos, node_pointer origin, node_pointer node) {
            node->parent = origin;
            pos = node;
            ++_count;
            if (_left_outer->left)
                _left_outer = _left_outer->left;
            _insert_balance(_root(), node);
        }

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
                    if (uncle != null_ptr && uncle->color == RED) {
                        uncle->color = BLACK;
                        key = key->parent->color = BLACK;
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
            node_pointer sibling = null_ptr;
            if (node->left == null_ptr || node->right == null_ptr)
                replace = node;
            else
                replace = next_tree_node(node);
            if (replace->left)
                child_replace = replace->left;
            else
                child_replace = replace->right;
            if (child_replace)
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
                replace->left->parent = node;
                replace->right = node->right;
                if (!replace->right)
                    replace->right->parent = replace;
                replace->color = node->color;
            }
            if ((set_red && !root) && (child_replace))
                child_replace->color = BLACK;
            else if (set_red && !root)
                _remove_balance(root, sibling);
        }

        void _remove_balance(node_pointer root, node_pointer sibling) {
            node_pointer tmp = null_ptr;
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
                    if ((sibling->left == null_ptr || sibling->left->color == BLACK) && (sibling->right == null_ptr || sibling->right->color == BLACK)) {
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
                        if (sibling->right == null_ptr || sibling->right->color == BLACK) {
                            sibling->left->color = BLACK;
                            sibling->color = RED;
                            _right_rotation(sibling);
                            sibling = sibling->parent;
                        }
                    }
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    _left_rotation(sibling->parent);
                    break;
                } else {
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        sibling->parent->color = RED;
                        _right_rotation(sibling->parent);
                        if (root == sibling->right)
                            root = sibling;
                        sibling = sibling->right->left;
                    }
                    if ((sibling->left == null_ptr || sibling->left->color == BLACK) && (sibling->right == null_ptr || sibling->right->color == BLACK)) {
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
                        if (sibling->left == null_ptr || sibling->left->color == BLACK) {
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
    };
};