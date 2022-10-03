#pragma once

#include <memory>
#include <iostream>
#include "container_defines.hpp"
#include "pair.hpp"
#include "iterator_traits.hpp"


#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */
//#define BLACK   "\033[30m"      /* Black */
//#define GREEN   "\033[32m"      /* Green */
//#define YELLOW  "\033[33m"      /* Yellow */
//#define MAGENTA "\033[35m"      /* Magenta */
//#define WHITE   "\033[37m"      /* White */
//#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
//#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
//#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
//#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
//#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
//#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
//#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
//#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace ft {
	template <class Key, class Value,  class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,Value> > >
	class bin_tree {
	public:

	protected:
		typedef struct tree_node {
			struct tree_node		*parent;
			struct tree_node		*left;
			struct tree_node		*right;
			pair<Key, Value>	k_v_pair;
			Key						first;
			Value					second;

			struct tree_node&	operator++() {
				if (this->right == NULL) {
					this = this->parent;
				} else {
					this = this->right;
					while (this->left != NULL)
						this = this->left;
				}
				return this;
			}
			struct tree_node	operator++(int) {
				struct tree_node temp = *this;
				++this;
				return temp;
			}
			struct tree_node&	operator--() {
				if (this->left == NULL) {
					this = this->parent;
				} else {
					this = this->left;
					while (this->right != NULL)
						this = this->right;
				}
				return this;
			}
			struct tree_node	operator--(int) {
				struct tree_node temp = *this;
				--this;
				return temp;
			}

			bool	operator==(const struct tree_node& sec) {
				if (this->k_v_pair == sec.k_v_pair)
					return true;
				return false;
			}
			bool	operator!=(const struct tree_node& sec) {
				if (this->k_v_pair == sec.k_v_pair)
					return false;
				return true;
			}
		} t_node;
	public:
		typedef				  pair<const Key, Value>				value_type;
		typedef		typename  Alloc::template rebind<t_node>::other		node_allocator;
		typedef		typename  node_allocator::pointer					pointer;
		typedef				  Key										key_type;
		typedef				  Value										mapped_type;
		typedef		typename  node_allocator::const_pointer				const_pointer;
		typedef		typename  node_allocator::reference					reference;
		typedef		typename  node_allocator::const_reference			const_reference;
		typedef				  node_allocator							allocator_type;
		typedef		typename  node_allocator::pointer					iterator;
		typedef		typename  node_allocator::const_pointer				const_iterator;
		typedef		typename  node_allocator::difference_type			node_diff;
		typedef		typename  node_allocator::const_reference			const_node_reference;
		typedef		typename  node_allocator::size_type					size_type;
		typedef		reverse_iterator<iterator, t_node, const_node_reference, node_diff>	reverse_iterator;
		typedef		::ft::reverse_iterator<const_iterator, t_node, const_reference, node_diff> const_reverse_iterator;
		typedef		typename ::ft::bidirectional_iterator_tag				iterator_category;


		Compare	val_compare;

		Compare		value_comp() const { return val_compare; }

		bool	_eq(value_type const &first, value_type const &second) const {
			return (!_cmp(first, second) && !_cmp(second, first));
		}
		explicit bin_tree(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : val_compare(comp) {
			tree = NULL;
		}

		explicit bin_tree(pair<Key, Value> keyval_pair, const Compare& comp = Compare()) : val_compare(comp) {
			add_node(keyval_pair, NULL);
			update_tree();
		}
		~bin_tree() {
			delete_tree();
		}
		bool	insert_node(const pair<Key, Value> &keyval_pair) {
			if (find(keyval_pair.first) != NULL)
				return false;
			pointer par = find_parent(keyval_pair.first);
			if (par == NULL)
				add_node(keyval_pair, NULL);
			else {
				if (par->k_v_pair.first > keyval_pair.first)
					par->left = add_node(keyval_pair, par);
				else
					par->right = add_node(keyval_pair, par);
			}
			rebalance_tree();
			update_tree();
			return true;
		}

		void	print() {
			private_print_tree(tree, 1);
		}

		iterator find(const Key& k) {
			iterator node;
			while (node != NULL) {
				if (k == node->first)
					return node;
				if (k > node->first)
					node = node->right;
				else
					node = node->left;
			}
			return NULL;
		}

		const_iterator	find(const Key& k) const {
			iterator node;
			while (node != NULL) {
				if (k == node)
					return node;
				if (k > node)
					node = node->right;
				else
					node = node->left;
			}
			return NULL;
		}

		Value& operator[] (const Key& k) {
			return find(k)->k_v_pair.second;
		}

		iterator	begin() const {
			return _most_left;
		}
		iterator	end() const {
			return _most_right + 1;
		}

		void	erase(iterator pos) {
			delete_node(&pos);
			update_tree();
		}

		void	erase(const Key& k) {
			delete_node(find(k));
			update_tree();
		}

		void	erase(iterator first, iterator last)  {
			while (first != last)
				delete_node(first++);
			delete_node(first);
			update_tree();
		}
		reverse_iterator	rbegin() const { return reverse_iterator(_most_right); }
		reverse_iterator	rend() const { return reverse_iterator(_most_left - 1); }

		size_type	size() const {
			size_type i = 0;
			for (iterator v = begin(); v != end() && v != NULL; v++)
				i++;
			return i;
		}

		size_type max_size() const {
			return allocator.max_size();
		}
	private:
		void	clear(pointer node) {
			if (!node)
				return;
			if (node->left)
				clear(node->left);
			if (node->right)
				clear(node->right);
			allocator.destroy(node);
		}
	public:
		void delete_tree() {
			clear(tree);
		}

	private: ///	PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE
		node_allocator	allocator;
		pointer			tree;
		pointer			_most_left;
		pointer			_most_right;


		void	swap_node(pointer* ori_target, pointer* ori_other) {
			pointer	node = *ori_target;
			pointer	other = *ori_other;
			if (!node || !other)
				return;

			t_node*	tmp1 = node->left;
			t_node* tmp2 = node->right;
			t_node* tmp3 = node->parent;
			t_node* tmp4 = node;

			t_node*	otmp1 = other->left;
			t_node* otmp2 = other->right;
			t_node* otmp3 = other->parent;

			*ori_target = other;
			other->left = tmp1;
			other->right = tmp2;
			other->parent = tmp3;
			if (tmp3) {
				if (node->parent->left == node)
					node->parent->left = other;
				else
					node->parent->right = other;
			}
			if (other->left)
				other->left->parent = other;
			if (other->right)
				other->right->parent = other;

			*ori_other = tmp4;
			node->left = otmp1;
			node->right = otmp2;
			node->parent = otmp3;
			if (otmp3) {
				if (otmp3->left == other)
					otmp3->left = node;
				else
					otmp3->right = node;
			}
			if (node->left)
				node->left->parent = node;
			if (node->right)
				node->right->parent = node;
		}

		void	delete_node(iterator* pos) {
			if ((*pos) == NULL)
				return;
			while ((*pos)->left || (*pos)->right) {
				if (get_highest_depth((*pos)->left) > get_highest_depth((*pos)->right))
					swap_node(pos, pos->left);
				else
					swap_node(pos, pos->right);
			}
			allocator.destroy(*pos);
			*pos = NULL;
		}

		void	update_tree() {
			pointer	node = tree;
			while (node != NULL && node->left != NULL)
				node = node->left;
			_most_left = node;
			node = tree;
			 while (node != NULL && node->right != NULL)
				node = node->right;
			_most_right = node;
		}

		void print_node(t_node* node) {
			if (node == NULL) {
				std::cout << "NULL";
				return;
			}
			if (node->parent != NULL) {
				if (node->parent->left == node)
					std::cout << BLUE << "L: ";
				else
					std::cout << RED << "R: ";
			} else
				std::cout << CYAN;
			if (node->parent == NULL)
				std::cout << "parent: " << "NULL;  ";
			else
				std::cout << "parent: " << node->parent->k_v_pair.first << ";  ";
			std::cout << "\"" << node->k_v_pair.first << "\"   \"" << node->k_v_pair.second << "\"" << RESET;
		}

		int private_print_tree(t_node *begin, int tabs) {
			int tmp = tabs;
			int old = tabs;
			int tmp2 = tabs;
			if (begin->left != NULL) {
				tmp2 += private_print_tree(begin->left, tabs);
				if (begin->right != NULL)
					std::cout <<  " | ";
			} else if (begin->right != NULL) {
				std::cout << "\t\t\t";
			}
			if (begin->right != NULL) {
				tmp += private_print_tree(begin->right, tabs);
			}
			if (begin->right != NULL || begin->left != NULL)
				std::cout << std::endl;
			if (tmp >= tmp2 && tmp)
				tabs = tmp;
			else if (tmp2 > tmp && tmp2)
				tabs = tmp2;
			for (int i = 0; i < tabs; i++)
				std::cout << "\t\t";
			print_node(begin);
			return (tabs - old) + 1;
		}


		pointer	find_parent(const Key& key_val) {
			pointer	curr = tree;

			while (tree != NULL) {
				if (key_val < curr->k_v_pair.first) {
					if (curr->left == NULL)
						return curr;
					else
						curr = curr->left;
				} else if (key_val > curr->k_v_pair.first) {
					if (curr->right == NULL)
						return curr;
					else
						curr = curr->right;
				} else
					return NULL;
			}
			return NULL;
		}


		size_type	get_lowest_depth(t_node* node) {
			size_type	ret = 0;
			size_type	tmp1 = 0;
			size_type	tmp2 = 0;
			if (!node)
				return 0;
			if (node->right)
				tmp1 = get_lowest_depth(node->right);
			if (node->left)
				tmp2 = get_lowest_depth(node->left);
			if (tmp1 > 0 && tmp1 <= tmp2)
				ret = tmp1;
			else if (tmp2 > 0 && tmp2 < tmp1)
				ret = tmp2;
			return ret + 1;
		}

		size_type	get_highest_depth(t_node* node) {
			size_type	ret = 0;
			size_type	tmp1 = 0;
			size_type	tmp2 = 0;
			if (!node)
				return 0;
			if (node->right)
				tmp1 = get_highest_depth(node->right);
			if (node->left)
				tmp2 = get_highest_depth(node->left);
			if (tmp1 > 0 && tmp1 >= tmp2)
				ret = tmp1 + 1;
			else if (tmp2 > 0 && tmp2 > tmp1)
				ret = tmp2 + 1;
			return ret + 1;
		}

		void	rotate_right(t_node** ori) {
			if ((*ori)->left == NULL)
				return;
			t_node* node = *ori;

			t_node*	tmp1 = node->left;
			t_node* tmp2 = node->left->right;
			t_node* tmp3 = node;
			t_node* tmp4 = node->parent;
			node = tmp1;
			node->right = tmp3;
			node->right->left = tmp2;
			if (tmp4) {
				if (tmp4->right == node->right) {
					tmp4->right = node;
				}

				if (tmp4->left == node->right) {
					tmp4->left = node;
				}
			}
			node->right->parent = node;
			node->right->left->parent = node->right;
			node->parent = tmp4;
		}

		void	rotate_left(t_node** ori) {
			if ((*ori)->right == NULL)
				return;
			t_node* node = *ori;
			t_node*	tmp1 = node->right;
			t_node* tmp2 = node->right->left;
			t_node* tmp3 = node;
			t_node* tmp4 = node->parent;
			node = tmp1;
			node->left = tmp3;
			node->left->right = tmp2;
			if (tmp4) {
				if (tmp4->right == node->left) {
					tmp4->right = node;
				}

				if (tmp4->left == node->left) {
					tmp4->left = node;
				}
			}
			node->left->parent = node;
			node->left->right->parent = node->left;
			node->parent = tmp4;
		}

		t_node*	find_lowest_balance_node() {
			t_node* node = tree;
			size_type low = get_lowest_depth(node);
			size_type high = get_highest_depth(node);
			while (high - low >= 3) {
				low = get_lowest_depth(node->right);
				high = get_highest_depth(node->right);
				if (high - low >= 3) {
					node = node->right;
				} else {
					low = get_lowest_depth(node->left);
					high = get_highest_depth(node->left);
					if (high - low >= 3)
						node = node->left;
					else
						return node;
				}
				low = get_lowest_depth(node);
				high = get_highest_depth(node);
			}
			return node;
		}

		void	rebalance_tree() {
			print();
			std::cout << "\n\n";
			t_node* node = find_lowest_balance_node();
			size_type low = get_lowest_depth(node);
			size_type high = get_highest_depth(node);
			if (high - low > 3) {
				rotate_left(&node);
				size_type sec_low = get_lowest_depth(node);
				size_type sec_high = get_highest_depth(node);
				if (sec_high - sec_low < high - low) {
					while (sec_high - sec_low < high - low && sec_high - sec_low > 3) {
						rotate_left(&node);
						sec_low = get_lowest_depth(node);
						sec_high = get_highest_depth(node);
					}
				} else {
					if (high - low <= 3)
						return;
					rotate_right(&node);
					sec_low = get_lowest_depth(node);
					sec_high = get_highest_depth(node);
					while (sec_high - sec_low < high - low && sec_high - sec_low > 3) {
						rotate_right(&node);
						sec_low = get_lowest_depth(node);
						sec_high = get_highest_depth(node);
					}
				}
			}
		}

		pointer	add_node(const pair<Key, Value> &keyval_pair, pointer parent) {
			if (parent == NULL) {
				tree = allocator.allocate(1);
				allocator.construct(tree);
				tree->k_v_pair = keyval_pair;
				tree->parent = NULL;
				tree->left = NULL;
				tree->right = NULL;
				return tree;
			} else {
				pointer node = allocator.allocate(1);
				allocator.construct(node);
				node->k_v_pair = keyval_pair;
				node->parent = parent;
				node->left = NULL;
				node->right = NULL;
				return node;
			}
		}
	};

}
