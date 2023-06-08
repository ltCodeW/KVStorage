#include "utils.h"



//判断一个没有分割符的字符串是路径或文件
//仅仅认为\w+[.]\w这类命名为文件
int is_doc_or_file(const std::string& path,
	std::string& doc,
	std::string& file) {
	doc = "";
	file = "";

	size_t pos = path.rfind('.');
	if (pos == std::string::npos) {
		doc = path;
		return IS_DOC;
	}
	else {
		if (pos > 0 && pos < path.size() - 1) {
			file = path;
			return IS_FILE;
		}
		else {
			doc = path;
			return IS_DOC;
		}
	}

}




int GetDocAndFile(const std::string& path,
	std::string& doc,
	std::string& file)
{
	doc = "";
	file = "";
	size_t split_pos1 = path.rfind('/');
	size_t split_pos2 = path.rfind('\\');
	std::string substr("");
	//确定最后一个分隔符的位置
	// 如果在最后，是一个doc
	if (split_pos1 == path.size() - 1 || split_pos2 == path.size() - 1) {
		doc = path;
		return IS_DOC;
	}
	//如果不存在分隔符，path为文件夹或者文件
	if (split_pos1 == std::string::npos && split_pos2 == std::string::npos) {
		return is_doc_or_file(path, doc, file);
	}
	else {
		//存在分隔符，确定最后分隔符的位置
		size_t split_pos = std::string::npos;
		if (split_pos1 == std::string::npos || split_pos2 == std::string::npos) {
			split_pos = (split_pos1 == std::string::npos ? split_pos2 : split_pos1);
		}
		else {
			split_pos = split_pos1 > split_pos2 ? split_pos1 : split_pos2;
		}
		//判断分隔符后的是文件还是路径
		std::string substr = path.substr(split_pos+1, path.size() - split_pos-1);
		auto ret = is_doc_or_file(substr, doc, file);
		ret |= IS_DOC;
		doc = path.substr(0, split_pos+1) + doc;
		return ret;
	}
}



std::string Binary2Base64(const char* binary_data, size_t size) {
	BIO* bio, * b64;
	BUF_MEM* bufferPtr;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	BIO_write(bio, binary_data, size);
	BIO_flush(bio);

	BIO_get_mem_ptr(bio, &bufferPtr);
	std::string base64_data(bufferPtr->data, bufferPtr->length);

	BIO_free_all(bio);

	return base64_data;
}

std::shared_ptr<char> Base64_2_Binary(const std::string& encoded_data, size_t& size) {
	BIO* bio, * b64;
	size = 0;

	char buffer[BIO_BUF_SIZE];
	memset(buffer, 0, BIO_BUF_SIZE);

	std::vector<char> alldata;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new_mem_buf(encoded_data.c_str(), encoded_data.size());
	bio = BIO_push(b64, bio);

	int length = 0;
	while (length = BIO_read(bio, buffer, BIO_BUF_SIZE)) {
		alldata.insert(alldata.end(), buffer, buffer+length);
		if (length < BIO_BUF_SIZE) {
			break;
		}
	}
		
	BIO_free_all(bio);

	size = alldata.size();
	std::unique_ptr<char> p_data(new char[size]);
	std::copy(alldata.data(), alldata.data() + size, p_data.get());
	return p_data;
	
}
