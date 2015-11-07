#define _POSIX_SOURCE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using std::cout;
using std::endl;

int main() {
  
  cout.setf(std::ios_base::unitbuf); // turn off buffering for cout
  pid_t pid, wpid;                   // various PIDs
  int pstatus;                       // process pstatus

  cout << "before fork" << endl;

  if ((pid = fork()) < 0) {          // error 
    perror("FORK ERROR");
  } else if (pid == 0) {             // in child
    for (int i = 0; i < 100; ++i) {
      cout << "i = "        << i         << ", "
	   << "my pid = "   << getpid()  << ", "
	   << "fork = "     << pid       << ", "
	   << "ppid = "     << getppid() << endl;
    } // for
    exit(42);
  } else {                           // in parent
    wpid = waitpid(pid, &pstatus, WNOHANG);
    if (WIFEXITED(pstatus)) {
      cout << "child with pid = "                << wpid                 << " "
	   << "exited normally with pstatus = "  << WEXITSTATUS(pstatus) << endl;
    } // if
  } // if
  return EXIT_SUCCESS;
} // main

