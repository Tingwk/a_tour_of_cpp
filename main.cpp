#include <iostream>
#include "move_semantics.hpp"
#include <vector>
#include <memory>
#include <cstdarg>
#include <cstring>
using namespace std;

    
    // vector<MemoryBlock> v;
    // v.push_back(MemoryBlock(23));
    // v.push_back(MemoryBlock(21));
    // return 0;
#include <string>
#include "utility/smart_ptr.hpp"

class Person {
  std::string name_;
 public:
  Person() :name_() {}
  ~Person() {
    std::cout << "Person was destoried" << std::endl;
  }
  void set_name(const std::string name) {name_ = name;}

  const std::string& name() const { return name_; }
};
using namespace std;
using namespace utility;

void simple_printf(const char* fmt...) {
  va_list args;
  va_start(args, fmt);
  printf("length:%lu\n", strlen(fmt));
  char ch;
  while ((ch = *fmt) != '\0') 
  {
    switch (ch)
    {
      case ('d'): {
        auto i = va_arg(args, int);
        printf("%d\n", i);
        break;
      }

      case 'c': {
        int c = va_arg(args, int);
        printf("%c\n", c);
        break;
      }

      case 'f': {
        auto d = va_arg(args, double);
        printf("%f\n", d);
        break;
      }
    
      default:
        printf("nothing to do\n");
        break;
    }
    ++fmt;
  }
  va_end(args);
}


int main() {

  {
    simple_printf("dcff", 3, 'a', 1.999, 42.5); 
  }

  // {
  //   SmartPtr<Person> person_ptr(new Person());
  //   person_ptr->set_name("Jeffy");
  //   cout << "name:" << person_ptr->name() << endl;
  // }
  // {
  //   // test shared_ptr.
  //   auto deleter =[](int *p) {
  //       cout << "call deleter" << endl;
  //       delete p;
  //   };
  //   std::shared_ptr<int> share_ptr(new int {100},[](int *p) {
  //       cout << "call deleter: " << *p << endl;
  //       delete p;
  //   });
  //   share_ptr.reset(new int {29});
  //   std::shared_ptr<int>ptr(new int (10));
  //   auto ptr_1(ptr);
  //   cout << ptr.use_count() << ' ' <<ptr_1.use_count() << '\n';
  //   ptr.reset();
  //   cout << ptr.use_count() << ' ' <<ptr_1.use_count() << '\n' ;
  //   }
  cout << "over" << endl;
  return 0;
}