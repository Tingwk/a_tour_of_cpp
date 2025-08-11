#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>
#include <memory>
using namespace std;
using namespace std::chrono;
void printMessage(int count)
{
  for (size_t i = 0; i < count; i++)
  {
    std::cout << "cpp thread:" << i << std::endl;
  }
}

class PrintTask
{
public:
  void operator()(int count)
  {
    for (int i = 0; i < count; ++i)
    {
      std::cout << "Hello from thread (function object)!\n";
    }
  }
};

void increment(int &x) { ++x; }

int counter;
std::mutex mu;
std::condition_variable cv;
bool ready{false};
void increment_times(int k)
{
  std::lock_guard<std::mutex> lck_guard(mu);
  for (size_t i = 0; i < k; i++)
  {
    ++counter;
  }
}

void workThread()
{
  std::unique_lock<std::mutex> lk(mu);
  cv.wait(lk, []()
          { return ready; });
  std::cout << "Fine, i got the job, so i will process it next" << std::endl;
}

void mainThread()
{
  std::lock_guard<std::mutex> lk_guard(mu);
  std::this_thread::sleep_for(std::chrono::seconds(3)); // sleep 3 seconds
  ready = true;
  std::cout << "ready has been set to true" << std::endl;
  cv.notify_all();
}
std::atomic<int> cnt{0};
void increment_using_atomic(int count)
{
  for (size_t i = 0; i < count; i++)
  {
    cnt.fetch_add(1);
  }
}
thread_local int local_data = 0;
void threadFunction(int seconds)
{
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  ++local_data;
  std::cout << std::this_thread::get_id() << "'s local data:" << local_data << std::endl;
}
#include <type_traits>
struct S
{
  S() = default;
  S(S &&) = delete;
  S(const S &) = default;
};
static_assert(std::is_copy_constructible<S>::value == true);
static_assert(std::is_move_constructible<S>::value != true);
std::atomic_int aint{0};
int my_cnt{};

void f()
{
  for (auto n{100000}; n; --n)
  {
    ++aint;
    ++my_cnt;
  }
}
static_assert(std::is_copy_constructible<std::thread>::value == false);
static_assert(std::is_move_constructible<std::thread>::value == true);

class Widget
{
public:
  Widget()
  {
    std::cout << "Widget default constructed\n";
  }

  Widget(const std::string &name)
  {
    std::cout << "Widget constructed from lvalue: " << name << "\n";
  }

  Widget(std::string &&name)
  {
    std::cout << "Widget constructed from rvalue: " << name << "\n";
  }
};

template <typename T>
std::unique_ptr<Widget> make_widgt(T &&arg)
{
  return std::make_unique<Widget>(std::forward<T>(arg));
  // return std::make_unique<Widget>(arg);
}

struct A
{
  A(int &&n) : val_{std::move(n)} { std::cout << "A(int&&), rvalue overload, n=" << n << '\n'; }
  A(int &n) : val_{n} { std::cout << "A(int&),lvalue overload, n=" << n << '\n'; }
  int val_;
};

class B
{
public:
  template <class T1, class T2, class T3>
  B(T1 &&t1, T2 &&t2, T3 &&t3) : a1_{std::forward<T1>(t1)},
                                 a2_{std::forward<T2>(t2)},
                                 a3_{std::forward<T3>(t3)}
  {
  }

public:
  A a1_, a2_, a3_;
};

template <class T, class U>
std::unique_ptr<T> make_unique1(U &&u)
{
  return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

template <class T, class... U>
std::unique_ptr<T> make_unique2(U &&...u)
{
  return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}

auto make_B(auto &&...args)
{
  return B(std::forward<decltype(args)>(args)...);
}

void f1(int n)
{
  for (size_t i = 0; i < 5; i++)
  {
    std::cout << "Thread 1 executing\n";
    ++n;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void f2(int &n)
{
  for (size_t i = 0; i < 5; i++)
  {
    std::cout << "Thread 2 executing\n";
    ++n;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

class foo
{
public:
  int n = 0;
  void bar()
  {
    for (int i = 0; i < 5; ++i)
    {
      std::cout << "Thread 3 executing\n";
      ++n;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
};

class baz
{
public:
  int n{0};
  void operator()()
  {
    std::cout << "Thread 4 executing\n";
    ++n;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
};

void independentThread()
{
  cout << "starting concurrent thread:" << endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  cout << "Exiting concurrent thread:" << endl;
}

void threadCaller()
{
  std::cout << "Starting thread caller.\n";
  std::thread t(independentThread);
  t.detach();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Exiting thread caller.\n";
}

void foo()
{
  std::this_thread::sleep_for(std::chrono::seconds(10));
}
 
void bar()
{
  std::this_thread::sleep_for(std::chrono::seconds(10));
}

void little_sleep(std::chrono::microseconds us) {
  auto start = std::chrono::high_resolution_clock::now();
  auto end = start + us;

  do {
    std::this_thread::yield(); // os may sc
  } while (std::chrono::high_resolution_clock::now() < end);
  

}

std::once_flag flag1, flag2;

void simple_do_once() {
  std::call_once(flag1, [](){std::cout << "Simple example: executed once" << '\n';});
}

void may_throw_function(bool do_throw) {
  if (do_throw) {
    std::cout << "Throw: call_once will retry\n";
    throw std::exception{};
  }
  std::cout << "Did not throw, call_once will not attempt again\n";
}

void do_once(bool do_throw) {
  try {
    std::call_once(flag2, may_throw_function, do_throw);
  } catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
   
}

std::chrono::milliseconds interval{100};
int job_shared{0};
int job_exclusive{0};

void job_1() {
  std::this_thread::sleep_for(interval);
  while (true)
  {
    if (mu.try_lock()) {
      ++job_shared;
      mu.unlock();
      return;
    } else {
      ++job_exclusive;
      std::cout << "job exclusive (" << job_exclusive << ")\n";
      std::this_thread::sleep_for(interval/2);
    }
  }
  
}

void job_2() {
  mu.lock();
  std::this_thread::sleep_for(interval * 5);
  ++job_shared;
  mu.unlock();
}

int main()
{

  {
    thread t1(job_1);
    thread t2(job_2);
    t1.join();
    t2.join();
    cout << job_exclusive << '\t' << job_shared << endl;
  }
  scoped_lock<std::mutex> lk(mu);
  scoped_lock<std::mutex> lk1(mu);
  cout << "impossible" << endl;
  

  // {
  //   std::thread t1(simple_do_once);
  //   std::thread t2(simple_do_once);
  //   std::thread t3(simple_do_once);
  //   std::thread t4(simple_do_once);
  //   t1.join();
  //   t2.join();
  //   t3.join();
  //   t4.join();

  // }
  // cout << "----------------------" << endl;
  // {
  //   std::thread t1(do_once, true);
  //   std::thread t2(do_once, true);
  //   std::thread t3(do_once, false);
  //   std::thread t4(do_once, true);
  //   t1.join();
  //   t2.join();
  //   t3.join();
  //   t4.join();
  // }


  // {
  //   auto start = std::chrono::high_resolution_clock::now();
  //   little_sleep(std::chrono::microseconds(100));
  //   auto end = std::chrono::high_resolution_clock::now() - start;
  //   cout << "wait for:" << std::chrono::duration_cast<std::chrono::microseconds>(end).count() << endl;
  // }

  // {
  //   std::thread t1(foo), t2(bar);
  //   cout << t1.get_id() << '\t' << t2.get_id() << endl;
  //   t1.swap(t2);
  //   cout << t1.get_id() << '\t' << t2.get_id() << endl;
  //   std::swap(t1,t2);
  //   cout << t1.get_id() << '\t' << t2.get_id() << endl;
  //   t1.detach();
  //   t2.detach();
  // }
  // {
  //   threadCaller();
  //   std::this_thread::sleep_for(std::chrono::seconds(3));

  //   cout << boolalpha;
  //   thread t;
  //   t.detach();
  //   cout << t.joinable() << endl;
  //   t = std::thread{f1, 1};
  //   cout << t.joinable() << endl;
  //   t.join();
  //   cout << t.joinable() << endl;
  //   t = std::thread{f1, 1};
  //   t.detach();
  //   cout << "after detaching:" << t.joinable() << endl;
  //   std::this_thread::sleep_for(std::chrono::milliseconds(155));
  // }

  // {
  //   int n = 0;
  //   foo f;
  //   baz b;
  //   std::thread t1;
  //   std::thread t2(f1,n+1);
  //   std::thread t3(f2, std::ref(n));
  //   cout << boolalpha << t3.joinable() << endl;
  //   std::thread t4(std::move(t3));
  //   std::thread t5(&foo::bar, &f);
  //   std::thread t6(b);
  //   cout << t5.get_id() << endl;
  //   t3 = std::move(t5);
  //   cout << t3.get_id() << endl;
  //   cout << boolalpha << t3.joinable() << '\t' << t4.joinable() << endl;
  //   t2.join();
  //   t4.join();
  //   t3.join();
  //   t6.join();
  //   std::cout << "Final value of n is " << n << '\n';
  //   std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
  //   std::cout << "Final value of b.n (baz::n) is " << b.n << '\n';
  // }

  // callable object in cpp:
  // lambda expression. functional object. function pointer.

  // std::forward
  // {
  //   auto p1 = make_unique1<A>(2); //rvalue
  //   int k = 10;
  //   int i = 11;
  //   auto p2 = make_unique1<A>(k);
  //   cout << p1->val_ << ' ' << p2->val_ << endl;

  //   auto t = make_unique2<B>(2, k, 3);// T is B.
  //   cout << t->a1_.val_ << ' ' << t->a2_.val_ << ' ' << t->a3_.val_ << std::endl;
  //   cout << "-------------------------------" << endl;
  //   [[maybe_unused]] B b = make_B(k,4,i);
  //   // std::string name = "Hello";
  //   // auto w1 = make_widgt(name);
  //   // auto w2 = make_widgt(std::string("Hello")); // here std::string("Hello") is a temprary value(rvalue)
  // }

  // {
  //   vector<std::jthread> pool;
  //   for (size_t i = 0; i < 10; i++)
  //   {
  //     pool.emplace_back(f);
  //   }
  // }
  // cout << aint.load() << ' ' << my_cnt << endl;

  // {
  //   S s;
  //   // std::thread t1(threadFunction,1);
  //   // std::thread t2(threadFunction,2);
  //   // t1.join();
  //   // t2.join();
  // }
  // std::atomic_bool b{false};
  // cout << boolalpha << b.load( ) << endl;
  //
  //   std::cout << "Initial value: " << cnt.load() << std::endl;
  //   std::thread t1(increment_using_atomic,100000);
  //   std::thread t2(increment_using_atomic,100000);
  //   t1.join();
  //   t2.join();
  //   std::cout << "Value after increment: " << cnt.load() << std::endl;
  // }
  // {
  //   std::thread t1(workThread);
  //   std::thread t2(mainThread);
  //   t1.join();
  //   t2.join();
  // }
  // std::thread t1(increment_times, 100000);
  // std::thread t2(increment_times, 100000);
  // t1.join();
  // t2.join();
  // std::cout << counter << std::endl;
  // int num = 0;
  // std::thread t(increment, std::ref(num));
  // t.join();
  // std::cout << "num:" << num << std::endl;
  // std::thread t(printMessage, 3);
  // std::thread t2(PrintTask(), 4);
  // t.join(); //等待线程执行完
  // t2.join();

  std::cout << "over" << std::endl;

  return 0;
}