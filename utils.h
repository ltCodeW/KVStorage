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


/*����string���ļ�������λ�ã�
* @param��
* path���ļ�·��
* doc,ִ�к����󣬱���path�е��ļ�·��
* file��ִ�к����󣬱���path�е��ļ���
* @ret��
* -1�����Ϸ����ַ������޷����зָ��ַ������ļ���
* 3��11���������ļ������ļ�·����
* 2��10��������һ���ļ�·��
* 1��01��������һ���ļ���
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
//����char*���ݵ�Base64��string����
//@param��
//binary_data��������������ַ���
//size���������ַ�������
std::string Binary2Base64(const char* binary_data, size_t size);
//��Base64��string���뷵��Ϊchar*
//@param��
//encoded_data��base64��������
//size_t:���������������ֽ�����
std::unique_ptr<char> Base64_2_Binary(const std::string& encoded_data, size_t& size);
