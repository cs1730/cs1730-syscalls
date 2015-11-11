
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void close_pipe(int pipefd [2]);
vector<char *> mk_cstrvec(vector<string> & strvec);
void dl_cstrvec(vector<char *> & cstrvec);
void nice_exec(vector<string> args);
inline void nope_out(const string & sc_name); 

int main(const int argc, const char * argv []) {

  int pipefd [2];
  int pid;

  // create pipe
  if (pipe(pipefd) == -1) nope_out("pipe");

  if ((pid = fork()) == -1) {
    nope_out("fork");
  } else if (pid == 0) {
    vector<string> strargs { "cat", "pipe2.cpp" };
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) nope_out("dup2");
    close_pipe(pipefd);
    nice_exec(strargs);
  } // if

  if ((pid = fork()) == -1) {
    nope_out("fork");
  } else if (pid == 0) {
    vector<string> strargs { "less" };
    if (dup2(pipefd[0], STDIN_FILENO) == -1)  nope_out("dup2");
    close_pipe(pipefd);
    nice_exec(strargs);
  } // if

  close_pipe(pipefd);
  waitpid(pid, nullptr, 0);
  return EXIT_SUCCESS;

} // main

void close_pipe(int pipefd [2]) {
  if (close(pipefd[0]) == -1) nope_out("close");
  if (close(pipefd[1]) == -1) nope_out("close");
} // close_pipe

vector<char *> mk_cstrvec(vector<string> & strvec) {
  vector<char *> cstrvec;
  for (unsigned int i = 0; i < strvec.size(); ++i) {
    cstrvec.push_back(new char [strvec.at(i).size() + 1]);
    strcpy(cstrvec.at(i), strvec.at(i).c_str());
  } // for
  cstrvec.push_back(nullptr);
  return cstrvec;
} // mk_cstrvec

void dl_cstrvec(vector<char *> & cstrvec) {
  for (unsigned int i = 0; i < cstrvec.size(); ++i) {
    delete[] cstrvec.at(i);
  } // for
} // dl_cstrvec

void nice_exec(vector<string> strargs) {
    vector<char *> cstrargs = mk_cstrvec(strargs);
    execvp(cstrargs.at(0), &cstrargs.at(0));
    perror("execvp");
    dl_cstrvec(cstrargs);
    exit(EXIT_FAILURE);
} // nice_exec

/** Prints out the latest errno error and exits the process with EXIT_FAILURE.
 *  It should be noted that the name of this function is not portable. Most
 *  persons older than you will NOT understand the name of this function. They
 *  will be confused. Keep this in mind. 
 */
inline void nope_out(const string & sc_name) {
  perror(sc_name.c_str());
  exit(EXIT_FAILURE);
} // nope_out

 
