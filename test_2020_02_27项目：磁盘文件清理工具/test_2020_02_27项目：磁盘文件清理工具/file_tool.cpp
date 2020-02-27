#pragma once
#include"file_tool.h"
#include<string>
#include<string.h>

//扫描目录下的所有文件
void scan_files(const std::string& subdir, std::unordered_set<std::string>& filesNameContainer)
{
	//要查找的文件是当前目录subir下的所有文件，所以用*.*，在这里find是支持通配符的
	std::string path = subdir + "\\" + "*.*";
	//文件结构体
	_finddata_t fileData;
	//文件句柄
	long handle = _findfirst(path.c_str(), &fileData);
	if (handle == -1)
	{
		perror("files scan failed!");
		std::cout << subdir << std::endl;
		return;
	}
	do
	{
		//如果是文件夹（目录）
		if (fileData.attrib & _A_SUBDIR)
		{
			//如果是当前目录或者上级目录，则跳过
			if (strcmp(fileData.name, "..") != 0 && strcmp(fileData.name, ".") != 0)
			{
				scan_files(subdir + "\\" + fileData.name, filesNameContainer);
			}
		}
		else
		{
				filesNameContainer.insert(subdir + "\\" + fileData.name);
		}
	} while (_findnext(handle,&fileData) == 0);
	_findclose(handle);
}

//删除指定文件
void delete_file(const std::string& filePath)
{
	if (remove(filePath.c_str()) == -1)
	{
		perror("remove failed!");
		return;
	}
	else
	{
		std::cout << filePath << "  delete success!" << std::endl;
	}
}