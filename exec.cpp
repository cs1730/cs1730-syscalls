
#include <iostream>
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>

using std::cout;
using std::endl;

void print_banner() {
  for (int i = 0; i < 80; ++i) cout << "#";
  cout << endl;
} // banner

int main(const int argc, char * const argv []) {
  if (argc > 1) {
    const char * filename = argv[1];
    cout << "attempting to exec: " << filename << endl;
    cout << "with options: " << endl;
    for (int i = 2; i < argc; ++i) {
      cout << argv[i] << endl;
    } // for
    print_banner();
    if (execvp(filename, argv + 1) == -1) perror(argv[0]);
  } // if
  return EXIT_FAILURE;
} // main

