#include <iostream>
#include <functional>
using namespace std;
struct Foo
{
  int num_;
  Foo(int num): num_{num}{}
  void print_add(int i) const { cout << num_ + i << endl;}
};

struct PrintNum{
  void operator()(int i) const {
    cout << i << endl;
  }
};

void print_num(int i) {cout<< i << endl;}

int main() {

  {
    std::function<void(int)> f_display = print_num;
    f_display(3);
    // store a lambda
    std::function<void()>f_display_42 = []() {print_num(42);};
    f_display_42();
    // store the result of a call to std::bind
    std::function<void()>f_display_31337 = std::bind(print_num,31337);
    f_display_31337(); 
    // store a call to a member function
    std::function<void(const Foo&, int)> f_display_member = &Foo::print_add;
    Foo foo(985);
    f_display_member(foo, 211);
    // store a call to a data member accessor
    std::function<int(const Foo&)> f_num = &Foo::num_;
    cout << "foo's num_ is: " << f_num(foo) << endl;
    // store a call to a member function and object
    std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, std::placeholders::_1);
    f_add_display2(212);
  }


  return 0;
}