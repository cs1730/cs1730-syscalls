
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

using namespace std;

#define MY_SOCK_PATH "socket.sock"
#define LISTEN_BACKLOG 50

void nope_out(string fname) {
  perror(fname.c_str());
  exit(EXIT_FAILURE);
} // nope_out

int main() {

  int n, sfd, cfd;
  char buffer [256];
  struct sockaddr_un my_addr, peer_addr;
  socklen_t peer_addr_size;

  // create socket
  if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    nope_out("socket");
  } // if

  // clear and set structure
  memset(&my_addr, 0, sizeof(struct sockaddr_un));
  my_addr.sun_family = AF_UNIX;
  strcpy(my_addr.sun_path, MY_SOCK_PATH);

  // bind the socket to an address
  if (bind(sfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un)) == -1) {
    nope_out("bind");
  } // if

  // listen for connections on the socket
  if (listen(sfd, LISTEN_BACKLOG) == -1) {
    nope_out("listen");
  } // if

  /* Now we can accept incoming connections one
     at a time using accept(2) */

  peer_addr_size = sizeof(struct sockaddr_un);

  for (int i = 0; i < 3; ++i) {

    // accept a connection on the socket
    if ((cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size)) == -1) {
      nope_out("accept");
    } // if

    dup2(cfd, STDERR_FILENO);

    cout << "Dumping File..." << endl;
    while ((n = read(cfd, buffer, 256)) > 0) {
      if (n < 256) buffer[n] = '\0';
      cout << buffer;
    } // while
    cout << endl;

    cerr << "i can hear you" << endl;

    if (shutdown(cfd, SHUT_RDWR) == -1) nope_out("shutdown(cfd)");
    if (close(cfd) == -1) nope_out("close(cfd)");

  } // for

  if (shutdown(sfd, SHUT_RDWR) == -1) nope_out("shutdown(sfd)");
  if (close(sfd) == -1) nope_out("close(sfd)");
  if (unlink(MY_SOCK_PATH) == -1) nope_out("unlink");

  return EXIT_SUCCESS;
} // main

