#include "Function.h"

int CharacterCount(char* Path) {    // �����ַ�����

	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);    // ���ļ��������򱨴�

	char code;
	// ����
	int count = 0;
	int num = 0;

	while ((code = fgetc(file)) != EOF) {     // ��ȡ�ַ�ֱ������
		code = fgetc(file);
		if (code == EOF) break;
		count += ((code != ' ') && (code != '\n') && (code != '\t'));    // �ж��Ƿ����ַ�    
	}
	fclose(file);
	return num;
}

int WordCount(char* Path) {    // ���㵥�ʸ���
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char word;
	int is_word = 0;    // ���ڼ�¼�ַ��Ƿ��ڵ�����
	int count = 0;

	while ((word = fgetc(file)) != EOF) {
		if ((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z')) {    // �ж��Ƿ�����ĸ            
			count += (is_word != 0);
			is_word = 1;    // ��¼����״̬
		}
		else
			is_word = 0;    // ��¼�����ڵ���״̬
	}
	fclose(file);
	return count;
}

int LineCount(char* Path) {    // ��������
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
			if ((ch = fgetc(file)) == '\t')    // ʶ���з�
				count++;
			_sleep(250);
		}
	}
	count++;
	fclose(file);
	return count;
}

void AllDetail(char* Path) {    // ��ʾ���У� �����У�ע����
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char* s = (char*)malloc(200 * sizeof(char));    // ����ռ�
	int i;
	int is_codeline = 0;    // ״̬��¼����
	int is_annoline = 0;
	int AnnoLock = 0;
	int AnnoFileLock = 0;

	int codecount = 0;
	int annocount = 0;
	int blankcount = 0;

	while (fgets(s, 200, file) != NULL) {    // ���ȡ�ļ��е���
		for (i = 0; *(s + i) != '\0'; i++) {

			if (((*(s + i) >= 'a' && *(s + i) <= 'z') || (*(s + i) >= 'A' && *(s + i) <= 'Z')) && AnnoFileLock == 0) {    // �ж��Ƿ��Ǵ�����
				codecount += (is_codeline == 0 && AnnoLock == 0);    // ��������е�ʱ������м�һ                    
				is_codeline = 1;
			}

			if (*(s + i) == '/' && *(s + i + 1) == '/' && is_codeline == 0 && AnnoFileLock == 0) {    // �ж��Ƿ�Ϊע����
				annocount++;
				AnnoLock = 1;
			}

			if (*(s + i) == '/' && *(s + i + 1) == '*') {    // �ж��ĵ�ע�Ϳ�ʼ
				AnnoFileLock = 1;
				annocount -= is_codeline;    // ע���ڴ������ע���У���˼�һ
			}

			if (*(s + i) == '*' && *(s + i + 1) == '/') {    // �ж��ĵ�ע�ͽ���
				AnnoFileLock = 0;
				annocount += (*(s + i + 2) == '\n');    // ע�ͺ������
			}
		}
		annocount += AnnoFileLock;    // ע���н���ʱ����ע���м�һ

		blankcount++;    // ÿһ�н���������һ�������״̬
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
	for (i = 1, j = 0; i < length; i++) {    //  ѭ���洢�ļ�·�������������ӽ�����
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
	for (i = 1, j = 0; i < length; i++) {    // ѭ���洢����ָ����������ӽ�����
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
	char a[10] = "";    // ��ʼ�� char* �Ա������㺯������Ҫ��
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
				result = strcat(result, "�ַ�����");
				count = CharacterCount(path[j]);
				sprintf(temp, "%d", count);
				result = strcat(result, temp);
				result = strcat(result, "\n");
				break;
			case 'l':
				result = strcat(result, "������");
				count = LineCount(path[j]);
				sprintf(temp, "%d", count);
				result = strcat(result, temp);
				result = strcat(result, "\n");
				break;
			case 'w':
				count = WordCount(path[j]);
				result = strcat(result, "��������");
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


