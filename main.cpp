#include <iostream>
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
int main() {
  {
    SmartPtr<Person> person_ptr(new Person());
    person_ptr->set_name("Jeffy");
    cout << "name:" << person_ptr->name() << endl;
  }
  cout << "over" << endl;
  return 0;
}