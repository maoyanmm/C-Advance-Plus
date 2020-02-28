#include"file_manager.h"

//扫盘
void FileManager::files_scanner(const std::string& subdir)
{
	scan_files(subdir, _filesName);
	to_MD5_to_File();
	show_copy();
}
//由filesName导入MD5toFile、FiletoMD5
void FileManager::to_MD5_to_File()
{
	for (auto& file : _filesName)
	{
		//先拿到该文件的MD5值
		std::string md5Tmp = _md5.cal_file_MD5(file.c_str());
		_FiletoMD5.insert(make_pair(file, md5Tmp));
		_md5.reset();
		_MD5toFile.insert(make_pair(md5Tmp, file));
		_md5.reset();
	}
}
//展示所有按MD5值归类好的文件
void FileManager::show_copy()
{
	std::cout << std::endl << "一共 [" << _filesName.size() << "] 个文件" << std::endl << std::endl;
	//先拿到第一个元素的MD5值
	auto begin = _MD5toFile.begin();
	while (begin != _MD5toFile.end())
	{
		//得到MD5值为begin->first的元素的范围
		auto pairIt = _MD5toFile.equal_range(begin->first);
		auto start = pairIt.first;
		auto finish = pairIt.second;
		std::cout << "MD5值为：" << start->first << " 的文件有：" << std::endl;
		int index = 1;
		for (; start != finish; ++start)
		{
			std::cout << "第 [" << index++ << "] 个文件：" << std::endl << start->second << std::endl;
		}
		begin = finish;
	}
	std::cout << std::endl;
}
//展示所有文件
void FileManager::show_files()
{
	std::cout << "所有文件： " << std::endl;
	for (auto& file : _filesName)
	{
		std::cout << file << std::endl;
	}
	std::cout << std::endl << "一共 [" << _filesName.size() << "] 个文件" << std::endl;
}
//删除所有拷贝文件（保留一份）
void FileManager::delete_all_copy()
{
	std::unordered_multimap<std::string, std::string> tmp_MD5toFile = _MD5toFile;
	auto begin = tmp_MD5toFile.begin();
	while (begin != tmp_MD5toFile.end())
	{
		auto pairIt = tmp_MD5toFile.equal_range(begin->first);
		auto start = pairIt.first;
		auto finish = pairIt.second;
		++start;
		for (; start != finish; ++start)
		{
			delete_file_for_name(start->second);
		}
		begin = finish;
	}
}
//删除指定文件
void FileManager::delete_file_for_name(const std::string& fileName)
{
	delete_file(fileName);
	_filesName.erase(fileName);
	_FiletoMD5.erase(fileName);
	auto cur = _MD5toFile.begin();
	for (; cur != _MD5toFile.end(); ++cur)
	{
		if (strcmp(cur->second.c_str(), fileName.c_str()) == 0)
		{
			_MD5toFile.erase(cur);
			break;
		}
	}
}

//查找文件是否存在
bool FileManager::search_file(const std::string& fileName)
{
	auto& begin = _filesName.begin();
	for (; begin != _filesName.end(); ++begin)
	{
		if (strcmp(begin->c_str(), fileName.c_str()) == 0)
		{
			break;
		}
	}
	if (begin == _filesName.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

//删除指定文件的副本
void FileManager::delete_copy_file_for_name(const std::string& fileName)
{
	if (!search_file(fileName))
	{
		std::cout << "没有该文件： " << fileName << std::endl;
		return;
	}

}

//删除模糊文件名的文件
void FileManager::delete_misty_file_for_name(const std::string& mistyFileName)
{

}

