#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(0);
  } // if

  const char * filename = argv[1];
  int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);

  if (fd != -1) {
    cout << "Opened " << filename << "; "
	 << "fd = " << fd << "; "
	 << "error = " << strerror(errno) 
	 << endl;
  } else {
    cout << "Could not open " << filename << "; "
	 << "fd = " << fd  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
    exit(0);
  } // if

  int ofd = dup(STDOUT_FILENO);       // make duplicate of standard out
  int nfd = dup2(fd, STDOUT_FILENO);  // redirect standard out

  if (nfd == -1) {
    cout << "Could not dup2 with " << filename << "; "
	 << "nfd = " << nfd  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
    exit(0);
  } // if

  cout << "hello" << endl;

  // redirect standard out again
  dup2(ofd, STDOUT_FILENO);

  int cr = close(fd);

  if (cr != -1) {
    cout << "Closed " << filename << "; "
	 << "cr = " << cr << "; "
	 << "error = " << strerror(errno) 
	 << endl;
  } else {
    cout << "Could not close " << filename << "; "
	 << "cr = " << cr  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
  } // if
  
  return EXIT_SUCCESS;
} // main

