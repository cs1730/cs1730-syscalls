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

  off_t size;
  size = lseek(fd, 0, SEEK_END);

  if (size != -1) {
    cout << "File size: " << size << endl;
  } else {
    cout << "lseek error with " << filename << "; "
	 << "size = " << size  << " (should be -1); "
	 << "error = " << strerror(errno) 
	 << endl;
  } // if

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

