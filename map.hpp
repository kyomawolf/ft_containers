#pragma once

#include "tree.hpp"

namespace ft {

	template <class Key, class Value, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,Value> > > class map {
	public:
		typedef					Key													key_type;
		typedef					Value												mapped_type;
		typedef					pair<const key_type, mapped_type>					value_type;
		typedef					Compare												key_compare;
		typedef					Alloc												allocator_type;
		typedef typename		allocator_type::reference							reference;
		typedef typename		allocator_type::const_reference						const_reference;
		typedef typename		allocator_type::pointer								pointer;
		typedef typename		allocator_type::const_pointer						const_pointer;
		typedef typename bin_tree<Key, Value, Compare>::iterator					iterator;
		typedef typename bin_tree<Key, Value, Compare>::const_iterator				const_iterator;
		typedef typename bin_tree<Key, Value, Compare>::reverse_iterator			reverse_iterator;
		typedef typename bin_tree<Key, Value, Compare>::const_reverse_iterator		const_reverse_iterator;
		typedef typename bin_tree<Key, Value, Compare>::node_diff					difference_type;
		typedef					size_t												size_type;

		class value_compare {
			friend class map;
		protected:
			Compare	_comp;

			explicit value_compare(Compare c) : _comp(c) {}
		public:
			typedef bool		result_type;
			typedef pair<Key, Value>	first;
			typedef pair<Key, Value>	second;
			bool operator() (pair<Key, Value> const &x, pair<Key, Value> const &y) const {
				return _comp(x.first, y.first);
			}
		};

	private:
		typedef pair<Key, Value> map_pair;
		bin_tree<Key, Value, Compare>	src_tree;
		typedef bin_tree<Key, Value, Compare> tree;
		friend class map<Key, Value, Compare>;
	public:
		explicit map(const Compare& comp = Compare() ) : src_tree(comp) {}
		explicit map(const map<Key, Value, Compare>& other) : src_tree(other.src_tree) {}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: src_tree() {
			for(; first  != last; first++) {
				src_tree.insert_node(first);
			}
		}

		map(const Value* first, const Value* last,
			const Compare& comp = Compare()) : src_tree(first, last, comp) {}

		map&	operator=(const map<Key, Value, Compare>& other) {
			src_tree.delete_tree();
			for (typename tree::iterator i = other.begin(); i != other.end(); i++)
				src_tree.insert_node(i->k_v_pair);
			return *this;
		}




		Compare		value_comp() const { return src_tree.value_comp(); }
		key_compare	key_comp() const { return src_tree.value_comp()._comp; }

		pair<iterator,bool>	insert(const value_type& keyval_pair) {
			bool it = src_tree.insert_node(keyval_pair);
			return pair<iterator, bool>(find(keyval_pair.first), it);
		}

		iterator insert (iterator position, const value_type& val) {
			bool it = src_tree.insert_node(val);
			return insert(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (; first != last; first++)
				src_tree.insert_node(first);
		}

		void	print_map() { src_tree.print(); }

		const_iterator begin() const {
			return src_tree.begin();
		}
		const_iterator end() const {
			return src_tree.end();
		}

		iterator begin() {
			return src_tree.begin();
		}
		iterator end() {
			return src_tree.end();
		}

		typename tree::reverse_iterator	rbegin() const { return src_tree.rbegin(); }
		typename tree::reverse_iterator	rend() const { return src_tree.rend(); }

		const_iterator	find(const Key& k) const {
			const_iterator it =  src_tree.find(k);
			if (it == NULL)
				return end();
		}

		iterator	find(const Key& k) {
			iterator it =  src_tree.find(k);
			if (it == NULL)
				return end();
		}

		Value&	operator[](const Key k) {
			return src_tree[k];
		};

		bool	empty() {
			if (src_tree.size() == 0)
				return true;
			return false;
		}

		typename tree::size_type	size() const {
			return src_tree.size();
		}

		typename tree::node_allocator	get_allocator() {return src_tree.allocator; }

		typename tree::size_type	count(const Key& k) {
			if (src_tree.find(k))
				return 1;
			return 0;
		}
		void	swap(map& other) {
			if (other.size() < this->size()) {
				map<Key, Value, Compare> temp(other);
				other = *this;
				*this = temp;
			} else {
				map<Key, Value, Compare> temp(*this);
				*this = other;
				other = *temp;
			}
		}
		void	clear () {
			src_tree.delete_tree();
		}

		iterator lower_bound (const key_type& k) {
			iterator it  = find(k);
			if (it == NULL) {

				for (it = src_tree.begin(); it != src_tree.end(); it++) {
					if (!key_comp()(it->first, k))
						return it - 1;
				}
				return it - 1;
			} else
				return it;
		}

		const_iterator lower_bound (const key_type& k) const {
			const_iterator it  = find(k);
			if (it == NULL) {

				for (it = src_tree.begin(); it != src_tree.end(); it++) {
					if (!key_comp()(it->first, k))
						return it;
				}
				return it - 1;
			} else
				return it;
		}

		iterator upper_bound (const key_type& k) {
			iterator it  = find(k);
			if (it == NULL) {

				for (it = src_tree.begin(); it != src_tree.end(); it++) {
					if (!key_comp()(it->first, k))
						return it;
				}
				return it - 1;
			} else
				return it + 1;
		}

		const_iterator upper_bound (const key_type& k) const {
			const_iterator it  = find(k);
			if (it == NULL) {

				for (it = src_tree.begin(); it != src_tree.end(); it++) {
					if (!key_comp()(it->first, k))
						return it;
				}
				return it - 1;
			} else
				return it + 1;
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			pair<const_iterator, const_iterator> ret;
			ret.first = find(k);
			if (ret.first == NULL) {
				ret.first = upper_bound(k);
			}
			ret.second = upper_bound(k);
			return ret;
		}
		pair<iterator,iterator>             equal_range (const key_type& k) {
			pair<iterator, iterator> ret;
			ret.first = find(k);
			if (ret.first == NULL) {
				ret.first = upper_bound(k);
			}
			ret.second = upper_bound(k);
			return ret;
		}

	};
}