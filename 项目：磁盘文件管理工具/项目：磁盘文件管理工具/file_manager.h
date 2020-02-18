#pragma once
#include<string>
#include<unordered_map>
#include<unordered_set>
#include"project_MD5.h"

class FileManager
{
public:
	//扫描输入路径下的文件
	void scan_dir(const std::string& path);
	//将文件与MD5存入多个关联式容器
	void get_MD5_to_file();
	//得到拷贝的文件列表
	void get_copy_list();
	//通过文件名删除文件
	void delete_by_name(const std::string& filename);
	//通过MD5值删除文件
	void delete_by_MD5(const std::string& MD5num);
	void delete_by_MD5_lv2(const std::string& MD5num);
	//删除所有拷贝的文件
	void delete_all_copy();
	//删除模糊匹配文件名的文件
	void delete_by_match_name(const std::string& filename);

	void showCopylist();
	void showAllfile();
private:
	std::unordered_set<std::string> _files_list;
	//存放file->MD5值
	std::unordered_map<std::string, std::string> _fileTomd5;
	//存放MD5值->file
	std::unordered_multimap<std::string, std::string> _md5Tofile;
	MD5 _md5;
};