#include <cstddef>
#include <iostream>
template <typename T, T v>
struct integral_constant {
  static constexpr T value = v;
  typedef T value_type;
  typedef integral_constant type;
};

typedef integral_constant<int, 2> two_type;
typedef integral_constant<int, 6> six_type;
static_assert(two_type::value * 3 == six_type::value, "2*3 != 6");

// bool constant
typedef integral_constant<bool, false> false_type;
typedef integral_constant<bool, true> true_type;


// for-loop
template<size_t N>
struct Factorial {
  static constexpr size_t value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<1> {
  static constexpr size_t value = 1;
};

// SFINAE(substitution failure is not an error.)
template<class T>
typename T::multiplication_result multiply(T t1, T t2) { 
  std::cout << "multiply(int,int)" << std::endl;
  return t1 * t2;
}

long multiply(int x, int y) { 
  std::cout << "multiply(int,int)" << std::endl;
  return x * y;
}

// enable_if

template<bool B, class T = void>
struct enable_if {
};

template<class T>
struct enable_if<true,T>{
  typedef T type;
};

struct two {
  char c[2];
};
namespace is_class_impl {
// 接受一个执行类的成员变量的指针作为参数。
template<class T> char test(int T::*);
template<class T> two test(...);

}
template<class T>
struct is_class : public integral_constant<bool, sizeof(is_class_impl::test<T>(0)) == 1>{};


