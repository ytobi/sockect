//
// Created by tobi on 3/21/18.
//

#include "client.h"
#include <arpa/inet.h>


Client::Client(std::size_t portNumber, char * severName)
{
    this->portNumber = portNumber;
    this->serverName = severName;
}

Client::~Client()
{
    close( clientFd );
}
void Client::init()
{

	clientFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   
	bzero( &serverAddress, sizeof( serverAddress ) );
	bzero( &server, sizeof( server ) );
	bzero( &serverAddress.sin_addr.s_addr, sizeof( serverAddress ) );
	
    server = gethostbyname( this->serverName );

    if( server == NULL )
    {
        std::cout << "unrecognised host" << std::endl;
        exit( 0 );
    }

    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);

    this->serverAddress.sin_port = htons(this->portNumber);
    this->serverAddress.sin_family = AF_INET;
   // serverAddress.sin_addr.s_addr = inet_addr( this->serverName );


  //  if( inet_aton( serverName, &serverAddress.sin_addr ) == 0)
  //  {
  //      std::cout << "Invalid server address" << std::endl;
  //      exit( 0 );
  //  }

    if( ( clientFd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0 )
    {
        std::cout << "Error creating socket" << std::endl;
        exit( 0 );
    }

    std::cout <<  "socket created" << std::endl;

    std::cout <<  "Trying to connecting..." << std::endl;

    socklen_t severAddressLength = sizeof( serverAddress );
    int cnnt = connect( clientFd, ( struct sockaddr *)&serverAddress, severAddressLength );

    if( cnnt != 0 )
    {
        std::cout.flush();
        std::cout << "Error creating connection " + cnnt << std::endl;
        close( clientFd );
        exit( 0 );
    }
    std::cout << "Got connection from a server " << server->h_name << std::endl;
    communicate( clientFd );

}
void Client::communicate( int clientFd )
{
    char * msg;

    std::cout << "waiting for connection" << std::endl;
    do
    {
        recv( clientFd, &msg, strlen( msg ), 0);
        std::cout << "server " + *msg << std::endl;

        if( std::cin.good() )
        {
            std::cin >> msg;
            send( clientFd, &msg, strlen( msg ), 0 );
        }
       recv( clientFd, &msg, strlen( msg ), 0);

        std::cout << "server >> " + *msg << std::endl;

    }while( clientFd > 0 );

    std::cout << "End of connection" << std::endl;

    close( clientFd );
}

int main( int argc, char* argv[] )
{
    if( argc < 3 )
    {
        std::cout << "Usage << Server Address >> << Port >> " << std::endl;
        exit( 0 );
    }

    Client client( atoi(argv[2]), argv[1] );

    client.init();
}
