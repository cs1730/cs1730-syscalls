#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  cout.setf(std::ios_base::unitbuf); // turn off buffering for 

  if (argc != 3) {
    cout << "Usage: time " << argv[0] << " BUFF_SIZE FILE" << endl;
    cout << "e.g.,: time " << argv[0] << " 4096 assets/random-big.txt" << endl;
    exit(0);
  } // if

  const unsigned int BUFF_SIZE = atoi(argv[1]);
  const char * filename = argv[2];

  int fd = open(filename, O_RDONLY);

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
  } // if

  int n;                                // number of bytes read
  char * buffer = new char [BUFF_SIZE]; // buffer

  cout << "Reading..." << endl;

  while ((n = read(fd, buffer, BUFF_SIZE)) > 0) {
    // do stuff
  } // while

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

  delete buffer;

  return EXIT_SUCCESS;

} // main

