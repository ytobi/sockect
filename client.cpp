
#include "client.h"
#include <arpa/inet.h>
#include <thread>


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
	bzero( &serverAddress.sin_addr.s_addr, sizeof( serverAddress ) );
	
    server = gethostbyname( this->serverName );

    if( server == NULL )
    {
        std::cout << "unrecognised host" << std::endl;
        exit( 0 );
    }

    this->serverAddress.sin_port = htons(this->portNumber);
    this->serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr( this->serverName );


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
    
    communicate( clientFd );

}
void Client::communicate( int clientFd )
{
    char msg[10];
    bzero( msg, sizeof( msg ) );

    do
    {
       // bzero( msg, sizeof( msg ) );
        if( read( clientFd, msg, strlen( msg ) ) > 0 )
            std::cout << "server>> "  << msg << std::endl;
        if( std::cin.peek() > 0 )
        {
            std::cin >> msg;
            write( clientFd, msg, strlen( msg ) );
        }

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
