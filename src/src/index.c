#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <direct.h> 
#include <string.h>
#include <graphics.h>
#include "include.h"
/*
与左栏相关的函数
*/
struct dir_tree tree;//目录树，用于加载左栏，以及通过左栏快速定位

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
	tree->is_branch_on = 0;
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
