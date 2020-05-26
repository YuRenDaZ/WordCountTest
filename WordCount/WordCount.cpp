#include "Function.h"

int main(int argc, char** argv) {
	if (argc <= 1) {
		printf("请输入程序命令行参数！");
		return 0;
	}
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
	return 0;
}

