#include"file_manager.h"

//ɨ��
void FileManager::files_scanner(const std::string& subdir)
{
	scan_files(subdir, _filesName);
	to_MD5_to_File();
	show_copy();
}
//��filesName����MD5toFile��FiletoMD5
void FileManager::to_MD5_to_File()
{
	for (auto& file : _filesName)
	{
		//���õ����ļ���MD5ֵ
		std::string md5Tmp = _md5.cal_file_MD5(file.c_str());
		_FiletoMD5.insert(make_pair(file, md5Tmp));
		_md5.reset();
		_MD5toFile.insert(make_pair(md5Tmp, file));
		_md5.reset();
	}
}
//չʾ���а�MD5ֵ����õ��ļ�
void FileManager::show_copy()
{
	std::cout << std::endl << "һ�� [" << _filesName.size() << "] ���ļ�" << std::endl << std::endl;
	//���õ���һ��Ԫ�ص�MD5ֵ
	auto begin = _MD5toFile.begin();
	while (begin != _MD5toFile.end())
	{
		//�õ�MD5ֵΪbegin->first��Ԫ�صķ�Χ
		auto pairIt = _MD5toFile.equal_range(begin->first);
		auto start = pairIt.first;
		auto finish = pairIt.second;
		std::cout << "MD5ֵΪ��" << start->first << " ���ļ��У�" << std::endl;
		int index = 1;
		for (; start != finish; ++start)
		{
			std::cout << "�� [" << index++ << "] ���ļ���" << std::endl << start->second << std::endl;
		}
		begin = finish;
	}
	std::cout << std::endl;
}
//չʾ�����ļ�
void FileManager::show_files()
{
	std::cout << "�����ļ��� " << std::endl;
	for (auto& file : _filesName)
	{
		std::cout << file << std::endl;
	}
	std::cout << std::endl << "һ�� [" << _filesName.size() << "] ���ļ�" << std::endl;
}
//ɾ�����п����ļ�������һ�ݣ�
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
//ɾ��ָ���ļ�
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

//�����ļ��Ƿ����
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

//ɾ��ָ���ļ��ĸ���
void FileManager::delete_copy_file_for_name(const std::string& fileName)
{
	if (!search_file(fileName))
	{
		std::cout << "û�и��ļ��� " << fileName << std::endl;
		return;
	}

}

//ɾ��ģ���ļ������ļ�
void FileManager::delete_misty_file_for_name(const std::string& mistyFileName)
{

}

