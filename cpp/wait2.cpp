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
    /* waitpid(): on success, returns the process ID of the child whose state
     * has changed; if WNOHANG was specified and one or more child(ren)
     * specified by pid exist, but have not yet changed state, then 0 is
     * returned. On error, -1 is returned.
     */
    if ((wpid = waitpid(pid, &pstatus, WNOHANG)) == -1) {
      perror("waitpid");
    } else if (wpid == 0) {
      cout << "no pstatus changes detected" << endl;
    } else if (WIFEXITED(pstatus)) {
      cout << "child with pid = "                << wpid                 << " "
	   << "exited normally with pstatus = "  << WEXITSTATUS(pstatus) << endl;
    } else if (WIFSIGNALED(pstatus)) {
      cout << "child with pid = "                << wpid                 << " "
	   << "exited abnormally from signal = " << WTERMSIG(pstatus)    << endl;
    } // if
  } // if
  return EXIT_SUCCESS;
} // main

