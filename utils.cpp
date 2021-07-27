#include <netdb.h>
#include <arpa/inet.h>

char * get_IP_from_hostname(char * hostname) {

    struct hostent * targetHostname = gethostbyname(hostname);
    if(targetHostname){

/*
         hostent struct has a member called h_addr
         h_addr is a pointer to a network address in network byte order
         in_addr is a struct with a singled unsigned 32-bits long member representing the ip
         inet_ntoa takes as input a struct in_addr
*/

        // the address of a struct is the address of its first member. in this case, our only member.
        in_addr * ipAddress = (in_addr *)targetHostname->h_addr;
        return inet_ntoa(*ipAddress); //dereferencing ipAddress pointer
    }

}