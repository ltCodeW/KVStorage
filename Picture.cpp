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

	char* buffer = new  char[picSz];
	file.read(buffer, picSz);

	std::string picDataCode(base64_encode(buffer, picSz));
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
			"_"+std::to_string(pic.GetPicSz()) + 
		    "_"+pic.GetData();
}

Picture fromSerializable(const std::string serializeStr){
	unsigned int parseIdx = 1;
	unsigned int nameSz = 0;
	while (std::isdigit(serializeStr[parseIdx])) {
		nameSz *= 10;
		nameSz += (serializeStr[parseIdx] -'0');
		parseIdx++;
	}
	parseIdx++;
	std::string name = serializeStr.substr(parseIdx, nameSz);
	unsigned int picSz = 0;

	parseIdx += nameSz;
	parseIdx++;
	while (std::isdigit(serializeStr[parseIdx])) {
		picSz *= 10;
		picSz += (serializeStr[parseIdx] - '0');
		parseIdx++;
	}
	parseIdx++;
	std::string data(serializeStr.substr(parseIdx, picSz));

	return Picture(name, picSz, data);
}

int Picture::ToDisk(const std::string& path) {
	//Â·¾¶ÅÐ¶Ï
	std::string path_doc("");
	std::string path_file("");
	if (GetDocAndFile(path, path_doc, path_file) == IS_DOC) {
		path_file = GetName();
	}
	//Ð´ÕÕÆ¬
	
	std::string outFile = path_doc + path_file;
	std::ofstream outfile(outFile, std::ios::out | std::ios::binary);
	if (outfile.is_open()) {
		outfile.write(reinterpret_cast<const char*>(
			this->data.c_str()), 
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


