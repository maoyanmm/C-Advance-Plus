#pragma once
#include<iostream>
#include<unordered_set>
#include<io.h>

//ɨ��Ŀ¼�µ������ļ�
void scan_files(const std::string& subdir, std::unordered_set<std::string>& filesNameContainer);

//ɾ��ָ���ļ�
void delete_file(const std::string& filePath);