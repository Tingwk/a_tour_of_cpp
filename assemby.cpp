#include <iostream>
#include <unistd.h>
// int test() {
//   int i = 1;
//   int j = 2;
//   return i + j;
// }
// int test1(int a,int b){ return a + b;}
int data = 0;
int main(void) {
  using namespace std;
  // test();
  // test1(199,221);
  // std::cout << "The answer is: 42\n" ;
  // int fd = fork();
  // if (fd > 0) {
  //   data = 100;
  //   std::cout << "parent process\n";
  // } else if (fd == 0) {
  //   // sleep(21);
  //   std::cout << "child process,data:"<< data << "\n";
  // }
  // 8 processes are created in total, including the process which executes main function.
  // fork();
  // fork();
  // fork();
  // std::cout << "hello\n";

  if (fork() != 0) {
    cout << "This\n";
  } else {
    if (fork() != 0 ) {
      cout << "answer\n";
    } else {
      if (fork() != 0) 
        cout << "is\n";
      else 
        cout << "42\n";
    }
  }

  return 0;
}