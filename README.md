# Yet Another Internet Relay Chat





# FT_IRC
## Description
```Create your own IRC server in C++, fully compatible with an official client.```

```
The keyword in IRC is "Relay." While "Internet" and "Chat" have obvious
meanings, "Relay" sounds a bit more mysterious. Let's have a look at the
basic concept of IRC in order to discover the meaning behind the term.
IRC, in its simplest form, is made up of two programs—a server
program that accepts connections and a client program that connects
to the server.
Of course, it isn't absolutely necessary to use a special program—
the server would view a simple network connection between you and
the server as a client. However, a client program handles some necessary
procedures automatically and provides a better and simpler user interface
than the more technical messages the client and server exchange.
IRC servers connect to each other via an IRC network of servers. Let's
use a very simple model of an IRC network for our example: two servers
and two clients. The servers are connected to each other, and each has a
client (a user) connected to it. The structure would look like this:
```
<img width="598" alt="Screen Shot 2024-02-29 at 11 21 02 AM" src="https://github.com/anastabiti/ft_irc/assets/79755743/d18a804a-4ce2-4e42-b337-041b86fdad1f">


<img width="672" alt="Screen Shot 2024-02-29 at 11 26 58 AM" src="https://github.com/anastabiti/ft_irc/assets/79755743/1c2e7cf0-ae22-40b5-a296-1527ab857a94">

# Networking API

All networking API function are considered equivalent to system calls
such as `read`{.verbatim} or `write`{.verbatim}, they lay in man(2).

``` c
#define INADDR_ANY              (u_int32_t)0x00000000

in_addr_t inet_addr(const char *cp);

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);

int socket(int domain, int type, int protocol);
int bind(int sock_fd, struct sockaddr *addr, socklen_t addr_size);

int listen(int socket, int backlog);
int connect(int socket, const struct sockaddr *address, socklen_t address_len);

ssize_t send(int socket, const void *buffer, size_t length, int flags);
ssize_t recv(int socket, void *buffer, size_t length, int flags);
```

## `socket()`{.verbatim} and `struct sockaddr`{.verbatim}

When `socket()`{.verbatim} is created, which is just allocating a file
resource in the OS, by specifiying the protocol family and type, and
which mode of transmission i.e. UDP or TCP. It requires additional
information on the address itself, namelty the host and the port, which
both should be in machine encoding i.e. same behaviour as
`hton()`{.verbatim}.

-   Except that `inet_addr()`{.verbatim} returns the address in machine
    encoding already

> As a legacy, there are two types `struct sockaddr`{.verbatim} and
> `struct sockaddr_in`{.verbatim}, they represent the same information,
> but the later is more convenient to work with.

At last, both the socket and the address are entangeled using
`bind()`{.verbatim}

## `listen()`{.verbatim}, `accept()`{.verbatim} and `poll()`{.verbatim} multiple clients

When getting a socket for the server, we may `listen()`{.verbatim} for
incoming connections. Each new connection is a new `socket()`{.verbatim}
associated with a client, that is created after calling
`accept()`{.verbatim}.

However, `listen()`{.verbatim} runs asynchronously,
`accept()`{.verbatim} should be called for as many clients that ahve
sent the request. Yet, it blocks e.g. same as waiting for IO. Thus if no
new request has been sent, `accept()`{.verbatim} will await and blocks
the process.

This can be resolved using multitasking, by telling the OS to not block
using `fcntl()`{.verbatim} to alter the flags of the socket file. And
then use `poll()`{.verbatim} to fetch only the ones that are ready to be
fetched. By setting event `POLLIN`{.verbatim} on creation, the OS would
set flags in return when it is unblocking. Now instead of blocking the
process, an `EWOULDBLOCK`{.verbatim} (or `EAGAIN`{.verbatim}) would be
raised, resolving the block.

## `recv()`{.verbatim} data

For each client that has sent, we may `recv()`{.verbatim} some data to
be put in a buffer, the length of the data is returned, and a closed
connection would return 0. However, the total length of the incoming
data may overfit the size of the buffer, thus it may require multiple
reads until it blocks by raising `errno`{.verbatim}.

## Sending Data

# Internet Relay Chat ([RFC1459](https://www.rfc-editor.org/rfc/rfc1459))

## Server

## Client

## Commands

# References
- [The UChicago χ-Projects Internet Relay Chat](http://chi.cs.uchicago.edu/chirc/irc.html) 
- [Beej’s Guide to Network Programming Using Internet Sockets](https://beej.us/guide/bgnet/pdf/bgnet_a4_c_1.pdf)
- https://ubuntu.com/tutorials/irc-server#5-build-the-server
- https://www.inspircd.org 
- https://linuxhint.com/irc_ubuntu/
- https://ircgod.com/docs/irc/to_know/
- [Projet Reseau
Warm Up Exercice — Building an IRC Client and Server
Under guidance of Benoˆıt Barbot & C´esar Rodr´ıguez](http://www.lsv.fr/~rodrigue/teach/npp/2012/tp1.pdf)
- [Service Name and Transport Protocol Port Number Registry
](https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml)
- [Check if a string starts with a certain string in C++
](https://www.techiedelight.com/check-if-a-string-starts-with-a-certain-string-in-cpp/)
- [Modern IRC Client Protocol](https://modern.ircdocs.horse/#errneedmoreparams-461)
- [Socket Programming Tutorial In C For Beginners | Part 1 | Eduonix](https://www.youtube.com/watch?v=LtXEMwSG5-8)
- [Creating a connection-oriented socket](https://www.ibm.com/docs/en/i/7.3?topic=design-creating-connection-oriented-socket)
- [What is the difference between a port and a socket?](https://stackoverflow.com/questions/152457/what-is-the-difference-between-a-port-and-a-socket)
- [The Definition of a Socket Joel M. Winett Lincoln Laboratory 360/677 May 1971](https://www.rfc-editor.org/rfc/rfc147)
- [Chapter 4. Elementary TCP Sockets](https://notes.shichao.io/unp/ch4/)
- [TCP Server-Client implementation in C](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/)
- [ARM BSD Socket](https://www.keil.com/pack/doc/mw6/Network/html/using_network_sockets_bsd.html)
- [sockets docs.oracle.com](https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2k/index.html)
-   [IRC Standard](https://www.rfc-editor.org/rfc/rfc1459)
-   [Using Freenode IRC
    Server](https://unicorn-utterances.com/posts/joining-freenode-irc)
-   [Beej\'s Guide to Network
    Programming](https://beej.us/guide/bgnet/html)
-   [DWise1\'s Sockets Programming
    Pages](http://dwise1.net/pgm/sockets/)
-   [Handling multiple users](http://www.kegel.com/c10k.html)

![visual_reference](https://user-images.githubusercontent.com/94152392/226868617-2b778553-9795-42b7-aa1d-ba27ec688cbd.png)

## Stackoverflow

-   [disable `recv`{.verbatim}
    blocking](https://stackoverflow.com/questions/36985793/blocking-recv-vs-fcntl)
-   [How to change a tcp socket to be non
    blocking](https://stackoverflow.com/questions/1543466/how-do-i-change-a-tcp-socket-to-be-non-blocking)





<img width="1040" alt="Screen Shot 2024-02-29 at 12 28 10 PM" src="https://github.com/anastabiti/ft_irc/assets/79755743/12b7fa9c-d9a8-4498-87f4-5ab9d906eeca">
<img width="1053" alt="Screen Shot 2024-02-29 at 11 50 41 AM" src="https://github.com/anastabiti/ft_irc/assets/79755743/19cbfe85-a0d3-4684-801c-6ab4574d7206">



