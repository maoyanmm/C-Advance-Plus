#pragma once
#include"file_manager.h"
#include"file_tool.h"

//扫描输入路径下的文件
void FileManager::scan_dir(const std::string& path)
{
	//扫描前，先将文件列表清空
	_files_list.clear();
	//将扫描到的文件存放到_files_list
	search_dir(path,_files_list);
	std::cout << "所有文件：" << std::endl << std::endl;
	showAllfile();
	//将文件和对应的md5存放
	get_MD5_to_file();
	std::cout << "整理后：" << std::endl << std::endl;
	showCopylist();
	get_copy_list();
	std::cout << "将相同内容的文件整理后：" << std::endl << std::endl;
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
//得到拷贝的文件列表，将单个的文件从文件列表剔除（不是删除文件）
void FileManager::get_copy_list()
{
	_fileTomd5.clear();
	//不能用范围for，因为下面涉及删除的操作，会导致迭代器失效
	auto it = _md5Tofile.begin();
	while (it != _md5Tofile.end())
	{
		//如果有相同的内容的文件
		if (_md5Tofile.count(it->first) > 1)
		{
			//得到这个相同的md5值的文件的范围
			auto pairIt = _md5Tofile.equal_range(it->first);
			auto begin = pairIt.first;
			//遍历MD5值相同的文件
			while (begin != pairIt.second)
			{
				//和下面的else对应，也就是最后两个map存储的东西一致
				_fileTomd5.insert(make_pair(begin->second, begin->first));
				++begin;
			}
			it = pairIt.second;
		}
		else
		{
			_files_list.erase(it->second);
			//如果是单个的就将它剔除
			it = _md5Tofile.erase(it);
		}
	}

}
//通过名字删除文件(删除和这个文件的内容相同的其他文件，这个文件不删除）
void FileManager::delete_by_name(const std::string& filename)
{

}
//通过MD5值删除文件(保留一个）
void FileManager::delete_by_MD5(const std::string& MD5num)
{
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "没有多余文件可以删除！" << std::endl;
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
	std::cout << "一共有" << count + 1 << "个MD5值为：" << MD5num << "的文件" << std::endl;
	std::cout << "一共删除了" << count << "个文件" << std::endl << std::endl;
}
//删除所有拷贝的文件
void FileManager::delete_all_copy()
{

}
//删除你指定名字的文件
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
		std::cout << "MD5值为：" << cur->first << " 的文件：" << std::endl;
		int index = 1;
		while (cur != pairIt.second)
		{
			std::cout << "第" << index++ << "个文件：" << cur->second << std::endl;
			++cur;
		}
		++it;
	}
	std::cout << "一共：" << total << "个文件" << std::endl << std::endl;

}
void FileManager::showAllfile()
{
	for (const auto& e : _files_list)
	{
		std::cout << e << std::endl;
	}
	int total = _files_list.size();
	std::cout << "一共：" << total << "个文件" << std::endl << std::endl;
}
void FileManager::showMD5map()
{

}