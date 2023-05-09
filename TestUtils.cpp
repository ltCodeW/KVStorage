#include <iostream>

#include "gtest/gtest.h"
#include "utils.h"


void doTEST_GetDocAndFile(const std::string& str, std::string& doc, std::string& file) {
	std::cout << str << std::endl;
	switch (GetDocAndFile(str, doc, file)) {
	case -1:
		std::cout << "Error path" << std::endl;
		break;
	case IS_DOC_AND_FILE:
		std::cout << "doc: " << doc << std::endl;
		std::cout << "file: " << file << std::endl;
		break;
	case IS_DOC:
		std::cout << "doc: " << doc << std::endl;
		break;
	case IS_FILE:
		std::cout << "flie: " << file << std::endl;
		break;
	}
}

TEST(testGetDocAndFile, test1)
{
	std::string doc("");
	std::string file("");
	const std::string str("./nihao/");
	doTEST_GetDocAndFile(str,doc,file);
	EXPECT_EQ("./nihao/", doc);
	EXPECT_EQ("", file);
}
TEST(testGetDocAndFile, test2)
{
	std::string doc("");
	std::string file("");
	const std::string str("D:/code/c++/googletest-master/googletest-master/build/lib/Debug/");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("D:/code/c++/googletest-master/googletest-master/build/lib/Debug/", doc);
	EXPECT_EQ("", file);
}
TEST(testGetDocAndFile, test3)
{
	std::string doc("");
	std::string file("");
	const std::string str("D:/code/c++/googletest-master/googletest-master/build/lib/Debug");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("D:/code/c++/googletest-master/googletest-master/build/lib/Debug", doc);
	EXPECT_EQ("", file);
}

TEST(testGetDocAndFile, test4)
{
	std::string doc("");
	std::string file("");
	const std::string str("D:/code/c++/googletest-master/googletest-master/build/lib/Debug/nihao.png");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("D:/code/c++/googletest-master/googletest-master/build/lib/Debug/", doc);
	EXPECT_EQ("nihao.png", file);
}

TEST(testGetDocAndFile, test5)
{
	std::string doc("");
	std::string file("");
	const std::string str("./nihao.png");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("./", doc);
	EXPECT_EQ("nihao.png", file);
}

TEST(testGetDocAndFile, test6)
{
	std::string doc("");
	std::string file("");
	const std::string str("nihao.png");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("", doc);
	EXPECT_EQ("nihao.png", file);
}

TEST(testGetDocAndFile, test7)
{
	std::string doc("");
	std::string file("");
	const std::string str("./.");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("./.", doc);
	EXPECT_EQ("", file);
}

TEST(testGetDocAndFile, test8)
{
	std::string doc("");
	std::string file("");
	const std::string str("");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("", doc);
	EXPECT_EQ("", file);
}

TEST(testGetDocAndFile, test9)
{
	std::string doc("");
	std::string file("");
	const std::string str("");
	doTEST_GetDocAndFile(str, doc, file);
	EXPECT_EQ("", doc);
	EXPECT_EQ("", file);
}

TEST(testBase64BinaryConvert, test1) {
	const char* binary_data = "235363advsfb846!^P_&=9284738\023jgsrg$%(%864629";
	size_t sz= sizeof("235363advsfb846!^P_&=9284738\023jgsrg$%(%864629");
	std::string base64Code(Binary2Base64(binary_data, sz));
	size_t decode_sz = 0;
	auto cptr(Base64_2_Binary(base64Code, decode_sz));
	std::cout << "bianary data size  " << sz << std::endl;
	EXPECT_EQ(sz, decode_sz);
	EXPECT_EQ(std::memcmp(binary_data, cptr.get(),sz),  0);



}


int main()
{
	testing::InitGoogleTest(); RUN_ALL_TESTS(); getchar(); return 0;
}
