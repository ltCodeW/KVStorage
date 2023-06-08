#include <iostream>

#include "gtest/gtest.h"
#include "kv.h"

#include <thread>
#include<cstring>
#include <random>


TEST(testKV, test1)
{
	KV kv;
	//存string
	kv.AddString("str", "ABC");
	EXPECT_EQ("ABC", kv.GetString("str"));
}
TEST(testKV, test2) {
	//测试覆盖str
	KV kv;
	kv.AddString("str", "ABC");
	kv.AddString("str", "New ABC");
	EXPECT_EQ("New ABC", kv.GetString("str"));
}
TEST(testKV, test3) {
	//测试插入、重写、获取int
	KV kv;
	kv.AddInt("Int1", 20.3);
	EXPECT_EQ(20, kv.GetInt("Int1"));
	//重写以及多次获得
	kv.AddInt("Int1", 40);
	EXPECT_EQ(40, kv.GetInt("Int1"));
	EXPECT_EQ(40, kv.GetInt("Int1"));
}
TEST(testKV, test4) {
	//测试插入、重写、获取double
	KV kv;
	kv.AddDouble("pi", 3.14);
	EXPECT_EQ(3.14, kv.GetDouble("pi"));
	kv.AddDouble("pi", 3.14159);
	EXPECT_EQ(3.14159, kv.GetDouble("pi"));
}
TEST(testKV, test5) {
	KV kv;
	//测试插入、重写、获取char
	kv.AddChar("char", 'N');
	EXPECT_EQ('N', kv.GetChar("char"));
}
TEST(testKV, test6) {
	//测试插入、获取picture
	Picture pic("input.png", "Diver Down");
	KV kv;
	if (pic.GetPicSz() == 0) {
		std::cout << " picture not exist" << std::endl;
	}else{
		kv.AddPicture("pic", pic);
		Picture pic2(kv.GetPicture("pic"));
		EXPECT_EQ(pic.GetName(), pic2.GetName());
		//EXPECT_EQ(pic.GetData(), pic2.GetData());
		EXPECT_EQ(pic.GetPicSz(), pic2.GetPicSz());
	}
}
TEST(testKV, test7){
	//测试删除后获取键
	KV kv;
	Picture pic("input1.png", "Diver Down");
	kv.AddPicture("pic", pic);
	kv.Remove("pic");
	EXPECT_EQ(0, kv.size());
}
//测试写到磁盘并读回
TEST(testKV, test8) {
	//测试删除后获取键
	KV writeKv;
	
	writeKv.AddChar("char", 'A');
	writeKv.AddDouble("pi", 3.14);
	writeKv.AddInt("Int", 222);
	writeKv.AddString("str", "ABC");
	WriteKeyValueFromDick( writeKv, "ouput.json");

	KV readKv;
	EXPECT_EQ(1,ReadKeyValueFromDisk("ouput.json", readKv));

	EXPECT_EQ('A', readKv.GetChar("char"));
	EXPECT_EQ(3.14, readKv.GetDouble("pi"));
	EXPECT_EQ(222, readKv.GetInt("Int"));
	EXPECT_EQ("ABC", readKv.GetString("str"));
}
TEST(testKV, test9) {
	KV writeKv;
	Picture pic("input1.png", "Diver Down");
	writeKv.AddPicture("pic", pic);

	Picture pic2(writeKv.GetPicture("pic"));
	EXPECT_EQ("Diver Down", pic2.GetName());
	EXPECT_EQ(pic.GetPicSz(), pic2.GetPicSz());
	pic.ToDisk("test_test9_ori.png");
	pic2.ToDisk("test_test9_rew.png");
}

//测试多线程写

void writeThread_int(KV& kv,int val) {
	kv.AddInt("Int", val);
	std::cout << "Write Int " << val << "over"<<std::endl;
}
void writeThread_string(KV& kv,const std::string& val) {
	kv.AddString("Str", val);
	std::cout << "Write Str " << val << "over" << std::endl;
}
void writeThread_pic(KV& kv,const Picture& pic) {
	kv.AddPicture("Pic", pic);
	std::cout << "Write Pic " << pic.GetName() <<"over"<< std::endl;
}
void readThread_int(const KV& kv) {
	std::cout << "Get Int " <<kv.GetInt("Int") << std::endl;
}
void readThread_string(const KV& kv) {
	std::cout << "Get Str " << kv.GetString("Str") << std::endl;
}
void readThread_pic(const KV& kv) {
	Picture pic(kv.GetPicture("Pic"));
	std::cout << "Get Pic " << pic.GetName() << std::endl;
	pic.ToDisk(pic.GetName() +".png");
}


TEST(testKV, test10) {
	KV kv;
	auto fwi1 = std::bind(writeThread_int, std::ref(kv), 1);
	auto fwi2 = std::bind(writeThread_int, std::ref(kv), 2);
	auto fws1 = std::bind(writeThread_string, std::ref(kv), "1111");
	auto fws2 = std::bind(writeThread_string, std::ref(kv), "2222");
	Picture pic1("input1.png");
	Picture pic2("input2.png");
	auto fwp1 = std::bind(writeThread_pic, std::ref(kv), std::cref(pic1));
	auto fwp2 = std::bind(writeThread_pic, std::ref(kv), std::cref(pic2));
	auto frp = std::bind(readThread_pic, std::cref(kv));
	auto fri = std::bind(readThread_int, std::cref(kv));
	auto frs = std::bind(readThread_string, std::cref(kv));

	std::random_device rd;  // 随机数产生器种子
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 6);
		
	int write_num = 0;
	int read_num = 0;

	int t_idx = 0;
	const int exe_num = 10;
	std::thread write_threads[exe_num];
	std::thread read_threads[exe_num];
	for (int i = 0; i < exe_num; i++) {
		t_idx = dis(gen);
		if (t_idx % 2 == 0) {
			//随机数偶数执行读操作
			switch (t_idx) {
			case 0:
				std::cout << "write int 1" << std::endl;
				write_threads[write_num] = std::thread(fwi1); break;
			case 1:
				std::cout << "write int 2" << std::endl;
				write_threads[write_num] = std::thread(fwi2); break;
			case 2:
				std::cout << "write string 1111" << std::endl;
				write_threads[write_num] = std::thread(fws1); break;
			case 3:
				std::cout << "write string 2222" << std::endl;
				write_threads[write_num] = std::thread(fws2); break;
			case 4:
				std::cout << "write pic1" << std::endl;
				write_threads[write_num] = std::thread(fwp1); break;
			case 5:
				std::cout << "write pic2" << std::endl;
				write_threads[write_num] = std::thread(fwp2); break;
			}
			write_num++;

		}
		else {
			//随机数奇数执行写操作
			switch (t_idx / 2) {
			case 0:
				std::cout << "read int " << std::endl;
				read_threads[read_num] = std::thread(fri); break;
			case 1:
				std::cout << "read string " << std::endl;
				read_threads[read_num] = std::thread(frs); break;
			case 2:
				std::cout << "read pic " << std::endl;
				read_threads[read_num] = std::thread(frp); break;
			}
			read_num++;
		}
	}
	for (int i = 0; i < read_num; i++) {
		read_threads[i].join();
	}
	for (int i = 0; i < write_num; i++) {
		write_threads[i].join();
	}
	std::cout << "main thread over~" << std::endl;

	
}


int main()
{
	testing::InitGoogleTest(); RUN_ALL_TESTS(); getchar(); return 0;
}