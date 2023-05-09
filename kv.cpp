#pragma once

#include "kv.h"


KV::KV() {
	doc.SetObject();
}

KV::~KV() {
}

void KV::AddInt(const std::string& key, int value) {
	if (doc.HasMember(key.c_str())) {
		doc[key.c_str()] = value;
	}
	else {
		rapidjson::Value Vkey(key.c_str(), doc.GetAllocator());
		doc.AddMember(Vkey, value, allocator);
	}
}
void KV::AddDouble(const std::string& key, double value) {
	if (doc.HasMember(key.c_str())) {
		doc[key.c_str()] = value;
	}
	else {
		rapidjson::Value Vkey(key.c_str(), doc.GetAllocator());
		doc.AddMember(Vkey, value, allocator);
	}
	
}
void KV::AddChar(const std::string& key, char value) {
	std::string c_str;
	c_str = value;
	AddString(key, c_str);

}
void KV::AddString(const std::string& key, const std::string& value, unsigned int str_len ) {
	if (str_len == 0) {
		str_len = value.size();
	}
	if (doc.HasMember(key.c_str())) {
		rapidjson::Value& Vvalue = doc[key.c_str()];
		Vvalue.SetString(value.c_str(), str_len,allocator);
	}
	else {
		rapidjson::Value Vkey(key.c_str(), doc.GetAllocator());
		rapidjson::Value Vvalue(value.c_str(), doc.GetAllocator());
		doc.AddMember(Vkey, Vvalue, allocator);
	}
}
void KV::AddPicture(const std::string& key, const Picture& value) {
	std::string serilizedPicture = toSerializable(value);
	AddString(key, serilizedPicture,value.GetPicSz());
}


const rapidjson::Value& KV::GetValue(const std::string& key) {
	return  doc[key.c_str()];
}



const int KV::GetInt(const std::string& key) {
	if (doc.HasMember(key.c_str())) {
		const rapidjson::Value& value = GetValue(key);
		return value.GetInt();
	}
	else {
		std::cerr << "No value is available" << std::endl;
		return -1;
	}
}
const double KV::GetDouble(const std::string& key) {
	if (doc.HasMember(key.c_str())) {
		const rapidjson::Value& value = GetValue(key);
		return value.GetDouble();
	}
	else {
		std::cerr << "No value is available" << std::endl;
		return -1;
	}
}

const std::string KV::GetString(const std::string& key) {
	if (doc.HasMember(key.c_str())) {
		const rapidjson::Value& value = doc[key.c_str()];
		return value.GetString();
	}
	else {
		std::cerr << "No value is available" << std::endl;
		return "";
	}
}
const char KV::GetChar(const std::string& key) {
	auto a = GetString(key);;
	std::string strChr(a);
	if (strChr.size() > 0) {
		return strChr[0];
	}
	else {
		std::cerr << "No value is available" << std::endl;
		return -1;
	}
}


const Picture KV::GetPicture(const std::string& key) {
	if (doc.HasMember(key.c_str())) {
		//图片用字符串形式保存、但是不可以用字符串形式读取
		//图片字符串中会有空字符，返回时被阶段
		//要按照大小读写
		const std::string serializeStr = GetValue(key).GetString();
		Picture pic(fromSerializable(serializeStr));
		return pic;
		}
	else {
		std::cerr << "No value is available" << std::endl;
		Picture pic;
		return pic;
	}
}

int KV::Remove(const std::string& key) {
	if (doc.HasMember(key.c_str())) {
		doc.EraseMember(key.c_str());
		return 1;
	}
	std::cout << "No key " << key << " can be remove";
	return -1;

}
void KV::Clear() {
	doc.RemoveAllMembers();
}

unsigned int KV::size() {
	return doc.MemberCount();
}

bool  KV::AcceptWriter(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const{
	return doc.Accept(writer);
}

void KV::CleanBuffer() {
	memset(buffer, 0, sizeof(buffer));
}
rapidjson::ParseResult KV::readFile(const std::string& fileName) {
	std::string path_doc("");
	std::string path_file("");
	if (GetDocAndFile(fileName, path_doc, path_file) == IS_DOC) {
		path_file = "kv.json";
	}
	std::string valified_path = path_doc + path_file;

	FILE* fp;
	if (fopen_s(&fp, valified_path.c_str(), "r") != 0) {
		return rapidjson::ParseResult(rapidjson::kParseErrorUnspecificSyntaxError,0);
	}   // 再次打开文件
	CleanBuffer();
	rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));
	fclose(fp);

	return doc.ParseStream(is);
}


int WriteKeyValueFromDick(const KV& kv, const std::string& path) {
	std::string path_doc("");
	std::string path_file("");
	if (GetDocAndFile(path, path_doc, path_file) ==IS_DOC) {
		path_file = "kv.json";
	}
	std::string valified_path = path_doc + path_file;

	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
	if (!kv.AcceptWriter(writer)) {
		return -1;
	}   // 将 DOM 对象格式化输出为字符串

	FILE* fout;
	if (fopen_s(&fout, valified_path.c_str(), "w")!=0) {
		return -1;
	}   // 打开文件
	fprintf(fout, "%s", sb.GetString());      // 将字符串写入文件
	fclose(fout);                             // 关闭文件

	return 0;

}

int ReadKeyValueFromDisk(const std::string& fileName, KV& kv) {
	if (kv.readFile(fileName)) {
		return 1;
	}
	else {
		return -1;
	}

	return 0;
}
