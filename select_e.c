#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>   // For struct timeval
#include <sys/types.h>  // For fd_set
#include <unistd.h>

// select
// Wait for file descriptors to become ready for I/O.

// int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
// struct timeval *timeout)
// nfds – number of file desctipros to monitor (add 1)
// readfds – fixed buffer with list of file descriptors to wait for read access
// writefds – fixed buffer with list of file descriptors to wait for write
// access exceptfds – fixed buffer with list of file descriptors to wait for
// exceptional conditions
// timeout – timeval structure with time to wait before returning

// typedef struct fd_set {
//     u_int  fd_count;
//     SOCKET fd_array[FD_SETSIZE];
// }

// struct timeval {
// 	   long    tv_sec;         /* seconds */
// 	   long    tv_usec;        /* microseconds */
// };

// Returns number of file descriptors, or zero if timeout occurs.

int main() {
  int sock1, sock2;
  struct sockaddr_in addr1, addr2;

  // Declares a fd_set variable, which is a bitmask used to represent a set of
  // file descriptors.
  fd_set readfds;
  int maxfd;
  char buf[256];

  // Create two UDP sockets
  sock1 = socket(AF_INET, SOCK_DGRAM, 0);
  sock2 = socket(AF_INET, SOCK_DGRAM, 0);

  // Configure addresses for sock1
  addr1.sin_family = AF_INET;
  addr1.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr1.sin_port = htons(11111);

  // Configure addresses for sock2
  addr2.sin_family = AF_INET;
  addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr2.sin_port = htons(22222);

  // Bind sockets to their respective addresses
  bind(sock1, (struct sockaddr *)&addr1, sizeof(addr1));
  bind(sock2, (struct sockaddr *)&addr2, sizeof(addr2));

  printf("Listening on ports 11111 and 22222...\n");

  // Calculate the maximum file descriptor for select()
  maxfd = (sock1 > sock2) ? sock1 : sock2;
  maxfd++;  // select() requires maxfd + 1

  while (1) {
    // Initialize the fd_set for reading.
    // This must be done in each iteration as select() modifies it.
    FD_ZERO(&readfds);
    FD_SET(sock1, &readfds);
    FD_SET(sock2, &readfds);

    // Call select() to wait for data on either socket
    // The last argument (timeout) is NULL, meaning it will block indefinitely
    // until a file descriptor is ready.
    select(maxfd, &readfds, NULL, NULL, NULL);

    // Check if sock1 has data
    if (FD_ISSET(sock1, &readfds)) {
      memset(buf, 0, sizeof(buf));
      recv(sock1, buf, sizeof(buf), 0);
      printf("Received on sock1: %s\n", buf);
    }

    // Check if sock2 has data
    if (FD_ISSET(sock2, &readfds)) {
      memset(buf, 0, sizeof(buf));
      recv(sock2, buf, sizeof(buf), 0);
      printf("Received on sock2: %s\n", buf);
    }
  }

  // Close sockets (unreachable in this infinite loop example)
  close(sock1);
  close(sock2);

  return 0;
}

// fd_set readfds;:
// Declares a fd_set variable, which is a bitmask used to represent a set of
// file descriptors.

// FD_ZERO(&readfds);:
// Initializes the fd_set by clearing all its bits, ensuring no file descriptors
// are initially set.

// FD_SET(sock1, &readfds);:
// Sets the bit corresponding to sock1 in readfds, indicating that select()
// should monitor sock1 for readability. The same is done for sock2.

// maxfd = (sock1 > sock2) ? sock1 : sock2; maxfd++;:
// Calculates the highest-numbered file descriptor being monitored and adds 1,
// as required by the first argument of select().

// select(maxfd, &readfds, NULL, NULL, NULL);:
// This is the core call.
// maxfd: The highest file descriptor + 1.
// &readfds: Pointer to the fd_set for monitoring readability.

// NULL, NULL: Pointers to fd_sets for writability and exceptional conditions,
// respectively, which are not used in this example.

// NULL: Pointer to a struct timeval for timeout. NULL means select() will block
// indefinitely until a file descriptor becomes ready.

// FD_ISSET(sock1, &readfds):
// After select() returns, this macro checks if the bit corresponding to sock1
// is set in readfds. If it is, sock1 is ready for reading. The same check is
// performed for sock2.

// FD_ZERO and FD_SET within the loop:
// select() modifies the fd_sets passed to it, so they must be re-initialized
// and re-populated in each iteration of the loop before calling select() again.

// sockaddr構造体(Linux)
// sockaddr構造体は、 #include <sys/socket.h>, #include <netinet/in.h>
// で読み込まれるファイルで 定義されている。実際には、Linux
// では次のようなファイルに含まれている。
// /usr/include/sys/socket.h (/usr/include/x86_64-linux-gnu/sys/socket.h)
// /usr/include/bits/socket.h (/usr/include/x86_64-linux-gnu/bits/socket.h)
// /usr/include/netinet/in.h
// /usr/include/sys/un.h (/usr/include/x86_64-linux-gnu/sys/un.h)
// TCP/IP (IPv4) の場合、アドレスの指定には、sockaddr_in 構造体を使う。connect()
// システムコールのマニュアルには、sockaddr 構造体を使うようにと書かれて
// いるが、TCP/IP では、そのサブクラス(オブジェクト指向用語)である sockaddr_in
// を使う。それには、 IP アドレスとポート番号が必要である。 その他に、sockaddr
// 構造体のサブクラスの中でも sockaddr_in であることを 示す定数 AF_INET
// が先頭に現れる。

// /usr/include/sys/socket.h:
// typedef __uint8_t sa_family_t;

// struct sockaddr {
//   __uint8_t   sa_len;       /* total length */
//   sa_family_t sa_family;    /* [XSI] address family */
//   char        sa_data[14];  /* [XSI] addr value (actually smaller or larger)
//   */
// };

// struct sockaddr_in
// IPv4。IPアドレスは、32ビット(4バイト)。ポート番号は、16ビット(2バイト)。
// /usr/include/netinet/in.h:
// typedef uint32_t in_addr_t;
// typedef uint16_t in_port_t;

// struct in_addr {
//   in_addr_t s_addr;
// };

// struct sockaddr_in {
//  __uint8_t       sin_len;
//  sa_family_t     sin_family;
//  in_port_t       sin_port;
//  struct  in_addr sin_addr;
//  char            sin_zero[8];
// };

// struct sockaddr_in6
// IPv6。IPアドレスは、128ビット(16バイト)。ポート番号は、16ビット(2バイト)。
// /usr/include/netinet6/in6.h:
// typedef struct in6_addr {
//   union {
//     __uint8_t   __u6_addr8[16];
//     __uint16_t  __u6_addr16[8];
//     __uint32_t  __u6_addr32[4];
//   } __u6_addr;  /* 128-bit IP6 address */
// } in6_addr_t;

// struct sockaddr_in6 {
//   __uint8_t       sin6_len;       /* length of this struct(sa_family_t) */
//   sa_family_t     sin6_family;    /* AF_INET6 (sa_family_t) */
//   in_port_t       sin6_port;      /* Transport layer port # (in_port_t) */
//   __uint32_t      sin6_flowinfo;  /* IP6 flow information */
//   struct in6_addr sin6_addr;      /* IP6 address */
//   __uint32_t      sin6_scope_id;  /* scope zone index */
// };

// struct sockaddr_un
// Unix ドメインのソケット。 ファイル名を使って通信相手を識別する。
// /usr/include/sys/un.h:
// struct  sockaddr_un {
//   unsigned char   sun_len;        /* sockaddr len including null */
//   sa_family_t     sun_family;     /* [XSI] AF_UNIX */
//   char            sun_path[104];  /* [XSI] path name (gag) */
// };

// struct sockaddr_storage
// recvfrom() など、受信時にバイト数が不明の時に使う。
// /usr/include/sys/socket.h:
// /*
//  * RFC 2553: protocol-independent placeholder for socket addresses
//  */
// #define _SS_MAXSIZE     128
// #define _SS_ALIGNSIZE   (sizeof(__int64_t))
// #define _SS_PAD1SIZE    \
//                 (_SS_ALIGNSIZE - sizeof(__uint8_t) - sizeof(sa_family_t))
// #define _SS_PAD2SIZE    \
//                 (_SS_MAXSIZE - sizeof(__uint8_t) - sizeof(sa_family_t) - \
//                                 _SS_PAD1SIZE - _SS_ALIGNSIZE)

// struct sockaddr_storage {
//   __uint8_t   ss_len;         /* address length */
//   sa_family_t ss_family;      /* [XSI] address family */
//   char        __ss_pad1[_SS_PAD1SIZE];
//   __int64_t   __ss_align;     /* force structure storage alignment */
//  char         __ss_pad2[_SS_PAD2SIZE];
// };