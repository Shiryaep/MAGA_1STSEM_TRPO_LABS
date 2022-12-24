#ifndef __DB__CPP__CLASS__
#define __DB__CPP__CLASS__
#include "db.hpp"
#include <errno.h>
#include <fstream>
template<typename KeyType, typename ValType>
ValType FILEDB<KeyType, ValType>::read_one(KeyType key) {
    std::ifstream ifile(this->dbfilename);
    std::string ikey, ival, nstr;
    while (std::getline(ifile, ikey, '=')) {
        if (ikey[0] == '\n'){
            ikey.erase(ikey.begin());
        }
        // std::strstream strs(nstr);
        // strstr
        // strstr = std::strstream(nstr);
        std::getline(ifile, ival);
        if (std::string(key) == ikey) {
            ifile.close();
            return ValType(ival);
        }
    }
    ifile.close();
    return "";
}
template<typename KeyType, typename ValType>
int FILEDB<KeyType, ValType>::write(KeyType key, ValType value) {
    std::ofstream ofile;
    ofile.open(this->dbfilename, std::ios::app);
    if (!ofile) {
        std::cout << strerror(errno) << " ";
        return -1;
    }
    if (this->read_one(key) != ValType()) {
        ofile.close();
        return -1;
    }
    ofile << std::endl << std::string(key) << "=" << std::string(value);
    if (ofile.bad()) {
        ofile.close();
        return -1;
    }
    ofile.close();

    return 0;
}
template<typename KeyType, typename ValType>
std::map<KeyType, ValType>* FILEDB<KeyType, ValType>::read_all() {
    std::map<KeyType, ValType> *res = new std::map<KeyType, ValType>;
    std::ifstream ifile(this->dbfilename);
    std::string ikey, ival;
    while (std::getline(ifile, ikey, '=')) {
        if (ikey[0] == '\n'){
            ikey.erase(ikey.begin());
        }
        std::getline(ifile, ival);
        (*res)[ikey] = ival;
    }
    ifile.close();
    return res;
}
template<typename KeyType, typename ValType>
int FILEDB<KeyType, ValType>::erase(KeyType key) {
    std::fstream ofile;
    // get all keys from file
    std::map<KeyType, ValType>* res = this->read_all();
    ofile.open(this->dbfilename, std::ios::out);
    if (!ofile) {
        std::cout << strerror(errno) << " ";
        return -1;
    }
    // Write all keys to file exept "key"
    for (auto [ ikey, ival ] : *res) {
        if (key != ikey){
            #ifdef DEBUG
            std::cout << ikey << ": " << ival << "<br>"; //DEBUG
            #endif
            ofile << std::string(ikey) << "=" << std::string(ival) << std::endl;
        }
    }
    delete res;
    if (ofile.bad()) {
        return -1;
    }
    ofile.close();

    return 0;
}
template<typename KeyType, typename ValType>
FILEDB<KeyType, ValType>::FILEDB() {
    this->dbfilename = "db.txt";
}
template<typename KeyType, typename ValType>
FILEDB<KeyType, ValType>::~FILEDB() {
    return;
}

#endif
