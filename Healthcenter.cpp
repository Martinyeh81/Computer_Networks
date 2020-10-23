#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>


#define PORT 6161 //8140821161 (6000+161)
#define BACKLOG 10
#define MAXDATASIZE 100 // max number of bytes we can get at once

using namespace std;
int TcpSockfd, UdpSockfd;
struct sockaddr_in TcpServer_addr, TcpClient_addr;
struct sockaddr_in UdpServer_addr, UdpClient_addr;

string test;


void store_data (string data) {
    
    ofstream write;
    write.open("/Users/martinyeh/Desktop/EE450/project/tempfile.txt", ios::out | ios::app);
    write << data;
    write << endl;
    write.close();

}

vector<string> readfile(const string filename) {
    ifstream infile(filename);

    if(!infile) { cerr << "Didn't find the file: " << filename << endl; }
    string line;
    vector<string> number;
    
    while (getline(infile, line)) {

        stringstream iss(line);
        vector<string> chars;
        string word;
        
        while (iss.good()) {
            getline(iss, word,'+'); // delimited by +
            chars.push_back(word);
        }

        for (int i=0; i<chars.size();i++) {
            
            number.push_back(chars[i]);
        }
       
    }
    
    return number;
}


vector<string> result(const string filename){
    
    map<string, string> department;

    vector<string> res = readfile(filename);

    for(int i=0;i<6;i+=2){
        department.insert(pair<string, string>(res[i], res[i+1]));
    }
    for(int i=7;i<13;i+=2){
        department.insert(pair<string, string>(res[i], res[i+1]));
    }
    for(int i=14;i<20;i+=2){
        department.insert(pair<string, string>(res[i], res[i+1]));
    }
    
    map<string, string>::iterator itr;
    vector<string> send_res(5,"0");
    string result1 = "";
    string result2 = "";
    string result3 = "";
    string result4 = "";
    string result5 = "";
    string reject = "reject";
    
    
    
    for(int i =24;i<29;i+=2) {
        for (itr = department.begin(); itr != department.end(); ++itr){
            if(res[i]==itr->first){
                string value = itr->second;
                int divide = (int) value.find(",");
                string severity_begin = value.substr(0,divide);
                string severity_final = value.substr(divide+1);
                if(res[22] >= severity_begin && res[22]<= severity_final){
                    result1 = res[29]+"#"+res[22]+"#"+"Accept#" + res[i] + "#hospital"+res[i].substr(0,1);
                    send_res[0] = result1;
                    break;
                }
                else{
                    result1 = "reject";
                    send_res[0] = res[29]+"#"+res[22]+"#"+result1;
                }
            }
        }
        if (send_res[0] != res[29]+"#"+res[22]+"#"+reject){
            break;
        }
    }
    
    
    for(int i =33;i<38;i+=2) {
       for (itr = department.begin(); itr != department.end(); ++itr) {
            if(res[i]==itr->first){
                string value = itr->second;
                int divide = (int) value.find(",");
                string severity_begin = value.substr(0,divide);
                string severity_final = value.substr(divide+1);
                if(res[31] >= severity_begin && res[31]<= severity_final){
                    result2 = res[38]+"#"+res[31]+"#"+"Accept#" + res[i] + "#hospital"+res[i].substr(0,1);
                    send_res[1] = result2;
                    break;
                }
                else{
                    result2 = "reject";
                    send_res[1] = res[38]+"#"+res[31]+"#"+result2;
                }
            }
        }
        if (send_res[1] != res[38]+"#"+res[31]+"#"+reject){
            break;
        }
    }
    for(int i =42;i<47;i+=2) {
        for (itr = department.begin(); itr != department.end(); ++itr){
            if(res[i]==itr->first){
                string value = itr->second;
                int divide = (int) value.find(",");
                string severity_begin = value.substr(0,divide);
                string severity_final = value.substr(divide+1);
                if(res[40] >= severity_begin && res[40]<= severity_final){
                    result3 = res[47]+"#"+res[40]+"#"+"Accept#" + res[i] + "#hospital"+res[i].substr(0,1);
                    send_res[2] = result3;
                    break;
                }
                else{
                    result3 = "reject";
                    send_res[2] = res[47]+"#"+res[40]+"#"+result3;
                }
            }
        }
        if (send_res[2] != res[47]+"#"+res[40]+"#"+reject){
            break;
        }
    }
    for(int i =51;i<56;i+=2) {
        for (itr = department.begin(); itr != department.end(); ++itr){
            if(res[i]==itr->first){
                string value = itr->second;
                int divide = (int) value.find(",");
                string severity_begin = value.substr(0,divide);
                string severity_final = value.substr(divide+1);
                if(res[49] >= severity_begin && res[49]<= severity_final){
                    result4 = res[56]+"#"+res[49]+"#"+"Accept#" + res[i] + "#hospital"+res[i].substr(0,1);
                    send_res[3] = result4;
                    break;
                }
                else{
                    result4 = "reject";
                    send_res[3] = res[56]+"#"+res[49]+"#"+result4;
                }
            }
        }
        if (send_res[3] != res[56]+"#"+res[49]+"#"+reject){
            break;
        }
    }
    for(int i =60;i<65;i+=2) {
        for (itr = department.begin(); itr != department.end(); ++itr){
            if(res[i]==itr->first){
                string value = itr->second;
                int divide = (int) value.find(",");
                string severity_begin = value.substr(0,divide);
                string severity_final = value.substr(divide+1);
                if(res[58] >= severity_begin && res[58]<= severity_final){
                    result5 = res[65]+"#"+res[58]+"#"+"Accept#" + res[i] + "#hospital"+res[i].substr(0,1);
                    send_res[4] = result5;
                    break;
                }
                else{
                    result5 = "reject";
                    send_res[4] = res[65]+"#"+res[58]+"#"+result5;
                }
            }
        }
        if (send_res[4] != res[65]+"#"+res[58]+"#"+reject){
            break;
        }
    }
    return send_res;
}

void clear_data(string filename) {
    ofstream clean;
    clean.open(filename.c_str(), ofstream::out | ofstream::trunc);
    clean.close();
}



void sigchld_handler(int s)
{
    (void)s; // quiet unused variable warning

    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

void TCP_server (int port){
    struct hostent *info;
    int yes=1;
    struct sigaction sa;
    
    TcpSockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TcpSockfd < 0) {
        perror("server: socket");
    }

    memset((char *) &TcpServer_addr, 0, sizeof(TcpServer_addr));
    TcpServer_addr.sin_family = AF_INET;
    TcpServer_addr.sin_addr.s_addr = INADDR_ANY;
    TcpServer_addr.sin_port = htons(PORT);

    if ((info = gethostbyname("127.0.0.1")) == NULL){
        perror("gethostbyname");
    }

    if (::bind(TcpSockfd, (struct sockaddr *) &TcpServer_addr, sizeof(TcpServer_addr)) < 0){
        perror("server: bind");
    }
    
    if (setsockopt(TcpSockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    
    printf("The health center has TCP port %d and IP address %s\n", PORT, inet_ntoa(*(struct in_addr*)info->h_addr));
    
    if (listen(TcpSockfd, 5) < 0){
        perror("Didn't listen");
    }
    
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}


void receive_hospital(int numb_client){
    int new_fd;
    char buf[MAXDATASIZE];
    int numbytes;
    pid_t childpid;
    for(int i=0; i<numb_client;i++){
        socklen_t client_len = sizeof(TcpClient_addr);
        new_fd = accept(TcpSockfd, (struct sockaddr *) &TcpClient_addr, &client_len);
        if (new_fd < 0) perror("Didn't accept");

        if((childpid=fork())==0){
            close(TcpSockfd);
            while(1){
                numbytes = read(new_fd, buf, MAXDATASIZE-1);
                if (numbytes > 0){
                    string data = string(buf);
                    test = string(buf);
                    string hos_numb = data.substr(0,1);
                    store_data(data);
//                    hos_data.find("A2")->second.c_str()
                    printf("Received the program list from <Hospital %s>\n", hos_numb.c_str());
                    exit(0);

                }
            }
        }
        sleep(3);
        close(new_fd);
    }
    
}



void receive_student(int numb_stud){
    int new_fd;
    char buf[MAXDATASIZE];
    int numbytes;
    pid_t childpid;
    memset(buf, 0, MAXDATASIZE);
    struct hostent *info;
    
    if ((info = gethostbyname("localhost")) == NULL){
        perror("gethostbyname");
    }
    printf("The health center has TCP port %d and IP address %s\n", ntohs(TcpServer_addr.sin_port), inet_ntoa(*(struct in_addr*)info->h_addr));
    
    
    for(int i=0; i<numb_stud;i++){
        socklen_t client_len = sizeof(TcpClient_addr);
        new_fd = accept(TcpSockfd, (struct sockaddr *) &TcpClient_addr, &client_len);
        if (new_fd < 0) perror("Didn't accept");

        if((childpid=fork())==0){
            close(TcpSockfd);
            while(1){
                numbytes = read(new_fd, buf, MAXDATASIZE-1);
                if (numbytes > 0){
                    string data = string(buf);
                    store_data(data);
                    printf("health center receive the application from <Student%d>\n", i+1);
                }
                string accept = "OK";
                strcpy(buf, accept.c_str());
                if ((numbytes = send(new_fd, buf, MAXDATASIZE-1, 0)) > 0) {
                    exit(0);
                }
            }
        }
        sleep(3);
        close(new_fd);
    }
    
}


void UdpClient(int port){
    struct hostent *info;
    char s[INET6_ADDRSTRLEN];
    
    if ( (UdpSockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&UdpServer_addr, 0, sizeof(UdpServer_addr));
      
    // Filling server information
    UdpServer_addr.sin_family = AF_INET;
    UdpServer_addr.sin_port = htons(port);
    UdpServer_addr.sin_addr.s_addr = INADDR_ANY;
    
    if ((info = gethostbyname("localhost")) == NULL){
        perror("gethostbyname");
    }
    
    bcopy(info->h_addr_list[0], (caddr_t)&UdpServer_addr.sin_addr, info->h_length);
    
    getsockname(UdpSockfd, (struct sockaddr *)&UdpServer_addr, (socklen_t *)sizeof(UdpServer_addr));
    inet_ntop(AF_INET, &UdpServer_addr.sin_addr, s, sizeof(s));
    printf("The health center has UDP port %d and IP address %s for Phase 2\n", ntohs(UdpServer_addr.sin_port), s);
    
    

    
}

void send_stud_result(string result){
    char buf[MAXDATASIZE];
    
    strcpy(buf, result.c_str());
    
    sendto(UdpSockfd, buf, MAXDATASIZE, 0, (const struct sockaddr *) &UdpServer_addr, sizeof(UdpServer_addr));
    
    
}

void UdpClient_hos(int port){
    struct hostent *info;
    char s[INET6_ADDRSTRLEN];
    
    if ( (UdpSockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&UdpServer_addr, 0, sizeof(UdpServer_addr));
      
    // Filling server information
    UdpServer_addr.sin_family = AF_INET;
    UdpServer_addr.sin_port = htons(port);
    UdpServer_addr.sin_addr.s_addr = INADDR_ANY;
    
    if ((info = gethostbyname("localhost")) == NULL){
        perror("gethostbyname");
    }
    
    bcopy(info->h_addr_list[0], (caddr_t)&UdpServer_addr.sin_addr, info->h_length);
    
    getsockname(UdpSockfd, (struct sockaddr *)&UdpServer_addr, (socklen_t *)sizeof(UdpServer_addr));
    inet_ntop(AF_INET, &UdpServer_addr.sin_addr, s, sizeof(s));

    
}

void send_hos_result(string result){
    char buf[MAXDATASIZE];
    
    strcpy(buf, result.c_str());
    
    sendto(UdpSockfd, buf, MAXDATASIZE, 0, (const struct sockaddr *) &UdpServer_addr, sizeof(UdpServer_addr));
    sleep(3);
    
    
}



int main(int argc, char *argv[])
{

    
    TCP_server(PORT);
    receive_hospital(3);
    printf("End of Phase 1 for the health center\n");
    receive_student(5);
    vector<string> res = result("/Users/martinyeh/Desktop/EE450/project/tempfile.txt");
    sleep(3);
    for (int i=0; i<5 ; i++){
        if(res[i].substr(0,8)=="student1"){
            UdpClient(21561);
            send_stud_result(res[i]);
            printf("The health center has send the application result to <Student1>\n");
            sleep(3);
        }
        else if(res[i].substr(0,8)=="student2"){
            UdpClient(21661);
            send_stud_result(res[i]);
            printf("The health center has send the application result to <Student2>\n");
            sleep(3);
        }
        else if(res[i].substr(0,8)=="student3"){
            UdpClient(21761);
            send_stud_result(res[i]);
            printf("The health center has send the application result to <Student3>\n");
            sleep(3);
        }
        else if(res[i].substr(0,8)=="student4"){
            UdpClient(21861);
            send_stud_result(res[i]);
            printf("The health center has send the application result to <Student4>\n");
            sleep(3);
        }
        else if(res[i].substr(0,8)=="student5"){
            UdpClient(21961);
            send_stud_result(res[i]);
            printf("The health center has send the application result to <Student5>\n");
            sleep(3);
        }
    }
    sleep(3);
    for (int i=0; i<5;i++){
        string last;
        last = res[i].back();
        if(last=="A"){
            UdpClient_hos(21261);
            send_hos_result(res[i]);
            printf("The health center has send one admitted student to <HospitalA>\n");
            
        }
        else if (last=="B"){
            UdpClient_hos(21361);
            send_hos_result(res[i]);
            printf("The health center has send one admitted student to <HospitalB>\n");

        }
        else if (last=="C"){
            UdpClient_hos(21461);
            send_hos_result(res[i]);
            printf("The health center has send one admitted student to <HospitalC>\n");

        }
    }

    clear_data("/Users/martinyeh/Desktop/EE450/project/tempfile.txt");
    

    
    
}

