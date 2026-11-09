#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main() {
int sockfd;
char buffer[BUFFER_SIZE];
struct sockaddr_in server_addr, client_addr;
socklen_t len;
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);
bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
printf("UDP Time Server Running...\n");
while(1) {
len = sizeof(client_addr);
recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr,
&len);
time_t current_time;
time(¤t_time);
strcpy(buffer, ctime(¤t_time));
sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr,
len);
}
close(sockfd);
return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <netinet/ip.h>
#define BUFFER_SIZE 65536
int main() {
int sock_raw;
unsigned char *buffer;
int packet_count = 0;
sock_raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
if(sock_raw < 0) {
perror("Socket Error");
return 1;
}
buffer = (unsigned char *)malloc(BUFFER_SIZE);
printf("Packet Capture Started...\n");
while(1) {
int data_size;
data_size = recvfrom(sock_raw, buffer, BUFFER_SIZE, 0, NULL, NULL);
if(data_size < 0) {
perror("Receive Error");
break;
}
struct iphdr *ip_header = (struct iphdr *)(buffer + 14);
struct sockaddr_in src, dst;
src.sin_addr.s_addr = ip_header->saddr;
dst.sin_addr.s_addr = ip_header->daddr;
printf("\nPacket No: %d\n", ++packet_count);
printf("Packet Size: %d bytes\n", data_size);
printf("Source IP: %s\n", inet_ntoa(src.sin_addr));
printf("Destination IP: %s\n", inet_ntoa(dst.sin_addr));
printf("-----------------------\n");
}
close(sock_raw);
free(buffer);
return 0;
}

