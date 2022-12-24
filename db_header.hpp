#ifndef __DB__HPP__CLASS__
#define __DB__HPP__CLASS__
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
/*
добавление записи, удаление, просмотр списка, просмотр одной записи.
Записи в базе данных хранятся построчно в файле, а отдельные поля записи разделены символами-разделителями.
*/
template<typename KeyType, typename ValType>
class FILEDB{
    public:
    FILEDB();
    FILEDB(std::string filename);
    ~FILEDB();

    // write record to db file
    int write(KeyType key, ValType value);
    // read one record from db file
    ValType read_one(KeyType key);
    // read all records from db file
    std::map<KeyType, ValType>* read_all();
    // erase record from db file
    int erase(KeyType key);
    private:
    std::string dbfilename;
};

#endif  // __DB__HPP__CLASS__
