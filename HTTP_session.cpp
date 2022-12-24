#ifndef __HTTP_CPP_SESSION_CLASS__
#define __HTTP_CPP_SESSION_CLASS__
#include "HTTP_session.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdio>
#include <cerrno>
#include <cstdlib>


/*
Removing a leading whitespace
*/
HTTP_session::HTTP_session() : HTTP(){
    std::string sessionID = this->getCookie("session");
    Session session;
    if(sessionID == ""){
        sessionID = session.generate_sessionID();
        this->setCookie("session",sessionID);
    }else{
        session.set_sessionID(sessionID);
    }
    if(this->httpGet("logout") == "true"){
        this->setCookie("session","");
    }

}
HTTP_session::~HTTP_session(){}


Session::Session()
{
}

Session::~Session()
{
}
void Session::set_sessionID(std::string _sessionID){
    this->sessionID = _sessionID;
}
std::string Session::generate_sessionID(){
    this->sessionID = "session123";
    return sessionID;
}

#endif
