//
// Created by tobi on 3/21/18.
//
/*
 * create socket
 * bind socket
 * listen on socket
 * accept connection
 */

#include <iostream>
#include <zconf.h>
#include <cstring>
#include "server.h"
#include <vector>

Server::Server(std::size_t portNumber)
{
    this->portNumber = portNumber;
}
Server::~Server()
{
    close( socketFd );
    close( activeConnection );
}
bool Server::init()
{

    bzero( &clientAddress, sizeof( clientAddress ) );
    bzero( &serverAddress, sizeof( serverAddress ) );

    Server::serverAddress.sin_family = AF_INET;
    Server::serverAddress.sin_port = htons( portNumber );
    Server::serverAddress.sin_addr.s_addr = INADDR_ANY;
	
    // creating sockect
    Server::socketFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if( socketFd < 0 )
    {
        alert("Creating socket" , false );

        exit( 0 );
    }
    // alert("Creating socket" , true );

    // binding sockect
    bool successfullBinding = bind( socketFd, ( struct sockaddr * )&serverAddress, sizeof( serverAddress ) );

    if( successfullBinding == -1 )
    {
        alert( "binding", false );
        exit( 0 );
    }

    // alert( "binding", true );
    communicate();

}

void Server::communicate()
{
    std::cout << "\t\t Chat Sever up and running" << std::endl;
    std::cout << "Waiting for client... " << std::endl;

    listen(socketFd, numberOfSocket);

    activeConnection = accept( socketFd, ( struct sockaddr *)&clientAddress, (unsigned *)sizeof(clientAddress));

    if( activeConnection < 0 )
     {
         alert( "Found a client!! ", false );
     }

    char *msg;
    strcpy( msg, "You'v found a sever" );
    send( socketFd, msg, strlen( msg ), 0 );

    for(;;)
    {
        if( std::cin.peek() > 0 )
        {
            std::cin >> msg;

            write( socketFd, msg, strlen( msg ));
        }
        if( read( socketFd, msg, 1024 ) > 0 )
        {
            std::cout << "client >> " + *msg << std::endl;
            if( strcpy( msg, "end") == 0 )
            {
                break;
            }
        }
    }

    close( socketFd );
    close( activeConnection );

}

// Alert a positive message true or error message false
bool Server::alert( std::string message, bool type )
{
    if( type == true ) // positive / success alert
        std::cout << "Succesfull " + message << std::endl;
    else
    {
        std::cout << "Unsuccesfull " + message << std::endl;
        return false;
    }

    return true;
}


int main( int argc, char* argv[] )
{
    Server server( atoi(argv[1]) );
    server.init();
}



