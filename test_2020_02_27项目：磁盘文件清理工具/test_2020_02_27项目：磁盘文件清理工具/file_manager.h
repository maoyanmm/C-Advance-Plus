#pragma once
#include"file_tool.h"
#include"MD5.h"
#include<unordered_map>

class FileManager
{
public:
	//扫盘
	void files_scanner(const std::string& subdir);
	//由filesName导入MD5toFile、FiletoMD5
	void to_MD5_to_File();
	//展示所有拷贝文件
	void show_copy();
	//展示所有文件
	void show_files();
	//删除所有拷贝文件（保留一份）
	void delete_all_copy();
	//删除指定文件
	void delete_file_for_name(const std::string& fileName);
	//删除指定文件的副本
	void delete_copy_file_for_name(const std::string& fileName);
	//删除模糊文件名的文件
	void delete_misty_file_for_name(const std::string& mistyFileName);
	//查找文件是否存在
	bool search_file(const std::string& fileName);
	
private:
	std::unordered_set<std::string> _filesName;
	std::unordered_multimap<std::string, std::string> _MD5toFile;
	std::unordered_map<std::string, std::string> _FiletoMD5;
	MD5 _md5;
};