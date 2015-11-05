#define _POSIX_SOURCE

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>

using std::cerr;
using std::cout;
using std::endl;

void enforce_background();
void sig_handler(int);
void set_sig_handler(int, sighandler_t);

int main() {
  cout.setf(std::ios_base::unitbuf);     // turn off buffering for cout
  enforce_background();                  // make sure we're in a bg process group
  set_sig_handler(SIGCONT, sig_handler); // set SIGCONT handler
  set_sig_handler(SIGTSTP, sig_handler); // set SIGTSTP handler
  set_sig_handler( SIGINT, sig_handler); // set  SIGINT handler
  while (true) pause();                  // pause until signal is received
  //for(;;) pause();                     // how a C programmer would write the previous line
  return EXIT_SUCCESS; 
} // main

void enforce_background() {
  int pgid;
  if ((pgid = tcgetpgrp(STDOUT_FILENO)) == getpgrp()) {
    cerr << "need to be in background" << endl;
    exit(EXIT_FAILURE);
  } else if (pgid == -1) {
    perror("tcgetpgrp");
    exit(EXIT_FAILURE);
  } // if
} // enforce_background

void sig_handler(int signo) {
  cout << "Caught signal " 
       << signo << " (" << strsignal(signo) << ") "
       << "[" << "use \"jobs -l\" to inspect" << "]"
       << endl;
} // sig_handler

void set_sig_handler(int signo, sighandler_t handler) {
  struct sigaction sa;     // sigaction struct object
  sa.sa_handler = handler; // set disposition
  if (sigaction(signo, &sa, nullptr) == -1) perror("sigaction");
} // setup_sig_handler


