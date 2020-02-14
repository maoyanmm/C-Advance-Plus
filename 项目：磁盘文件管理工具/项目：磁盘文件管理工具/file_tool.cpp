#pragma once
#include"file_tool.h"

void search_dir(const std::string& path, std::unordered_set<std::string>& subdir)
{
	std::string matchFile = path + "\\" + "*.*";//*.*是通配符
	_finddata_t fileAttr;//文件属性
	long handle = _findfirst(matchFile.c_str(), &fileAttr);//将句柄记录下来
	if (-1 == handle)//如果没找到，0是找到
	{
		perror("No such a file or directory!");
		std::cout << matchFile << std::endl;
		return;
	}
	do
	{
		if (fileAttr.attrib & _A_SUBDIR)//说明是目录，则进去继续搜索
		{
			//这一步是为了防止递归的寻找当前的目录和上级目录
			if (strcmp(fileAttr.name, ".") != 0 && strcmp(fileAttr.name, "..") != 0)
			{
				search_dir(path + "\\" + fileAttr.name, subdir);
			}
		}
		else
		{
			subdir.insert(path + "\\" + fileAttr.name);//将这个文件名放进数组里
		}
	} while (_findnext(handle, &fileAttr) == 0);
	_findclose(handle);
}

void delete_file(const char* fileName)
{
	if (remove(fileName) == -1)
	{
		perror("file delete failed!");
	}
	else
	{
		std::cout << "delete file:" << fileName << "success!" << std::endl;
	}
}