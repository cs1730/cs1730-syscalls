
/* THIS IS NOT THE LS YOU NEED FOR YOUR PROJECT. IT IS A SMALL EXAMPLE. */

#include <iostream>
#include <list>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>

using std::cout;
using std::endl;
using std::list;

bool direnticmp(struct dirent * a, struct dirent * b) {
  return strcasecmp(a->d_name, b->d_name) < 0; 
} // direnticmp

int main() {

  list<struct dirent *> entries;                 // entry list
  struct dirent * entry = nullptr;               // entry pointer
  DIR * pwd = opendir(".");                      // open directory

  if (pwd == nullptr) { 
    perror("ls");
  } else {
    while ((entry = readdir(pwd)) != nullptr) {  // read entries
      entries.push_back(entry);                  // add entry to list
    } // while
    entries.sort(direnticmp);                    // sort entries
    for (auto dir : entries) cout << dir->d_name // process entries
				  << endl;       // print entry name
    closedir(pwd);                               // close directory; avoid memory leak
  } // if

  return EXIT_SUCCESS;

} // main

