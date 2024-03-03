#include<iostream>
#include "network_utils.hpp"
#include "clientInfo.hpp"
#include<cstring>
#include<pthread.h>
using namespace std;
string logfile="./logs/poxy.log";
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void* handle_request(void* params){
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