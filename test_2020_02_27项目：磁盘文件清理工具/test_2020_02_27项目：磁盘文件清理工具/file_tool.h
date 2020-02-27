#pragma once
#include<iostream>
#include<unordered_set>
#include<io.h>

//扫描目录下的所有文件
void scan_files(const std::string& subdir, std::unordered_set<std::string>& filesNameContainer);

//删除指定文件
void delete_file(const std::string& filePath);