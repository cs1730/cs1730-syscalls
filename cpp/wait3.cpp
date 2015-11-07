#define _POSIX_SOURCE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
    cout << "this child is about to sleep for 20s" << endl;
    sleep(20);
    exit(42);
  } else {                           // in parent
    bool dead = false;
    while (!dead) {
      cout << "checking on child with pid = " << pid << endl;
      if ((wpid = waitpid(pid, &pstatus, WNOHANG)) == -1) {
	perror("waitpid");
      } else if (wpid == 0) {
	cout << "no pstatus changes detected" << endl;
      } else if (WIFEXITED(pstatus)) {
	cout << "child with pid = "                << wpid                 << " "
	     << "exited normally with pstatus = "  << WEXITSTATUS(pstatus) << endl;
	dead = true;
      } else if (WIFSIGNALED(pstatus)) {
	int sig = WTERMSIG(pstatus);
	cout << "child with pid = "                << wpid           << " "
	     << "exited abnormally from signal = " << sig            << " "
	     << "("                                << strsignal(sig) << ")"
	     << endl;
	dead = true;
      } // if
      sleep(2);
    } // while
  } // if
  return EXIT_SUCCESS;
} // main

