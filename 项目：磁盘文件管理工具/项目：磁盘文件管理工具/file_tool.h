#pragma once
#include<io.h>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>

//ɨ���·���µ������ļ�
void search_dir(const std::string& path, std::unordered_set<std::string>& subdir);

//ɾ��ָ���ļ�
void delete_file(const char* fileName);