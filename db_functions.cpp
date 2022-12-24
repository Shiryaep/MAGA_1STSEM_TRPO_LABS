#ifndef __DB__CPP__CLASS__
#define __DB__CPP__CLASS__
#include "db_header.hpp"
#include <fstream>
template<typename keyT, typename valueT>
valueT FILEDB<keyT, valueT>::read_one(keyT key) 
{
    std::ifstream ifile(this->dbfilename);
    std::string ikey, ival, nstr;
    while (std::getline(ifile, ikey, '=')) 
    {
        if (ikey[0] == '\n')
        { ikey.erase(ikey.begin()); }
        std::getline(ifile, ival);
        if (std::string(key) == ikey) 
        {   
            ifile.close();
            return valueT(ival);
        }
    }
    ifile.close();
    return "";
}
template<typename keyT, typename valueT>
int FILEDB<keyT, valueT>::write(keyT key, valueT value) 
{
    std::ofstream ofile;
    ofile.open(this->dbfilename, std::ios::app);
    if (!ofile) 
    {
        std::cout << strerror(errno) << " ";
        return -1;
    }
    if (this->read_one(key) != valueT()) 
    {
        ofile.close();
        return -1;
    }
    ofile << std::endl << std::string(key) << "=" << std::string(value);
    if (ofile.bad()) 
    {
        ofile.close();
        return -1;
    }
    ofile.close();

    return 0;
}
template<typename keyT, typename valueT>
std::map<keyT, valueT>* FILEDB<keyT, valueT>::read_all() 
{
    std::map<keyT, valueT> *res = new std::map<keyT, valueT>;
    std::ifstream ifile(this->dbfilename);
    std::string ikey, ival;
    while (std::getline(ifile, ikey, '=')) 
    {
        if (ikey[0] == '\n')
        {
            ikey.erase(ikey.begin());
        }
        std::getline(ifile, ival);
        (*res)[ikey] = ival;
    }
    ifile.close();
    return res;
}
template<typename keyT, typename valueT>
int FILEDB<keyT, valueT>::erase(keyT key) 
{
    std::fstream ofile;
    // get all keys from file
    std::map<keyT, valueT>* res = this->read_all();
    ofile.open(this->dbfilename, std::ios::out);
    if (!ofile) 
    {
        std::cout << strerror(errno) << " ";
        return -1;
    }
    // Write all keys to file exept "key"
    for (auto [ ikey, ival ] : *res) 
    {
        if (key != ikey)
        {
            #ifdef DEBUG
            std::cout << ikey << ": " << ival << "<br>"; //DEBUG
            #endif
            ofile << std::string(ikey) << "=" << std::string(ival) << std::endl;
        }
    }
    delete res;
    if (ofile.bad()) 
    {
        return -1;
    }
    ofile.close();

    return 0;
}
template<typename keyT, typename valueT>
FILEDB<keyT, valueT>::FILEDB() 
{   this->dbfilename = "db.txt"; }

template<typename keyT, typename valueT>
FILEDB<keyT, valueT>::~FILEDB() 
{   return; }

#endif
