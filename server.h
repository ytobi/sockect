//
// Created by tobi on 3/21/18.
//


#ifndef SOCKECT_SERVER_H
#define SOCKECT_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>
#include <arpa/inet.h>

class Server
{
private:
    std::size_t portNumber;
    std::size_t numberOfSocket;
    std::size_t socketFd;
    std::size_t activeConnection;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;


public:

    Server( std::size_t portNumber );   // constructor

    ~Server();

    bool init();                        // initialise server socket

    void communicate();                 // manages communication

    std::string recieve();              // captures a messages
    // raise success true or error false alerts
    bool alert( std::string message, bool type );
};

#endif //SOCKECT_SERVER_H
