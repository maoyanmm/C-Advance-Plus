#pragma once
#include"file_tool.h"
#include<string>
#include<string.h>

//ɨ��Ŀ¼�µ������ļ�
void scan_files(const std::string& subdir, std::unordered_set<std::string>& filesNameContainer)
{
	//Ҫ���ҵ��ļ��ǵ�ǰĿ¼subir�µ������ļ���������*.*��������find��֧��ͨ�����
	std::string path = subdir + "\\" + "*.*";
	//�ļ��ṹ��
	_finddata_t fileData;
	//�ļ����
	long handle = _findfirst(path.c_str(), &fileData);
	if (handle == -1)
	{
		perror("files scan failed!");
		std::cout << subdir << std::endl;
		return;
	}
	do
	{
		//������ļ��У�Ŀ¼��
		if (fileData.attrib & _A_SUBDIR)
		{
			//����ǵ�ǰĿ¼�����ϼ�Ŀ¼��������
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

//ɾ��ָ���ļ�
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