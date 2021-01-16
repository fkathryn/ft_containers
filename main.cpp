#include <iostream>
#include "List.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
#include <gtest/gtest.h>
#include <stack>
#include <vector>

TEST(BasicStack, TestStack) {
	ft::stack<std::string> str;
	std::stack<std::string> strStd;

	EXPECT_EQ(str.empty(), strStd.empty());

}

TEST(BasicVector, TestVector) {
	ft::vector<int> v1(1, 5);
	std::vector<int> vStd(1, 5);

	EXPECT_EQ(v1.empty(), vStd.empty());
//	EXPECT_EQ(v1.max_size(), vStd.max_size());
	EXPECT_EQ(v1.at(5), vStd.at(5));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

