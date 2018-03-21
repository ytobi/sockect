//
// Created by tobi on 3/21/18.
//

#include "client.h"


Client::Client(std::size_t portNumber, char * severName)
{
    this->portNumber = portNumber;
    this->serverName = severName;
}

void Client::init()
{

    hostent *server;

    server = gethostbyname( this->serverName );

    int t = server->h_length;
    this->serverAddress.sin_port = htons( this->portNumber );
    this->serverAddress.sin_family = AF_INET;


    memcpy( ( void *)&serverAddress.sin_addr, server->h_addr_list, server->h_length );

//    bcopy(( &server->h_addr_list),
//          (&serverAddress.sin_addr), server->h_length );

    if( ( Client::clientFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0 )
    {
        std::cout <<  "Error creating socket" << std::endl;
        exit( 0 );
    }

    std::cout <<  "socket created" << std::endl;

    std::cout <<  "Trying to connecting..." << std::endl;


    if( connect( clientFd, (struct sockaddr *)(&serverAddress), sizeof( serverAddress) ) == 0 )
    {
        std::cout << "Error creating connection" << std::endl;
    }
    std::cout << "Got connection from a server " << server->h_name << std::endl;
    communicate( clientFd );

}
void Client::communicate( int clientFd )
{
    char *msg = nullptr;

    std::cout << "waiting for connection" << std::endl;
    do
    {

        if( std::cin.good() )
        {
            std::cin.getline( msg, 1024 );
            send( clientFd, msg, 1024, 0 );
        }
        if( recv( clientFd, msg, 1024, 0) )
        {
            std::cout << "server >> " + *msg << std::endl;
        }

    }while( clientFd > 0 );

    std::cout << "End of connection" << std::endl;

    close( clientFd );
}

int main( int argc, char* argv[] )
{


    if( argc < 3 )
    {
        std::cout << "Ussage << Server Address >> << Port >> " << std::endl;
        exit( 0 );
    }


    Client client( *argv[2], argv[1] );

    client.init();
}