#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <unistd.h>
 
using namespace std;
 
#define MY_SOCK_PATH "socket.sock"
#define LISTEN_BACKLOG 50
 
void nope_out(string fname) {
  perror(fname.c_str());
  exit(EXIT_FAILURE);
} // nope_out
 
int main() {
 
  int cfd;
  int n;
  char buffer [256];
  struct sockaddr_un my_addr;
 
  // create socket
  if ((cfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    nope_out("socket");
  } // if
 
  // clear and set structure
  memset(&my_addr, 0, sizeof(struct sockaddr_un));
  my_addr.sun_family = AF_UNIX;
  strcpy(my_addr.sun_path, MY_SOCK_PATH);
 
  // connect to the socket
  connect(cfd, (struct sockaddr *) &my_addr, sizeof(my_addr));
 
  bool done = false;
 
  while (!done) {

    string input;

    cout << "Enter a message to the server: ";
   
    getline(cin, input);
   
    if (input.compare("quit") == 0) {
      done = true;
      send(cfd, "quit", 4, 0);
      if (shutdown(cfd, SHUT_RDWR) == -1) nope_out("shutdown(sfd)");
      if (close(cfd) == -1) nope_out("close(sfd)");
    } else {
      send(cfd, input.c_str(), strlen(input.c_str()), 0);
      if ((n = recv(cfd, buffer, 256, 0)) < 256) buffer[n] = '\0';
      string response = buffer;
      cout << response << endl;
    } // if
   
  } // while
 
  return EXIT_SUCCESS;

} // main

