
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
void nice_exec(vector<string> args);

int main(const int argc, const char * argv []) {

  int pipefd [2];
  int pid;

  // create pipe
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  } // if

  if ((pid = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {

    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
      perror("dup2");
      exit(EXIT_FAILURE);
    } // if

    close_pipe(pipefd);

    vector<string> strargs { "cat", "pipe.cpp" };
    nice_exec(strargs);

  } // if

  if ((pid = fork()) == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {

    if (dup2(pipefd[0], STDIN_FILENO) == -1) {
      perror("dup2");
      exit(EXIT_FAILURE);
    } // if

    close_pipe(pipefd);

    vector<string> strargs { "less" };
    nice_exec(strargs);

  } // if

  close_pipe(pipefd);

  waitpid(pid, nullptr, 0);
  return EXIT_SUCCESS;

} // main

void close_pipe(int pipefd [2]) {
  if (close(pipefd[0]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
  if (close(pipefd[1]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
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

void nice_exec(vector<string> strargs) {
    vector<char *> cstrargs = mk_cstrvec(strargs);
    execvp(cstrargs.at(0), &cstrargs.at(0));
    perror("execvp");
    exit(EXIT_FAILURE);
} // nice_exec

