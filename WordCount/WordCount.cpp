#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <io.h>


struct words   //单词结构体
{
	char word[40];
	int count;
};

void CountWordsFrequency(char* path)
{
	// 修改动态分布内存的链表可解决越界问题
	struct words word[1000] = { 0 }, stmp = { 0 };
	int i = 0, j = 0, k = 0, flag = 0;
	char c, tmp[40] = { 0 };
	FILE* fp = NULL;
	errno_t er = fopen_s(&fp,path, "r"); 
	assert(fp != NULL);
	//读文件解析成单词
	while ((c = fgetc(fp)) != EOF)
	{
		//这些符号分割的都认为是一个单词结束
		if (c <= 'Z' && c >= 'A' || c >= 'a' && c <= 'z' || c == '-' && j != 0)
		{
			tmp[j++] = (c >= 'A' && c <= 'Z') ? c + 32 : c; //全转成小写 就可以无视大小写统计了
		}
		else
		{
			tmp[j] = '\0';
			j = 0;
			flag = 0;
			//判断单词是否已经记录 如果已有则使用率加1
			for (k = 0; k < i; k++)
			{
				if (strcmp(tmp, word[k].word) == 0)
				{
					word[k].count++;
					flag = 1;
					break;
				}
			}
			//没有则存入单词结构体数组保存
			if (!flag)
			{
				strcpy_s(word[i].word, tmp);
				word[i].count++;
				i++;
			}
		}
	}
	fclose(fp);
	//使用率排序
	for (j = 0; j < i; j++)
	{
		for (k = 0; k < i - j - 1; k++)
		{
			if (word[k].count > word[k + 1].count)
			{
				stmp = word[k];
				word[k] = word[k + 1];
				word[k + 1] = stmp;
			}
		}
	}
	//输出排序后的频度前四单词
	for (k = 0; k < 3; k++)
	{
		printf("[%s][%d]\n", word[k].word, word[k].count);
	}
}

int CodeCount(char* Path) {    //计算字符个数

	FILE* file = NULL;
	errno_t er =  fopen_s(&file,Path, "r");
	assert(file != NULL);    //若文件不存在则报错

	char code;
	int count = 0;

	while ((code = fgetc(file)) != EOF)     //读取字符直到结束
		count += ((code != ' ') && (code != '\n') && (code != '\t'));    //判断是否是字符    

	fclose(file);

	return count;
}

int WordCount(char* Path) {    //计算单词个数
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char word;
	int is_word = 0;    //用于记录字符是否处于单词中
	int count = 0;

	while ((word = fgetc(file)) != EOF) {
		if ((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z')) {    //判断是否是字母            
			count += (is_word == 0);
			is_word = 1;    //记录单词状态
		}
		else
			is_word = 0;    //记录不处于单词状态
	}
	fclose(file);

	return count;
}

int LineCount(char* Path) {    //计算行数
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char* s = (char*)malloc(200 * sizeof(char));
	int count = 0;

	for (; fgets(s, 200, file) != NULL; count++);    //逐次读行

	free(s);
	fclose(file);

	return count;
}

void AllDetail(char* Path) {    //显示空行， 代码行，注释行
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char* s = (char*)malloc(200 * sizeof(char));//申请空间
	int i;
	int is_codeline = 0;    //状态记录变量
	int is_annoline = 0;
	int AnnoLock = 0;
	int AnnoFileLock = 0;

	int codecount = 0;
	int annocount = 0;
	int blankcount = 0;

	while (fgets(s, 200, file) != NULL) {    //逐次取文件中的行
		for (i = 0; *(s + i) != '\0'; i++) {

			if (((*(s + i) >= 'a' && *(s + i) <= 'z') || (*(s + i) >= 'A' && *(s + i) <= 'Z')) && AnnoFileLock == 0) {//判断是否是代码行
				codecount += (is_codeline == 0 && AnnoLock == 0);    //进入代码行的时候代码行加一                    
				is_codeline = 1;
			}

			if (*(s + i) == '/' && *(s + i + 1) == '/' && is_codeline == 0 && AnnoFileLock == 0) {    //判断是否为注释行
				annocount++;
				AnnoLock = 1;
			}

			if (*(s + i) == '/' && *(s + i + 1) == '*') {    //判断文档注释开始
				AnnoFileLock = 1;
				annocount -= is_codeline;    //注释在代码后不算注释行，因此减一
			}

			if (*(s + i) == '*' && *(s + i + 1) == '/') {    //判断文档注释结束
				AnnoFileLock = 0;
				annocount += (*(s + i + 2) == '\n');    //注释后换行情况
			}
		}
		annocount += AnnoFileLock;    //注释行结束时算作注释行加一

		blankcount++;    //每一行结束计数加一，并清空状态
		is_codeline = 0;
		is_annoline = 0;
		AnnoLock = 0;
	}
	free(s);
	fclose(file);

	blankcount = blankcount - codecount - annocount;
	printf("codeline:%d, annoline:%d, blankline:%d\n", codecount, annocount, blankcount);
}

//void Scan(char* Path, char Type) {
//	char* FileName = NULL;
//	char* FileType = NULL;
//	char Temp[30];    //用于暂存改变得字符串
//	long Head;
//	struct _finddata_t FileData;
//	int i = 0;
//
//	FileName = Path;
//	while (*(Path + i) != '\0') {    //找出文件名和文件类型的位置
//		if (*(Path + i) == '\\')
//			FileName = Path + i + 1;
//		if (*(Path + i) == '.')
//			FileType = Path + i + 1;
//		i++;
//	}
//
//	strcpy_s(Temp, FileType);//调整字符串
//	*FileType = '*';
//	*(FileType + 1) = '\0';
//
//	Head = _findfirst(Path, &FileData);
//
//	strcpy(FileType, Temp);//恢复字符串
//
//	do {
//		if (!strcmp(FileData.name, "..") || !strcmp(FileData.name, "."))    //去除前驱文件路径
//			continue;
//
//		if (_A_SUBDIR == FileData.attrib)    //是文件夹
//		{
//			strcpy_s(Temp, FileName);    //调整字符串
//			for (i = 0; *(FileData.name + i) != '\0'; i++) {
//				*(FileName + i) = *(FileData.name + i);
//			}
//			*(FileName + i) = '\\';
//			*(FileName + i + 1) = '\0';
//			strcat(Path, Temp);
//
//			Scan(Path, Type);
//
//			strcpy(FileName, Temp);    //恢复字符串            
//		}
//		else//是文件 
//		{
//			for (i = 0; *(FileData.name + i) != '.'; i++);
//			if (!strcmp(FileData.name + i + 1, FileType)) {    //是指定类型的文件
//
//				strcpy(Temp, FileName);
//				strcpy(FileName, FileData.name); //调整字符串
//
//				printf("%s:  ", FileData.name);
//				//main(Type, NULL, Path);    //将地址及功能传到启动函数
//				printf("\n");
//
//				strcpy(FileName, Temp);//恢复字符串
//			}
//		}
//	} while (_findnext(Head, &FileData) == 0);
//
//	_findclose(Head);
//}

char** ScanPath(int length, char** parameter) {
	char** path = NULL;
	int i, j = 0;
	for (i = 1; i < length; i++) {
		if (parameter[i][0] != '-') {
			path[j] = parameter[i];
			j++;
		}
	}
	return path;
}

char** ScanCommand(int length, char** parameter) {
	char** command = NULL;
	int i, j = 0;
	for (i = 1; i < length; i++)
	{
		if (parameter[i][0] == '-') {
			command[j] = parameter[i];
			j++;
		}
	}
	return command;
}

void Run(char* path[100], char* command[20], char *result) {
	// 初始化 char* 以便于满足函数参数要求
	char a[10] = "";
	//char b[200] = "";
	char* temp = a;
	int count = 0;
	//char* result = b;
	int i = 0, j = 0;
	while (strcmp(path[j], "\0") != 0) {
		if (strcmp(command[i], "\0") == 0)
			CountWordsFrequency(path[j]);
		while (strcmp(command[i], "\0") != 0)
		{
			switch (command[i][1])
			{
			case 'c':
				result = strcat(result, "字符数：");
				count = CodeCount(path[j]);
				sprintf(temp, "%d", count);
				result = strcat(result,temp );
				result = strcat(result, "\n");
				printf("%s", result);
				break;
			case 'l':
				result = strcat(result, "行数：\n");
				count = LineCount(path[j]);
				sprintf(temp, "%d", count);
				result = strcat(result, temp);
				result = strcat(result, "\n");
				break;
			case 'w':
				count = WordCount(path[j]);
				result = strcat(result, "单词数：\n");
				sprintf(temp, "%d", count);
				result = strcat(result, temp);
				result = strcat(result, "\n");
				break;
			default:
				break;
			}
			i++;
		}
		j++;
	}
	//return result;
}

void writeToFile(char * result) {
	FILE* file = NULL;
	errno_t er = fopen_s(&file, "result.txt", "w+");
	assert(!er);
	fprintf(file, result);
	fclose(file);
}

void main(int argc, char** argv) {
	int i, j = 0;
	char* command[20];
	char* path[100];
	for (i = 1; i < argc; i++) {         // 循环存储命令指令，并在最后添加结束符
		if (argv[i][0] == '-') {
			command[j] = argv[i];
			command[++j] = (char*)"\0";
		}
		else
		{
			command[j++] = (char*)"\0";
		}
	}

	for (i = 1, j = 0; i < argc; i++) {           //  循环存储文件路径，并在最后添加结束符
		if (argv[i][0] != '-') {
			path[j] = argv[i];
			path[++j] = (char*)"\0";
		}
		/*else
		{
			path[j++] = (char*)"\0";
		}*/
	}
	char a[500] = "";
	char* result = a;
	Run(path, command, result);  // 启动统计程序，得到结果字符串
	writeToFile(result);
	getchar();
}

