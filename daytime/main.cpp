#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
 int sockfd;
 char buffer[4096];
 struct sockaddr_in server_addr;
 if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
     std::cerr << "Error creating socket" << std::endl;
     return 1;
 }
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(13); // порт службы daytime
 server_addr.sin_addr.s_addr = inet_addr("172.16.40.1");
 if (sendto(sockfd, " ", 1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
     std::cerr << "Error sending data" << std::endl;
     return 1;
 }
 int n;
 socklen_t len;
 if ((n = recvfrom(sockfd, (char *)buffer, 4096, 0, (struct sockaddr *)&server_addr, &len)) < 0) {
     std::cerr << "Error receiving data" << std::endl;
     return 1;
 }
 buffer[n] = '\0';
 std::cout << "Ответ от сервера: " << buffer << std::endl;
 close(sockfd);
 return 0;
}