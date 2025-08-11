#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class T>
ostream& operator<<(ostream& os, const std::vector<T>& v) {
  os.put('{');
  for (char comma[]{'\0', ' ', '\0'};const auto&e : v) {
    os << comma << e, comma[0] = ',';
  }
  os << "}\n";
  return os;
}


int main() 
{
  vector<string> words1 {"the", "frogurt", "is", "also", "cursed"};
  cout << words1;
  
  return 0;
}