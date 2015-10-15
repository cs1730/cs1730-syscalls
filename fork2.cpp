#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;

int globvar = 6;

int main() {

  int locvar = 3;
  pid_t pid;

  cout << "before fork";

  if ((pid = fork()) < 0) { // error
    perror("FORK ERROR");
  } else if (pid == 0) {    // in child process
    ++globvar;
    ++locvar;
  } else {                  // in parent process
    sleep(3);
  } // if

  cout << endl;

  cout << "after fork: "
       << "pid = "     << pid     << ", "
       << "globvar = " << globvar << ", "
       << "locvar = "  << locvar  << endl;

  return EXIT_SUCCESS;

} // main

