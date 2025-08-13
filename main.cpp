#include <iostream>
#include "move_semantics.hpp"
#include <vector>
#include <memory>
#include <cstdarg>
#include <cstring>
#include <type_traits>
#include <string_view>
#include <utility>
#include <any>
#include <cmath>
#include <variant>

#include <gsl/gsl>
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

// c++17's namespace
namespace X::Y::Z {
  auto msg = "C++ standard 17 is awesome" ;
}

struct mystruct {
  const char* msg;
  int answer;
};

mystruct
give_me_a_struct() {
  return {"The answer is :", 42};
}

std::pair<const char*, int>
give_me_a_pair() {
  return {"The answer is :", 42};
}

struct anystruct{
  int data;
};

// a example to illustrate the idea of RAII
class myclass{
  public:
  int *ptr;
  myclass():ptr{new int (42)} {cout << "Hello from constructor" << endl;}
  ~myclass() {
    delete ptr;
    cout << "Hello from destructor" << endl; 
  }
  int get() const {return *ptr;}
};

class myclass2{
  FILE *m_file;
 public:
  myclass2(const char* filename): m_file{fopen(filename, "rb")} {
    if (m_file == 0) {
      throw std::runtime_error{std::string("failed to open file:" + string(filename))};
    }
  }
  ~myclass2() {
    fclose(m_file);
    clog << "Hello from destructor" << endl;
  }
};

int main() {

  {
    int array[5] {1,2,3,4,5};
    auto span = gsl::span(array);
    for (const auto &elem : span)
      clog << elem << endl;
  }


  {
    myclass2 c1("test.txt");
    try {
      myclass2 c2("does_not_exist.txt");
    } catch (const std::exception &e) {
      cout << "exception: " << e.what() << endl;
    }
  }

  // int * ptr ;
  // {
  //   myclass c;
  //   cout << c.get() << endl;
  //   ptr = c.ptr;
  //   cout << ptr << '\t' <<c.ptr << '\t' << *ptr << endl;
  // }
  // cout << *ptr << endl;
  // {
  //   std::variant<int, double, std::string> var;
  //   var = 37;
  //   cout << std::get<int>(var) << endl;
  //   var = 3.145;
  //   cout << std::get<double>(var) << endl;
  //   var = "Variant";
  //   cout << std::get<std::string>(var) << endl;
  // }

  // {
  //   auto myany = std::make_any<int>(121);
  //   cout << any_cast<int>(myany) << endl;
  //   myany = 4.21;
  //   cout << any_cast<double>(myany) << endl;
  //   myany = anystruct{29};
  //   cout << any_cast<anystruct>(myany).data << endl;
  // }

  // {
  //   std::string_view sview{"Hello Ubuntu"};
  //   cout << sview << endl;
  //   cout << sview.substr(0,5) << endl;
  //   cout << sview.front() << endl;
  //   cout << sview.back() << endl;
  //   cout << sview.at(1) << endl;
  //   cout << sview.data() << '\t' << sview.size() << endl;
  //   auto sz = sview.size();
    
  //   // the following code will throw out_of_index exception ×
  //   cout << sview[sz] << endl;

  //   sview.remove_prefix(2);
  //   sview.remove_suffix(1);
  //   cout << sview << endl;
  // }

  // auto [msg, num] = give_me_a_pair();
  // cout << msg << num << endl;
  // auto [msg1, ans1] = give_me_a_struct();
  // cout << msg1 << ans1 << endl;

  // cout << X::Y::Z::msg << endl;
  // if (auto i = 42; i) {
  //   cout << i << " is not zero\n";
  // }
  // if constexpr (constexpr auto i = 42;i > 0) {
  //   cout << "Hello system programming" << endl;
  // }
  // {
  //   simple_printf("dcff", 3, 'a', 1.999, 42.5); 
  // }

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