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

#define PORT 21261 //8140821161 (21100 + 161)

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
            getline(iss, word,'#'); // delimited by #
            chars.push_back(word);
        }

        for (int i=0; i<chars.size();i++) {
            
            number.push_back(chars[i]); // string convert into array of integer
        }
       
    }
    return number;
}

void client(){
    char s[INET6_ADDRSTRLEN];
    struct hostent *info;
    
    
    TcpSockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TcpSockfd < 0) perror("server: socket");
    
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
    printf("<HospitalA> has TCP por %d and IP address %s for Phase 1\n", ntohs(server_addr.sin_port), s);
    printf("<HospitalA> is now connected to the admission office\n");
    
    
    
    
}

void send(){
    int numbytes;
    char buf[MAXDATASIZE];
    string totalinfo = "";
    vector<string> data = read_hospital("/Users/martinyeh/Desktop/EE450/project/HospitalA.txt");
    for (int i = 0; i<data.size();i++){
        totalinfo = totalinfo + data[i]+"+";
    }
    strcpy(buf, totalinfo.c_str());
    if ((numbytes = send(TcpSockfd, buf, MAXDATASIZE-1, 0)) > 0) {
        printf("<Hospital%s> has sent <department> to the admission office\n", data[0].substr(0,1).c_str());
        printf("Updating the admission office is done for <Hospital%s>\n",data[0].substr(0,1).c_str());
    }
    sleep(1);
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
    printf("<HospitalA> has UDP port %d and IP address %s for Phase 2\n", ntohs(UdpServer_addr.sin_port), inet_ntoa(*(struct in_addr*)info->h_addr));
    
    
}

           
void receive_result(int numb_stud) {
 
    for (int i=0; i<numb_stud;i++){
        char buf[MAXDATASIZE];
        socklen_t client_len = sizeof(UdpClient_addr);
        if ((recvfrom(UdpSockfd, buf, MAXDATASIZE-1, 0, (struct sockaddr *) &UdpClient_addr, &client_len)) == -1) {

          perror("recvfrom");
          exit(1);
        }
        string result = string(buf);
        string finalresult = result.substr(7,1);
        printf("<Student%s> has been admitted to <HospitalA>\n", finalresult.c_str());
        

        sleep(1);
       
    }
    
     close(UdpSockfd);
    
}

           

int main(int argc, char *argv[])
{
    client();
    send();
    printf("End of Phase 1 for <HospitalA>\n");
    Udpserver();
    receive_result(3);
    
    
}
