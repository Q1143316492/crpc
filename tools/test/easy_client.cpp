#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename( argv[0] ));
        // basename :
        // Return the file name within directory of FILENAME.  We don't
        //  declare the function if the `basename' macro is available (defined
        //  in <libgen.h>) which makes the XPG version of this function
        //  available.
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi( argv[2] );

    printf("ip = %s port = %d\n", ip, port);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof( server_address ));
    server_address.sin_family = AF_INET;    //#define PF_INET 2 //IP protocol family. // PF_INET equal AF_INET

    inet_pton( AF_INET, ip, &server_address.sin_addr );
    server_address.sin_port = htons( port );

    int sockfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( sockfd >= 0 );

    if( connect( sockfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) < 0 )
    {
        printf("connection failed\n");
    }
    else
    {
        const char *oob_data = "abc";
        const char *normal_data = "123";
        send(sockfd, normal_data, strlen(normal_data), 0);
        send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
        send(sockfd, normal_data, strlen(normal_data), 0);
    }
    close(sockfd);
    return 0;
}