#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include "HTTP.hpp"
#include "db_header.hpp"
#include "db_functions.cpp"
using namespace std;
int main()
{
    HTTP http;
    http.init();
    FILEDB<std::string, std::string> db;
    std::string getparam = http.rawURLDecode(string(http.httpGet("get")));
    std::string getallparam = string(http.httpGet("getall"));
    if(http.httpGet("gui")!="false"){
        http.httpSendFile("uploadFile.html");
    }
    for(auto i = http.filesData.begin();i != http.filesData.end();i++){
        auto key = (*i).first;
        auto val = (*i).second;
        // cout << key <<endl;
        if(val.error == -1){
            cout <<" filename:"<<val.filename<<" size:" << (val.size)<< " is bigger then MAX FILE SIZE: "<<http.INTCONFIG["MAX_FILESIZE"] << " bytes</br>";
            unlink(val.tmp_name.c_str());
            continue;
        }
        int res = http.move_uploaded_file(val,"./usrfiles/"+val.filename);
        // int res = http.move_uploaded_file(val,"/tmp/"+val.filename);
        if(res != 0){
            std::cout << strerror(errno)<<" ";
            cout <<res<<" filename:"<<val.filename<<" size:" << (val.size) << "</br>";
            unlink(val.tmp_name.c_str());
        }else{
            cout <<res<<" filename:"<<val.filename<<" size:" << (val.size) <<" OK" << "</br>";
        }
    }
    http.send();
}
