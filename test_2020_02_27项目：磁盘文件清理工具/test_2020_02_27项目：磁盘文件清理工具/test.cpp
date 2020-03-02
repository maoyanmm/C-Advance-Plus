#pragma once
#include<iostream>
#include"MD5.h"
#include"file_tool.h"
#include"file_manager.h"

void test_Hex_to_MD5()
{
	MD5 md5;
	std::cout << md5.to_Hex_MD5(0x12345678) << std::endl;
}

void test_cal_file_MD5()
{
	MD5 md5;
	const char* file = "MD5test2.txt";
	std::cout << md5.cal_file_MD5(file) << std::endl;
}

void test_scan_files()
{
	std::unordered_set<std::string> fileNameContainer;
	std::string path = "F:\\Visual studio 2013���\\�����ļ�\\test_2020_02_27��Ŀ�������ļ�������\\test_2020_02_27��Ŀ�������ļ�������";
	scan_files(path, fileNameContainer);
	std::cout << "�ļ���С��" << fileNameContainer.size() << std::endl << std::endl;
	for (auto& e : fileNameContainer)
	{
		std::cout << e << std::endl;
	}
}

void test_delete_file()
{
	delete_file("F:\\Visual studio 2013���\\�����ļ�\\test_2020_02_27��Ŀ�������ļ�������\\test_2020_02_27��Ŀ�������ļ�������\\MD5test2.txt");
}

void test_files_scanner()
{
	FileManager fm;
	std::string path = "F:\\������Ե��ļ���";
	fm.files_scanner(path);
}

void test_delete_file_for_name()
{
	FileManager fm;
	std::string name = ".\\MD5test3.txt";
	fm.delete_file_for_name(name);
}

void test_delete_all_copy()
{
	FileManager fm;
	std::string path = "F:\\������Ե��ļ���";
	fm.files_scanner(path);
	fm.delete_all_copy();
}

int main()
{
	system("pause");
	return 0;
}