#pragma once
#include<io.h>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>

void search_dir(const std::string& path, std::unordered_set<std::string>& subdir);

void delete_file(const char* fileName);