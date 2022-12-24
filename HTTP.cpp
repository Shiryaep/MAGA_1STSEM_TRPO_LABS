#ifndef __HTTP_CPP_CLASS__
#define __HTTP_CPP_CLASS__
#include "HTTP.hpp"
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
std::string & ltrim(std::string * str)
{
  if (*((*str).begin()) == ' '){
  (*str).erase((*str).begin());
  }
  if ((*((*str).end()-1) == '\n') or (*((*str).end()-1) == '\r')){
  (*str).erase((*str).end()-1);
    // (*str).pop_back();
  }
  return *str;
}
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
std::string HTTP::escaping(std::string str)
{
    // for()
    for (auto [key, val] : this->escape){
        str = ReplaceAll(str, key, val);
    }
    return str;
}
std::string HTTP::httpGet(std::string name){
    return this->getparams[name];
}
std::string HTTP::httpPost(std::string name){
    return this->postparams[name];
}
std::string HTTP::getCookie(std::string name){
    return this->cookie[name];
}
std::string HTTP::setCookie(std::string name, std::string value){
    this->outcookie[name] = value;
    return value;
}
void HTTP::init(){
    // redirecting cout stream to string stream
    std::streambuf *x = std::cout.rdbuf(this->OUT.rdbuf());
}
void HTTP::send(){
    // set headers
    fprintf(stdout, "Content-Type: text/html; charset=utf-8\n");
    // set cookie
    for (const auto& [key, value] : this->outcookie){
        fprintf(stdout, "Set-Cookie:  %s=%s; ", key.c_str(), value.c_str());
    }
    // fprintf(stdout, "\r\n\r\n");
    fprintf(stdout, "\n\n");
    // output recorded cout
    fprintf(stdout, "%s", OUT.str().c_str());
}
HTTP::HTTP(std::string query, std::string postdata){
    std::vector<std::string> out;
    std::stringstream getstrstm(query);
    std::stringstream poststrstm(postdata);
    auto key = std::string{};
    auto val = std::string{};

    while (std::getline(getstrstm, key, '=')) {
        std::getline(getstrstm, val, '&');
        key = escaping(key);
        val = escaping(val);
        this->getparams[key] = val;
    }
    while (std::getline(poststrstm, key, '=' )) {
        std::getline(poststrstm, val, '&');
        this->postparams[key] = val;
    }
return;
}
HTTP::HTTP(){
    FILE * fp = fopen("err.txt", "w");
    std::stringstream getstrstm(getenv("QUERY_STRING"));
    auto key = std::string{};
    auto val = std::string{};

    // parse GET params
    while (std::getline(getstrstm, key, '=' )) {
        std::getline(getstrstm, val, '&');
        this->getparams[key] = val;
    }
    // parse cookie
    if (getenv("HTTP_COOKIE") != nullptr){
        std::stringstream cookiestrstm(getenv("HTTP_COOKIE"));
        while (std::getline(cookiestrstm, key, '=')) {
            std::getline(cookiestrstm, val, ';');
            key = ltrim(&key);
            key = escaping(key);
            val = escaping(val);
            this->cookie[key] = val;
        }
    }
    if (getenv("CONTENT_TYPE") != nullptr){
        UploadedFile upf;
        std::string boundary;
        std::stringstream strstm(getenv("CONTENT_TYPE"));
        std::getline(strstm, val, ';');  // Get Content-Type
        // fprintf(fp,"%s\n",val.c_str());
        if (val == "multipart/form-data"){
            std::getline(strstm, val, '=');  // skip " boundary="
            std::getline(strstm, boundary);  // get boundary
            int flag = 100000;
            int tmpfd = -1;
            std::string name;
            std::string filename;
            while (flag)
            {
                std::string ContentType[2];
                std::getline(std::cin, val);
                if(std::cin.eof()){
                    fprintf(fp,"ERROR: end of cin!!\n");
                    return;
                }
                long long int fs = 0;
                // fprintf(fp,"%s\n",val.c_str());

                if (ltrim(&val) == ("--" + boundary)){
                    if (tmpfd != -1){
                        close(tmpfd);
                    }

                    std::getline(std::cin, val, '\"');  // SKIP Content-Disposition: form-data; name="
                    std::getline(std::cin, name, '\"');  // get name
                    // fprintf(fp,"n %s\n",name.c_str());
                    std::getline(std::cin, val, '\"');  // SKIP "; filename="
                    std::getline(std::cin, filename, '\"');  // get filename
                    // fprintf(fp,"fn %s\n",filename.c_str());
                    std::getline(std::cin, val, '\n');  // skip '"\n'
                    std::getline(std::cin, val, ' ');  // skip "Content-Type: "
                    std::getline(std::cin, ContentType[0], '/');  // get content type before '/'
                    // fprintf(fp,"CT %s\n",ContentType[0].c_str());
                    std::getline(std::cin, ContentType[1], '\n');  // get content type
                    filesData[name].type = ContentType[0];
                    std::getline(std::cin, val, '\n');  // skip empty line

                    filesData[name].filename = filename;
                    filesData[name].size = 0;
                    filesData[name].error = 0;
                    // Create temp file
                    char tmpfilename[] = "/tmp/HTTPtemp_XXXXXX";
                    tmpfd = mkstemp(tmpfilename);
                    if (tmpfd == -1){
                    // fprintf(fp,"%i\n",tmpfd);
                    }
                    // fprintf(fp,"%s\n",tmpfilename);
                    filesData[name].tmp_name = tmpfilename;
                    // unlink(filename);              // Delete the temporary file.
                }else{
                    if (ltrim(&val) == ("--" + boundary + "--")){  // Exit if end
                        // fprintf(fp,"e\n");
                        break;
                    }
                    if (tmpfd != -1){
                    write(tmpfd, (val+'\n').c_str(), val.size()+1);
                    filesData[name].size += val.size()+1;
                    if (filesData[name].size > INTCONFIG["MAX_FILESIZE"]){
                        filesData[name].error = -1;
                        break;
                    }
                    // fprintf(fp,"%s %li\n",val.c_str(),val.size());
                    }
                }
                flag--; //Stop if > 100000 lines
                if(!flag){
                    fprintf(fp,"max count!\n");
                }
            }
        }else{
            if (val == "application/x-www-form-urlencoded"){
                    // parse POST params
                std::string postdata;
                std::getline(std::cin, postdata, static_cast<char>(0));
                std::stringstream poststrstm(postdata);
                while (std::getline(poststrstm, key, '=' )) {
                    std::getline(poststrstm, val, '&');
                    this->postparams[key] = val;
                }
            }
        }
    }
    return;
}

int HTTP::move_uploaded_file(UploadedFile tmpFile, std::string path){
    // if(std::rename(tmpFile.tmp_name.c_str(), path.c_str()) < 0) {
    //     std::cout << strerror(errno) << '\n';
    //     return errno;
    // }
    // return system(("ls 1>/dev/null"));
    std::ifstream  src(tmpFile.tmp_name, std::ios::binary);
    std::ofstream  dst(path,   std::ios::binary);
    if (!src.is_open()){
        return -1;
    }
    if (!dst.is_open()){
        return -2;
    }
    dst << src.rdbuf();
    unlink(tmpFile.tmp_name.c_str());
    return 0;
}

int HTTP::httpSendFile(std::string name){
    std::ifstream ifile;
    ifile.open(name, std::ios::in);
    if (!ifile){
        return -1;
    }
    std::string str;
    while (std::getline(ifile, str, '\n')) {
        std::cout << str << std::endl;
    }
    return 0;
}

HTTP::~HTTP(){
    return;
}

std::string HTTP::rawURLDecode(std::string str)
{
  std::string res = "";
  for (int i = 0; i < str.length (); i++)
    {
      if (str[i] != '%')
	{
	  res.append(1, str[i]);
	}
      if (str[i] == '%')
	{
	    i++;  // skip '%'
        res.append(1, static_cast<char>(CCtoI(str[i], str[i + 1])));
        i++;  // skip one hex (other hex will be skiped by i++ in for)
        continue;
	}
    }
  return res;
}

unsigned int HTTP::CtoI(char ch){
    if (ch >= 'A'){
	      return static_cast<int>(ch - 'A' + 10);
	  }else{
	      return static_cast<int>(ch - '0');
	  }
}

unsigned int HTTP::CCtoI(char ch1, char ch2){
    return ((CtoI(ch1) << 4) + CtoI(ch2));
}


#endif
