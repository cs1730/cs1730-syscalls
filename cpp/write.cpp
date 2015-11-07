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
  int fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0644);

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

  int n;           // number of bytes read
  char buffer [] = "supa' mike says hello world\n";
  int len = strlen(buffer);

  cout << "Writing File..." << endl;
  n = write(fd, buffer, len);
  if (n != -1) cout << "wrote to file" << endl;

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

