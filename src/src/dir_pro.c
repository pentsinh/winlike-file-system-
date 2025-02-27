#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <direct.h> 
#include <string.h>
#include <graphics.h>
#include "include.h"

char history[HISTORY_LENGTH][1024] = { 0 };//目录操作记录
char path[1024];//当前路径
int now_history = 0;//当前在路径在history中的位置，服务撤销操作
struct dir_tree tree;//目录树，用于加载左栏，以及通过左栏快速定位
char chosen_name[13]={-1};//被选中的文件名

void read_dir(DIR* dir, struct dirent* entry, struct file_info* info)//读取当前目录下文件
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

		if (j == 10)//***********暂时只读取10个，后面做翻页功能时优化
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

void new_history()//更新目录操作历史
{	
	int i;	
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	strcpy(history[0], path);
}


int change_dir(struct file_info* info, int x, int y)//更改目录.返回1选中，返回2确认
{
	int i, j;
	//static int is_chosen = 0;//是否处于选中状态
	//static char chosen_name[13];//记录选中的文件
	char target[1024];
	//查找鼠标点击的区域的文件序号
	for (j = 0; j < 10; j++)
		if (y > 90 + j * 20 && y < 90 + j * 20 + 20)
		{
			i = j;
			break;
		}
	if ((info + i)->name == 0)//如果点击空白
	{
		strcpy(chosen_name, 0);
		return 0;
	}
	else if ((info + i)->name != 0 && strcmp((info + i)->type, "Fold") == 0 && strcmp(chosen_name, (info + i)->name) == 0)//如果点击两次，进入
	{
		strcpy(chosen_name, 0);
		strcpy(target, ".");
		strcat(target, "\\");
		strcat(target, (info + i)->name);
		chdir(target);
		return 2;
	}
	else if ((info + i)->name != 0 && strcmp(chosen_name, (info + i)->name) != 0)//如果点击一次，选中
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


void tree_make(struct dir_tree* tree)//目录树初始化
{
	//*********这里copy了main.c的部分定义，注意区分	
	DIR* dir;//指向目录流
	struct dirent* entry;//指向目录中的一个条目（文件或文件夹）
	struct file_info info_for_tree[10];//存放文件信息
	//***********
	int flag = 0;//是否为c盘
	int i;//循环变量
	int j = 0;//正在构建的树枝编号
	struct dir_tree* p;//链表操作辅助指针，用于申请空间
	//打开目录流,//初始化tree根及分支方向
	if (strcmp(tree->path, 0) == 0)
	{
		strcpy(tree->path, "C:\\"); //如果是根，初始化为C盘
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
	//筛选出Fold，并且构建tree
	for (i = 0; info_for_tree[i].name != 0; i++)
	{
		if (strcmp(info_for_tree[i].type, "Fold") == 0)
		{			
			p = (struct dir_tree*)malloc(sizeof(struct dir_tree));//向内存申请空间
			//完善分支信息
			tree->branch[j] = p;
			strcpy(p->name, info_for_tree[i].name);//
			strcpy(p->path, tree->path);//输入分支的完整路径
			if (!flag)//如果不是c盘
				strcat(p->path, "\\");
			strcat(p->path, p->name);

			//对目录的子目录进一步构建，递归
			tree_make(tree->branch[j]);
			j++;
		}
	}	
}
