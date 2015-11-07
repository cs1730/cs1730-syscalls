#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  //int n;           // number of bytes read
  char buffer [] = "supa' mike says hello world\n";
  int len = strlen(buffer);

  write(STDOUT_FILENO, buffer, len);

  return EXIT_SUCCESS;
} // main

