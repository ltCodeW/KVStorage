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
	std::string out;

	// 创建 BIO 对象
	BIO* b64 = BIO_new(BIO_f_base64());
	BIO* bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	// 执行编码操作
	BIO_write(bio, binary_data, size);
	BIO_flush(bio);

	// 获取编码结果
	char* data = nullptr;
	int len = BIO_get_mem_data(bio, &data);
	if (len > 0) {
		out.assign(data, len - 1);  // 注意去掉结尾的回车符
	}

	// 释放资源
	BIO_free_all(bio);

	return out;
}

std::unique_ptr<char> Base64_2_Binary(const std::string& encoded_data, size_t& size) {
	size = 0;
	// 创建 BIO 对象
	BIO* b64 = BIO_new(BIO_f_base64());
	BIO* bio = BIO_new_mem_buf(encoded_data.c_str(), encoded_data.size());
	BIO* bio_dec = BIO_new(BIO_s_mem());
	if (!b64 || !bio ||!bio_dec) {
		BIO_free_all(bio);
		return nullptr;
	}

	bio = BIO_push(b64, bio);
	BIO_set_flags(bio_dec, BIO_FLAGS_BASE64_NO_NL);
	BIO_write(bio_dec, encoded_data.c_str(), encoded_data.size());
	BIO_flush(bio_dec);

	// 执行解码操作
	std::vector<char> read_data;
	const int read_sz = 1024;
	char buf[read_sz];
	int len = 0;
	while ((len = BIO_read(bio, buf, read_sz)) > 0) {
		size += len;
		read_data.insert(read_data.end(), buf, buf + len);
	}
	if (len < 0) {
		BIO_free_all(bio);
		std::cout << "Error reading data" << std::endl;;
		return nullptr;
	}
	// 释放资源
	BIO_free_all(bio);
	auto ptr = std::make_unique<char>(read_data.size());
	memcpy(ptr.get(), read_data.data(), read_data.size());
	return ptr;
}
