#pragma once
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <io.h>
void AllDetail(char* Path);    // 显示空行， 代码行，注释行
int CharacterCount(char* Path);	  // 计算字符个数
int LineCount(char* Path);    // 计算行数
void Run(char* path[100], char* command[20], char* result);    // 运行命令
void ScanCommand(int length, char** parameter, char**& command);    // 获取命令
int WordCount(char* Path);    // 单词统计
char** ScanPath(int length, char** parameter, char**& path);    // 获取文件
void WriteToFile(char* result);    // 输出到文件 

