#pragma once
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <io.h>
void AllDetail(char* Path);    // ��ʾ���У� �����У�ע����
int CharacterCount(char* Path);	  // �����ַ�����
int LineCount(char* Path);    // ��������
void Run(char* path[100], char* command[20], char* result);    // ��������
void ScanCommand(int length, char** parameter, char**& command);    // ��ȡ����
int WordCount(char* Path);    // ����ͳ��
char** ScanPath(int length, char** parameter, char**& path);    // ��ȡ�ļ�
void WriteToFile(char* result);    // ������ļ� 

