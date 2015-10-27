#define _POSIX_SOURCE

#include <iostream>
#include <ctgmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using std::cout;
using std::endl;

void alarm_handler(int sig) {
  cout << "    wake up! " 
       << "(" << sig << ")     "
       << endl;

  alarm(1);
  for (int iters = 0; iters < 100; ++iters) {
    for (int i = 0; i < 1000000; ++i) pow(2.1, i);
  } // for
  cout << "finished loop" << endl;
  signal(SIGALRM, SIG_DFL);
} // alarm_handler

int main() {

  cout.setf(std::ios_base::unitbuf); // turn off buffering for cout
  pid_t pid, wpid;                   // various PIDs
  int pstatus;                       // process pstatus

  cout << "before fork" << endl;

  if ((pid = fork()) < 0) {          // error 
    perror("FORK ERROR");
  } else if (pid == 0) {             // in child
    //signal(SIGALRM, SIG_IGN);        // ignore SIGALRM signal
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGALRM, &sa, nullptr);
    cout << "this child is about to set an alarm for 20s" << endl;
    alarm(20);
    while(true);
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

