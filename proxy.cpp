#include<iostream>
#include<fstream>
#include "network_utils.hpp"
#include "clientInfo.hpp"
#include<cstring>
#include<pthread.h>
#include<ctime>
#include "parser.hpp"
#include "split.hpp"
using namespace std;
 std::ofstream outputFile("./logs/proxy.log");
 Network_UTILS* net=new Network_UTILS();
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void handleGet(Parser* parser,int clientFd, string clientIP,int requestID){


}
void handleConnect(Parser* parser){

}
void handlePost(Parser* parser){

}
string now(){
    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the time to a tm structure
    std::tm* timeInfo = std::localtime(&currentTime);

    // Format the time as a string
    char timeStr[30]; // Buffer to hold the formatted time
    std::strftime(timeStr, sizeof(timeStr), "%a %b %e %T %Y", timeInfo);

    // Print the formatted time
    std::cout << "Formatted time: " << timeStr << std::endl;
    return string(timeStr);
}
void* handle_request(void* params){
    ClientInfo* info=(ClientInfo*)params;
    int clientfd=info->getSocketFd();
    string clientIP=info->getIp();
    int request_id=info->getRequestId();
    char buffer[65536];
    int recvLength=recv(clientfd,buffer,sizeof(buffer),0);
    if(recvLength<=0){
        cerr<<"receive error"<<endl;
        return NULL;
    }
    std::string requestMessage=std::string(buffer);
    if(requestMessage=="" || requestMessage=="\r"||requestMessage=="\n"){
        return NULL;
    }
    Parser* parser=new Parser(requestMessage);
    outputFile<<parser->getRequestHeader()<<"from"<<clientIP<<"@"<<now();
    if(parser->getRequestType()=="GET"){
        handleGet(parser,clientfd,clientIP,request_id);
    }else if(parser->getRequestType()=="POST"){
        handlePost(parser);
    }else if(parser->getRequestType()=="CONNECT"){
        handleConnect(parser);
    }
    return NULL;
}

int main(){
    Network_UTILS* networkutils=new Network_UTILS();
    int serversocket=networkutils->build_server("12345");
    int request_id=0;
    while(true){
         pthread_t thread;
         string clientip="";
         int clientsocket=networkutils->server_accept(serversocket,&clientip);
         request_id+=1;
         ClientInfo* clientInfo=new ClientInfo(clientsocket,clientip,request_id);
         pthread_mutex_lock(&lock);
         pthread_create(&thread,NULL,&handle_request,clientInfo);
         pthread_mutex_unlock(&lock);
    }
    return 0;
}