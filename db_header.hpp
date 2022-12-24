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
template<typename keyT, typename valueT>
class FILEDB
{
    public:
    // конструкторы
    FILEDB();
    FILEDB(std::string filename);

    ~FILEDB();

    // записать строчку в базу данных
    int write(keyT key, valueT value);
    // считать строку из базы данных по ключу
    valueT read_one(keyT key);
    // считать все из базы даных
    std::map<keyT, valueT>* read_all();
    // стереть строку из базы данных по ключу
    int erase(keyT key);
    private:
    // название файла с базой данных
    std::string dbfilename;
};

#endif  // __DB__HPP__CLASS__
