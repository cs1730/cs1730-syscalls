
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

void handler1() {
  cout << "handler1" << endl;
} // handler1

void handler2() {
  cout << "handler2" << endl;
} // handler2

void handler3() {
  cout << "handler3" << endl;
} // handler3

int main() {
  atexit(handler1);
  atexit(handler2);
  cout << "before exiting" << endl;
  atexit(handler3);
  atexit(handler1);
  return EXIT_SUCCESS;
} // main
