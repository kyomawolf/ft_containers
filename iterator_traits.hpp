
#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP
#include <stack>

namespace ft {
/*
** true/false_type
*/
    struct true_type {
        static const bool value = true;
        typedef true_type type;
    };

    struct false_type {
        static const bool  value = false;
        typedef false_type type;
    };

/*
** enable_if
*/
    template <bool B, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> {
        typedef T type;
    };

/*
** remove
*/

    template <typename T>
    struct remove_const {
        typedef T type;
    };

    template <typename T>
    struct remove_const<const T> {
        typedef T type;
    };

    template <typename T>
    struct remove_volatile {
        typedef T type;
    };

    template <typename T>
    struct remove_volatile<volatile T> {
        typedef T type;
    };

    template <typename T>
    struct remove_cv {
        typedef typename remove_volatile<typename remove_const<T>::type>::type type;
    };

/*
** is_integral
*/
    template <typename>
    struct is_integral_base : public false_type {};

    template <>
    struct is_integral_base<bool> : public true_type {};

    template <>
    struct is_integral_base<char> : public true_type {};

    template <>
    struct is_integral_base<signed char> : public true_type {};

    template <>
    struct is_integral_base<short int> : public true_type {};

    template <>
    struct is_integral_base<int> : public true_type {};

    template <>
    struct is_integral_base<long int> : public true_type {};

    template <>
    struct is_integral_base<unsigned char> : public true_type {};

    template <>
    struct is_integral_base<unsigned short int> : public true_type {};

    template <>
    struct is_integral_base<unsigned int> : public true_type {};

    template <>
    struct is_integral_base<unsigned long int> : public true_type {};

    template <typename T>
    struct is_integral : is_integral_base<typename remove_cv<T>::type> {};

/*
**  Compare for equality of types.
*/
    template <typename, typename>
    struct are_same : public false_type {};

    template <typename T>
    struct are_same<T, T> : public true_type {};

}  // namespace ft

#endif  // FT_TYPE_TRAITS_HPP

//#pragma once
//
//namespace ft {
//    typedef std::output_iterator_tag        output_iterator_tag;
//    typedef std::input_iterator_tag         input_iterator_tag;
//    typedef std::forward_iterator_tag       forward_iterator_tag;
//    typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
//    typedef std::random_access_iterator_tag random_access_iterator_tag;
//
//    template <typename Category, typename T, typename Distance = ptrdiff_t,
//            typename Pointer = T*, typename Reference = T&>
//    struct iterator {
//        typedef T         value_type;
//        typedef Distance  difference_type;
//        typedef Pointer   pointer;
//        typedef Reference reference;
//        typedef Category  iterator_category;
//    };
//
//    template <typename Iter>
//    struct iterator_traits {
//        typedef typename Iter::value_type        value_type;
//        typedef typename Iter::difference_type   difference_type;
//        typedef typename Iter::pointer           pointer;
//        typedef typename Iter::reference         reference;
//        typedef typename Iter::iterator_category iterator_category;
//    };
//
//    template <typename T>
//    struct iterator_traits<T*> {
//        typedef T                          value_type;
//        typedef std::ptrdiff_t             difference_type;
//        typedef T*                         pointer;
//        typedef T&                         reference;
//        typedef random_access_iterator_tag iterator_category;
//    };
//
//    template <typename T>
//    struct iterator_traits<const T*> {
//        typedef T                          value_type;
//        typedef std::ptrdiff_t             difference_type;
//        typedef const T*                   pointer;
//        typedef const T&                   reference;
//        typedef random_access_iterator_tag iterator_category;
//    };
//}
