#pragma once
#include<string>

class KVStorage
{
public:
	//使用KVStorage解析，后面再
	KVStorage():isOpen(false) {}
	

	KVStorage(const std::string& path):savePath(path), isOpen(false) {
		openPath();
	}

	~KVStorage() {
		if (isOpen) {
			closePath();
		}
	}
	
	int SetPath(const std::string& path) {

	}

	kv GetValue()

	
	
private:
	std::string savePath;
	bool isOpen;

	int openPath();
	int closePath();

};

