#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<vector>

#include "utils.h"

class Picture {
public:
    Picture();
    Picture(const Picture& other);
    Picture(const std::string& path);
    Picture(const std::string& path, const std::string& picName);
    Picture(const std::string name, unsigned int picSz, const std::string& picData);

    ~Picture();
    const std::string& GetName() const;
    const std::string& GetData() const;
    unsigned int GetPicSz() const;

    void SetName(const std::string& picName) ;
    void SetPicture(const std::string& cp, unsigned int picSz) ;
    int ToDisk(const std::string& path);

private:

    int readPicture(const std::string& path);
    //图片名
    std::string name;
    //图片的base64编码数据
    std::string data;
    //图片原二进制大小
    unsigned int picSz;
};
const std::string toSerializable(const Picture& pic) ;
Picture fromSerializable(const std::string& serializeStr);

