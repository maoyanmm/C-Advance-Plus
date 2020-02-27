#pragma once
#include"file_tool.h"
#include"MD5.h"
#include<unordered_map>

class FileManager
{
public:
	//ɨ��
	void files_scanner(const std::string& subdir);
	//��filesName����MD5toFile��FiletoMD5
	void to_MD5_to_File();
	//չʾ���п����ļ�
	void show_copy();
	//չʾ�����ļ�
	void show_copy();
	//ɾ�����п����ļ�
	void delete_all_copy();
	//ɾ��ָ���ļ�
	void delete_file_for_name(const std::string& fileName);
	//ɾ��ģ���ļ������ļ�
	void delete_misty_file_for_name(const std::string& mistyFileName);
	
private:
	std::unordered_set<std::string> filesName;
	std::unordered_map<std::string, std::string> MD5toFile;
	std::unordered_map<std::string, std::string> FiletoMD5;
};