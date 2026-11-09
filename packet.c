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