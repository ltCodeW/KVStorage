#include <iostream>

#include "gtest/gtest.h"
#include "Picture.h"

TEST(testPicture, test1)
{
	Picture pic("./input.png");
	pic.ToDisk("./output.png");
}

TEST(testPicture, test2)
{
	Picture pic("./input.png");
	pic.ToDisk("../");
}

TEST(testPicture, test3)
{
	Picture pic("./input.png");
	Picture pic2(pic);
	pic2.ToDisk("./copytest_output.png");
}

TEST(testPicture, test4)
{
	Picture pic("./input.png");
	std::string picSerilizeStr(toSerializable(pic));
	Picture pic2(fromSerializable(picSerilizeStr));
	EXPECT_EQ(pic2.GetData(), pic.GetData());
	pic2.ToDisk("./Serialize_output.png");
}



int main()
{
	testing::InitGoogleTest(); RUN_ALL_TESTS(); getchar(); return 0;
}