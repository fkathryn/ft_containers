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
	//----------default constructor----------
	ft::vector<int> sas;
	sas.push_back(1);
//	std::cout << sas.size() << std::endl;
//	std::cout << sas.capacity() << std::endl;
	//----------fill constructor----------
	ft::vector<int> v1(38, 1);
	std::vector<int> vStd1(38, 1);
	for (int i = 0; i < v1.size(); i++)
		EXPECT_EQ(v1.at(i), vStd1.at(i));
	EXPECT_EQ(v1.size(), vStd1.size());

	//----------range constructor----------
	std::vector<int> vStd2(10, 5);
	for (int i = 10; i >= 0; --i)
		vStd2.push_back(i);
	ft::vector<int> v2(vStd2.begin(), vStd2.end());
	EXPECT_EQ(v2.empty(), vStd2.empty());
	EXPECT_EQ(v2.max_size(), vStd2.max_size());
	EXPECT_EQ(v2.max_size(), vStd2.max_size());
	for (int i = 0; i < vStd2.size(); i++)
		EXPECT_EQ(v2.at(i), vStd2.at(i));

	//-----------erase-----------
	std::cout << "my: " << v2.size() << std::endl;
	std::cout <<vStd2.size() << std::endl;
	for (int i = 0; i < vStd2.size(); i++) {
		EXPECT_EQ(v2.at(i), vStd2.at(i));
		std::cout << v2.at(i) << std::endl;
	}
	for (int i = 0; i < v2.size(); i++) {
		std::cout <<  "erase: " << i << v2.at(i) << std::endl;
	}
	//-----------copy constructor----------
	ft::vector<int> std(21, 42);
	ft::vector<int> my(std);
	for (int i = 0; i < my.size(); i++)
		EXPECT_EQ(my.at(i), std.at(i));
	//----------resize----------
	v2.resize(3);
	vStd2.resize(3);
	EXPECT_EQ(v2.size(), vStd2.size());
//	//----------assign----------
	v2.assign(20, 42);
	vStd2.assign(20, 42);
	for (int i = 0; i != vStd2.size(); i++) {
		EXPECT_EQ(v2.at(i), vStd2.at(i));
	}


}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

