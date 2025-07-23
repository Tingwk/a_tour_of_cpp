#include <ios>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <type_traits>
#include "type_traits.h"
#include <memory>

using std::cout, std::cin, std::endl;

template<class T>
class Vector {
 public:
  explicit Vector(int sz): size_(sz) {
    if (sz <= 0)
      throw std::length_error{"Vector Constructor: non-positive vector size"};
    size_ = sz;
    elem_ = new T[sz];
  }
  Vector(std::initializer_list<T> l){
    size_ = static_cast<int>(l.size());
    elem_ = new T[size_];
    auto pos = l.begin();
    for (int i = 0; i < size_; i++, ++pos)
    {
      elem_[i] = *pos;
    }
    
  }
  ~Vector() {
    if (elem_) {
      delete[] elem_;
    }
  }
  T& operator[](int k) {
    if (k < 0 || k >= size_)
      throw std::out_of_range{"T& operator[]()"};
    return elem_[k];
  }
  const T& operator[](int k) const {
    if (k < 0 || k >= size_)
      throw std::out_of_range{"const T& operator[]() const"};
    return elem_[k];
  }
  int size() const { return size_; }
 private:
  int size_;
  T* elem_;
};

// to support range-based for loop
template<class T>
T* begin(Vector<T>& v) {
  cout << "begin\n";
  return &v[0];
}

template<class T>
T* end(Vector<T>& v) {
  cout << "end\n";
  return &v[0] + v.size();
}
template<typename T>
void write(Vector<T>& v) {
  for (auto vv : v)
    cout << vv << '\n';
}

template<class Seq, class Value>
Value sum(const Seq& seq, Value& v) {
  for(auto & x : seq)
    v += x;
  return v;
}

template<class T>
class Less_than {
 public:
  explicit Less_than(T val):val_(val) {}
  bool operator()(const T other) {return other < val_;}
  const T val_;
};

template<class T>
class PositiveInteger {
 public:
  PositiveInteger() {}
  bool operator()(T t) {
    return t > 0;  
  }
};
template<class Seq, class Pred>
int count_if(Seq& seq, Pred& pred) {
  int count {0};
  for (auto& item: seq)
    if (pred(item))
      ++count;
  return count;
}
// #1
template<class T>
typename enable_if<std::is_pointer<T>::value, void>::type
do_something(T) {
  std::cout << "Calling do_something(T*), returns nothing" << std::endl;
}

// #2
template<class T>
typename enable_if<!std::is_pointer<T>::value, T>::type
do_something(T t) {
  std::cout << "Calling do_something(T), returns " << t << std::endl;
  return t;
}
template<typename T>
void test(T t) {
  if (std::is_pointer<T>::value) {
    cout << "t is an pointer" << std::endl;
    return;
  }
  std::cout << "t is an ordinary type" << std::endl;
}

class B{};
struct A{};
enum class C{};


// is_function
struct AA {
  int fun();
};

template <typename T> struct PM_traits {};
template<typename U, typename V>
struct PM_traits<U V::*> {
  using member_type = U;
};
int f();

void print(std::shared_ptr<int>& ptr) {
  cout << ptr.use_count() << '\t' << &ptr << '\n';
  cout << *ptr << endl;
}

int main() {
  {
    std::vector<int> v;
    constexpr int count = 33;
    for (int i = 0; i < count; i++) {
      v.emplace_back(i + 1);
      cout << v.capacity() <<' ';
      if (i % 8 == 0) 
        cout << '\n';
    }
    cout << '\n';
    std::vector<int> v1;
    v1.reserve(count);
    for (int i = 0; i < count; i++) {
      v.push_back(i + 1);
      cout << v.capacity() <<' ';
      if (i % 8 == 0) 
        cout << '\n';
    }
  }
  // {
  //   std::shared_ptr<int> ptr(new int (10));
  //   cout << ptr.use_count() << '\t' << &ptr << '\n';
  //   print(ptr);
  //   cout << ptr.use_count() << '\t' << &ptr << '\n';
  // }
  // {
  //   struct AA
  //   {
  //     char a;
  //     char c;
  //     int b;
  //   };
  //   cout << sizeof(AA) << endl;
    
  // }
  // is_pointer
  // {
  //   struct A
  //   {
  //       int m;
  //       void f() {}
  //   };
 
  //   int A::*mem_data_ptr = &A::m;     // a pointer to member data
  //   void (A::*mem_fun_ptr)() = &A::f; // a pointer to member function
 
  //   static_assert(
  //          ! std::is_pointer<A>::value
  //       && ! std::is_pointer_v<A>    // same thing as above, but in C++17!
  //       && ! std::is_pointer<A>()    // same as above, using inherited operator bool
  //       && ! std::is_pointer<A>{}    // ditto
  //       && ! std::is_pointer<A>()()  // same as above, using inherited operator()
  //       && ! std::is_pointer<A>{}()  // ditto
  //       &&   std::is_pointer_v<A*>
  //       &&   std::is_pointer_v<A const* volatile>
  //       && ! std::is_pointer_v<A&>
  //       && ! std::is_pointer_v<decltype(mem_data_ptr)>
  //       && ! std::is_pointer_v<decltype(mem_fun_ptr)>
  //       &&   std::is_pointer_v<void*>
  //       && ! std::is_pointer_v<int>
  //       &&   std::is_pointer_v<int*>
  //       &&   std::is_pointer_v<int**>
  //       && ! std::is_pointer_v<int[10]>
  //       && ! std::is_pointer_v<std::nullptr_t>
  //       &&   std::is_pointer_v<void (*)()>
  //   );
  //   cout << std::boolalpha << std::is_pointer<nullptr_t>::value << endl;
  // }
  // is_enum
  // {
  //   struct A
  //   {
  //     enum  T{};
  //   };
  //   enum E{};
  //   enum class Ec : int {};
  //   cout << std::boolalpha;
  //   cout << std::is_enum<A>::value << endl; // false
  //   cout << std::is_enum<A::T>::value << endl; // true
  //   cout << std::is_enum<E>::value << endl; // true
  //   cout << std::is_enum<Ec>::value << endl;  // true
  //   cout << std::is_enum<int>::value << endl; // false
    
  // }
  // is_array
  // {
  //   class A{};
  //   cout << std::boolalpha;
  //   cout << std::is_array<A>::value << endl; // false
  //   cout << std::is_array<A[]>::value << endl; // true
  //   cout << std::is_array<A[3]>::value << endl; // true
  //   cout << std::is_array<float>::value << endl; // false
  //   cout << std::is_array<int>::value << endl; // false
  //   cout << std::is_array<int[3]>::value << endl; // true
  //   cout << std::is_array<int[]>::value << endl; // true
  //   cout << std::is_array<std::array<int,3>>::value << endl; // fasle.
  // }
  // {
  //   std::cout << std::boolalpha;
  //   std::cout << std::is_class<A>::value << std::endl;// outputs true, which indicates that struct is an class.
  //   std::cout << std::is_class<B>::value << std::endl;
  //   std::cout << std::is_class<C>::value << std::endl;
  //   std::cout << std::is_class<int>::value << std::endl;
  //   // is_function
  //   std::cout << std::is_function<AA>::value << std::endl;
  //   std::cout << std::is_function<int(int)>::value << std::endl;
  //   std::cout << std::is_function<decltype(f)>::value << std::endl;
  //   std::cout << std::is_function<int>::value << std::endl;
  //   using T = PM_traits<decltype(&AA::fun)>::member_type;
  //   std::cout << std::is_function<T>::value << std::endl;
  // }
  // {
  //   int i = 3;
  //   do_something(&i);
  //   do_something(i);
  //   test(i);
  //   test(&i);
  // }
  // {
  //   std::cout << "5! = " << Factorial<5>::value << std::endl;
  //   std::cout << multiply(3.1,3.1) << std::endl;
  // }
  {
    // std::vector<int> v{22,-11,3,-2,0};
    // PositiveInteger<int> pred;
    // std::vector<std::string> strs{"AG","Russia", "Dwc", "Ocd"};
    // Less_than<std::string> str{"Backus"};
    // auto positive_count = count_if(v, pred);
    // cout << "Positive numbers in v: "<< positive_count << '\n';
    // cout << "The number of strings less than " << str.val_ << ": " << count_if(strs, str) << '\n'; 
    // using std::vector;
    // vector<int> v{22,11,33};
    // Less_than<int> l(10);
    // auto k = 100;
    // if (l.operator()(k)) {
    //   cout << l.val_ << " less than " <<  k << endl;
    // }
    // std::sort(v.begin(), v.end(), Less_than<int>())
    // using Less_than to sort an vector
  }
  // {
  //   Vector v {"Sjtu", "Fdu"};
  //   write(v);
  // }
  // {
  //   constexpr int N = 5;
  //   std::array<int, N> arr;
  //   for (int i = 0; i < N; i++)
  //   {
  //     arr[i] = i + 1;
  //   }
  //   for(auto item: arr)
  //     cout << item << ' ';
  //   cout << '\n';
  // }
  // {
  //   Vector<std::string> v(3);
  //   v[0] ="Mit";
  //   v[1] = "Delft";
  //   v[2] = "Sjtu";
  //   write(v);
  // }
  return 0;
}