#pragma once
#include"file_manager.h"
#include"file_tool.h"

//ɨ������·���µ��ļ�
void FileManager::scan_dir(const std::string& path)
{
	//ɨ��ǰ���Ƚ��ļ��б����
	_files_list.clear();
	//��ɨ�赽���ļ���ŵ�_files_list
	search_dir(path,_files_list);
	std::cout << "�����ļ���" << std::endl << std::endl;
	showAllfile();
	//���ļ��Ͷ�Ӧ��md5���
	get_MD5_to_file();
	std::cout << "�����" << std::endl << std::endl;
	showCopylist();
	get_copy_list();
	std::cout << "����ͬ���ݵ��ļ������" << std::endl << std::endl;
	showCopylist();
}
void FileManager::get_MD5_to_file()
{
	_md5Tofile.clear();
	for (const auto& e : _files_list)
	{
		_md5.reset();
		_md5Tofile.insert(make_pair(_md5.getFileMD5(e.c_str()), e));
	}

}
//�õ��������ļ��б����������ļ����ļ��б��޳�������ɾ���ļ���
void FileManager::get_copy_list()
{
	_fileTomd5.clear();
	//�����÷�Χfor����Ϊ�����漰ɾ���Ĳ������ᵼ�µ�����ʧЧ
	auto it = _md5Tofile.begin();
	while (it != _md5Tofile.end())
	{
		//�������ͬ�����ݵ��ļ�
		if (_md5Tofile.count(it->first) > 1)
		{
			//�õ������ͬ��md5ֵ���ļ��ķ�Χ
			auto pairIt = _md5Tofile.equal_range(it->first);
			auto begin = pairIt.first;
			//����MD5ֵ��ͬ���ļ�
			while (begin != pairIt.second)
			{
				//�������else��Ӧ��Ҳ�����������map�洢�Ķ���һ��
				_fileTomd5.insert(make_pair(begin->second, begin->first));
				++begin;
			}
			it = pairIt.second;
		}
		else
		{
			_files_list.erase(it->second);
			//����ǵ����ľͽ����޳�
			it = _md5Tofile.erase(it);
		}
	}

}
//ͨ������ɾ���ļ�(ɾ��������ļ���������ͬ�������ļ�������ļ���ɾ����
void FileManager::delete_by_name(const std::string& filename)
{

}
//ͨ��MD5ֵɾ���ļ�(����һ����
void FileManager::delete_by_MD5(const std::string& MD5num)
{
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "û�ж����ļ�����ɾ����" << std::endl;
		return;
	}
	auto pairIt = _md5Tofile.equal_range(MD5num);
	auto begin = pairIt.first;
	++begin;
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
	_md5Tofile.erase(begin, pairIt.second);
	std::cout << "һ����" << count + 1 << "��MD5ֵΪ��" << MD5num << "���ļ�" << std::endl;
	std::cout << "һ��ɾ����" << count << "���ļ�" << std::endl << std::endl;
}
//ɾ�����п������ļ�
void FileManager::delete_all_copy()
{

}
//ɾ����ָ�����ֵ��ļ�
void FileManager::delete_by_match_name(const std::string& filename)
{

}

void FileManager::showCopylist()
{
	auto it = _md5Tofile.begin();
	int total = _md5Tofile.size();
	while (it != _md5Tofile.end())
	{
		auto pairIt = _md5Tofile.equal_range(it->first);
		auto cur = pairIt.first;
		std::cout << "MD5ֵΪ��" << cur->first << " ���ļ���" << std::endl;
		int index = 1;
		while (cur != pairIt.second)
		{
			std::cout << "��" << index++ << "���ļ���" << cur->second << std::endl;
			++cur;
		}
		++it;
	}
	std::cout << "һ����" << total << "���ļ�" << std::endl << std::endl;

}
void FileManager::showAllfile()
{
	for (const auto& e : _files_list)
	{
		std::cout << e << std::endl;
	}
	int total = _files_list.size();
	std::cout << "һ����" << total << "���ļ�" << std::endl << std::endl;
}
void FileManager::showMD5map()
{

}