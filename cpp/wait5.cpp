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

  if ((pid = fork()) < 0) {          // error 
    perror("fork");
  } else if (pid == 0) {             // in child
    exit(EXIT_SUCCESS);
  } // if

  sleep(2);

  if ((pid = fork()) < 0) {          // error 
    perror("fork");
  } else if (pid == 0) {             // in child
    kill(getpid(), SIGSTOP);
    exit(EXIT_SUCCESS);
  } // if

  sleep(2);

  while ((wpid = waitpid(-1, &pstatus, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
    if (WIFEXITED(pstatus)) {
      cout << "child with pid = "                << wpid                 << " "
	   << "exited normally with pstatus = "  << WEXITSTATUS(pstatus) << endl;
    } else if (WIFSTOPPED(pstatus)) {
      int sig = WSTOPSIG(pstatus);
      cout << "child with pid = "      << wpid           << " "
	   << "stopped from signal = " << sig            << " "
	   << "("                      << strsignal(sig) << ")"
	   << endl;
    } else if (WIFSIGNALED(pstatus)) {
      int sig = WTERMSIG(pstatus);
      cout << "child with pid = "                << wpid           << " "
	   << "exited abnormally from signal = " << sig            << " "
	   << "("                                << strsignal(sig) << ")"
	   << endl;
    } // if
  } // while

  if (wpid == -1) {
    perror("waitpid");
  } else if (wpid == 0) {
    cout << "no more status changes detected" << endl;
  } // if

  return EXIT_SUCCESS;

} // main

