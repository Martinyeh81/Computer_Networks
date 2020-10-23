#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#define PORT 21661 //8140821161 (21500 + 161)

#define MAXDATASIZE 100 // max number of bytes we can get at once

using namespace std;
int TcpSockfd,UdpSockfd;
struct sockaddr_in my_addr, server_addr;
struct sockaddr_in UdpServer_addr, UdpClient_addr;



vector<string> read_hospital(const string filename) {
    ifstream infile(filename);

    if(!infile) { cerr << "Didn't find the file: " << filename << endl; }
    string line;
    vector<string> number;
    
    while (getline(infile, line)) {

        stringstream iss(line);
        vector<string> chars;
        string word;
        
        while (iss.good()) {
            getline(iss, word,':'); // delimited by :
            chars.push_back(word);
        }

        for (int i=0; i<chars.size();i++) {
            
            number.push_back(chars[i]);
        }
       
    }
    
    return number;
}

void Tcpclient(){
    char s[INET6_ADDRSTRLEN];
    struct hostent *info;
    
    
    TcpSockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TcpSockfd < 0) perror("ERROR opening socket");
    
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6161);
    
    if ((info = gethostbyname("localhost")) == NULL){
        perror("gethostbyname");
    }
    
    bcopy(info->h_addr_list[0], (caddr_t)&server_addr.sin_addr, info->h_length);
    

    if (connect(TcpSockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection Failed \n");

    }
    
    
    getsockname(TcpSockfd, (struct sockaddr *)&server_addr, (socklen_t *)sizeof(server_addr));
    inet_ntop(AF_INET, &server_addr.sin_addr, s, sizeof(s));
    printf("<Student2> has TCP port %d and IP address %s\n", ntohs(server_addr.sin_port), s);

}

void send(){
    int numbytes;
    char buf[MAXDATASIZE];
    string totalinfo = "";
    vector<string> data = read_hospital("/Users/martinyeh/Desktop/EE450/project/student2.txt");
    for (int i = 0; i<data.size();i++){
        totalinfo = totalinfo + data[i]+"+";
    }
    
    if (data.size()<8){
        for (int i = (int) data.size(); i<8;i++){
            totalinfo = totalinfo + "0+";
        }
    }
    
    totalinfo = totalinfo + "student2";
    strcpy(buf, totalinfo.c_str());
    if ((numbytes = send(TcpSockfd, buf, MAXDATASIZE-1, 0)) > 0) {
        printf("Completed sending application for <Student2>.\n");
    }
    if ((numbytes = recv(TcpSockfd, buf, MAXDATASIZE-1, 0)) > 0) {
        printf("<Student2> has received the reply from the health center\n");

    }
    sleep(1);
    close(TcpSockfd);
}

void Udpserver(){

    struct hostent *info;
    
    UdpSockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (UdpSockfd < 0) perror("socket creation failed");

    memset(&UdpServer_addr, 0, sizeof(UdpServer_addr));
    memset(&UdpClient_addr, 0, sizeof(UdpClient_addr));
    
    UdpServer_addr.sin_family = AF_INET;
    UdpServer_addr.sin_addr.s_addr = INADDR_ANY;
    UdpServer_addr.sin_port = htons(PORT);

    if (::bind(UdpSockfd, (const struct sockaddr *)&UdpServer_addr, sizeof(UdpServer_addr)) < 0) perror("bind failed");
    
    if ((info = gethostbyname("127.0.0.1")) == NULL) perror("gethostbyname");
    printf("<Student2> has UDP port %d and IP address %s for Phase 2\n", ntohs(UdpServer_addr.sin_port), inet_ntoa(*(struct in_addr*)info->h_addr));
    
    
}

           
void receive_result() {
    
    char buf[MAXDATASIZE];
    
    socklen_t client_len = sizeof(UdpClient_addr);
    
    if ((recvfrom(UdpSockfd, buf, MAXDATASIZE-1, 0, (struct sockaddr *) &UdpClient_addr, &client_len)) == -1) {

      perror("recvfrom");
      exit(1);
    }
    string result = string(buf);
    int position = (int) result.find("#");
    int nextpostition = (int) result.find("#",position+1,1);
    string finalresult = result.substr(nextpostition+1);
    printf("<Student2> has received the application result is %s\n", finalresult.c_str());
    

    sleep(3);
    close(UdpSockfd);
    
}




int main(int argc, char *argv[])
{
    Tcpclient();
    send();
    Udpserver();
    receive_result();
    
    
    
}

