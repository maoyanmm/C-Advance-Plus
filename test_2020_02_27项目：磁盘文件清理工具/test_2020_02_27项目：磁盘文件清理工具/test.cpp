#pragma once
#include<iostream>
#include"MD5.h"
#include"file_tool.h"

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

int main()
{
	test_delete_file();
	system("pause");
	return 0;
}