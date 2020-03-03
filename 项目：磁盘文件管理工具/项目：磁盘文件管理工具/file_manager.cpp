#pragma once
#include"file_manager.h"
#include"file_tool.h"
#include<time.h>


//ɨ������·���µ��ļ�
void FileManager::scan_dir(const std::string& path)
{
	clock_t start, stop;
	double duration;
	//ɨ��ǰ���Ƚ��ļ��б����
	_files_list.clear();
	//��ɨ�赽���ļ���ŵ�_files_list
	search_dir(path,_files_list);
	std::cout << "�����ļ���" << std::endl << std::endl;
	start = clock();
	showAllfile();
	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$��ʱ��     " << duration << std::endl;
	//���ļ��Ͷ�Ӧ��md5���
	start = clock();
	get_MD5_to_file();
	std::cout << "�����" << std::endl << std::endl;
	showCopylist();
	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$��ʱ��     " << duration << std::endl;
}
void FileManager::get_MD5_to_file()
{
	_md5Tofile.clear();
	_fileTomd5.clear();
	for (const auto& e : _files_list)
	{
		_md5.reset();
		_md5Tofile.insert(make_pair(_md5.getFileMD5(e.c_str()), e));
		_md5.reset();
		_fileTomd5.insert(make_pair(e, _md5.getFileMD5(e.c_str())));
	}

}

void FileManager::delete_by_name(const std::string& filename)
{
	std::string MD5num = _fileTomd5[filename];
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "û�ж�����ļ�����ɾ����" << std::endl;
		return;
	}
	auto pairIt = _md5Tofile.equal_range(MD5num);
	auto begain = pairIt.first;
	//��Ҫɾ�����ļ�����
	int count = _md5Tofile.count(MD5num)-1;
	while (begain != pairIt.second)
	{
		if (begain->second != filename)
		{
			_fileTomd5.erase(begain->second);
			_files_list.erase(begain->second);
			delete_file(begain->second.c_str());
			_md5Tofile.erase(begain);
			pairIt = _md5Tofile.equal_range(MD5num);
			begain = pairIt.first;
		}
		else
		{
			++begain;
		}
	}
	std::cout << "һ����" << count + 1 << "����" << filename << "������ͬ���ļ�" << std::endl;
	std::cout << "һ��ɾ����" << count << "���ļ�" << std::endl << std::endl;
}
//ͨ��MD5ֵɾ���ļ�(����һ����
void FileManager::delete_by_MD5(const std::string& MD5num)
{
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "û�ж����ļ�����ɾ����" << std::endl;
		return;
	}
	//�õ�������ͬ���ļ��ķ�Χ
	auto pairIt = _md5Tofile.equal_range(MD5num);
	auto begin = pairIt.first;
	//ȡ��һ������һ����ɾ������һ��
	++begin;
    //��Ҫɾ��������
	int count = _md5Tofile.count(MD5num) - 1;
	while (begin != pairIt.second)
	{
		_files_list.erase(begin->second);
		_fileTomd5.erase(begin->second);
		delete_file(begin->second.c_str());
		++begin;
	}
	begin = pairIt.first;
	++begin;
	//_md5Tofile���ں���ɾ������Ϊ���������һ����ɾ���ᵼ�µ�����ʧЧ
	_md5Tofile.erase(begin, pairIt.second);
	std::cout << "һ����" << count + 1 << "��MD5ֵΪ��" << MD5num << "���ļ�" << std::endl;
	std::cout << "һ��ɾ����" << count << "���ļ�" << std::endl << std::endl;
}
void FileManager::delete_by_MD5_lv2(const std::string& MD5num)
{
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "û�ж����ļ�����ɾ����" << std::endl;
		return;
	}
	auto it = _md5Tofile.find(MD5num);
	delete_by_name(it->second);
}

//ɾ�����п������ļ�
void FileManager::delete_all_copy()
{
	std::unordered_set<std::string> tmp;
	//�����е�MD5��¼���������ظ���
	for (const auto& e:_md5Tofile)
	{
		tmp.insert(e.first);
	}
	//����ÿ����ͬMD5ֵ���ļ���ɾ�����ᱣ��һ����
	for (const auto& e:tmp)
	{
		delete_by_MD5_lv2(e);
	}
}
//ģ��ɾ����ɾ��������İ��������ַ������ļ��ĸ���
void FileManager::delete_by_match_name(const std::string& filename)
{
	std::unordered_set<std::string> allMatchfile;
	for (const auto& e : _files_list)
	{
		//�������ģ����ƥ�䵽���ʹ������
		if (e.find(filename) != std::string::npos)
		{
			allMatchfile.insert(e);
		}
	}
	for (const auto& e : allMatchfile)
	{
		if (_files_list.count(e) != 0)
		{
			delete_by_name(e);
		}
	}
}

//��ӡ�и������ļ�
void FileManager::showCopylist()
{
	int total = _md5Tofile.size();
	std::unordered_set<std::string> md5Container;
	for (const auto& e : _md5Tofile)
	{
		md5Container.insert(e.first);
	}
	auto it = md5Container.begin();
	while (it != md5Container.end())
	{
		auto pairIt = _md5Tofile.equal_range(*it);
		auto begain = pairIt.first;
		int index = 1;
		std::cout << "MD5ֵΪ��" << begain->first << " ���ļ���" << std::endl;
		while (begain != pairIt.second)
		{
			std::cout << "��" << index++ << "���ļ���" << begain->second << std::endl;
			++begain;
		}
		++it;
	}
	std::cout << "һ����" << total << "���ļ�" << std::endl << std::endl;
}

void FileManager::showAllfile()
{
	for (const auto& e : _files_list)
	{
		std::cout << e<< std::endl;
	}
	int total = _files_list.size();
	std::cout << "һ����" << total << "���ļ�" << std::endl << std::endl;
}