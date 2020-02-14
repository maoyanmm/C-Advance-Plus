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
	//get_copy_list();
	//std::cout << "将相同内容的文件整理后：" << std::endl << std::endl;
	//showCopylist();
}
void FileManager::get_MD5_to_file()
{
	_md5Tofile.clear();
	for (const auto& e : _files_list)
	{
		_md5.reset();
		_md5Tofile.insert(make_pair(_md5.getFileMD5(e.c_str()), e));
		_fileTomd5.insert(make_pair(e, _md5.getFileMD5(e.c_str())));
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
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << _md5Tofile.size() << _fileTomd5.size() << _files_list.size() << std::endl;
	std::string MD5num = _fileTomd5[filename];
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "没有多余的文件可以删除！" << std::endl;
		return;
	}
	auto pairIt = _md5Tofile.equal_range(MD5num);
	auto begain = pairIt.first;
	//需要删除的文件数量
	int count = _md5Tofile.count(MD5num)-1;//1000
	while (begain != pairIt.second)
	{
		if (begain->second != filename)
		{
			_fileTomd5.erase(begain->second);
			_files_list.erase(begain->second);
			_md5Tofile.erase(begain);
			pairIt = _md5Tofile.equal_range(MD5num);
			begain = pairIt.first;
		}
		else
		{
			++begain;
		}
	}
	std::cout << "一共有" << count + 1 << "个和" << filename << "内容相同的文件" << std::endl;
	std::cout << "一共删除了" << count << "个文件" << std::endl << std::endl;
}
//通过MD5值删除文件(保留一个）
void FileManager::delete_by_MD5(const std::string& MD5num)
{
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "没有多余文件可以删除！" << std::endl;
		return;
	}
	//得到内容相同的文件的范围
	auto pairIt = _md5Tofile.equal_range(MD5num);
	auto begin = pairIt.first;
	//取下一个，第一个不删除，留一个
	++begin;
    //需要删除的数量
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
	//_md5Tofile放在后面删除：因为如果在上面一个个删除会导致迭代器失效
	_md5Tofile.erase(begin, pairIt.second);
	std::cout << "一共有" << count + 1 << "个MD5值为：" << MD5num << "的文件" << std::endl;
	std::cout << "一共删除了" << count << "个文件" << std::endl << std::endl;
}
void FileManager::delete_by_MD5_lv2(const std::string& MD5num)
{
	if (_md5Tofile.count(MD5num) <= 1)
	{
		std::cout << "没有多余文件可以删除！" << std::endl;
		return;
	}
	auto it = _md5Tofile.find(MD5num);
	delete_by_name(it->second);
}

//删除所有拷贝的文件
void FileManager::delete_all_copy()
{
	std::unordered_set<std::string> tmp;
	//将所有的MD5记录下来（不重复）
	for (const auto& e:_md5Tofile)
	{
		tmp.insert(e.first);
	}
	//按照每个不同MD5值的文件来删除（会保留一个）
	for (const auto& e:tmp)
	{
		delete_by_MD5(e);
	}
}
//模糊删除：删除你输入的包含部分字符串的文件的副本
void FileManager::delete_by_match_name(const std::string& filename)
{
	std::unordered_set<std::string> allMatchfile;
	for (const auto& e : _files_list)
	{
		//如果可以模糊的匹配到，就存放起来
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

//打印有副本的文件
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
		std::cout << "MD5值为：" << begain->first << " 的文件：" << std::endl;
		while (begain != pairIt.second)
		{
			std::cout << "第" << index++ << "个文件：" << begain->second << std::endl;
			++begain;
		}
		++it;
	}
	std::cout << "一共：" << total << "个文件" << std::endl << std::endl;
}

void FileManager::showAllfile()
{
	for (const auto& e : _files_list)
	{
		std::cout << e<< std::endl;
	}
	int total = _files_list.size();
	std::cout << "一共：" << total << "个文件" << std::endl << std::endl;
}