#include <stdio.h>
#include <dirent.h>
#include <direct.h> 
#include <string.h>
#include <graphics.h>
#include "include.h"

char history[HISTORY_LENGTH][1024] = { 0 };//Ŀ¼������¼
char path[1024];
int now_history = 0;//��ǰ��·����history�е�λ�ã�����������

void read_dir(DIR* dir, struct dirent* entry, struct file_info* info)//��ȡ��ǰĿ¼���ļ�
{
	int j = 0;
	dir=opendir(path);	
	memset(info, 0, sizeof(struct file_info) * 10);
	while ((entry = readdir(dir)) != NULL)
	{
		//newmouse(&MouseX, &MouseY, &press);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		info[j].num = j;
		get_file_info(entry->d_name, &info[j]);
		j++;

		if (j == 10)//***********��ʱֻ��ȡ10������������ҳ����ʱ�Ż�
			break;
	}
	closedir(dir);
}

void undo_dir()
{
	if (now_history < HISTORY_LENGTH - 1 && strcmp(history[now_history + 1], "\0") != 0)
		now_history++;
	chdir(history[now_history]);	
}
void anti_undo_dir()
{
	if (now_history > 0)
		now_history--;
	chdir(history[now_history]);
}
void back()
{
	int i;
	chdir("..");
	getcwd(path, sizeof(path));	
	if (now_history != 0)
	{
		for (i = 0; i < now_history && i + now_history < HISTORY_LENGTH; i++)		
			strcpy(history[i], history[i + now_history]);		
		for (i = 0; i < now_history && i + now_history < HISTORY_LENGTH; i++)		
			strcpy(history[HISTORY_LENGTH - 1 - i], "\0");		
		now_history = 0;
	}
}

void new_history()//����Ŀ¼������ʷ
{	
	int i;	
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	strcpy(history[0], path);
}


int change_dir(struct file_info* info, int x, int y)//����Ŀ¼.����1ѡ�У�����2ȷ��
{
	int i, j;
	static int is_chosen = 0;//�Ƿ���ѡ��״̬
	char target[1024];
	//�����������������ļ����
	for (j = 0; j < 10; j++)
		if (y > 95 + j * 20 && y < 95 + j * 20 + 20)
		{
			i = j;
			break;
		}
	if ((info + i)->name == 0)//�������հ�
		return 0;
	else if ((info + i)->name != 0 && is_chosen == 0)
	{
		is_chosen = 1;
		setcolor(YELLOW);
		rectangle(120, 95 + i, 640, 95 + i + 20);
		return 1;
	}
	else if ((info + i)->name != 0 && strcmp((info + i)->type, "Fold") == 0 && is_chosen == 1)
	{
		is_chosen = 0;
		/*strcpy(target, path);
		strcpy(target, "\\");
		strcpy(target, (info + i)->name);*/
		strcpy(target, ".");
		strcpy(target, "\\");
		strcpy(target, (info + i)->name);
		chdir(target);
	}
	else
		return 0;
}