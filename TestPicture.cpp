//#include <iostream>
//
//#include "gtest/gtest.h"
//#include "Picture.h"
//
//TEST(testPicture, test1)
//{
//	Picture pic("./input.png");
//	pic.ToDisk("./output.png");
//}
//
//TEST(testPicture, test2)
//{
//	Picture pic("./input.png");
//	pic.ToDisk("../");
//}
//
//TEST(testPicture, test3)
//{
//	Picture pic("./input.png");
//	std::string picSerilizeStr(toSerializable(pic));
//	Picture pic2(fromSerializable(picSerilizeStr));
//	pic2.ToDisk("./Serialize_output.png");
//}
//
//TEST(testPicture, testsee)
//{
//	std::string s1("ABC\0ABC");
//	std::string s2(s1);
//}
//
//int main()
//{
//	testing::InitGoogleTest(); RUN_ALL_TESTS(); getchar(); return 0;
//}