#pragma once
#include<string>
#include<unordered_map>
#include<unordered_set>
#include"project_MD5.h"

class FileManager
{
public:
	//ɨ������·���µ��ļ�
	void scan_dir(const std::string& path);
	void get_MD5_to_file();
	//�õ��������ļ��б�
	void get_copy_list();
	//ͨ������ɾ���ļ�
	void delete_by_name(const std::string& filename);
	//ͨ��MD5ֵɾ���ļ�
	void delete_by_MD5(const std::string& MD5num);
	void delete_by_MD5_lv2(const std::string& MD5num);
	//ɾ�����п������ļ�
	void delete_all_copy();
	//ɾ����ָ�����ֵ��ļ�
	void delete_by_match_name(const std::string& filename);

	void showCopylist();
	void showAllfile();
private:
	std::unordered_set<std::string> _files_list;
	//���file->MD5ֵ
	std::unordered_map<std::string, std::string> _fileTomd5;
	//���MD5ֵ->file
	std::unordered_multimap<std::string, std::string> _md5Tofile;
	MD5 _md5;
};