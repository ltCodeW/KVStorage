#include "Picture.h"
#include "utils.h"


Picture::Picture():
name(""), data(""), picSz(0) {}

Picture::Picture(const Picture& other):
name(other.GetName()), data(other.GetData()), picSz(other.GetPicSz())
{}

Picture::Picture(const std::string& path) :
	name(""), data(""), picSz(0) {
	readPicture(path);
	name = path;
}

Picture::Picture(const std::string& path, const std::string& picName):
	name(""),data(""),picSz(0){
	readPicture(path);
	name = picName;
}

Picture::Picture(const std::string name, unsigned int picSz,const std::string& picData):
	name(name), data(picData), picSz(picSz) {}



Picture::~Picture() {
	
}
int Picture::readPicture(const std::string& path) {
	std::ifstream file;
	file.open(path, std::ios::binary);
	if(!file.is_open()) {
		std::cout << "No Picture can be read in path " << path << std::endl;
		return -1;
	}

	file.seekg(0, std::ios::end);
	picSz = file.tellg();
	file.seekg(0);

	char* buffer = new char[picSz];
	int len = 0;
	file.read(buffer, picSz);

	std::string picDataCode(Binary2Base64(buffer, picSz));
	data.assign(picDataCode.begin(), picDataCode.end());

	delete[] buffer; 
	file.close();
}
const std::string& Picture::GetName() const {
	return name;
}
const std::string& Picture::GetData() const {
	return data;
}
unsigned int Picture::GetPicSz() const {
	return picSz;
}

void Picture::SetName(const std::string& picName) {
	name = picName;
}
void Picture::SetPicture(const std::string& cp, unsigned int picSz) {
	this->picSz = picSz;
	data = cp;
}


const std::string toSerializable(const Picture& pic) {
	return "_" + std::to_string(pic.GetName().size()) +
			"_"+ pic.GetName() +
			"_"+ std::to_string(pic.GetData().size()) + 
		    "_"+pic.GetData()+
			"_" + std::to_string(pic.GetPicSz());
			
}

Picture fromSerializable(const std::string& serializeStr){
	unsigned int parseIdx = 1;
	unsigned int nameSz = 0;
	//获得图片名长度，根据名字长度获取图片名
	while (std::isdigit(serializeStr[parseIdx])) {
		nameSz *= 10;
		nameSz += (serializeStr[parseIdx] -'0');
		parseIdx++;
	}
	parseIdx++;
	std::string name = serializeStr.substr(parseIdx, nameSz);
	//获得图片data长度，根据data长度获取图片名
	unsigned int dataSz = 0;
	parseIdx += nameSz;
	parseIdx++;
	while (std::isdigit(serializeStr[parseIdx])) {
		dataSz *= 10;
		dataSz += (serializeStr[parseIdx] - '0');
		parseIdx++;
	}
	parseIdx++;
	std::string data(serializeStr.substr(parseIdx, dataSz));
	//获取图片原始大小
	unsigned int picSz = 0;
	parseIdx += dataSz;
	parseIdx++;
	while (std::isdigit(serializeStr[parseIdx])) {
		picSz *= 10;
		picSz += (serializeStr[parseIdx] - '0');
		parseIdx++;
	}
	return Picture(name, picSz, data);
}

int Picture::ToDisk(const std::string& path) {
	//路径判断
	std::string path_doc("");
	std::string path_file("");
	if (GetDocAndFile(path, path_doc, path_file) == IS_DOC) {
		path_file = GetName();
	}
	//写照片
	
	std::string outFile = path_doc + path_file;
	std::ofstream outfile(outFile, std::ios::out | std::ios::binary);
	
	size_t recDataSize = 0;
	auto cptr(Base64_2_Binary(data, recDataSize));

	if (recDataSize != picSz) {
		std::cout << "Error : base64 decode error." << std::endl;
	}

	if (outfile.is_open()) {
		outfile.write(reinterpret_cast<const char*>(
			cptr.get()),
			this->GetPicSz());
		outfile.close();
		return 1;
	}
	else {
		std::cerr << "Failed to open file." << std::endl;
		return -1;
	}
	return 0;
}


