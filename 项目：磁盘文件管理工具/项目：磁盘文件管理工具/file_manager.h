#pragma once
#include<string>
#include<unordered_map>
#include<unordered_set>

class FileManager
{
public:
	//扫描输入路径下的文件
	void scan_dir(const std::string& path);
	//通过名字删除文件
	void delete_by_name(const std::string& filename);
	//通过MD5值删除文件
	void delete_by_MD5(const std::string& MD5num);
	//删除所有拷贝的文件
	void delete_all_copy();
	//删除你指定名字的文件
	void delete_by_match_name(const std::string& filename);

private:
	//存放file->MD5值
	std::unordered_map<std::string, std::string> fileTomd5;
	//存放MD5值->file
	std::unordered_set<std::string, std::string> md5Tofile;
};