/*
 *  Daytime Client (TCP)
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 128
#define DAYTIME_SERVER_PORT 13

void daytime(int connectionFd);

int main (int argc, char *argv[] )
{
  int connectionFd;
  int port;
  struct sockaddr_in servaddr;

  if ((argc < 2) || (argc > 3)) {
    fprintf(stderr,"Usage: %s <Server IP> [<Daytime Port>]\n",
            argv[0]);
    exit(1);
  }

  if (argc == 3)
    port=atoi(argv[2]);
  else
    port=DAYTIME_SERVER_PORT;

  connectionFd = socket(PF_INET, SOCK_STREAM, 0);

  if (connectionFd < 0) {
    fprintf(stderr,"nie dai sie polaczyc\n");
    exit(1);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);

  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  int ans = connect(connectionFd, (struct sockaddr *)&servaddr,
           sizeof(servaddr)) ;
  if (ans < 0) {
    fprintf(stderr,"nie dai sie polaczyc\n");
    exit(1);
  }

  daytime(connectionFd);

  return(0);
}
void daytime(int connectionFd)
{
    int n;
    char buffer[MAX_BUFFER+1];
    char bufferRead[MAX_BUFFER+1];
    snprintf(buffer,
              MAX_BUFFER, "12345678");

    int number_to_send = strlen(buffer); // Put your value
    int converted_number = htonl(number_to_send);

    // Write the number to the opened socket
    write(connectionFd, &converted_number, sizeof(converted_number));

    int ans =  write(connectionFd, buffer, strlen(buffer));
    if(ans < 0) {
      fprintf(stderr,"nie dai sie wyslac funkcji\n");
      exit(1);
    } else {
      printf("OK wyslano bjaty\n");
    }
  
    printf("OK czekam na ODP\n");
      while ( n = read(connectionFd,
                        bufferRead, 1) > 0) {
          bufferRead[n] = 0;
          break;
      }
      printf("OK dostalem ODP\n");

//     //wyslij login
    snprintf(buffer,
              MAX_BUFFER, "emil");

    number_to_send = strlen(buffer); // Put your value
    converted_number = htonl(number_to_send);

    // Write the number to the opened socket
    write(connectionFd, &converted_number, sizeof(converted_number));

     ans =  write(connectionFd, buffer, strlen(buffer));
    if(ans < 0) {
      fprintf(stderr,"nie dai sie wyslac funkcji\n");
      exit(1);
    } else {
      printf("OK wyslano bjaty\n");
    }

     printf("OK czekam na ODP\n");
      while ( n = read(connectionFd,
                        bufferRead, 1) > 0) {
          bufferRead[n] = 0;
          break;
      }

   snprintf(buffer,
              MAX_BUFFER, "password123");

     number_to_send = strlen(buffer); // Put your value
    converted_number = htonl(number_to_send);

    // Write the number to the opened socket
    write(connectionFd, &converted_number, sizeof(converted_number));

    ans =  write(connectionFd, buffer, strlen(buffer));
    if(ans < 0) {
      fprintf(stderr,"nie dai sie wyslac funkcji\n");
      exit(1);
    } else {
      printf("OK wyslano bjaty\n");
    }
}
