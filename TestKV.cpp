//#include <iostream>
//
//#include "gtest/gtest.h"
//#include "kv.h"
//
//#include<cstring>
//
//
//
//TEST(testKV, test1)
//{
//	KV kv;
//	//存string
//	kv.AddString("str", "ABC");
//	EXPECT_EQ("ABC", kv.GetString("str"));
//}
//TEST(testKV, test2) {
//	//测试覆盖str
//	KV kv;
//	kv.AddString("str", "ABC");
//	kv.AddString("str", "New ABC");
//	EXPECT_EQ("New ABC", kv.GetString("str"));
//}
//TEST(testKV, test3) {
//	//测试插入、重写、获取int
//	KV kv;
//	kv.AddInt("Int1", 20.3);
//	EXPECT_EQ(20, kv.GetInt("Int1"));
//	//重写以及多次获得
//	kv.AddInt("Int1", 40);
//	EXPECT_EQ(40, kv.GetInt("Int1"));
//	EXPECT_EQ(40, kv.GetInt("Int1"));
//}
//TEST(testKV, test4) {
//	//测试插入、重写、获取double
//	KV kv;
//	kv.AddDouble("pi", 3.14);
//	EXPECT_EQ(3.14, kv.GetDouble("pi"));
//	kv.AddDouble("pi", 3.14159);
//	EXPECT_EQ(3.14159, kv.GetDouble("pi"));
//}
//TEST(testKV, test5) {
//	KV kv;
//	//测试插入、重写、获取char
//	kv.AddChar("char", 'N');
//	EXPECT_EQ('N', kv.GetChar("char"));
//}
//TEST(testKV, test6) {
//	//测试插入、获取picture
//	Picture pic("input.png", "Diver Down");
//	KV kv;
//	kv.AddPicture("pic", pic);
//	Picture pic2(kv.GetPicture("pic"));
//	EXPECT_EQ(pic.GetName(), pic2.GetName());
//	//EXPECT_EQ(pic.GetData(), pic2.GetData());
//	EXPECT_EQ(pic.GetPicSz(), pic2.GetPicSz());
//}
//TEST(testKV, test7){
//	//测试删除后获取键
//	KV kv;
//	Picture pic("input.png", "Diver Down");
//	kv.AddPicture("pic", pic);
//	kv.Remove("pic");
//	EXPECT_EQ(0, kv.size());
//}
////测试写到磁盘并读回
//TEST(testKV, test8) {
//	//测试删除后获取键
//	KV writeKv;
//	
//	writeKv.AddChar("char", 'A');
//	writeKv.AddDouble("pi", 3.14);
//	writeKv.AddInt("Int", 222);
//	writeKv.AddString("str", "ABC");
//	WriteKeyValueFromDick( writeKv, "ouput.json");
//
//	KV readKv;
//	EXPECT_EQ(1,ReadKeyValueFromDisk("ouput.json", readKv));
//
//	EXPECT_EQ('A', readKv.GetChar("char"));
//	EXPECT_EQ(3.14, readKv.GetDouble("pi"));
//	EXPECT_EQ(222, readKv.GetInt("Int"));
//	EXPECT_EQ("ABC", readKv.GetString("str"));
//
//	
//}
//TEST(testKV, test9) {
//	KV writeKv;
//	Picture pic("input.png", "Diver Down");
//	writeKv.AddPicture("pic", pic);
//
//	Picture pic2(writeKv.GetPicture("pic"));
//	EXPECT_EQ("Diver Down", pic2.GetName());
//	EXPECT_EQ(pic.GetPicSz(), pic2.GetPicSz());
//	pic.ToDisk("test_test7_ori.png");
//	pic2.ToDisk("test_test7_read.png");
//}
//
//TEST(testKV, testsee) {
//	std::string str("ABC\0ABC");
//	std::cout << "str" << std::endl;
//	std::cout << str.size() << std::endl;
//}
////测试多线程写没有问题
//
//
//
//
//int main()
//{
//	testing::InitGoogleTest(); RUN_ALL_TESTS(); getchar(); return 0;
//}