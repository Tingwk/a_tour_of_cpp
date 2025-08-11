#include <tuple>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


template<class Os, class T>
Os& operator<<(Os& os, std::vector<T> const& v)
{
    os << '{';
    for (auto i{v.size()}; const T& e : v)
        os << e << (--i ? "," : "");
    return os << '}';
}


template<class T>
void print_single(T const& v)
{
    if constexpr (std::is_same_v<T, std::decay_t<std::string>>)
        std::cout << std::quoted(v);
    else if constexpr (std::is_same_v<std::decay_t<T>, char>)
        std::cout << "'" << v << "'";
    else
        std::cout << v;
}
 

template<class Tuple, std::size_t N>
struct TuplePrinter
{
  static void print(const Tuple& t) {
    TuplePrinter<Tuple, N-1>::print(t);
    std::cout << " ,";
    print_single(std::get<N-1>(t));
  }
};


template<class T>
struct TuplePrinter<T, 1>
{
  static void print(const T&t) {
    print_single(std::get<0>(t));
  }
};


template<class... Args>
void print(std::string_view message, const std::tuple<Args...>& t) {
  cout << message << " (" ;
  TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
  cout << ")\n";
}

template<class... Args>
void size(const std::tuple<Args...>&t) {
  std::cout << (sizeof...(Args)) << endl;
}

template<class T>
void print_vars(T t) {
  cout << "size:1\n";
  cout << t << endl;
}

template<class T, class... Args>
void print_vars(T t, Args... args) {
  cout << "size:" << (sizeof...(args)) << endl;
  cout << t << endl;
  print_vars(args...);
}



int main()
{
  std::tuple<int, std::string, double> t1;
  cout << std::get<0>(t1) << '\t' << std::get<1>(t1) << '\t' << std::get<2>(t1)  << endl;
  std::tuple<int, std::string, double> t2{42, "Test", -3.14};
  print("Initialized with values, t2:", t2);
  size(t2);
  
  print_vars(42, "Test", -3.14);
  return 0;
}