#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <typeinfo>
using namespace std;


int main() {
  std::array<int, 3> a1{ {1, 2, 3} }; // double-braces required in C++11 (not in C++14)
  std::array<int, 3> a2 = {1, 2, 3};  // never required after =
  std::array<std::string, 2> a3 = { std::string("a"), "b" };
  std::reverse_copy(a1.begin(), a1.end(), std::ostream_iterator<int>(std::cout, " "));
  cout << endl;
  
  
  return 0;
}