// ClassB.h
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<iostream>
#ifndef CLIENTINFO_H
#define CLIENTINFO_H
using namespace std;
class ClientInfo{
     private:
         int socket_fd;
         string ip;
         int request_id;
     public:
          ClientInfo(int socket_fd, string ip,int request_id){
                this->socket_fd=socket_fd;
                this->ip=ip;
                this->request_id=request_id;
          }
          int getSocketFd(){
            return socket_fd;
          }
          string getIp(){
            return ip;
          }
         
};
#endif