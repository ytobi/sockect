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
#include "server.h"

Server::Server(std::size_t portNumber)
{
    this->portNumber = portNumber;
}
Server::~Server()
{
    close( sockedFd );
}
bool Server::init()
{
    // check if port number is assinged

    portNumber = 4001;

    Server::serverAddress.sin_family = AF_INET;
    Server::serverAddress.sin_port = htons( portNumber );
    Server::serverAddress.sin_addr.s_addr = INADDR_ANY;


    // creating sockect
    Server::sockedFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if( Server::sockedFd < 0 )
    {
        alert("Creating socket" , false );
    }

    alert("Creating socket" , true );

    // binding sockect
    bool successfullBinfidng = bind( sockedFd, ( const sockaddr *)&serverAddress, sizeof( sockaddr ) );

    if( successfullBinfidng )
    {
        alert( "binding", false );
    }

    alert( "binding", true );
    communicate();

}

void Server::communicate()
{
    std::cout << "Waiting for client... " << std::endl;


    listen(sockedFd, Server::numberOfSocket);

    int clientConnection = accept(Server::sockedFd, (sockaddr *) &clientAddress, (unsigned *) sizeof(&clientAddress) );

    std::string msg = "";
    do
    {
        std::cout << "Accepted connections from " + htonl(clientAddress.sin_addr.s_addr) << std::endl;
        if( std::cin.good() )
        {
            std::cin >> msg;
            send( clientConnection, ( const void *)&msg, msg.length(), 0 );
        }

        if( recv( clientConnection, ((void *)&msg), msg.length(), 0) )
        {
            std::cout << "Client " + msg << std::endl;
        }

    }while ( clientConnection > 0 );

    close( clientConnection );

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

/*
int main()
{
    Server server( 4001 );
    server.init();
}
*/


