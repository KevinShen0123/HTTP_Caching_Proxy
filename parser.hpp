#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<iostream>
#include<sstream>
#include <vector>
#include "split.hpp"
#include <map>
#ifndef PARSER_H
#define PARSER_H
using namespace std;
class Parser{
     private:
         string requestMessage="";
         string requestHeader="";
         string requestType="";
         string resourcePath="";
         string HTTPVersion="HTTP/1.1";
         map<std::string, std::string> myMap;
     public:
         Parser(string requestMessage){
             this->requestMessage=requestMessage;
             this->Parse();
         }
         string getRequestMessage(){
            return this->requestMessage;
         }
         string getRequestHeader(){
            return this->requestHeader;
         }
         string getRequestType(){
            return this->requestType;
         }
         string getResourcePath(){
            return this->resourcePath;
         }
         string getHTTPVersion(){
            return this->HTTPVersion;
         }
         map<std::string, std::string> getMap(){
            return this->myMap;
          }
         void Parse(){
            string myrequest=this->requestMessage;
            if(myrequest.length()>0){
                  string line;
                  istringstream mystream(myrequest);
                  int cnt=0;
                  while(getline(mystream,line)){
                       if(cnt==0){
                          requestHeader=line;
                          std::vector<string> params=split(line," ");
                          this->requestType=params[0];
                          this->resourcePath=params[1];
                          if(params.size()>2){
                            this->HTTPVersion=params[2];
                          }
                       }else{
                            std::vector<string> params=split(line,":");
                            if(params.size()>1){
                              this->myMap[params[0]]=params[1];
                            }else{
                              break;
                            }
                       }
                       cnt+=1;
                  }
            }
         }
};
#endif