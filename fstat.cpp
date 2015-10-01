#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cerrno>
#include <fcntl.h>
#include <sys/stat.h>
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

  struct stat buf;
  fstat(fd, &buf);
  cout << "Permissions: "
       << (((buf.st_mode & S_IRUSR) != 0) ? "r" : "-") // user-read?
       << (((buf.st_mode & S_IWUSR) != 0) ? "w" : "-") // user-write?
       << (((buf.st_mode & S_IXUSR) != 0) ? "x" : "-") // user-execute?
       << (((buf.st_mode & S_IRGRP) != 0) ? "r" : "-") // group-read?
       << (((buf.st_mode & S_IWGRP) != 0) ? "w" : "-") // group-write?
       << (((buf.st_mode & S_IXGRP) != 0) ? "x" : "-") // group-execute?
       << (((buf.st_mode & S_IROTH) != 0) ? "r" : "-") // other-read?
       << (((buf.st_mode & S_IWOTH) != 0) ? "w" : "-") // other-write?
       << (((buf.st_mode & S_IXOTH) != 0) ? "x" : "-") // other-execute?
       << endl;

  cout << "Time of last access: "
       << ctime(&buf.st_atim.tv_sec);

  cout << "Time of last modification: "
       << ctime(&buf.st_mtim.tv_sec);

  cout << "Time of last status change: "
       << ctime(&buf.st_ctim.tv_sec);

  if (S_ISREG(buf.st_mode)) cout << "Regular File" << endl;
  if ((buf.st_mode & S_IFMT) == S_IFDIR) cout << "Directory File" << endl;

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

