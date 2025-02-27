#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <direct.h> 
#include <string.h>
#include <graphics.h>
#include "include.h"

char history[HISTORY_LENGTH][1024] = { 0 };//Ŀ¼������¼
char path[1024];//��ǰ·��
int now_history = 0;//��ǰ��·����history�е�λ�ã�����������
struct dir_tree tree;//Ŀ¼�������ڼ����������Լ�ͨ���������ٶ�λ
char chosen_name[13]={-1};//��ѡ�е��ļ���

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
	//static int is_chosen = 0;//�Ƿ���ѡ��״̬
	//static char chosen_name[13];//��¼ѡ�е��ļ�
	char target[1024];
	//�����������������ļ����
	for (j = 0; j < 10; j++)
		if (y > 90 + j * 20 && y < 90 + j * 20 + 20)
		{
			i = j;
			break;
		}
	if ((info + i)->name == 0)//�������հ�
	{
		strcpy(chosen_name, 0);
		return 0;
	}
	else if ((info + i)->name != 0 && strcmp((info + i)->type, "Fold") == 0 && strcmp(chosen_name, (info + i)->name) == 0)//���������Σ�����
	{
		strcpy(chosen_name, 0);
		strcpy(target, ".");
		strcat(target, "\\");
		strcat(target, (info + i)->name);
		chdir(target);
		return 2;
	}
	else if ((info + i)->name != 0 && strcmp(chosen_name, (info + i)->name) != 0)//������һ�Σ�ѡ��
	{
		strcpy(chosen_name, (info + i)->name);		
		//setcolor(YELLOW);
		//rectangle(120, 90 + i * 20, 640, 90 + i * 20 + 20);
		return 1;
	}

	else
	{
		strcpy(chosen_name, 0);
		return 0;
	}
}


void tree_make(struct dir_tree* tree)//Ŀ¼����ʼ��
{
	//*********����copy��main.c�Ĳ��ֶ��壬ע������	
	DIR* dir;//ָ��Ŀ¼��
	struct dirent* entry;//ָ��Ŀ¼�е�һ����Ŀ���ļ����ļ��У�
	struct file_info info_for_tree[10];//����ļ���Ϣ
	//***********
	int flag = 0;//�Ƿ�Ϊc��
	int i;//ѭ������
	int j = 0;//���ڹ�������֦���
	struct dir_tree* p;//�����������ָ�룬��������ռ�
	//��Ŀ¼��,//��ʼ��tree������֧����
	if (strcmp(tree->path, 0) == 0)
	{
		strcpy(tree->path, "C:\\"); //����Ǹ�����ʼ��ΪC��
		dir = opendir(tree->path);		
		flag = 1;
	}
	else
		dir = opendir(tree->path);	

	for (i = 0; i < 10; i++)
	{
		tree->branch[i] = NULL;
	}

	read_dir(dir, entry, info_for_tree);
	closedir(tree->path);
	//ɸѡ��Fold�����ҹ���tree
	for (i = 0; info_for_tree[i].name != 0; i++)
	{
		if (strcmp(info_for_tree[i].type, "Fold") == 0)
		{			
			p = (struct dir_tree*)malloc(sizeof(struct dir_tree));//���ڴ�����ռ�
			//���Ʒ�֧��Ϣ
			tree->branch[j] = p;
			strcpy(p->name, info_for_tree[i].name);//
			strcpy(p->path, tree->path);//�����֧������·��
			if (!flag)//�������c��
				strcat(p->path, "\\");
			strcat(p->path, p->name);

			//��Ŀ¼����Ŀ¼��һ���������ݹ�
			tree_make(tree->branch[j]);
			j++;
		}
	}	
}
