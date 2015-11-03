
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;

int main() {
  pid_t pid;
  while (true) {
    if ((pid = fork()) == 0) {
      cout << "in child process PID = " << getpid() << endl;
      while (true);
    } // if
  } // while
  return EXIT_SUCCESS;
} // main


