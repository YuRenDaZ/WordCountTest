#include "Function.h"

struct words   //���ʽṹ��
{
	char word[40];
	int count;
};

// ��Ϊ��չ����ͳ�Ƴ���Ƶ��ǰ�ĵĵ��������ṩ˼·���Ǵ��벻��ȫ��ȷ��
void CountWordsFrequency(char* path)
{
	// �޸�Ϊ��̬�ֲ��ڴ������ɽ��Խ������
	struct words word[1000] = { 0 }, stmp = { 0 };
	int i = 0, j = 0, k = 0, flag = 0;
	char c, tmp[40] = { 0 };
	FILE* fp = NULL;
	errno_t er = fopen_s(&fp, path, "r");
	assert(fp != NULL);
	//���ļ������ɵ���
	while ((c = fgetc(fp)) != EOF)
	{
		//��Щ���ŷָ�Ķ���Ϊ��һ�����ʽ���
		if (c <= 'Z' && c >= 'A' || c >= 'a' && c <= 'z' || c == '-' && j != 0)
		{
			tmp[j++] = (c >= 'A' && c <= 'Z') ? c + 32 : c; //ȫת��Сд �Ϳ������Ӵ�Сдͳ����
		}
		else
		{
			tmp[j] = '\0';
			j = 0;
			flag = 0;
			//�жϵ����Ƿ��Ѿ���¼ ���������ʹ���ʼ�1
			for (k = 0; k < i; k++)
			{
				if (strcmp(tmp, word[k].word) == 0)
				{
					word[k].count++;
					flag = 1;
					break;
				}
			}
			//û������뵥�ʽṹ�����鱣��
			if (!flag)
			{
				strcpy_s(word[i].word, tmp);
				word[i].count++;
				i++;
			}
		}
	}
	fclose(fp);
	//ʹ��������
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
	//���������Ƶ��ǰ�ĵ���
	for (k = 0; k < 3; k++)
	{
		printf("[%s][%d]\n", word[k].word, word[k].count);
	}
}

int CodeCount(char* Path) {    // �����ַ�����

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
	printf("�ַ�����%d\n", num);
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
	printf("��������%d\n", count);
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
			if ((ch = fgetc(file)) == '\t') // ʶ���з�
				count++;
			_sleep(250);
		}
	}
	count++;
	fclose(file);
	printf("������%d\n", count);
	return count;
}

void AllDetail(char* Path) {    // ��ʾ���У� �����У�ע����
	FILE* file = NULL;
	errno_t er = fopen_s(&file, Path, "r");
	assert(file != NULL);

	char* s = (char*)malloc(200 * sizeof(char));// ����ռ�
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

			if (((*(s + i) >= 'a' && *(s + i) <= 'z') || (*(s + i) >= 'A' && *(s + i) <= 'Z')) && AnnoFileLock == 0) { // �ж��Ƿ��Ǵ�����
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

void Run(char* path[100], char* command[20], char* result) {
	// ��ʼ�� char* �Ա������㺯������Ҫ��
	char a[10] = "";
	//char b[200] = "";
	char* temp = a;
	int count = 0;
	//char* result = b;
	int i = 0, j = 0;
	while (strcmp(path[j], "\0") != 0) {
		if (strcmp(command[i], "\0") == 0) {
			CodeCount(path[j]);
			WordCount(path[j]);
			LineCount(path[j]);
		}
		//CountWordsFrequency(path[j]);
		while (strcmp(command[i], "\0") != 0)
		{
			switch (command[i][1])
			{
			case 'c':
				result = strcat(result, "�ַ�����");
				count = CodeCount(path[j]);
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
	//return result;
}

void writeToFile(char* result) {
	FILE* file = NULL;
	errno_t er = fopen_s(&file, "result.txt", "w+");
	assert(!er);
	fprintf(file, result);
	fclose(file);
}


