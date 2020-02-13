#pragma once
#include<string>
#include<unordered_map>
#include<unordered_set>

class FileManager
{
public:
	//ɨ������·���µ��ļ�
	void scan_dir(const std::string& path);
	//ͨ������ɾ���ļ�
	void delete_by_name(const std::string& filename);
	//ͨ��MD5ֵɾ���ļ�
	void delete_by_MD5(const std::string& MD5num);
	//ɾ�����п������ļ�
	void delete_all_copy();
	//ɾ����ָ�����ֵ��ļ�
	void delete_by_match_name(const std::string& filename);

private:
	//���file->MD5ֵ
	std::unordered_map<std::string, std::string> fileTomd5;
	//���MD5ֵ->file
	std::unordered_set<std::string, std::string> md5Tofile;
};