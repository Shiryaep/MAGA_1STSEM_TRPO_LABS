#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include "HTTP_session.hpp"
#include "db.hpp"
#include "db.cpp"
#include <cpp_redis/cpp_redis>
using namespace std;
int main()
{
    HTTP_session http;
    http.init();
    
    FILE * fp = fopen("err.txt", "w");
    cout<<" session "<<endl;
    try{
    cpp_redis::client client;
    // client.connect();
    }
	catch (cpp_redis::redis_error e)
	{
        fprintf(fp,"before::%s\n","s");
		std::cout << e.what() << endl;
	}

    // client.set("hello", "45");
    cout<<" redis "<<endl;
    // fprintf(fp,"aft\n");
    // std::string 
    // auto rep = client.get("hello");
    // OUT << rep.get() ;
    //! also support std::future
    //! std::future<cpp_redis::reply> get_reply = client.get("hello");

    // client.sync_commit();
    //! or client.commit(); for asynchronous call

    http.send();
}
