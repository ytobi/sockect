//
// Created by tobi on 3/21/18.
//

#include "client.h"


Client::Client(std::size_t portNumber, std::string severName)
{
    this->portNumber = portNumber;
    this->serverName = severName;
}

void Client::init()
{

    hostent *server;

    char * name = "localhost";
    server = gethostbyname( name );

    int t = server->h_length;
    this->serverAddress.sin_port = htons( this->portNumber );
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;


    memcpy( (void *)&serverAddress.sin_addr, server->h_addr_list, server->h_length );

//    bcopy(( &server->h_addr_list),
//          (&serverAddress.sin_addr), server->h_length );

    if( !( Client::clientFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP )) )
    {
        std::cout <<  "Erro creating socket" << std::endl;
        exit( 0 );
    }

    std::cout <<  "socket created" << std::endl;

    std::cout <<  "wating for connecting..." << std::endl;

    size_t connectionFd = 0;
    if( !( connectionFd = connect( Client::clientFd, (sockaddr *)(&serverAddress), sizeof( serverAddress) )))
    {
        std::cout << "Erro connecting" << std::endl;
    }
    std::cout << "Erro connecting" << std::endl;
    communicate( connectionFd );




}
void Client::communicate( int connectionFd )
{
    char *msg = "";

    std::cout << "waiting for connection" << std::endl;
    do
    {
        if( std::cin.good() )
        {
            std::cin.getline( msg, 1024 );
            send( connectionFd, static_cast<void *>(&msg), 1024, 0 );
        }
        if( recv( connectionFd, &msg, 1024, 0) )
        {
            std::cout << "server >> " + *msg << std::endl;
        }

    }while( connectionFd > 0 );

    std::cout << "End of connection" << std::endl;

    close( connectionFd );
}

int main( int argc, char* argv[] )
{
    argc = 3;
    argv[1] = "localhost";
    *argv[2] = 4001;

    std::cout << "Ussage << Server Address  >> " << std::endl;

    if( argc < 3 )
        std::cout << "Ussage << Server Address >> << Port >> " << std::endl;

    Client client(4001, "127.0.0.1" );

    client.init();
}