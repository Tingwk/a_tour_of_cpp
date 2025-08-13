#include <iostream>
#include <numeric>
#include <stdint.h>
#include <cxxabi.h>
#include <typeinfo>
#include <string>
#include <cstdlib>
using namespace std;


template<typename T>
std::string type_name() {
  int status;
  string name = typeid(T).name();
  auto demangled_name = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
  if (status == 0) {
    name = demangled_name;
    std::free(demangled_name);
  }
  return name;
}

template<typename T, typename U>
void are_equal() {
  #define red "\033[1;31m"
  #define reset "\033[0m"
  cout << type_name<T>() << " vs " << type_name<U>() << endl;
  if (sizeof(T) == sizeof(U)) {
    cout << " - size: both == " << sizeof(T) << endl;
  } else {
    cout << red " - size: " << sizeof(T) << " != " << sizeof(U) << reset "\n";
  }
  if (type_name<T>() == type_name<U>()) {
    std::cout << " - name: both == " << type_name<T>() << '\n';
  }
  else {
    std::cout << red " - name: " << type_name<T>() << " != " << type_name<U>() << reset "\n";
  }
}

struct mystruct
{
  uint16_t data2;
  uint64_t data1;
};


int main(int argc, char const *argv[])
{
  {
    int16_t s = 43;
    int16_t result = s + 42;
    cout << "Size:" << sizeof(result) << endl;
    cout << sizeof(mystruct) << endl;
  }

  // {
  //   are_equal<uint8_t, int8_t>();
  //   are_equal<uint8_t, uint32_t>();
  //   are_equal<signed char, int8_t>();
  //   are_equal<unsigned char, uint8_t>();

  //   are_equal<signed short int, int16_t>();
  //   are_equal<unsigned short int, uint16_t>();
  //   are_equal<signed int, int32_t>();
  //   are_equal<unsigned int, uint32_t>();
  //   are_equal<signed long int, int64_t>();
  //   are_equal<unsigned long int, uint64_t>();
  //   are_equal<signed long long int, int64_t>();
  //   are_equal<unsigned long long int, uint64_t>();
  // }

  // auto nl_sc = std::numeric_limits<signed char>();
  // auto nl_uc = std::numeric_limits<unsigned char>();
  // cout << sizeof(signed char) << '\t' << +nl_sc.min() << '\t' << +nl_sc.max() << endl;
  // cout << sizeof(unsigned char) << '\t' << +nl_uc.min() << '\t' << +nl_uc.max() << endl;

  // auto nl_wsc = std::numeric_limits<wchar_t>();
  // cout << sizeof(wchar_t) << '\t' << +nl_wsc.min()  << '\t' << +nl_wsc.max() << endl;
  // auto nl_usc = std::numeric_limits< wchar_t>();
  // cout << sizeof(wchar_t) << '\t' << +nl_usc.min()  << '\t' << +nl_usc.max() << endl;
  // cout << sizeof(long int) << '\t' << sizeof(long long int) << endl; 
  // // char c = 0x42;
  // // const char *str = "Hello C++ system programming\n";
  // // cout << c << endl;  
  // // cout << str ;

  // auto num_bytes_signed = sizeof(signed long int);
  // auto min_signed = std::numeric_limits<signed long int>().min();
  // auto max_signed = std::numeric_limits<signed long int>().max();
  // auto num_bytes_unsigned = sizeof(unsigned long int);
  // auto min_unsigned = std::numeric_limits<unsigned long int>().min();
  // auto max_unsigned = std::numeric_limits<unsigned long int>().max();
  // std::cout << "num bytes (signed): " << num_bytes_signed << '\n';
  // std::cout << "min value (signed): " << min_signed << '\n';
  // std::cout << "max value (signed): " << max_signed << '\n';
  
  // std::cout << '\n';
  // std::cout << "num bytes (unsigned): " << num_bytes_unsigned << '\n';
  // std::cout << "min value (unsigned): " << min_unsigned << '\n';
  // std::cout << "max value (unsigned): " << max_unsigned << '\n';

  // cout << sizeof(float) << ' ' << sizeof(double) << ' ' << sizeof(long double) << endl;

  return 0;
}
