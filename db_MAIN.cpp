#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
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
        http.httpSendFile("db.html");
    }
    std::string eraseparam = string(http.httpPost("erase"));
    int res = db.erase(http.rawURLDecode(eraseparam));
    if (eraseparam != ""){
        if (res == 0){
            cout << "{\"status\": [201, \"OK\"]}";
        }else{
            cout << "{\"status\": [500, \"Server Error\"]}";
        }
    }

    if (getparam != ""){
        http.setCookie("get", getparam);
        std::string res = db.read_one(getparam);
        if (res != ""){
            std::string outStr_New_01 = "<table><tr><th>Key</th><th>Value</th><th>Delete</th></tr>";
            std::string outStr_New_02 = "<tr><td>" + http.escaping(getparam) + "</td><td>" + http.escaping(res) + "</td>";
            //cout <<"{ \"" << http.escaping(getparam) << "\": \"" <<http.escaping(res) << "\"}";
            cout << outStr_New_01;
            cout << outStr_New_02;
            cout << "<td><form enctype=\"application/x-www-form-urlencoded\" method=\"post\"><input id=\"keyinpgetall\" name=\"erase\" value=\"";
            cout << getparam;
            cout << "\" hidden=\"hidden\"><input class=\"button-delete\" type=\"submit\" value=\"Delete this line\"></form></td></tr></table>";
        }
    }
    if (getallparam != ""){
        std::map<string, string> *res = db.read_all();
        //cout << "{";
        int i = 0;
        std::string outStr_New_01 = "<table><tr><th>Key</th><th>Value</th><th>Delete</th></tr>";
        cout << outStr_New_01;
        for (auto [key, val] : *res){
            /*if (i > 0){
                cout << ", ";
            }*/
            std::string outStr_New_02 = "<tr><td>" + http.escaping(key) + "</td><td>" + http.escaping(val) + "</td>";
            cout << outStr_New_02;
            //cout << "\"" << http.escaping(key) << "\": \"" << http.escaping(val) << "\"";
            i++;
            cout << "<td><form enctype=\"application/x-www-form-urlencoded\" method=\"post\"><input id=\"keyinpgetall\" name=\"erase\" value=\"";
            cout << key;
            cout << "\" hidden=\"hidden\"><input class=\"button-delete\"  type=\"submit\" value=\"Delete this line\"></form></td></tr>";
        }
        //cout << "}";
        cout << "</table>";
    }
    std::string setparam = string(http.httpPost("set"));
    if (setparam != ""){
        http.setCookie("get", http.rawURLDecode(setparam));
        int res = db.write(http.rawURLDecode(setparam), http.rawURLDecode(string(http.httpPost("value"))));
        if (res == 0){
            cout << "{\"status\": [201, \"OK\"]}";
        }else{
            cout << "{\"status\": [500, \"Server Error\"]}";
        }
    }
    
    // std::string eraseparam = string(http.httpPost("erase"));
    // if (eraseparam != ""){
    //     int res = db.erase(http.rawURLDecode(eraseparam));
    //     if (res == 0){
    //         cout << "{\"status\": [201, \"OK\"]}";
    //     }else{
    //         cout << "{\"status\": [500, \"Server Error\"]}";
    //     }
    // }
    

    http.send();
}