#pragma once
#include"file_tool.h"

void search_dir(const std::string& path, std::unordered_set<std::string>& subdir)
{
	std::string matchFile = path + "\\" + "*.*";//*.*��ͨ���
	_finddata_t fileAttr;//�ļ�����
	long handle = _findfirst(matchFile.c_str(), &fileAttr);//�������¼����
	if (-1 == handle)//���û�ҵ���0���ҵ�
	{
		perror("No such a file or directory!");
		std::cout << matchFile << std::endl;
		return;
	}
	do
	{
		if (fileAttr.attrib & _A_SUBDIR)//˵����Ŀ¼�����ȥ��������
		{
			//��һ����Ϊ�˷�ֹ�ݹ��Ѱ�ҵ�ǰ��Ŀ¼���ϼ�Ŀ¼
			if (strcmp(fileAttr.name, ".") != 0 && strcmp(fileAttr.name, "..") != 0)
			{
				search_dir(path + "\\" + fileAttr.name, subdir);
			}
		}
		else
		{
			subdir.insert(path + "\\" + fileAttr.name);//������ļ����Ž�������
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