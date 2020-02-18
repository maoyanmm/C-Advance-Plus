#pragma once
#include<io.h>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>

//扫描该路径下的所有文件
void search_dir(const std::string& path, std::unordered_set<std::string>& subdir);

//删除指定文件
void delete_file(const char* fileName);