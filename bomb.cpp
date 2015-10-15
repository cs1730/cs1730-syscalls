
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;

int main() {
  pid_t pid;
  while (true) {
    pid = fork();
    if (pid == 0) {
      cout << "in process PID = " << getpid() << endl;
    } // if
  } // while
  return EXIT_SUCCESS;
} // main


