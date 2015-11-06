
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void close_pipe(int pipefd [2]);
void setup_exec(char ** args, int pipefd [2], int stdin, int stdout);

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

    char ** args = new char * [3];
    args[0] = new char [4];
    strcpy(args[0], "cat");
    args[1] = new char [9];
    strcpy(args[1], "pipe.cpp");
    args[2] = nullptr;

    execvp(args[0], args);
    
    perror("execvp");
    for (int i = 0; i < 3; ++i) delete[] args[i];
    delete[] args;
    exit(EXIT_FAILURE);

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

    char ** args = new char * [2];
    args[0] = new char [5];
    strcpy(args[0], "less");
    args[1] = nullptr;

    execvp(args[0], args);
    
    perror("execvp");
    for (int i = 0; i < 2; ++i) delete[] args[i];
    delete[] args;
    exit(EXIT_FAILURE);

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

void setup_exec(char ** args, int pipefd [2], int stdin, int stdout) {


} // setup_exec


