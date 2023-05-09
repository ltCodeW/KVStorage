
#pragma once
#include <filesystem>
#include <iostream>

#include "rapidjson/document.h"
#include"rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"


#include"Picture.h"
#include"utils.h"
//支持 int、char、double、string、picture的键值对存储

#define  BUF_SZ 40960
class KV {
public:
    friend int toDick(const KV& kv);
    
    KV();
    ~KV();
   
    void AddInt(const std::string& key,int value);
    void AddDouble(const std::string& key, double value);
    void AddChar(const std::string& key, char value);
    void AddString(const std::string& key, const std::string& value,unsigned int str_len = 0);
    void AddPicture(const std::string& key, const Picture& value);
    
    const int GetInt(const std::string& key);
    const double GetDouble(const std::string& key);
    const char GetChar(const std::string& key);
    const std::string GetString(const std::string& key);
    const Picture GetPicture(const std::string& key);

    int Remove(const std::string& key);
    void Clear();
    unsigned int size();

    bool AcceptWriter(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
    rapidjson::ParseResult readFile(const std::string& fileName);
    


    
private:
    void CleanBuffer();
    
    char buffer[BUF_SZ];
    const rapidjson::Value& GetValue(const std::string& key);
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
};


int WriteKeyValueFromDick(const KV& kv,const std::string& path);
int ReadKeyValueFromDisk(const std::string& fileName,KV& kv);
