#include "Function.h"

int main(int argc, char** argv) {
	int i, j = 0;
	char** command = NULL;  // 命令存储变量
	command = (char**)malloc(20 * sizeof(char*));
	char** path = NULL;  // 文件存储变量
	path = (char**)malloc(100 * sizeof(char*));
	ScanCommand(argc, argv, command);
	ScanPath(argc, argv, path);
	char a[500] = "";
	char* result = a;
	Run(path, command, result);  // 启动统计程序，得到结果字符串
	printf("%s", result);
	WriteToFile(result);
	return 0;
}

