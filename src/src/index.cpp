#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <direct.h>
#include <string.h>
#include <graphics.h>
#include "include.h"
/*
��������صĺ���
*/

#define MAX_DEPTH 10  // �趨���ݹ����
struct dir_tree tree; // Ŀ¼�������ڼ����������Լ�ͨ���������ٶ�λ
/*void tree_make(struct dir_tree* tree, int depth) // Ŀ¼����ʼ��
{
	struct file_info info_for_tree[10] = {0}; // ����ļ���Ϣ
	int i;									  // ѭ������
	int j = 0;								  // ���ڹ�������֦���
	struct dir_tree *p;						  // �����������ָ�룬��������ռ�
	// ��ʼ��tree������֧����
	if (strcmp(tree->path, "") == 0)
	// if (flag == 0)
	{
		// strcpy(tree->path, "C:\\"); // ����Ǹ�����ʼ��ΪC��
		// strcpy(tree->name, "C");
		strcpy(tree->path, "C:\\PROJECT"); // ����Ǹ�����ʼ��ΪC��
		strcpy(tree->name, "PROJECT");
		// strcpy(tree->path, "C:\\BORLANDC"); // ����Ǹ�����ʼ��ΪC��
		// strcpy(tree->name, "BORLANDC");
	}
	tree->is_branch_on = 1;
	for (i = 0; i < 10; i++)
	{
		tree->branch[i] = NULL;
	}
	printf("Building tree for path: %s\n", tree->path); // �������******************************************************
	read_dir(tree->path, info_for_tree);
	// ɸѡ��Fold�����ҹ���tree
	for (i = 0; strcmp(info_for_tree[i].name, "") != 0; i++)
	// for (i = 0; info_for_tree[i].name != 0; i++)
	{
		// if (info_for_tree[i].type == 0 || strcmp(info_for_tree[i].type, "") == 0)
		//	outtextxy(10, i * 10, "erroring");//**************
		// else(outtextxy(10, i * 10, info_for_tree[i].name));//***********
		if (info_for_tree[i].flag == 2 && strcmp(info_for_tree[i].name, "DPMI16BI.OVL") != 0)
		{

			tree->branch[j] = (struct dir_tree *)malloc(sizeof(struct dir_tree)); // ���ڴ�����ռ�
			if (!tree->branch[j])
			{
				perror("Memory allocation failed\n");
				continue;
			}

			// ���Ʒ�֧��Ϣ

			strcpy(tree->branch[j]->name, info_for_tree[i].name); //
			strcpy(tree->branch[j]->path, tree->path);			  // �����֧������·��
			// if (!is_C)//�������c��
			// if (!flag)
			if (strlen(tree->branch[j]->path) > 0 && tree->branch[j]->path[strlen(tree->branch[j]->path) - 1] != '\\')
				strcat(tree->branch[j]->path, "\\");
			strcat(tree->branch[j]->path, tree->branch[j]->name);

			// ��Ŀ¼����Ŀ¼��һ���������ݹ�
			tree_make(tree->branch[j], depth++);
			j++;
		}
	}
	printf("Building tree for path OK!: %s\n", tree->path); // �������******************************************************
}*/

// void tree_make(struct My_filenode *node, int depth)
// {
// 	DIR *dir;
// 	struct dirent *entry;
// 	struct My_filenode *p; // ���ڹ�������һ����Ŀ¼
// 	char path[64];		   // ��ǰ�ڵ����·��
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
// 		return; // �����Ŀ¼ʧ�ܣ�ֹͣ��ȡ
// 	}
// 	printf("Build %s OK\n", path);
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
// 			continue;
// 		// sprintf(tmp, "%s\\%s", path, entry->d_name);
// 		// printf("%s:%d\n", get_file_path(node, entry->d_name), get_file_type((get_file_path(node, entry->d_name)))); // �������
// 		if (get_file_type((get_file_path(node, entry->d_name))) == 2) // �����Ŀ¼
// 		{
// 			if (node->son_list_head == NULL) // ��Ŀ¼ͷ�ڵ�
// 			{
// 				node->son_list_head = (struct My_filenode *)malloc(sizeof(struct My_filenode));
// 				strcpy(node->son_list_head->name, entry->d_name);
// 				node->son_list_head->father = node;
// 				set_bit(&node->son_list_head->flag, 5, 1); // ���λͷ�ڵ�
// 				p = node->son_list_head;
// 				tree_make(p, depth + 1);
// 			}
// 			else // ��Ŀ¼��ͷ�ڵ�
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

void tree_make(struct My_filenode *node, int depth) // Ŀ¼���������ⲿ����ʱ�����Ŀ¼
{
	DIR *dir;
	struct dirent *entry;
	struct My_filenode *p; // ���ڹ�������һ����Ŀ¼
	char *path;			   // ��ǰ�ڵ����·��
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
		return; // �����Ŀ¼ʧ�ܣ�ֹͣ��ȡ
	}
	printf("Build %s OK\n", path);
	if (depth < 2) // Ŀǰֻ�ܶ�ȡ���ڶ������Ŀ¼
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;

			// printf("%s\n", entry->d_name);

			char *file_path = get_file_path(node, entry->d_name);

			// printf("%s\n", file_path);

			if (!file_path)
			{
				closedir(dir);
				return;
			}

			if (get_file_type(file_path) == 2) // �����Ŀ¼
			{
				if (node->son_list_head == NULL) // ��Ŀ¼ͷ�ڵ�
				{
					node->son_list_head = (struct My_filenode *)malloc(sizeof(struct My_filenode));
					if (!node->son_list_head)
					{
						perror("Memory allocation failed for son_list_head");
						free(file_path);
						closedir(dir);
						return;
					}
					// �ڵ��ʼ��
					strcpy(node->son_list_head->name, entry->d_name);
					node->son_list_head->father = node;
					node->son_list_head->next = NULL;
					node->son_list_head->son_list_head = NULL;
					node->son_list_head->flag = 0;
					set_bit(&node->son_list_head->flag, 5, 1); // ���λͷ�ڵ�
					set_bit(&node->son_list_head->flag, 4, 1); // չ��

					p = node->son_list_head;
					tree_make(p, depth + 1);
				}
				else // ��Ŀ¼��ͷ�ڵ�
				{
					p->next = (struct My_filenode *)malloc(sizeof(struct My_filenode));
					if (!p->next)
					{
						perror("Memory allocation failed for next node");
						free(file_path);
						closedir(dir);
						return;
					}
					// �ڵ��ʼ��
					strcpy(p->next->name, entry->d_name);
					p->next->father = node;
					p->next->next = NULL;
					p->next->son_list_head = NULL;
					p->next->flag = 0;
					set_bit(&p->next->flag, 5, 0); // ��ͷ�ڵ�
					set_bit(&p->next->flag, 4, 1); // չ��

					p = p->next;
					tree_make(p, depth + 1);
				}
				free(file_path);
			}
		}
	}
	closedir(dir);
	printf("Build %s OK\n", path);
}

// ��ȡ�ڵ����·��
char *get_node_path(struct My_filenode *node)
{
	// printf("1\n");
	if (node == NULL)
		return NULL;
	// printf("2\n");
	//  ����Ǹ��ڵ㣬ֱ�ӷ���������
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
		// �ݹ��ȡ���ڵ��·��
		char *father_path = get_node_path(node->father);
		// printf("4\n");
		if (father_path == NULL)
			return NULL;

		// ��鸸·���Ƿ��Է�б�ܽ�β
		size_t father_path_len = strlen(father_path);
		if (father_path_len > 0 && father_path[father_path_len - 1] == '\\')
		{
			// �����·���Է�б�ܽ�β����ȥ�����һ���ַ�
			father_path[father_path_len - 1] = '\0';
		}

		// ���������ڴ��С
		size_t len = strlen(father_path) + strlen(node->name) + 2; // +2 ��Ϊ�˷ָ������ַ���������
		char *path = (char *)malloc(len);
		// printf("5\n");
		if (path == NULL)
		{
			free(father_path);
			return NULL;
		}

		// ƴ��·��
		sprintf(path, "%s\\%s", father_path, node->name);
		if (path[0] == '\\')
			strcpy(path, path + 1);

		// �ͷŸ��ڵ�·�����ڴ�
		free(father_path);

		return path;
	}
}

// ��ȡ�ڵ��µ��ļ�·��
char *get_file_path(struct My_filenode *node, char *filename)
{
	char *path = get_node_path(node);
	// printf("6\n");
	if (path == NULL)
		return NULL;

	size_t path_len = strlen(path);
	if (path_len > 0 && path[path_len - 1] != '\\')
	{
		// ����ڵ�·�����Է�б�ܽ�β������ӷ�б��
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
		// ����ڵ�·���Է�б�ܽ�β����ֱ��ƴ���ļ���
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

char *get_file_path_left(struct My_filenode *node, int x, int y);// ������ֱ�ӵ���ļ��У���ȡ�ļ��о���·��
{
	//������λ�ö�Ӧ���ļ�
	if()
}
