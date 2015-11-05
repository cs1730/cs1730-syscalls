#define _POSIX_SOURCE

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>

using std::cerr;
using std::cout;
using std::endl;

void sig_handler(int);
void set_sig_handler(int, sighandler_t);

int main() {
  cout.setf(std::ios_base::unitbuf);     // turn off buffering for cout
  set_sig_handler(SIGCONT, sig_handler); // set SIGCONT handler
  set_sig_handler(SIGTSTP, sig_handler); // set SIGTSTP handler
  set_sig_handler( SIGINT, sig_handler); // set  SIGINT handler
  cout << "PID = " << getpid() << endl;  // display pid
  int counter = 0;                       // counter for elapsed time
  while (true) {
    sleep(2);                            // sleep for 2s or until signal is recv
    counter += 2;                        // increment counter
    cout << counter << endl;             // display counter
  } // while
  return EXIT_SUCCESS; 
} // main

void sig_handler(int signo) {
  cout << "Caught signal " 
       << signo << " (" << strsignal(signo) << ") "
       << "[" << "use \"jobs -l\" to inspect" << "]"
       << endl;
} // sig_handler

// Why not just use the signal function? (see signal(2))
void set_sig_handler(int signo, sighandler_t handler) {
  struct sigaction sa;     // sigaction struct object
  sa.sa_handler = handler; // set disposition
  if (sigaction(signo, &sa, nullptr) == -1) perror("sigaction");
} // setup_sig_handler


