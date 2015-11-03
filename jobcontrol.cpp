#define _POSIX_SOURCE

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>

using std::cout;
using std::endl;

void enforce_background();
void sig_handler(int);

int main() {
  enforce_background();
  struct sigaction sa;
  sa.sa_handler = sig_handler;
  sigaction(SIGCONT, &sa, nullptr);
  sigaction(SIGTSTP, &sa, nullptr);
  //  sigaction( SIGINT, &sa, nullptr);
  while (true) pause();
  return EXIT_SUCCESS;
} // main

void enforce_background() {
  if (tcgetpgrp(STDOUT_FILENO) == getpgrp()) {
    cout << "need to be in background" << endl;
    exit(EXIT_FAILURE);
  } // if
} // enforce_background

void sig_handler(int signo) {
  cout << "Caught signal " 
       << signo << " (" << strsignal(signo) << ")"
       << endl;
  switch (signo) {
  case SIGCONT:
    cout << "even though we handled this (SIGCONT), the process still continues if stopped."
	 << endl;
    break;
  case SIGTSTP:
    cout << "since we handled this (SIGTSTP), it will not stop"
	 << endl;
    break;
  case SIGINT:
    cout << "nice try! can't SIGINT this..."
	 << endl;
    break;
  default:
    cout << "this should never happen! (we hope)"
	 << endl;
  } // switch
} // sig_handler


