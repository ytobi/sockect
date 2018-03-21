//
// Created by tobi on 3/21/18.
//

#ifndef SOCKECT_CLIENT_H
#define SOCKECT_CLIENT_H


#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <zconf.h>

class Client
{
private:
    std::size_t portNumber;
    int clientFd;
    char * serverName;
    struct sockaddr_in serverAddress;
    struct hostent *server;


public:
    Client( std::size_t portNumber, char * severName );
    void init();
    void communicate( int connectionFd );
};

#endif //SOCKECT_CLIENT_H
