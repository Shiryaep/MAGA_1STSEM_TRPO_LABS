#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include "HTTP.hpp"

using namespace std;


int main()
{
    HTTP http;
    http.init();

    cout << "<p>200 OK</p>" << endl;
    if (http.httpGet("verbose") == "true")
    {
        cout << "<p>Привет, User!</p>" << endl;
        // cout << "<p>Локальный IP-адрес: " << getenv("REMOTE_ADDR") 	   << ".</p>" << endl;
        // cout << "<p>Ваш IP-адрес: " << getenv("X-Forwarded-For") 	   << ".</p>" << endl;
        cout << "<p>Ваш браузер: "
	       << getenv("HTTP_USER_AGENT") << ".</p>" << endl;
        cout << "<p>Запрос " << getenv("QUERY_STRING") << ".</p>" << endl;
        cout << "<p>Метод " << getenv("REQUEST_METHOD") << ".</p>" << endl;
        cout << "http Get parameters: " << "<br>" <<endl;
        for (const auto& [key, value] : http.getparams)
            cout << key << ": " << value << "<br>";
        cout <<"<br>\nCookies: " << "<br>" << endl;
        for (const auto& [key, value] : http.cookie)
            cout << key << ": " << value << "<br>";
    }
    cout << "<br>\n";
    if (string(getenv("REQUEST_METHOD")) == string("GET"))
    {
        if (http.httpGet("getcookie") != "")
        {
            cout << "Requested Cookie: " << "<br>" << endl;
            cout << http.httpGet("getcookie") << ": "
            << http.getCookie(http.httpGet("getcookie")) << "<br>";
        }
        if (http.httpGet("setcookie") != "")
        {
            cout <<"<br>\nRequested Set Cookie: " << "<br>" <<endl;
            cout << http.httpGet("setcookie") <<": "
            << http.setCookie(http.httpGet("setcookie"), http.httpGet("value")) << "<br>";
        }
    }
    if (string(getenv("REQUEST_METHOD")) == string("POST"))
    {
        char data[2000];
        cin.getline(data, 2000);
        cout <<"DATA: \n"<< data <<endl;
        for (const auto& [key, value] : http.postparams)
        {
            cout << key << ": " << value << "<br>";
        }
    }
    if (http.httpGet("verbose") == "true")
    {
        cout << "<br>\nEOF" << endl;
    }

    http.send();
    return 0;
}
