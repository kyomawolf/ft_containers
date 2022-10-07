

#ifndef FT_ITERATOR_TRAITS_HPP
#define FT_ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iterator>

#include "iterator_traits.hpp"

namespace ft
{
/*
** iterator_traits
*/
// struct input_iterator_tag
// {};

// struct output_iterator_tag
// {};

// struct forward_iterator_tag
//     : public input_iterator_tag
// {};

// struct bidirectional_iterator_tag
//     : public forward_iterator_tag
// {};

// struct random_access_iterator_tag
//     : public bidirectional_iterator_tag
// {};

    typedef std::output_iterator_tag        output_iterator_tag;
    typedef std::input_iterator_tag         input_iterator_tag;
    typedef std::forward_iterator_tag       forward_iterator_tag;
    typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
    typedef std::random_access_iterator_tag random_access_iterator_tag;

    template <typename Category, typename T, typename Distance = ptrdiff_t,
            typename Pointer = T*, typename Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    template <typename Iter>
    struct iterator_traits {
        typedef typename Iter::value_type        value_type;
        typedef typename Iter::difference_type   difference_type;
        typedef typename Iter::pointer           pointer;
        typedef typename Iter::reference         reference;
        typedef typename Iter::iterator_category iterator_category;
    };

    template <typename T>
    struct iterator_traits<T*> {
        typedef T                          value_type;
        typedef std::ptrdiff_t             difference_type;
        typedef T*                         pointer;
        typedef T&                         reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template <typename T>
    struct iterator_traits<const T*> {
        typedef T                          value_type;
        typedef std::ptrdiff_t             difference_type;
        typedef const T*                   pointer;
        typedef const T&                   reference;
        typedef random_access_iterator_tag iterator_category;
    };

/*
**  iter_helper
*/
    template <typename Iter>
    inline typename iterator_traits<Iter>::iterator_category iterator_category(
            const Iter&)
    {
        return typename iterator_traits<Iter>::iterator_category();
    }

/*
** random_iterator
*/
    template <typename Iter, typename Container>
    class random_iterator
    {
    protected:
        Iter current_;

        typedef ft::iterator_traits<Iter> traits_type_;

    public:
        typedef Iter                                     iterator_type;
        typedef typename traits_type_::iterator_category iterator_category;
        typedef typename traits_type_::value_type        value_type;
        typedef typename traits_type_::difference_type   difference_type;
        typedef typename traits_type_::pointer           pointer;
        typedef typename traits_type_::reference         reference;

        random_iterator() : current_(iterator_type()) {}

        random_iterator(const iterator_type& other) : current_(other) {}

        template <typename U>
        random_iterator(const random_iterator<
                U, typename ft::enable_if<
                        ft::are_same<U, typename Container::pointer>::value,
                        Container>::type>& it)
                : current_(it.base())
        {
        }

        ~random_iterator() {}

        reference operator*()                   const { return *current_; }

        reference operator[](difference_type n) const { return current_[n]; }

        pointer operator->()                    const { return &(operator*()); }

        random_iterator& operator++()
        {
            ++current_;
            return *this;
        }

        random_iterator operator++(int)
        {
            random_iterator tmp(*this);
            ++current_;
            return tmp;
        }

        random_iterator& operator--()
        {
            --current_;
            return *this;
        }

        random_iterator operator--(int)
        {
            random_iterator tmp(*this);
            --current_;
            return tmp;
        }

        random_iterator operator+(difference_type n) const
        {
            return random_iterator(current_ + n);
        }

        random_iterator& operator+=(difference_type n)
        {
            current_ += n;
            return *this;
        }

        random_iterator operator-(difference_type n) const
        {
            return random_iterator(current_ - n);
        }

        random_iterator& operator-=(difference_type n)
        {
            current_ -= n;
            return *this;
        }

        iterator_type base() const { return current_; }
    };

    template <typename IterL, typename IterR, typename Container>
    inline bool operator==(const random_iterator<IterL, Container>& lhs,
                           const random_iterator<IterR, Container>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename IterL, typename IterR, typename Container>
    inline bool operator!=(const random_iterator<IterL, Container>& lhs,
                           const random_iterator<IterR, Container>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename IterL, typename IterR, typename Container>
    inline bool operator<(const random_iterator<IterL, Container>& lhs,
                          const random_iterator<IterR, Container>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename IterL, typename IterR, typename Container>
    inline bool operator<=(const random_iterator<IterL, Container>& lhs,
                           const random_iterator<IterR, Container>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename IterL, typename IterR, typename Container>
    inline bool operator>(const random_iterator<IterL, Container>& lhs,
                          const random_iterator<IterR, Container>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename IterL, typename IterR, typename Container>
    inline bool operator>=(const random_iterator<IterL, Container>& lhs,
                           const random_iterator<IterR, Container>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename IterL, typename IterR, typename Container>
    inline typename random_iterator<IterL, Container>::difference_type operator-(
            const random_iterator<IterL, Container>& lhs,
            const random_iterator<IterR, Container>& rhs)
    {
        return lhs.base() - rhs.base();
    }

    template <typename Iter, typename Container>
    inline typename random_iterator<Iter, Container>::difference_type operator-(
            const random_iterator<Iter, Container>& lhs,
            const random_iterator<Iter, Container>& rhs)
    {
        return lhs.base() - rhs.base();
    }

    template <typename Iter, typename Container>
    inline random_iterator<Iter, Container> operator+(
            typename random_iterator<Iter, Container>::difference_type n,
            random_iterator<Iter, Container>                           it)
    {
        it += n;
        return it;
    }

/*
** reverse_iterator
*/
    template <typename Iter>
    class reverse_iterator
            : public iterator<typename ft::iterator_traits<Iter>::iterator_category,
                    typename ft::iterator_traits<Iter>::value_type,
                    typename ft::iterator_traits<Iter>::difference_type,
                    typename ft::iterator_traits<Iter>::pointer,
                    typename ft::iterator_traits<Iter>::reference>
    {
    protected:
        Iter current_;

        typedef ft::iterator_traits<Iter> traits_type_;

    public:
        typedef Iter                                     iterator_type;
        typedef typename traits_type_::iterator_category iterator_category;
        typedef typename traits_type_::value_type        value_type;
        typedef typename traits_type_::difference_type   difference_type;
        typedef typename traits_type_::pointer           pointer;
        typedef typename traits_type_::reference         reference;

        reverse_iterator() : current_() {}

        explicit reverse_iterator(iterator_type x) : current_(x) {}

        template <typename U>
        reverse_iterator(const reverse_iterator<U>& x) : current_(x.base())
        {
        }

        ~reverse_iterator() {}

        template <typename U>
        reverse_iterator& operator=(const reverse_iterator<U>& other)
        {
            current_ = other.base();
            return *this;
        }

        iterator_type base() const { return current_; }

        reference operator*() const
        {
            iterator_type tmp = current_;
            return *(--tmp);
        }

        pointer operator->() const { return &(operator*()); }

        reverse_iterator& operator++()
        {
            --current_;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            --current_;
            return tmp;
        }

        reverse_iterator& operator--()
        {
            ++current_;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp(*this);
            ++current_;
            return tmp;
        }

        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(current_ - n);
        }

        reverse_iterator& operator+=(difference_type n)
        {
            current_ -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(current_ + n);
        }

        reverse_iterator& operator-=(difference_type n)
        {
            current_ += n;
            return *this;
        }

        reference operator[](difference_type n) const { return *(*this + n); }
    };

    template <typename IterL, typename IterR>
    inline bool operator==(const reverse_iterator<IterL>& lhs,
                           const reverse_iterator<IterR>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename IterL, typename IterR>
    inline bool operator!=(const reverse_iterator<IterL>& lhs,
                           const reverse_iterator<IterR>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename IterL, typename IterR>
    inline bool operator<(const reverse_iterator<IterL>& lhs,
                          const reverse_iterator<IterR>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename IterL, typename IterR>
    inline bool operator<=(const reverse_iterator<IterL>& lhs,
                           const reverse_iterator<IterR>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename IterL, typename IterR>
    inline bool operator>(const reverse_iterator<IterL>& lhs,
                          const reverse_iterator<IterR>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename IterL, typename IterR>
    inline bool operator>=(const reverse_iterator<IterL>& lhs,
                           const reverse_iterator<IterR>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iter>
    inline typename reverse_iterator<Iter>::difference_type operator-(
            const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <typename IterL, typename IterR>
    inline typename reverse_iterator<IterL>::difference_type operator-(
            const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <typename Iter>
    inline reverse_iterator<Iter> operator+(
            typename reverse_iterator<Iter>::difference_type n,
            const reverse_iterator<Iter>&                    rit)
    {
        return reverse_iterator<Iter>(rit.base() - n);
    }

/*
**  distance
*/
    template <typename InputIter>
    inline typename ft::iterator_traits<InputIter>::difference_type _distance(
            InputIter first, InputIter last, input_iterator_tag)
    {
        typename ft::iterator_traits<InputIter>::difference_type count(0);
        while (first != last) {
            ++first;
            ++count;
        }
        return count;
    }

    template <typename RandomAccessIter>
    inline typename ft::iterator_traits<RandomAccessIter>::difference_type
    _distance(RandomAccessIter first, RandomAccessIter last,
              random_access_iterator_tag)
    {
        return last - first;
    }

    template <typename InputIter>
    inline typename ft::iterator_traits<InputIter>::difference_type distance(
            InputIter first, InputIter last)
    {
        return _distance(
                first, last,
                typename ft::iterator_traits<InputIter>::iterator_category());
    }

}  // namespace ft

#endif  // FT_ITERATOR_TRAITS_H


//#pragma once
//
//#include "container_defines.hpp"
//#include "iterator_traits.hpp"
//#include <memory>
//#include "vector.hpp"
//
//namespace ft {
//
//	template <class iterator, class T>
//	class input_iterator{
//		typedef ft::input_iterator<iterator, T> self;
//	public:
//		explicit input_iterator(iterator val) : curr(val) {};
//		input_iterator(const input_iterator& ori) {
//			curr = ori.getVal();
//		}
//		self&	operator=(const input_iterator& ori) {
//			curr = ori.getVal();
//			return *this;
//		}
//		T&		operator*() {
//			return *curr;
//		}
//		T&		operator->() {
//			return *curr;
//		}
//		iterator	getVal() const {
//			return curr;
//		}
//		bool	operator==(const self& sec) {
//			return (sec.getVal() == curr);
//		}
//		bool	operator!=(const self& sec) {
//			return (sec.getVal() != curr);
//		}
//		self&	operator++() {
//			++curr;
//			return *this;
//		}
//		self	operator++(int) {
//			self	temp = *this;
//			++curr;
//			return temp;
//		}
//		self&	operator--() {
//			--curr;
//			return *this;
//		}
//		self	operator--(int) {
//			self	temp = *this;
//			--curr;
//			return temp;
//		}
//	protected:
//		iterator	curr;
//	};
//
//    template <typename iterator>
//    class reverse_iterator {
//    public:
//        typedef typename	iterator::value_type		value_type;
//        typedef typename	iterator::difference_type	difference_type;
//        typedef typename	iterator::pointer			pointer;
//        typedef typename	iterator::reference			reference;
//        typedef typename	iterator::iterator_category	iterator_category;
//    private:
//        iterator _iterator;
//    public:
//        reverse_iterator() : _iterator() { }
//        explicit reverse_iterator(iterator const &in) : _iterator(in) { }
//        template<typename Iter>
//        reverse_iterator(reverse_iterator<Iter> const &in) : _iterator(in.base()) { }
//        ~reverse_iterator() {}
//        iterator		base() const { return _iterator; }
//        reverse_iterator	&operator++() {
//            --_iterator;
//            return *this;
//        }
//        reverse_iterator	operator++(int) {
//            reverse_iterator	ret = *this;
//            ++(*this);
//            return ret;
//        }
//        reverse_iterator	&operator--() {
//            ++_iterator;
//            return *this;
//        }
//        reverse_iterator	operator--(int) {
//            reverse_iterator	ret = *this;
//            --(*this);
//            return ret;
//        }
//        reference	operator[](size_t index) { return (_iterator[-index - 1]); }
//        pointer		operator->() { return &(this->operator*()); }
//        pointer		operator->() const { return &(this->operator*()); }
//        reference	operator*()  { return *(_iterator - 1); }
//        reference	operator*()  const { return *(_iterator - 1); }
//        reverse_iterator	operator=(reverse_iterator const &in)  { _iterator = in._iterator; return *this; }
//        reverse_iterator	operator+=(int const &value) { _iterator -= value; return *this; }
//        reverse_iterator	operator-=(int const &value) { _iterator += value; return *this; }
//        int					operator-(reverse_iterator const &rhs) const { return rhs._iterator - _iterator; }
//        reverse_iterator	operator+(int const &value)				const { return reverse_iterator(_iterator - (value)); }
//        reverse_iterator	operator-(int const &value)				const { return reverse_iterator(_iterator + (value)); }
//    };
//    template<typename iterator>
//    reverse_iterator<iterator>	operator-(const int &lhs, reverse_iterator<iterator> const &rhs) { return rhs - lhs; }
//    template<typename iterator>
//    reverse_iterator<iterator>	operator+(const int &lhs, reverse_iterator<iterator> const &rhs) { return rhs + lhs; }
//
//    template <class Iterator_L, class Iterator_R>
//    bool	operator== (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }
//    template<typename iterator>
//    bool	operator==(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) { return (lhs.base() == rhs.base()); }
//
//    template <class Iterator_L, class Iterator_R>
//    bool	operator!= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }
//    template<typename iterator>
//    bool	operator!=(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) { return (lhs.base() != rhs.base()); }
//
//    template <class Iterator_L, class Iterator_R>
//    bool	operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }
//    template<typename iterator>
//    bool	operator< (reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) { return (lhs.base() > rhs.base()); }
//
//    template <class Iterator_L, class Iterator_R>
//    bool	operator> (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }
//    template<typename iterator>
//    bool	operator> (reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) { return (lhs.base() < rhs.base()); }
//
//    template <class Iterator_L, class Iterator_R>
//    bool	operator>= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }
//    template<typename iterator>
//    bool	operator>=(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) { return (lhs.base() <= rhs.base()); }
//
//    template <class Iterator_L, class Iterator_R>
//    bool	operator<= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }
//    template<typename iterator>
//    bool	operator<=(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) { return (lhs.base() >= rhs.base()); }
//
//
//	template <typename value_temp, typename vec>
//	class random_access_iterator   {
//	private:
//		value_temp _val_ptr;
//        typedef ft::iterator_traits<value_temp> traits;
//	public:
////		typedef ptrdiff_t difference_type;
//        typedef value_temp                         iterator_type;
//        typedef typename traits::iterator_category iterator_category;
//        typedef typename traits::value_type        value_type;
//        typedef typename traits::difference_type   difference_type;
//        typedef typename traits::pointer           pointer;
//        typedef typename traits::reference         reference;
//
//		random_access_iterator() : _val_ptr() {};
//
//		random_access_iterator(const value_temp& val) : _val_ptr(val) {};
//
//        pointer		base() const { return _val_ptr; }
//		reference operator[](size_t index) {
//			return *(_val_ptr + index);
//		};
//
//		pointer operator->() {
//            return &(operator*());
//		};
//
////		reference operator*() {
////			return *_val_ptr;
////		};
//
//		reference operator*() const {
//			return *_val_ptr;
//		};
//
//		random_access_iterator operator=(random_access_iterator const &other) {
//			_val_ptr = other._val_ptr;
//			return *this;
//		};
//
//		difference_type operator-(random_access_iterator const &rhs) const {
//			return _val_ptr - rhs._val_ptr;
//		};
//
//		random_access_iterator operator+(int const &value) const {
//			return (_val_ptr + value);
//		};
//
//		random_access_iterator operator-(int const &value) const {
//			return (_val_ptr - value);
//		};
//
//		random_access_iterator operator+=(int const &value) {
//			_val_ptr += value;
//			return *this;
//		};
//
//		random_access_iterator &operator++() {
//			_val_ptr++;
//			return *this;
//		};
//
//		random_access_iterator operator++(int) {
//			random_access_iterator ret = *this;
//			++(*this);
//			return ret;
//		};
//
//		random_access_iterator &operator--() {
//			_val_ptr--;
//			return *this;
//		};
//
//		random_access_iterator operator--(int) {
//			random_access_iterator ret = *this;
//			--(*this);
//			return ret;
//		};
//	};
//	template<typename p, typename vec>
//	random_access_iterator<p, vec>	operator-(const int &lhs, random_access_iterator<p,vec> const &rhs) { return random_access_iterator<p,vec>(lhs - rhs.base()); }
//	template<typename p, typename vec>
//	random_access_iterator<p, vec>	operator+(const int &lhs, random_access_iterator<p,vec> const &rhs) { return random_access_iterator<p,vec>(lhs + rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator!=(random_access_iterator<p, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (rhs.base() != lhs.base()); }
//	template<typename p, typename vec>
//	bool	operator!=(random_access_iterator<const typename vec::value_type, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (rhs.base() != lhs.base()); }
//	template<typename p, typename vec>
//	bool	operator!=(random_access_iterator<p, vec> const &lhs, random_access_iterator<const typename vec::value_type, vec> const &rhs) { return (rhs.base() != lhs.base()); }
//	template<typename p, typename vec>
//	bool	operator==(random_access_iterator<p, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (rhs.base() == lhs.base()); }
//	template<typename p, typename vec>
//	bool	operator==(random_access_iterator<const typename vec::value_type, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (rhs.base() == lhs.base()); }
//	template<typename p, typename vec>
//	bool	operator==(random_access_iterator<p, vec> const &lhs, random_access_iterator<const typename vec::value_type, vec> const &rhs) { return (rhs.base() == lhs.base()); }
//	template<typename p, typename vec>
//	bool	operator< (random_access_iterator<p, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() < rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator< (random_access_iterator<const typename vec::value_type, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() < rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator< (random_access_iterator<p, vec> const &lhs, random_access_iterator<const typename vec::value_type, vec> const &rhs) { return (lhs.base() < rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator> (random_access_iterator<p, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() > rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator> (random_access_iterator<const typename vec::value_type, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() > rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator> (random_access_iterator<p, vec> const &lhs, random_access_iterator<const typename vec::value_type, vec> const &rhs) { return (lhs.base() > rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator>=(random_access_iterator<p, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() >= rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator>=(random_access_iterator<const typename vec::value_type, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() >= rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator>=(random_access_iterator<p, vec> const &lhs, random_access_iterator<const typename vec::value_type, vec> const &rhs) { return (lhs.base() >= rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator<=(random_access_iterator<p, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() <= rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator<=(random_access_iterator<const typename vec::value_type, vec> const &lhs, random_access_iterator<p, vec> const &rhs) { return (lhs.base() <= rhs.base()); }
//	template<typename p, typename vec>
//	bool	operator<=(random_access_iterator<p, vec> const &lhs, random_access_iterator<const typename vec::value_type, vec> const &rhs) { return (lhs.base() <= rhs.base()); }
//
//	template <typename InputIterator, typename difference_type>
//	difference_type	difference(InputIterator first, InputIterator last) {
//		difference_type ret = 0;
//		for (InputIterator it = first; it != last; it++)
//			ret++;
//		return ret;
//	}
//	} // namespace ft
