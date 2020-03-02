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
	void show_files();
	//ɾ�����п����ļ�������һ�ݣ�
	void delete_all_copy();
	//ɾ��ָ���ļ�
	void delete_file_for_name(const std::string& fileName);
	//ɾ��ָ���ļ��ĸ���
	void delete_copy_file_for_name(const std::string& fileName);
	//ɾ��ģ���ļ������ļ�
	void delete_misty_file_for_name(const std::string& mistyFileName);
	//�����ļ��Ƿ����
	bool search_file(const std::string& fileName);
	
private:
	std::unordered_set<std::string> _filesName;
	std::unordered_multimap<std::string, std::string> _MD5toFile;
	std::unordered_map<std::string, std::string> _FiletoMD5;
	MD5 _md5;
};