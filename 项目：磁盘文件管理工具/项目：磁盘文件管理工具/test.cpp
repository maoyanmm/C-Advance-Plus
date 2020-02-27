#pragma once
#include<iostream>
#include"project_MD5.h"
#include<vector>
#include"file_tool.h"
#include"file_manager.h"
#include"APP¡ªfile_manager.h"

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
	const char* file1 = "MD5test2.txt";
	std::cout << md5.getFileMD5(file1) << std::endl;
}

//void test_search_dir()
//{
//	std::string path;
//	std::cout << "ÇëÊäÈëÄ¿Â¼£º" << std::endl;
//	std::getline(std::cin, path);
//	std::unordered_set<std::string> subdir;
//	search_dir(path, subdir,allFilesName);
//	for (auto& e : subdir)
//	{
//		std::cout << e << std::endl;
//	}
//}

void test_scan_dir()
{
	FileManager fm;
	fm.scan_dir(".");
}

void test_APP¡ªfile_manager()
{
	file_app fm;
	fm.menu();
}

int main()
{
	/*test_changeHex();*/
	/*test_getStringMD5();*/
	/*test_getFileMD5();*/
	/*test_search_dir();*/
	/*test_scan_dir();*/
	test_getFileMD5();
	/*test_APP¡ªfile_manager();*/
	system("pause");
	return 0;
}