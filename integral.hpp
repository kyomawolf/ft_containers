
namespace ft {
//	template <class T, T var>
//	class integral_constant {
//	public:
//		static const T value = var;
//		typedef T value_type;
//		typedef integral_constant<T, var> type;
//		operator T() {
//			return var;
//		}
//	};
//	typedef integral_constant<bool, true>  true_type;
//	typedef integral_constant<bool, false> false_type;
//
//	template <class T>
//	struct is_integral_base : public false_type {};
//	template <>
//	struct is_integral_base<bool> : public true_type {};
//	template <>
//	struct is_integral_base<char> : public true_type {};
//	template <>
//	struct is_integral_base<signed char> : public true_type {};
//	template <>
//	struct is_integral_base<unsigned char> : public true_type {};
//	template <>
//	struct is_integral_base<short> : public true_type {};
//	template <>
//	struct is_integral_base<unsigned short> : public true_type {};
//	template <>
//	struct is_integral_base<int> : public true_type {};
//	template <>
//	struct is_integral_base<unsigned int> : public true_type {};
//	template <>
//	struct is_integral_base<long> : public true_type {};
//	template <>
//	struct is_integral_base<unsigned long> : public true_type {};
//	template <>
//	struct is_integral_base<long long> : public true_type {};
//	template <>
//	struct is_integral_base<unsigned long long> : public true_type {};
////    template <>
////    struct is_integral_base<unsigned long int> : public true_type {};
//
//    template <typename T>
//    struct remove_const {
//        typedef T type;
//    };
//
//    template <typename T>
//    struct remove_const<const T> {
//        typedef T type;
//    };
//
//    template <typename T>
//    struct remove_volatile {
//        typedef T type;
//    };
//
//    template <typename T>
//    struct remove_volatile<volatile T> {
//        typedef T type;
//    };
//    template <typename T>
//    struct remove_cv {
//        typedef typename remove_volatile<typename remove_const<T>::type>::type type;
//    };
//    template <typename T>
//    struct is_integral : is_integral_base<typename remove_cv<T>::type> {};

//    template <bool is_integral, typename T>
//    struct is_integral_res {
//        typedef T type;
//        static const bool value = is_integral;
//    };
//
//    template <typename>
//    struct is_integral_type : public is_integral_res<false, bool> {};
//
//    template <>
//    struct is_integral_type<bool> : public is_integral_res<true, bool> {};
//
//    template <>
//    struct is_integral_type<char> : public is_integral_res<true, char> {};
//
//    template <>
//    struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
//
//    template <>
//    struct is_integral_type<short int> : public is_integral_res<true, short int> {};
//
//    template <>
//    struct is_integral_type<int> : public is_integral_res<true, int> {};
//
//    template <>
//    struct is_integral_type<long int> : public is_integral_res<true, long int> {};
//
//    template <>
//    struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
//
//    template <>
//    struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
//
//    template <>
//    struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
//
//    template <>
//    struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
//
//    template <>
//    struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
//
//    template <>
//    struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};
//
//
//    template <typename T>
//    struct is_integral : public is_integral_type<T> { };
//
//    template<bool Cond, class T = void> struct enable_if {};
//    template<class T> struct enable_if<true, T> { typedef T type; };
//	template <bool Condition, class T = void> struct enable_if{};
//
//    template <class T>
//	struct enable_if<true, T> {
//		typedef T type;
//	};
}
