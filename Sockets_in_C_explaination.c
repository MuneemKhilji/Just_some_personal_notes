#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include<string.h>
#include <stdlib.h>
#include<signal.h>

//please note:
	//u might have to add extra recvfrom or recv calls
    //if the sendall_udp_ipv6 or send_all_udp_ipv4
    //or send_all functions
    // make more than one send or sendto
    // function calls in the code examples i gave
    //that use sendall_udp_ipv6 or send_all_udp_ipv4
    //or send_all functions. it is because these functions
    //have one goal which is to send a buffer
    //no matter how big it is and no matter how many
    //sendto or send() calls it takes, meanwhile
    // one recv or recvfrom function call
    // can only recieve the 
    // data  from one sendto or send function. it cant
    //recieve the data from a lot sendto and send
    // function calls  hence u might have to use more 
    // than one recv or recvfrom function call.

// both the port and ip used in the code
//has to be available. 

#define PORT	 7777
#define MAXLINE 1024
int sendall( int socket, char *buf, size_t *len ) {
size_t total = 0;// how many bytes we've sent
size_t bytesleft = *len; // how many bytes we have left to send
size_t data_send_on_the_specifc_call;
while( total < *len ) {
data_send_on_the_specifc_call = 
send
( socket, buf + total, bytesleft, 0 );
if (data_send_on_the_specifc_call == -1) {
*len = total; // set len to the amount of bytes
//sent successfully
return -1; 
}
total += data_send_on_the_specifc_call;
bytesleft -= data_send_on_the_specifc_call;
}
*len = total; // set len to the amount of bytes
//sent successfully
return 0; 
}

int sendall_udp_ipv4( int socket, char *buf, size_t *len, struct sockaddr_in destination,  socklen_t size_of_sockaddr_in) {
size_t total = 0;// how many bytes we've sent
size_t bytesleft = *len; // how many bytes we have left to send
size_t data_send_on_the_specifc_call;
while( total < *len ) {
data_send_on_the_specifc_call = 
sendto
( socket, buf + total, bytesleft, 0,(struct sockaddr*)&destination, 
size_of_sockaddr_in );
if (data_send_on_the_specifc_call == -1) {
*len = total; // set len to the amount of bytes
//sent successfully
return -1; 
}
total += data_send_on_the_specifc_call;
bytesleft -= data_send_on_the_specifc_call;
}
*len = total; // set len to the amount of bytes
//sent successfully
return 0; 
}
int sendall_udp_ipv6( int socket, char *buf, size_t *len, struct sockaddr_in6 destination,  socklen_t size_of_sockaddr_in) {
size_t total = 0;// how many bytes we've sent
size_t bytesleft = *len; // how many bytes we have left to send
size_t data_send_on_the_specifc_call;
while( total < *len ) {
data_send_on_the_specifc_call = 
sendto
( socket, buf + total, bytesleft, 0,(struct sockaddr*)&destination, size_of_sockaddr_in );
if (data_send_on_the_specifc_call == -1) {
*len = total; // set len to the amount of bytes
//sent successfully
return -1; 
}
total += data_send_on_the_specifc_call;
bytesleft -= data_send_on_the_specifc_call;
}
*len = total; // set len to the amount of bytes
//sent successfully
return 0; 
}
int main(int argc, char *argv[])
{
if(argc!=3){
    printf("\n there must be exactly two arguments for this program to work, not less nor more. the first argument is the url of the website u wonna scan, second is the port of that url\n");
    return -1;
}
//     To create a socket use the function below:
// int socket( int domain, int type, int protocol )
//the function is in library : sys/socket.h
//the first argument :
// The domain argument specifies a communication 
// domain; this
//        selects the protocol family which 
// will be used for communication.
//        These families are defined in <sys/socket.h>.
//   The formats
//        currently understood by the Linux 
// kernel include:
//        Name         Purpose                                    Man page
//        AF_UNIX      Local communication                        unix(7)
//        AF_LOCAL     Synonym for AF_UNIX
//        AF_INET      IPv4 Internet protocols                    ip(7)
//        AF_AX25      Amateur radio AX.25 protocol               ax25(4)
//        AF_IPX       IPX - Novell protocols
//        AF_APPLETALK AppleTalk                                  ddp(7)
//        AF_X25       ITU-T X.25 / ISO/IEC 8208 protocol         x25(7)
//        AF_INET6     IPv6 Internet protocols                    ipv6(7)
//        AF_DECnet    DECet protocol sockets
//        AF_KEY       Key management protocol, originally
//                     developed for usage with IPsec
//        AF_NETLINK   Kernel user interface device               netlink(7)
//        AF_PACKET    Low-level packet interface                 packet(7)
//        AF_RDS       Reliable Datagram Sockets (RDS) protocol   rds(7)
//                                                                rds-rdma(7)
//        AF_PPPOX     Generic PPP transport layer, for setting
//                     up L2 tunnels (L2TP and PPPoE)
//        AF_LLC       Logical link control (IEEE 802.2 LLC)
//                     protocol
//        AF_IB        InfiniBand native addressing
//        AF_MPLS      Multiprotocol Label Switching
//        AF_CAN       Controller Area Network automotive bus
//                     protocol
//        AF_TIPC      TIPC, "cluster domain sockets" protocol
//        AF_BLUETOOTH Bluetooth low-level socket protocol
//        AF_ALG       Interface to kernel crypto API
//        AF_VSOCK     VSOCK (originally "VMWare VSockets")       vsock(7)
//                     protocol for hypervisor-guest
//                     communication
//        AF_KCM       KCM (kernel connection multiplexer)
//                     interface
//        AF_XDP       XDP (express data path) interface

//        Further details of the above address families, 
// as well as
//        information on several other address families,
//  can be found in       the man page

    //  The socket has the indicated type, which specifies the
    //    communication semantics.  Currently defined types are:

    //    SOCK_STREAM
    //           Provides sequenced, reliable, two-way, connection-based
    //           byte streams.  An out-of-band data transmission mechanism
    //           may be supported.

    //    SOCK_DGRAM
    //           Supports datagrams (connectionless, unreliable messages of
    //           a fixed maximum length).

    //    SOCK_SEQPACKET
    //           Provides a sequenced, reliable, two-way connection-based
    //           data transmission path for datagrams of fixed maximum
    //           length; a consumer is required to read an entire packet
    //           with each input system call.

    //    SOCK_RAW
    //           Provides raw network protocol access.

    //    SOCK_RDM
    //           Provides a reliable datagram layer that does not guarantee
    //           ordering.

    //    SOCK_PACKET
    //           Obsolete and should not be used in new programs; see
    //           packet(7).

    //    Some socket types may not be implemented by all protocol
    //    families.

    //    Since Linux 2.6.27, the type argument serves a second purpose: in
    //    addition to specifying a socket type, it may include the bitwise
    //    OR of any of the following values, to modify the behavior of
    //    socket():

    //    SOCK_NONBLOCK
    //           Set the O_NONBLOCK file status flag on the open file
    //           description (see open(2)) referred to by the new file
    //           descriptor.  Using this flag saves extra calls to fcntl(2)
    //           to achieve the same result.

    //    SOCK_CLOEXEC
    //           Set the close-on-exec (FD_CLOEXEC) flag on the new file
    //           descriptor.  See the description of the O_CLOEXEC flag in
    //           open(2) for reasons why this may be useful.
 
//  The third argument which is called protocol
//   specifies a particular protocol to be used with the
//        socket.  Normally only a single protocol exists
//for a specific combination of the first two
//arguments,hence normally the field can be specified
//  as 0.  However, it is possible
//        that many protocols exist for a specific 
// combination of the first two
//arguments , in which 
// case a particular
//        protocol must be specified in the protocol field.  
 
// the computer ur using might order bytes in 
//a different way than the ordering used in networking.

//the section below explains how to 
//convert from the order used by ur computer
// to the order used in networking

// There are some  functions in arpa/inet.h
//   to help us out to translate from whatever 
//  byte order that ur computer uses to the 
// byte order used in networking, and vice versa. 
// Their use is 
// advisable even if you are sure that the computer 
// you are using is ordering bytes in the same order
//  as the order used in networking
// because you should always keep ur code portable 
// . The functions
//  come in 32-bit and 16-bit variants depending
// on what you need.
// uint32_t htonl( uint32_t hostint32 )  converts 4 
// bytes from the format of the ordering that
//  ur computer 
// uses to the  format of 
// ordering used in networking 
// uint16_t htons( uint16_t hostint16 )  converts 
// 2 bytes from the format of the ordering that 
// ur computer
//  uses to
//  the format of ordering used in networking 
// uint32_t ntohl( uint32_t netint32 ) converts 
// 4 bytes from the format of  ordering used in
//  networking  to
//  the format of  ordering used in ur computer
// uint16_t ntohs( uint16_t netint16 ) converts 
// 2 bytes from the format of ordering used in
//  networking  to
//  the format of  ordering used in ur computer





//the structure that can be  used to define the address
//  and the port of the source socket or the
//destination socket in case the
// source or destination socket is using ipv4 is :
// struct sockaddr_in {
// sa_family_t sin_family;  //specifies the 
//socket domain of the source or the destination
// socket and yes by socket domain i mean
// the same domain u passed in the first argument 
// of the
// socket() function. so this has to be equal to 
//the domain u passed to the socket() function

// in_port_t sin_port;  Port number 

// struct in_addr sin_addr; /* IPv4 Address */
// };
//example of how one might set this structure:
// struct sockaddr_in server_addr;
// server_addr.sin_family = AF_INET;
// server_addr.sin_port = htons( 2520 );

// server_addr.sin_addr.s_addr = htonl( INADDR_ANY );//element sin_addr in server_addr  will contain any 
// available ipv4 address

// in case u use this to set sin_addr:
// 	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
// then server_addr.sin_addr will contain  "127.0.0.1"

//the structure that can be  used to define the address
//  and the port of the source socket or the
//destination socket in case the
// source or destination socket is using ipv6 is:
// typedef struct sockaddr_in6 {
//   ADDRESS_FAMILY sin6_family;
//   USHORT         sin6_port;
//   ULONG          sin6_flowinfo;
//   IN6_ADDR       sin6_addr;
//   union {
//     ULONG    sin6_scope_id;
//     SCOPE_ID sin6_scope_struct;
//   };}
// Members:

//note:only sin6_family, sin6_addr, sin6_port are 
// required to be set while the rest are optional
//example on how u would set them:
	// struct sockaddr_in6 server_addr;
// server_addr.sin6_family = AF_INET6;
// 	inet_pton(AF_INET6, "::1", &server_addr.sin6_addr);
//sin6_addr will contain ::1
// 	server_addr.sin6_port = htons(SERVER_PORT);
//if u set the sin6_addr as:
// note:i didnt use htonl() or htons() on in6addr_any
//in the example below cuz its not needed in the
//particular example below:
//      server_addr.sin6_addr = in6addr_any;
//then sin6_addr will contain any available ipv6 
// address

// sin6_family

// Is equal to the domain value used in the 
// first argument of the socket() call

// sin6_port

//  port number.

// sin6_flowinfo

// The IPv6 flow information.

// sin6_addr

// An IN6_ADDR structure that contains the used 
// IPv6 address.

// sin6_scope_id

// A ULONG representation of the IPv6 scope 
// identifier that is defined in the 
// sin6_scope_struct member.

// sin6_scope_struct

// A SCOPE_ID structure that contains the scope identifier for the IPv6 transport address. The SCOPE_ID structure is defined as follows:

// typedef struct {
//   union {
//     struct {
//       ULONG  Zone : 28;
//       ULONG  Level : 4;
//     };
//     ULONG  Value;
//   };
// } SCOPE_ID, *PSCOPE_ID;

// Zone

// The zone index that identifies the zone to which the transport address pertains. Zones of the different scopes are instantiated as follows:

//     Each interface on a node comprises a single zone of interface-local scope.

//     Each link, and the interfaces attached to that link, comprise a single zone of link-local scope.

//     There is a single zone of global scope that comprises all of the links and interfaces in the Internet.

//     The boundaries of zones of scope other than interface-local, link-local, and global are defined by network administrators.

// A value of zero specifies the default zone.
// Level

// The scope of the IPv6 transport address. This scope must be the same as the IPv6 scope value that is embedded in the IPv6 transport address. This member can be one of the following:

// ScopeLevelInterface

// The transport address has interface-local scope.

// ScopeLevelLink

// The transport address has link-local scope.

// ScopeLevelSubnet

// The transport address has subnet-local scope.

// ScopeLevelAdmin

// The transport address has admin-local scope.

// ScopeLevelSite

// The transport address has site-local scope.

// ScopeLevelOrganization

// The transport address has organization-local scope.

// ScopeLevelGlobal

// The transport address has global scope.
// Value

// A ULONG representation of the IPv6 scope identifier.


//now as a client u might not need to specify 
//ur port and address even thought u can if u want to
//  but as a server u should do it cuz if u dont 
//then the client wont know which ip and port to 
//connect to.

// and to actualy bind a port and ip to a socket, u have
// to first make a sockaddr_in or sockaddr_in6
//  structure and set the elements in it and then
// bind it to ur socket using the function:
//int bind(int sockfd, const struct sockaddr *addr,
//socklen_t addrlen);
                
//first argument is the socket u wonna bind the
//structure to, the second is the address of 
// sockaddr_in or sockaddr_in6 structure
//which u have to type cast to  struct sockaddr*.
//the last argument is the size of the  sockaddr_in
//or sockaddr_in6
//  structure that u passed in the second argument
    
// Step two is listen() in a server is: 
// to wait for incoming connections. This is the 
// simplest step and you just call:
// int listen(int sockfd, int backlog);
// the first argument is the socket to listen to 
// When multiple clients try to connect to the server,
//  the 
// server then holds the incoming requests that arent 
// accepted yet in a queue. 
//the backlog parameter specifies the number of
//  pending connections the queue will hold.

// as a server after calling the listen function u will
// have to call the accept function.
//  the accept function will return
// a socket that would help u talk to the cleint.
//the accept function is:
// int accept( int sockfd, struct sockaddr *addr, socklen_t *len );
//first argument is the socket that our server is using
//to listen for connection requests from  cleints.
//  the second is the address of 
// sockaddr_in or sockaddr_in6 structure(that
// will contain the ip and port of the newly accepted
//cleint)
//which u have to type cast to  struct sockaddr*.
//the last argument is the size of the  sockaddr_in
//or sockaddr_in6
//  structure that u passed in the second argument


// as a client to connect to a sever the function then 
// would be:
// int connect( int sockfd, struct sockaddr *addr, socklen_t len);
//the first argument is the socket that will
//connect to the server.
//  the second is the address of 
// sockaddr_in or sockaddr_in6 structure(that
// will contain the ip and port of the server u wonna
// conntect to)
//which u have to type cast to  struct sockaddr*.
//the last argument is the size of the  sockaddr_in
//or sockaddr_in6
//  structure that u passed in the second argument
// example of a ipv4 tcp cleint:
int cleint_socket = -1;
struct sockaddr_in server_addr;
cleint_socket = socket(AF_INET, 
SOCK_STREAM, 0);
	if (cleint_socket == -1) {
		perror("socket()");
		return EXIT_FAILURE;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("1.1.1.1");
	server_addr.sin_port = htons(80);

	if ( connect(cleint_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
	// perror("connect()");uncomment if u wonna
        //print the error
    close(cleint_socket);
	}


    
// example of ipv6 tcp client:
int cleint_socket_ = -1;
struct sockaddr_in6 addr;
cleint_socket_ = socket(AF_INET6, 
SOCK_STREAM, 0);
	if (cleint_socket_ == -1) {
		perror("socket()");
		return EXIT_FAILURE;
	}
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(5000);
    inet_pton(AF_INET6, "::1", &addr.sin6_addr);

	if ( connect(cleint_socket_, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		// perror("connect()");uncomment if u wonna
        //print the error
		close(cleint_socket_);
	}

//these cleints will only work if the ip and ports 
//specified are the ip and ports of a server
//listening for new connections

//u can use function:
//  int getaddrinfo(const char *node,
// const char *service, 
// const struct addrinfo *hints,
// struct addrinfo **res);
//  to get the info of a url in a pointer of
// struct sockaddr_in or the struct sockaddr_in6
//the first argument is the  url of the server.
//second is the port number, in case u put http
//in the second argument then the port number
//defined for http will be used
//the last argument has to be a empty pointer
//cuz all the data in the forth argument will be filled
//by the getaddrinfo function
//the last argument is the argument where a link
//list will be returned.each element of link list
//is of addrinfo structure type.each element
//will contain info about each socket that is in the 
//server side.
//to get to the next argument of the linklist u would
//need a element inside addrinfo named:
// struct addrinfo *ai_next which points to the
//next element of the linklist. if there is no next
//element then struct addrinfo *ai_next will be null.
//the third argument  points to an
// addrinfo structure whose ai_family, ai_socktype, 
// and ai_protocol specify criteria for a a element to
//exist in the link list thats inside the third argument.
//the third argument can be NULL.

//each element of the linklist has a member inside of
//it's structure called :struct sockaddr *ai_addr;
//this member can be used to be typecasted
//to sockaddr_in or sockaddr_in6

//the addrinfo structure has many elements
//they are :
        // int              ai_flags;
        //        int              ai_family;
        //        int              ai_socktype;
        //        int              ai_protocol;
        //        socklen_t        ai_addrlen;
        //        struct sockaddr *ai_addr;
        //        char            *ai_canonname;
        //        struct addrinfo *ai_next;


//to send data using tcp the function is:
//ssize_t send(int sockfd, const void buf[.len], size_t len, int flags);
//first argument is the socket u wonna send
//the data through.
//in case of client u have to put ur cleint socket
//in the first argument.
//in case of the server u have to put the socket
// that accept functin returned.
//second argument is the data u wonna send.
//third argument is the length of the data that
//  u wonna send
//last argument  contains some flags but for 
// now we dont need
//to go deep into it.
//the return value is -1 on error and 
// when no error is there then its
// the amount of bytes left
// to send from the second argument.
//the ideal way is that u would keep on sending
//from the second argument until all the data
//in the second argument is sent.
//to do that u would keep an account of the amount
//of data left and the amount of data sent.
//amount of data sent
//would be the value passed
//in the third argument minus
//  the return value of send function.
// example of a function that uses the send() function
//to keep on sending data from a buffer
// until all the data in the buffer is sent:
//note all these send function calls that the 
// sendall function would do 
// will be recieved from individual recv calls.
//in other words if ur sendall function calls the 
//send function 4 times then on the destination
//side the data would still be recieved from 4 
//recv function calls.
// int sendall( int socket, char *buf, size_t *len ) {
// size_t total = 0;// how many bytes we've sent
// size_t bytesleft = *len; // how many bytes we have left to send
// size_t data_send_on_the_specifc_call;
// while( total < *len ) {
// data_send_on_the_specifc_call = 
// send
// ( socket, buf + total, bytesleft, 0 );
// if (data_send_on_the_specifc_call == -1) {
// return -1; 
// }
// total += data_send_on_the_specifc_call;
// bytesleft -= data_send_on_the_specifc_call;
// }
// *len = total; // set len to the amount of bytes
// //sent successfully
// return 0; 
// }


//to receive data using tcp the function is:
// ssize_t recv(int sockfd, void buf[.len], size_t len,
//                         int flags);
//first argument is the socket u wonna recieve
//the data through.
//in case of client u have to put ur cleint socket
//in the first argument
//in case of the server u have to put the socket
//that accept function returned.
//second argument is the destination of the data 
// received.
//third argument is the length of the data u wonna 
//recieve
// last argument contains some flags but for 
// now we dont need
//to go any deep into it
//the return value is -1 on error and 
//and If you got back 0, it means the other side
//  hung up on you which means that they closed the
// socket. So no point in waiting anymore.
// upon success it will return the amount of
//data recieved


// to send function using udp the function is:
// int sendto( int sockfd, const void* msg, int length, 
// unsigned int flags, const struct sockaddr* to, 
// socklen_t tolength )
//first argument is the socket u wonna send
//the data through.
//in case of client u have to put ur cleint socket
//in the first argument.
//in case of the server u have to put the socket
// that accept functin returned.
//second argument is the data u wonna send.
//third argument is the length of the data that
//  u wonna send
//the forth argument  contains some flags but for 
// now we dont need
//to go deep into it.
//the fifth argument is the pointer to 
// sockaddr_in or sockaddr_in6
// structure which has to be typecasted to 
// sockaddr*. the fifth argument will
//contain socket info like ip and port of the 
//destination and any other fields that exists
// in the sockaddr_in structure or the sockaddr_in6 
// structure.
//the last argument is the size of the fifth argument
//the return value is -1 on error and 
// when no error is there then its
// the amount of bytes left
// to send from the second argument.
//the ideal way is that u would keep on sending
//from the second argument until all the data
//in the second argument is sent.
//to do that u would keep an account of the amount
//of data left and the amount of data sent.
//amount of data sent
//would be the value passed
//in the third argument minus
//  the return value of send function.
// example of a function that uses the sendto() 
// function to keep on sending data from a buffer
// until all the data in the buffer is sent:
//note all these sendto function calls that the 
// sendall_udp_ipv4 or sendall_udp_ipv6 
//does would be recieved from individual recvfrom calls.
//in other words if ur sendall_udp_ipv4 or 
//sendall_udp_ipv6 functions calls the 
//sendto function 4 times then on the destination
//sides the data would still be recieved from 4 
//recvfrom function calls.
// int sendall_udp_ipv4( int socket, char *buf, size_t *len, struct sockaddr_in destination,  socklen_t size_of_sockaddr_in) {
// size_t total = 0;// how many bytes we've sent
// size_t bytesleft = *len; // how many bytes we have left to send
// size_t data_send_on_the_specifc_call;
// while( total < *len ) {
// data_send_on_the_specifc_call = 
// sendto
// ( socket, buf + total, bytesleft, 0,(struct sockaddr*)&destination, size_of_sockaddr_in );
// if (data_send_on_the_specifc_call == -1) {
// *len = total; // set len to the amount of bytes
// //sent successfully
// return -1; 
// }
// total += data_send_on_the_specifc_call;
// bytesleft -= data_send_on_the_specifc_call;
// }
// *len = total; // set len to the amount of bytes
// //sent successfully
// return 0; 
// }
// int sendall_udp_ipv6( int socket, char *buf, size_t *len, struct sockaddr_in6 destination,  socklen_t size_of_sockaddr_in) {
// size_t total = 0;// how many bytes we've sent
// size_t bytesleft = *len; // how many bytes we have left to send
// size_t data_send_on_the_specifc_call;
// while( total < *len ) {
// data_send_on_the_specifc_call = 
// sendto
// ( socket, buf + total, bytesleft, 0,(struct sockaddr*)&destination, size_of_sockaddr_in );
// if (data_send_on_the_specifc_call == -1) {
// *len = total; // set len to the amount of bytes
// //sent successfully
// return -1; 
// }
// total += data_send_on_the_specifc_call;
// bytesleft -= data_send_on_the_specifc_call;
// }
// *len = total; // set len to the amount of bytes
// //sent successfully
// return 0; 
// }


// to recieve function using udp the function is:
// ssize_t recvfrom(int sockfd, void buf[restrict .len], 
// size_t len,int flags,
//struct sockaddr *_Nullable restrict src_addr,
//socklen_t *_Nullable restrict addrlen);
//first argument is the socket u wonna recieve
//the data through.
//in case of client u have to put ur cleint socket
//in the first argument
//in case of the server u have to put the socket
//that accept function returned.
//second argument is the destination of the data 
// received.
//third argument is the length of the data u wonna 
//recieve
// forth argument contains some flags but for 
// now we dont need
//to go any deep into it.
//the fifth argument is the pointer to 
// sockaddr_in or sockaddr_in6
// structure which has to be typecasted to 
// sockaddr*. the fifth argument will
//contain socket info like ip and port of the 
//source and any other fields that exists
// in the sockaddr_in structure or the sockaddr_in6 
// structure.
//the last argument is the size of the fifth argument
//the return value is -1 on error.
//Datagram sockets in various domains 
// (e.g., the UNIX and Internet domains) permit 
// zero-length datagrams.  When such a datagram is
//received, the return value is 0.
//the return value is the number of bytes received
//if there was no error and if the datagram isnt a
// zero-length datagram


//example of a code that uses getaddrinfo
//as client to get the  information of the 
//sockets on a specific port of the url 
// is below. the ip address
//of the sockets are printed while the cleint which is
//us then attempts to connect to each socket
//and tries to send a packet and recieves a response.
// example:


struct addrinfo *socketinfo;
int result = getaddrinfo(
    argv[1], argv[2], 
    NULL, &socketinfo);
if (result != 0) {
    perror("\nissues with getraddrinfo function:");
return -1;
}
for(int sockfd, counter=0;(void*)((*socketinfo).ai_next)!=NULL;counter++){
    printf("\ngonna handle socket number %d of the server\n", counter);
    socketinfo=socketinfo->ai_next;//pointing
    //socketinfo to the next element in the link list
    if(socketinfo->ai_family==AF_INET){
        struct sockaddr_in info=*((struct sockaddr_in*)socketinfo->ai_addr);
        uint8_t ipaddress[4];
        memcpy(ipaddress, &(info.sin_addr), 
        sizeof(info.sin_addr));
        printf("\nthe ip is:");
        for(int i=0;i<4;i++){
        printf("%d",ipaddress[i]);    
        if(i!=3){
            printf(".");
        }
    }
    printf("\n");

    }

    if(socketinfo->ai_family==AF_INET6){
        struct sockaddr_in6 info=*((struct sockaddr_in6*)socketinfo->ai_addr);
        char ipaddress[16];
        memcpy(ipaddress, &(info.sin6_addr), 
        sizeof(info.sin6_addr));
        for(int i=0;i<16;i++){
        printf("%02X", ipaddress[i]);
        if(i!=15){
            printf(":");
        }
        }
        printf("\n");
    }
     sockfd= socket(socketinfo->ai_family, 
     socketinfo->ai_socktype, 
     socketinfo->ai_protocol);
     if(sockfd==-1){
        perror("\n socket creation failed because of:");
     }
if( connect(sockfd, 
socketinfo->ai_addr, 
socketinfo->ai_addrlen)==-1){
    perror("\nconnecting failed because:");
}
size_t len=sizeof(char)*(strlen("GET / HTTP/1.0\r\n\r\n")+1);
sendall(sockfd, "GET / HTTP/1.0\r\n\r\n",&len);
if(len==-1){
    printf("\n error in sendall function\n");
}
//note:
// u might have to send a different http packet 
//based on the website to get the response that
//u are expecting
char response[10000];
memset(response, 0, sizeof(char)*10000);
int pid__=fork();//pid will contain the pid
//of child process in the parent process
if (pid__==0) {
recv(sockfd, response, sizeof(char)*10000, 0);
printf("\nthe response is:%s\n", response);
return 0;
}
else{
    sleep(1);
    kill(pid__, 9);
}
close(sockfd);
}


// in udp client and server relationship dosent exist.
//the relationship in udp is simple
//  two computers sending packets
//to each other using sendto and recvfrom
// ipv4 udp example:
//the code sends a packet to its own socket and
//recieves that same packet and then prints it
	

	
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in	 socket_info;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&socket_info, 0, sizeof(socket_info));
		
	// Filling server information
	socket_info.sin_family = AF_INET;
	socket_info.sin_port = htons(PORT);
	socket_info.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd, (struct sockaddr*)&socket_info, sizeof(struct sockaddr_in))==-1)	{
        perror("bind failed in udp ipv4,and the  error is :");
    }
    size_t len = strlen("this is a message")+1;
    socklen_t lenght_of_socket_info=0;
	sendall_udp_ipv4(sockfd,"this is a message", &len, socket_info, sizeof(socket_info));
	printf("Hello message sent.\n");
			
	 recvfrom(sockfd, buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &socket_info,
                &lenght_of_socket_info);
	printf("Server : %s\n", buffer);
	
	close(sockfd);


}
// ipv6 udp example:
//the code sends a packet to its own socket and
//recieves that same packet and then prints it
	

	
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in6	 socket_info;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&socket_info, 0, sizeof(socket_info));
		
	// Filling server information
  socket_info.sin6_family = AF_INET6;
    socket_info.sin6_port = htons(5000);
   socket_info.sin6_addr = in6addr_any;
   	if(bind(sockfd, (struct sockaddr*)&socket_info, sizeof(struct sockaddr_in6))==-1)	{
        perror("bind failed in udp ipv6,and the  error is :");
    }
    size_t len = strlen("this is a message")+1;
    socklen_t lenght_of_socket_info=0;
	sendall_udp_ipv6(sockfd,"this is a message", &len, socket_info , sizeof(socket_info));
	printf("Hello message sent.\n");
			
	 recvfrom(sockfd, buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &socket_info,
                &lenght_of_socket_info);
	printf("Server : %s\n", buffer);

	close(sockfd);


}

    return 0;
}
