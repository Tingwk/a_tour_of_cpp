#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>

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

int main() {
  {
    std::vector<int> v{22,-11,3,-2,0};
    PositiveInteger<int> pred;
    std::vector<std::string> strs{"AG","Russia", "Dwc", "Ocd"};
    Less_than<std::string> str{"Backus"};
    auto positive_count = count_if(v, pred);
    cout << "Positive numbers in v: "<< positive_count << '\n';
    cout << "The number of strings less than " << str.val_ << ": " << count_if(strs, str) << '\n'; 
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