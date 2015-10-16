#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

void print_now(string s) {
  if (write(STDOUT_FILENO, s.c_str(), s.size()) == -1) {
    perror("println");
  } // if
} // print

void println_now(string s = "") {
  print_now(s + "\n");
} // println

int main() {

  pid_t pid;

  println_now("before fork");

  if ((pid = fork()) < 0) { // error
    perror("FORK ERROR");
  } // if

  for (int i = 0; i < 100; ++i) {
    cout << "i = "        << i         << ", "
	 << "my pid = "   << getpid()  << ", "
	 << "fork = "     << pid       << ", "
	 << "ppid = "     << getppid() << endl;
  } // for

  return EXIT_SUCCESS;

} // main

