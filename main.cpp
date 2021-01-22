#include <iostream>
#include "List.hpp"
#include "Vector.hpp"
#include "Iterator.hpp"
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
	std::vector<int> std;
	std::cout << "cap: " << sas.capacity() << " size: " << sas.size() << std::endl;
	sas.pop_back();
	sas.push_back(1);
	sas.push_back(2);
	sas.push_back(3);
	std::cout << "cap: " << sas.capacity() << " size: " << sas.size() << std::endl;
	sas.printVector();
	sas.insert(sas.begin() + 3, 21);
	std::cout << sas.size() << std::endl;
	std::cout << sas.capacity() << std::endl;
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
	v2.printVector();
	//----------resize----------
	std::cout << "my: " << " " << v2.size();
	std::cout << " std: "<< " " << vStd2.size() << std::endl;
	v2.resize(23, 21);
	vStd2.resize(23, 21);
	EXPECT_EQ(v2.size(), vStd2.size());

	//-----------erase-----------
	std::cout << "my: " << v2.size() << std::endl;
	std::cout << "std: " << vStd2.size() << std::endl;
	for (int i = 0; i < vStd2.size(); i++) {
		EXPECT_EQ(v2.at(i), vStd2.at(i));
		std::cout << "my: i - " << i << " " << v2.at(i);
		std::cout << " std: i - " << i << " " << vStd2.at(i) << std::endl;
	}
	v2.erase(v2.begin() + 15);
	for (int i = 0; i < v2.size(); i++) {
		std::cout <<  "erase: i = " << i  << " - " << v2.at(i) << std::endl;
	}
	//-----------copy constructor----------
	ft::vector<int> std1(21, 42);
	ft::vector<int> my1(std1);
	for (int i = 0; i < my1.size(); i++)
		EXPECT_EQ(my1.at(i), std1.at(i));
	//-----------insert----------
	v2.printVector();
	std::cout << "size 0: " << v2.size() << " capacity: " << v2.capacity() << std::endl;
	v2.insert(v2.begin() + 5, 21);
	v2.printVector();
	std::cout << "size 1: " << v2.size() << " capacity: " << v2.capacity() << std::endl;
	v2.insert(v2.begin() + 5, 23, 42);
	v2.printVector();
	std::cout << "size 2: " << v2.size() << " capacity: " << v2.capacity() << std::endl;
	ft::vector<int> s(3, 15);
	v2.insert(v2.begin() + 20, s.begin() + 1, s.end());
	//----------assign----------
	v2.assign(12, 42);
	vStd2.assign(12, 42);
	for (int i = 0; i != vStd2.size(); i++) {
		EXPECT_EQ(v2.at(i), vStd2.at(i));
	}


}

int main(int argc, char **argv) {
//	ft::vector<int> myvector (3,100);
//	ft::vector<int>::iterator it;
//
//	it = myvector.begin();
//	it = myvector.insert ( it , 200 );
//
//	myvector.insert (it,2,300);
//
//	// "it" no longer valid, get a new one:
//	it = myvector.begin();
//
//	ft::vector<int> anothervector (2,400);
//	myvector.insert (it+2,anothervector.begin(),anothervector.end());
//
//	int myarray [] = { 501,502,503 };
//	myvector.insert (myvector.begin(), myarray, myarray+3);
//
//	std::cout << "myvector contains:";
//	for (it=myvector.begin(); it<myvector.end(); it++)
//		std::cout << ' ' << *it;
//	std::cout << '\n';
//
//	return 0;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

