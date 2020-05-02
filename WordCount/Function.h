#pragma once
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <io.h>
void AllDetail(char* Path);   //显示空行， 代码行，注释行
int CodeCount(char* Path);	  //计算字符个数
void CountWordsFrequency(char* path);
int LineCount(char* Path);    //计算行数
void Run(char* path[100], char* command[20], char* result);
char** ScanCommand(int length, char** parameter);
int WordCount(char* Path);
char** ScanPath(int length, char** parameter);
void writeToFile(char* result);

