#include <arpa/inet.h>  // for inet_addr
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main(void) {
  int socket_desc;
  struct sockaddr_in server;
  char message[1000], server_reply[2000];

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  // Prepare the sockaddr_in structure
  server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
  server.sin_family = AF_INET;
  server.sin_port = htons(8888);  // Server port

  // Connect to remote server
  if (connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("connect error");
    return 1;
  }
  puts("Connected");

  // Send some data (example)
  strcpy(message, "Hello server, I am the client.");
  if (send(socket_desc, message, strlen(message), 0) < 0) {
    puts("Send failed");
    return 1;
  }
  puts("Data Send");

  // **Receive a reply from the server**
  // recv() blocks until data is available.
  // The received data is stored in the `server_reply` buffer.
  // The return value is the number of bytes received, or -1 on error, or 0 if
  // the connection is closed.
  int bytes_received =
      recv(socket_desc, server_reply, sizeof(server_reply) - 1, 0);
  if (bytes_received < 0) {
    puts("recv failed");
  } else {
    puts("Reply received");
    server_reply[bytes_received] =
        '\0';  // Null-terminate the string if necessary
    puts(server_reply);
  }

  // Close the socket (not shown in snippet but necessary)
  // close(socket_desc);

  return 0;
}
