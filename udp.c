#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX 1024
void translate(char *str) {
char temp[MAX], result[MAX] = "", *token;
strcpy(temp, str);
token = strtok(temp, " ,.!?\n");
while(token != NULL) {
char word[50];
strcpy(word, token);
for(int i = 0; word[i]; i++) word[i] = tolower(word[i]);
if(strcmp(word, "tbh") == 0) strcat(result, "to be honest");
else if(strcmp(word, "idc") == 0) strcat(result, "I don't care");
else if(strcmp(word, "ig") == 0) strcat(result, "I guess");
else if(strcmp(word, "tbf") == 0) strcat(result, "to be fair");
else if(strcmp(word, "atm") == 0) strcat(result, "at the moment");
else if(strcmp(word, "irl") == 0) strcat(result, "in real life");
else if(strcmp(word, "lol") == 0) strcat(result, "laughing out loud");
else if(strcmp(word, "asap") == 0) strcat(result, "as soon as possible");
else if(strcmp(word, "omg") == 0) strcat(result, "oh my God");
else if(strcmp(word, "ttyl") == 0) strcat(result, "talk to you later");
else if(strcmp(word, "idk") == 0) strcat(result, "I don't know");
else if(strcmp(word, "nvm") == 0) strcat(result, "never mind");
else strcat(result, token);
strcat(result, " ");
token = strtok(NULL, " ,.!?\n");
}
strcpy(str, result);
}
int main() {
int sockfd;
char buffer[MAX];
struct sockaddr_in server_addr, client_addr;
socklen_t len = sizeof(client_addr);
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);
bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
printf("UDP Server Running...\n");
recvfrom(sockfd, buffer, MAX, 0, (struct sockaddr *)&client_addr, &len);
printf("Received: %s\n", buffer);
translate(buffer);
sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr *)&client_addr,
len);
printf("Translated message sent.\n");
    close(sockfd);
return 0;
}


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX 1024
int main() {
int sockfd;
char message[MAX], buffer[MAX];
struct sockaddr_in server_addr;
socklen_t len = sizeof(server_addr);
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = INADDR_ANY;
printf("Enter sentence:\n");
fgets(message, MAX, stdin);
sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr *)&server_addr,
len);
recvfrom(sockfd, buffer, MAX, 0, (struct sockaddr *)&server_addr, &len);
printf("\nTranslated Sentence:\n%s\n", buffer);
close(sockfd);
return 0;
}