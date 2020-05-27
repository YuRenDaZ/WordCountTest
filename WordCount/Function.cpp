#include "Function.h"

int CharacterCount(char* Path) {    // 计算字符个数

	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);    // 若文件不存在则报错

	char code;
	// 计数
	int count = 0;
	int num = 0;

	while ((code = fgetc(file)) != EOF) {     // 读取字符直到结束
		code = fgetc(file);
		if (code == EOF) break;
		count += ((code != ' ') && (code != '\n') && (code != '\t'));    // 判断是否是字符    
	}
	fclose(file);
	return num;
}

int WordCount(char* Path) {    // 计算单词个数
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char word;
	int is_word = 0;    // 用于记录字符是否处于单词中
	int count = 0;

	while ((word = fgetc(file)) != EOF) {
		if ((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z')) {    // 判断是否是字母            
			count += (is_word != 0);
			is_word = 1;    // 记录单词状态
		}
		else
			is_word = 0;    // 记录不处于单词状态
	}
	fclose(file);
	return count;
}

int LineCount(char* Path) {    // 计算行数
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);
	int count = 0;
	char ch;
	int i = 0;
	while (!feof(file))
	{
		if ((ch = fgetc(file)) != EOF)
		{
			if ((ch = fgetc(file)) == '\t')    // 识别换行符
				count++;
			_sleep(250);
		}
	}
	count++;
	fclose(file);
	return count;
}

void AllDetail(char* Path) {    // 显示空行， 代码行，注释行
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char* s = (char*)malloc(200 * sizeof(char));    // 申请空间
	int i;
	int is_codeline = 0;    // 状态记录变量
	int is_annoline = 0;
	int AnnoLock = 0;
	int AnnoFileLock = 0;

	int codecount = 0;
	int annocount = 0;
	int blankcount = 0;

	while (fgets(s, 200, file) != NULL) {    // 逐次取文件中的行
		for (i = 0; *(s + i) != '\0'; i++) {

			if (((*(s + i) >= 'a' && *(s + i) <= 'z') || (*(s + i) >= 'A' && *(s + i) <= 'Z')) && AnnoFileLock == 0) {    // 判断是否是代码行
				codecount += (is_codeline == 0 && AnnoLock == 0);    // 进入代码行的时候代码行加一                    
				is_codeline = 1;
			}

			if (*(s + i) == '/' && *(s + i + 1) == '/' && is_codeline == 0 && AnnoFileLock == 0) {    // 判断是否为注释行
				annocount++;
				AnnoLock = 1;
			}

			if (*(s + i) == '/' && *(s + i + 1) == '*') {    // 判断文档注释开始
				AnnoFileLock = 1;
				annocount -= is_codeline;    // 注释在代码后不算注释行，因此减一
			}

			if (*(s + i) == '*' && *(s + i + 1) == '/') {    // 判断文档注释结束
				AnnoFileLock = 0;
				annocount += (*(s + i + 2) == '\n');    // 注释后换行情况
			}
		}
		annocount += AnnoFileLock;    // 注释行结束时算作注释行加一

		blankcount++;    // 每一行结束计数加一，并清空状态
		is_codeline = 0;
		is_annoline = 0;
		AnnoLock = 0;
	}
	free(s);
	fclose(file);

	blankcount = blankcount - codecount - annocount;
	printf("codeline:%d, annoline:%d, blankline:%d\n", codecount, annocount, blankcount);
}

char** ScanPath(int length, char** parameter, char**& path) {
	int i, j = 0;
	for (i = 1, j = 0; i < length; i++) {    //  循环存储文件路径，并在最后添加结束符
		if (parameter[i][0] != '-') {
			path[j] = parameter[i];
			path[++j] = (char*)"\0";
		}
		/*else
		{
			path[j++] = (char*)"\0";
		}*/
	}
	return path;
}

void ScanCommand(int length, char** parameter, char**& command) {
	int i, j = 0;
	for (i = 1, j = 0; i < length; i++) {    // 循环存储命令指令，并在最后添加结束符
		if (parameter[i][0] == '-') {
			command[j] = parameter[i];
			command[++j] = (char*)"\0";
		}
		else
		{
			command[j++] = (char*)"\0";
		}
	}
}

void Run(char* path[100], char* command[20], char* result) {
	char a[10] = "";    // 初始化 char* 以便于满足函数参数要求
	char* temp = a;
	int count = 0;
	int i = 0, j = 0;
	while (strcmp(path[j], "\0") != 0) {
		if (strcmp(command[i], "\0") == 0)
			break;
		while (strcmp(command[i], "\0") != 0)
		{
			switch (command[i][1])
			{
			case 'c':
				result = strcat(result, "字符数：");
				count = CharacterCount(path[j]);
				sprintf(temp, "%d", count);
				result = strcat(result, temp);
				result = strcat(result, "\n");
				break;
			case 'l':
				result = strcat(result, "行数：");
				count = LineCount(path[j]);
				sprintf(temp, "%d", count);
				result = strcat(result, temp);
				result = strcat(result, "\n");
				break;
			case 'w':
				count = WordCount(path[j]);
				result = strcat(result, "单词数：");
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
}

void WriteToFile(char* result) {
	FILE* file = NULL;
	errno_t er = fopen_s(&file, "result.txt", "w+");
	assert(!er);
	fprintf(file, result);
	fclose(file);
}


