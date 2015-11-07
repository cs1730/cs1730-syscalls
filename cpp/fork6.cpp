// WHY DOES THIS BREAK

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using std::cout;
using std::endl;

int main() {
  
  cout.setf(std::ios_base::unitbuf); // turn off buffering for cout
  pid_t pid;                         // various PIDs

  cout << "before fork" << endl;

  if ((pid = fork()) < 0) { // error
    perror("FORK ERROR");
  } // if

  for (int i = 0; i < 100; ++i) {
    cout << "pid = " << pid << ", "
	 << "i = "   << i   << endl;
  } // for

  return EXIT_SUCCESS;

} // main

