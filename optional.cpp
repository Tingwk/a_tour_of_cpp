#include<iostream>
#include<optional>
#include<type_traits>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
using namespace std;

std::optional<std::string> create(bool f) {
  if (f) {
    return "Godzilla";
  }
  return {};
}

std::optional<std::string> create2(bool f) {
  return f ? std::optional{"Godzilla"} : std::nullopt;
}

int main() {
  {
    cout << create(false).value_or("Empty") << endl;
    cout << create(true).value_or("Empty") << endl;
    cout << create2(false).value_or("Empty") << endl;
    cout << create2(true).value_or("Empty") << endl;
  }

  {
    std::string str = "Salt";
    std::vector<std::string> vec;
    vec.push_back(str);
    // printf("%p %p\n", str.c_str(), vec[0].c_str());
    // printf("%s\t %s\n", str.c_str(), vec[0].c_str());
    // vec.push_back(std::move(str));
    // printf("%p %s", vec[1].c_str(), vec[1].c_str());
    std::cout << "After copy, str is:" << std::quoted(str) << endl;
    vec.push_back(std::move(str));
    std::cout << "After move, str is:" << std::quoted(str) << endl;
    std::cout << "The contents of the vector are {" << std::quoted(vec[0])
              << ", " << std::quoted(vec[1]) << "}\n";
  }
  
  // {
  //   std::optional<int> o(100);
  //   cout << o.has_value() <<'\t' << o.value() << endl;
  //   auto o1 (o);
  //   cout << o1.has_value() << '\t' << o.has_value() << endl;
  //   std::string str(3,'a');
  //   cout << str << endl;
  //   std::optional<std::string> o3(std::in_place, 3,'a');
  //   cout << o3.has_value() << '\t' << o3.value() << '\n';
  //   std::optional<string> o4(std::in_place,{'C','B','A'});
  //   cout << o4.has_value() << '\t' << o4.value() << '\n';
    
  // }



  // decltype(std::remove_const_t<const int>::value) k;
  // std::remove_const_t<const int> k{100};
  // remove_const<const int>::type t{100};
  // const int k1 = 100;
  // cout << typeid(t).name() << endl;
  // cout << typeid(k1).name() << endl;
  // cout << k << '\n';
  // k = 10;
  // cout << k << '\n';
  return 0;
}