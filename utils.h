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
#include <openssl/buffer.h>

#define BIO_BUF_SIZE 1024
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






//����char*���ݵ�Base64��string����
//@param��
//binary_data��������������ַ���
//size���������ַ�������
std::string Binary2Base64(const char* binary_data, size_t size);
//��Base64��string���뷵��Ϊchar*
//@param��
//encoded_data��base64��������
//size_t:���������������ֽ�����
std::shared_ptr<char> Base64_2_Binary(const std::string& encoded_data, size_t& size);
