#include<iostream>
#include"project_MD5.h"
#include<vector>
#include"file_search.hpp"

void test_changeHex()
{
	MD5 md5;
	std::string str = md5.Hex_change_MD5(0x23456789);
	std::cout << str << std::endl;
}

void test_getStringMD5()
{
	MD5 md5;
	const std::string str1 = "123456789abcdefgh";
	const std::string str2 = "abcdee";
	std::cout << md5.getStringMD5(str1) << std::endl;
}

void test_getFileMD5()
{
	MD5 md5;
	const char* file1 = "MD5test1.txt";
	std::cout << md5.getFileMD5(file1) << std::endl;
	md5.reset();
}

void test_search_dir()
{
	std::string path;
	std::cout << "ÇëÊäÈëÄ¿Â¼£º" << std::endl;
	std::getline(std::cin, path);
	std::vector<std::string> subdir;
	search_dir(path, subdir);
	for (auto& e : subdir)
	{
		std::cout << e << std::endl;
	}
}

int main()
{
	/*test_changeHex();*/
	/*test_getStringMD5();*/
	/*test_getFileMD5();*/
	test_search_dir();
	system("pause");
	return 0;
}