#pragma once

#include <windows.h>
#include <string>
#include <iostream>
#include <iterator> 
#include <algorithm>
#include <cstdint>
#include <vector>

#include <openssl/bio.h>
#include <openssl/evp.h>


/*返回string中文件截至的位置：
* @param：
* path，文件路径
* doc,执行函数后，保存path中的文件路径
* file，执行函数后，保存path中的文件名
* @ret：
* -1：不合法的字符串，无法从中分割字符串或文件名
* 3（11）：包括文件名和文件路径，
* 2（10）：这是一个文件路径
* 1（01）：这是一个文件名
*/
enum PathAnalyze {
	IS_FILE = 1,
	IS_DOC = 2,
	IS_DOC_AND_FILE =3
};
int GetDocAndFile(const std::string& path,
	std::string& doc,
	std::string& file);





static const char b64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char reverse_table[128] = {
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
};
//返回char*数据的Base64的string编码
//@param：
//binary_data：待编码二进制字符串
//size：二进制字符串长度
std::string Binary2Base64(const char* binary_data, size_t size);
//将Base64的string编码返回为char*
//@param：
//encoded_data：base64编码数据
//size_t:解码后二进制数据字节数量
std::unique_ptr<char> Base64_2_Binary(const std::string& encoded_data, size_t& size);
