// #include <stdio.h>
// #include <stdlib.h>
// #include <dirent.h>
// #include <direct.h>
// #include <string.h>
// #include <graphics.h>
#include "include.h"
// #include "index.h"
// #include "bit_pro.h"
/*
与左栏相关的函数
*/

#define MAX_DEPTH 10  // 设定最大递归深度
struct dir_tree tree; // 目录树，用于加载左栏，以及通过左栏快速定位
/*void tree_make(struct dir_tree* tree, int depth) // 目录树初始化
{
	struct file_info info_for_tree[10] = {0}; // 存放文件信息
	int i;									  // 循环变量
	int j = 0;								  // 正在构建的树枝编号
	struct dir_tree *p;						  // 链表操作辅助指针，用于申请空间
	// 初始化tree根及分支方向
	if (strcmp(tree->path, "") == 0)
	// if (flag == 0)
	{
		// strcpy(tree->path, "C:\\"); // 如果是根，初始化为C盘
		// strcpy(tree->name, "C");
		strcpy(tree->path, "C:\\PROJECT"); // 如果是根，初始化为C盘
		strcpy(tree->name, "PROJECT");
		// strcpy(tree->path, "C:\\BORLANDC"); // 如果是根，初始化为C盘
		// strcpy(tree->name, "BORLANDC");
	}
	tree->is_branch_on = 1;
	for (i = 0; i < 10; i++)
	{
		tree->branch[i] = NULL;
	}
	printf("Building tree for path: %s\n", tree->path); // 调试输出******************************************************
	read_dir(tree->path, info_for_tree);
	// 筛选出Fold，并且构建tree
	for (i = 0; strcmp(info_for_tree[i].name, "") != 0; i++)
	// for (i = 0; info_for_tree[i].name != 0; i++)
	{
		// if (info_for_tree[i].type == 0 || strcmp(info_for_tree[i].type, "") == 0)
		//	outtextxy(10, i * 10, "erroring");//**************
		// else(outtextxy(10, i * 10, info_for_tree[i].name));//***********
		if (info_for_tree[i].flag == 2 && strcmp(info_for_tree[i].name, "DPMI16BI.OVL") != 0)
		{

			tree->branch[j] = (struct d
			ir_tree *)malloc(sizeof(struct dir_tree)); // 向内存申请空间
			if (!tree->branch[j])
			{
				perror("Memory allocation failed\n");
				continue;
			}

			// 完善分支信息

			strcpy(tree->branch[j]->name, info_for_tree[i].name); //
			strcpy(tree->branch[j]->path, tree->path);			  // 输入分支的完整路径
			// if (!is_C)//如果不是c盘
			// if (!flag)
			if (strlen(tree->branch[j]->path) > 0 && tree->branch[j]->path[strlen(tree->branch[j]->path) - 1] != '\\')
				strcat(tree->branch[j]->path, "\\");
			strcat(tree->branch[j]->path, tree->branch[j]->name);

			// 对目录的子目录进一步构建，递归
			tree_make(tree->branch[j], depth++);
			j++;
		}
	}
	printf("Building tree for path OK!: %s\n", tree->path); // 调试输出******************************************************
}*/

// void tree_make(struct My_filenode *node, int depth)
// {
// 	DIR *dir;
// 	struct dirent *entry;
// 	struct My_filenode *p; // 正在构建的上一个子目录
// 	char path[64];		   // 当前节点绝对路径
// 	char tmp[64];
// 	if (depth == 0)
// 	{
// 		strcpy(node->name, "C:\\");
// 		node->flag = 1;
// 		strcpy(path, "C:\\");
// 		// strcpy(node->name, "C:\\BORLANDC");
// 		// node->flag = 1;
// 		// strcpy(path, "C:\\BORLANDC");
// 		// strcpy(node->name, "C:\\PROJECT");
// 		// node->flag = 1;
// 		// strcpy(path, "C:\\PROJECT");
// 	}
// 	else
// 	{
// 		strcpy(path, get_node_path(node));
// 	}
// 	dir = opendir(path);
// 	printf("Building %s\n", path);
// 	if (!dir)
// 	{
// 		perror("Failed to open directory");
// 		return; // 如果打开目录失败，停止读取
// 	}
// 	printf("Build %s OK\n", path);
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
// 			continue;
// 		// sprintf(tmp, "%s\\%s", path, entry->d_name);
// 		// printf("%s:%d\n", get_file_path(node, entry->d_name), get_file_type((get_file_path(node, entry->d_name)))); // 调试输出
// 		if (get_file_type((get_file_path(node, entry->d_name))) == 2) // 如果是目录
// 		{
// 			if (node->son_list_head == NULL) // 子目录头节点
// 			{
// 				node->son_list_head = (struct My_filenode *)malloc(sizeof(struct My_filenode));
// 				strcpy(node->son_list_head->name, entry->d_name);
// 				node->son_list_head->father = node;
// 				set_bit(&node->son_list_head->flag, 5, 1); // 标记位头节点
// 				p = node->son_list_head;
// 				tree_make(p, depth + 1);
// 			}
// 			else // 子目录非头节点
// 			{
// 				p->next = (struct My_filenode *)malloc(sizeof(struct My_filenode));
// 				strcpy(p->next->name, entry->d_name);
// 				p->next->father = node;
// 				set_bit(&p->next->flag, 5, 0);
// 				p = p->next;
// 				tree_make(p, depth + 1);
// 			}
// 		}
// 	}
// 	closedir(dir);
// 	printf("Build %s OK\n", path);
// }

void tree_make(struct My_filenode *node, int depth) // 目录树构建，外部调用时传入根目录
{
	DIR *dir;
	struct dirent *entry;
	struct My_filenode *p; // 正在构建的上一个子目录
	char *path;			   // 当前节点绝对路径
	if (depth == 0)
	{

		node->flag = 0;
		set_bit(&node->flag, 0, 1);
		set_bit(&node->flag, 4, 1);
		strcpy(node->name, "C:\\");
		path = (char *)malloc(sizeof(char) * (strlen("C:\\") + 1));
		strcpy(path, "C:\\");
		// strcpy(node->name, "C:\\PROJECT");
		// path = (char *)malloc(sizeof(char) * (strlen("C:\\PROJECT") + 1));
		// strcpy(path, "C:\\PROJECT");
	}
	else
	{
		strcpy(path, get_node_path(node));
	}
	dir = opendir(path);
	printf("Building %s\n", path);
	if (!dir)
	{
		perror("Failed to open directory");
		return; // 如果打开目录失败，停止读取
	}
	printf("Build %s OK\n", path);
	// if (depth < 3) // 目前只能读取到第二层的子目录
	// {
	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		// printf("%s\n", entry->d_name);

		char *file_path = get_file_path_node(node, entry->d_name);

		// printf("%s\n", file_path);

		if (!file_path)
		{
			closedir(dir);
			return;
		}

		if (get_file_type(file_path) == 2) // 如果是目录
		{
			if (node->son_list_head == NULL) // 子目录头节点
			{
				node->son_list_head = (struct My_filenode *)malloc(sizeof(struct My_filenode));
				if (!node->son_list_head)
				{
					perror("Memory allocation failed for son_list_head");
					free(file_path);
					closedir(dir);
					return;
				}
				// 节点初始化
				strcpy(node->son_list_head->name, entry->d_name);
				node->son_list_head->father = node;
				node->son_list_head->next = NULL;
				node->son_list_head->son_list_head = NULL;
				node->son_list_head->flag = 0;
				set_bit(&node->son_list_head->flag, 5, 1);	   // 标记位头节点
				if (depth == 0)								   // 第一级目录默认可见
					set_bit(&node->son_list_head->flag, 4, 1); // 展开

				p = node->son_list_head;
				if (depth < 2) // 限制递归深度
					tree_make(p, depth + 1);
			}
			else // 子目录非头节点
			{
				p->next = (struct My_filenode *)malloc(sizeof(struct My_filenode));
				if (!p->next)
				{
					perror("Memory allocation failed for next node");
					free(file_path);
					closedir(dir);
					return;
				}
				// 节点初始化
				strcpy(p->next->name, entry->d_name);
				p->next->father = node;
				p->next->next = NULL;
				p->next->son_list_head = NULL;
				p->next->flag = 0;
				set_bit(&p->next->flag, 5, 0);	   // 非头节点
				if (depth == 0)					   // 第一级目录默认可见
					set_bit(&p->next->flag, 4, 1); // 展开

				p = p->next;
				if (depth < 2) // 限制递归深度
					tree_make(p, depth + 1);
			}
			free(file_path);
		}
	}
	//}
	closedir(dir);
	printf("Build %s OK\n", path);
}

// 获取节点绝对路径
char *get_node_path(struct My_filenode *node)
{
	// printf("1\n");
	if (node == NULL)
		return NULL;
	// printf("2\n");
	//  如果是根节点，直接返回其名称
	if (node->father == NULL)
	{
		char *path = (char *)malloc(strlen(node->name) + 1);
		// printf("3\n");
		if (path == NULL)
			return NULL;
		strcpy(path, node->name);
		return path;
	}
	else
	{
		// 递归获取父节点的路径
		char *father_path = get_node_path(node->father);
		// printf("4\n");
		if (father_path == NULL)
			return NULL;

		// 检查父路径是否以反斜杠结尾
		size_t father_path_len = strlen(father_path);
		if (father_path_len > 0 && father_path[father_path_len - 1] == '\\')
		{
			// 如果父路径以反斜杠结尾，则去掉最后一个字符
			father_path[father_path_len - 1] = '\0';
		}

		// 计算所需内存大小
		size_t len = strlen(father_path) + strlen(node->name) + 2; // +2 是为了分隔符和字符串结束符
		char *path = (char *)malloc(len);
		// printf("5\n");
		if (path == NULL)
		{
			free(father_path);
			return NULL;
		}

		// 拼接路径
		sprintf(path, "%s\\%s", father_path, node->name);
		if (path[0] == '\\')
			strcpy(path, path + 1);

		// 释放父节点路径的内存
		free(father_path);

		return path;
	}
}

// 获取节点下的文件路径
char *get_file_path_node(struct My_filenode *node, char *filename)
{
	char *path = get_node_path(node);
	// printf("6\n");
	if (path == NULL)
		return NULL;

	size_t path_len = strlen(path);
	if (path_len > 0 && path[path_len - 1] != '\\')
	{
		// 如果节点路径不以反斜杠结尾，则添加反斜杠
		char *new_path = (char *)malloc(path_len + strlen(filename) + 2);
		// printf("7\n");
		if (new_path == NULL)
		{
			free(path);
			return NULL;
		}
		sprintf(new_path, "%s\\%s", path, filename);
		free(path);
		return new_path;
	}
	else
	{
		// 如果节点路径以反斜杠结尾，则直接拼接文件名
		char *new_path = (char *)malloc(path_len + strlen(filename) + 1);
		// printf("8\n");
		if (new_path == NULL)
		{
			free(path);
			return NULL;
		}
		sprintf(new_path, "%s%s", path, filename);
		free(path);
		return new_path;
	}
}

// 从左栏直接点击文件夹，传入root获取文件夹绝对路径****基于左栏最多展开三级目录的前提****
char *get_file_path_left(struct My_filenode *node, int x, int y)
{

	struct My_filenode *p = node->son_list_head;
	if (p == NULL)
		return NULL;
	// 计算点击位置对应的文件
	int row;										  // 点击位置为第几行，***之后将参与运算***
	int i;											  // y轴像素
	for (i = 80, row = 1; i < 480; i += 10, row += 1) // 第一条从y=80开始
	{
		if (y > i && y < i + 10)
			break;
	}
	do
	{
		if (count_son_son_visible(p) + 1 >= row && x > 30) // 从一级目录计数
		{
			if (row == 1) // 一级目录未展开
				return get_file_path_node(p->father, p->name);
			else
			{
				p = p->son_list_head;
				row -= 1; // 进入一级目录，在二级目录中查找
				do
				{
					if (count_son_visible(p) + 1 >= row && x > 40)
					{
						if (row == 1) // 如果该二级目录未展开
							return get_file_path_node(p->father, p->name);

						else
						{
							p = p->son_list_head;
							row -= 1;
							for (i = 1; p->next != NULL; i++) // 20为防止死循环的任意量
							{
								if (i == row && x > 50)
									return get_file_path_node(p->father, p->name);
								p = p->next;
							}
						}
					}
					row -= (count_son_visible(p) + 1);
					p = p->next;
				} while (p != NULL);
			}
		}
		row -= (count_son_son_visible(p) + 1);
		p = p->next;
	} while (p != NULL);

	return NULL;
}

int count_son_visible(struct My_filenode *node) // 计算可见子目录数量
{
	if (get_bit(node->flag, 4) == 0) // 如果传入目录未展开
		return 0;
	struct My_filenode *p = node->son_list_head;
	int num = 0;
	if (p == NULL)
		return 0;
	do
	{
		num++;
		p = p->next;
	} while (p != NULL);
	return num;
}

// 计算可见子目录及其可见子目录数量
int count_son_son_visible(struct My_filenode *node)
{
	if (get_bit(node->flag, 4) == 0) // 如果传入目录未展开
		return 0;
	struct My_filenode *p = node->son_list_head;
	int num = 0;
	if (p == NULL)
		return 0;
	do
	{
		num++;
		if (get_bit(p->flag, 4) == 1) // 如果子目录展开（可见）
			num += count_son_visible(p);
		p = p->next;

	} while (p != NULL);
	return num;
}

int unfold(struct My_filenode *node, int x, int y) // 点击>展开（返回1）/收起（返回2）目录***这里的算法参考上面的get_file_path_left，这里不再写详细注释***
{
	// 计算点击位置对应的文件
	struct My_filenode *p = node->son_list_head;
	if (p == NULL)
		return 0;
	int row;										  // 点击位置为第几行，***之后将参与运算***
	int i;											  // y轴像素
	for (i = 80, row = 1; i < 480; i += 10, row += 1) // 第一条从y=80开始
	{
		if (y > i && y < i + 10)
			break;
	}
	do
	{
		if (count_son_son_visible(p) + 1 >= row) // 从一级目录计数
		{
			if (row == 1 && get_bit(p->flag, 4) == 0 && x > 20 && x < 30) // 一级目录未展开
			{
				set_bit(&p->flag, 4, 1);
				return 1;
			}
			else if (row == 1 && get_bit(p->flag, 4) == 1 && x > 20 && x < 30)
			{
				set_bit(&p->flag, 4, 0);
				fold_sonlist(p);
				return 2;
			}
			else
			{
				p = p->son_list_head;
				row -= 1; // 进入一级目录，在二级目录中查找
				do
				{
					if (count_son_visible(p) + 1 >= row)
					{
						if (row == 1 && get_bit(p->flag, 4) == 0 && x > 30 && x < 40) // 如果该二级目录未展开
						{
							set_bit(&p->flag, 4, 1);
							return 1;
						}
						else if (row == 1 && get_bit(p->flag, 4) == 1 && x > 30 && x < 40)
						{
							set_bit(&p->flag, 4, 0);
							return 2;
						}
						else
						{
							p = p->son_list_head;
							row -= 1;
							for (i = 1; i < 20; i++) // 20为防止死循环的任意量
							{
								if (i == row && 40 < x < 50 && get_bit(p->flag, 4) == 0)
								{
									set_bit(&p->flag, 4, 1);
									return 1;
								}
								else if (i == row && 40 < x < 50 && get_bit(p->flag, 4) == 1)
								{
									set_bit(&p->flag, 4, 0);
									return 2;
								}

								p = p->next;
							}
						}
					}
					row -= (count_son_visible(p) + 1);
					p = p->next;
				} while (p != NULL);
			}
		}

		row -= (count_son_son_visible(p) + 1);
		p = p->next;
	} while (p != NULL);

	return 0;
}

// 折叠传入节点的所有子目录
void fold_sonlist(struct My_filenode *node)
{
	struct My_filenode *p = node->son_list_head;
	if (p == NULL)
		return;
	do
	{
		set_bit(&p->flag, 4, 0);
		p = p->next;
	} while (p != NULL);
}