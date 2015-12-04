
/** @author  Jackson Wright, Michael E. Cotterell
 *  @see     LICENSE (MIT style license file)
 */

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

// @TODO implement; unwaited children are zombies
void check_children() {
  
} // check_children
 
int main() {
 
  int sfd, cfd;
  char buffer [256];
  struct sockaddr_un my_addr, peer_addr;
  socklen_t peer_addr_size;
 
  // create socket
  if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    nope_out("socket");
  } // if
 
  // clear and set structure
  memset(&my_addr, 0, sizeof(struct sockaddr_un));
  my_addr.sun_family = AF_UNIX; //address family
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
 
  bool done = false;
 
  /* This is the main server loop, will forever accept connections
     and fork, and no more */
  while (!done) {
   
    // accept a connection on the socket
    if ((cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size)) == -1) {
      nope_out("accept");
    } // if
   
    int pid = fork();
   
    /* From hereonout, the CHILD process will branch out to send a receive
       inputs with the client until the client exits, whereupon it will terminate.
       The parent process will instead continue handling connections. */
    if (pid == 0) {
     
      /* This is a inner server loop, will forever receive and send inputs,
         and no more */
      while (!done) {
        string input;
        int inputAmount = 0;
       
        inputAmount = recv(cfd, buffer, 256, 0);
       
        if (inputAmount < 256) buffer[inputAmount] = '\0';
        input = buffer;
         
        // If their first four chars are "ping"
        if ((input.substr(0,4).compare("ping") == 0) &&
            ('0'<= input.back() && input.back() <= '9')) { //Is a digit
         
          // Send back "pong" and a number
          if(('0'<= input.back() && input.back() <= '9') && // Is even
             ((input.back() - '0') % 2 == 0)) {
           
            string response = "pong 0";
            send(cfd, response.c_str(), strlen(response.c_str()), 0);
           
          }
         
          else { // Is odd
           
            string response = "pong 1";
            send(cfd, response.c_str(), strlen(response.c_str()), 0);
           
          }
         
        }
       
        // If their first four chars are "quit"
        else if (input.substr(0,4).compare("quit") == 0) {
          // Break out of the loop
          done = true;
         
          // End the connection
          if (shutdown(cfd, SHUT_RDWR) == -1) nope_out("shutdown(cfd)");
          if (close(cfd) == -1) nope_out("close(cfd)");
         
          exit(EXIT_SUCCESS);
        }
       
        // If their command is unkown
        else {
          string response = "unknown";
          send(cfd, response.c_str(), strlen(response.c_str()), 0);
        }
     
      } // while
   
    } // if
 
  } // while
 
  /* Technically the following doesn't happen because the server doesnt shut
     down when the client wants to exit */
  if (shutdown(sfd, SHUT_RDWR) == -1) nope_out("shutdown(sfd)");
  if (close(sfd) == -1) nope_out("close(sfd)");
  if (unlink(MY_SOCK_PATH) == -1) nope_out("unlink");
 
  return EXIT_SUCCESS;

} // main
