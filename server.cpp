
#include <iostream>
#include <zconf.h>
#include <cstring>
#include "server.h"
#include <vector>

Server::Server(std::size_t portNumber)
{
    this->portNumber = portNumber;
    this->numberOfSocket = 1;
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
    bzero( &serverAddress.sin_addr, sizeof( serverAddress ) );
    bzero( &serverAddress.sin_addr.s_addr, sizeof( serverAddress ) );

    Server::serverAddress.sin_family = AF_INET;
    Server::serverAddress.sin_port = htons( portNumber );
    Server::serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	
    // creating sockect
    Server::socketFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if( socketFd < 0 )
    {
        alert("Creating socket" , false );

        exit( 0 );
    }
    // alert("Creating socket" , true );

    // binding sockect
    int successfullBinding = bind( socketFd, ( struct sockaddr * )&serverAddress, sizeof( serverAddress ) );

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

    int activeConnection = accept( socketFd, ( struct sockaddr *)NULL, NULL );

    if( activeConnection < 0 )
     {
         alert( "Found a client!! ", false );
     }

    char msg[10];
    bzero( msg, sizeof( msg ) );

    strcpy( msg, "I am a sever" );
    write( activeConnection, msg, strlen( msg ) );
    std::cout << "Server >> " << msg << std::endl;

    do
    {
        // bzero( msg, sizeof( msg ) );
        if ( read( activeConnection, msg, strlen( msg ) ) > 0 )
        {
            std::cout << "client >> " << msg << std::endl;
        }
        if( std::cin.peek() > 0 )
        {
            std::cin >> msg;
            write( activeConnection, msg, strlen( msg ));
        }
    }while( activeConnection > 0 );

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



