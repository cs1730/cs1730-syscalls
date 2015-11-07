#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

int globvar = 6;

void print_now(string s) {
  if (write(STDOUT_FILENO, s.c_str(), s.size()) == -1) {
    perror("println");
  } // if
} // print

void println_now(string s = "") {
  print_now(s + "\n");
} // println

int main() {

  int locvar = 3;
  pid_t pid;

  print_now("before fork");

  if ((pid = fork()) < 0) { // error
    perror("FORK ERROR");
  } else if (pid == 0) {    // in child process
    ++globvar;
    ++locvar;
  } else {                  // in parent process
    sleep(3);
  } // if

  println_now();

  cout << "after fork: "
       << "my pid = "   << getpid()  << ", "
       << "fork = "     << pid       << ", "
       << "ppid = "     << getppid() << ", "
       << "globvar = "  << globvar   << ", "
       << "locvar = "   << locvar    << endl;

  return EXIT_SUCCESS;

} // main

