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
��������صĺ���
*/
#define TEST
#define MAX_DEPTH 10  // �趨���ݹ����
struct dir_tree tree; // Ŀ¼�������ڼ����������Լ�ͨ���������ٶ�λ

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
#ifdef TEST
	printf("Building %s\n", path);
#endif
	if (!dir)
	{
		perror("Failed to open directory");
		return; // �����Ŀ¼ʧ�ܣ�ֹͣ��ȡ
	}
#ifdef TEST
	printf("Build %s OK\n", path);
#endif
	//  if (depth < 3) // Ŀǰֻ�ܶ�ȡ���ڶ������Ŀ¼
	//  {
	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		char *file_path = get_file_path_node(node, entry->d_name);

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
				set_bit(&node->son_list_head->flag, 5, 1);	   // ���λͷ�ڵ�
				if (depth == 0)								   // ��һ��Ŀ¼Ĭ�Ͽɼ�
					set_bit(&node->son_list_head->flag, 4, 1); // չ��

				p = node->son_list_head;
				if (depth < 2) // ���Ƶݹ����
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
				set_bit(&p->next->flag, 5, 0);	   // ��ͷ�ڵ�
				if (depth == 0)					   // ��һ��Ŀ¼Ĭ�Ͽɼ�
					set_bit(&p->next->flag, 4, 1); // չ��

				p = p->next;
				if (depth < 2) // ���Ƶݹ����
					tree_make(p, depth + 1);
			}
			free(file_path);
		}
	}
	//}
	closedir(dir);
#ifdef TEST
	printf("Build %s OK\n", path);
#endif
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
char *get_file_path_node(struct My_filenode *node, char *filename)
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

// ������ֱ�ӵ���ļ��У�����root��ȡ�ļ��о���·��****�����������չ������Ŀ¼��ǰ��****
char *get_file_path_left(struct My_filenode *node, int x, int y)
{

	struct My_filenode *p = node->son_list_head;
	if (p == NULL)
		return NULL;
	// ������λ�ö�Ӧ���ļ�
	int row;										  // ���λ��Ϊ�ڼ��У�***֮�󽫲�������***
	int i;											  // y������
	for (i = 80, row = 1; i < 480; i += 10, row += 1) // ��һ����y=80��ʼ
	{
		if (y > i && y < i + 10)
			break;
	}
	do
	{
		if (count_son_son_visible(p) + 1 >= row && x > 30) // ��һ��Ŀ¼����
		{
			if (row == 1) // һ��Ŀ¼δչ��
				return get_file_path_node(p->father, p->name);
			else
			{
				p = p->son_list_head;
				row -= 1; // ����һ��Ŀ¼���ڶ���Ŀ¼�в���
				do
				{
					if (count_son_visible(p) + 1 >= row && x > 40)
					{
						if (row == 1) // ����ö���Ŀ¼δչ��
							return get_file_path_node(p->father, p->name);

						else
						{
							p = p->son_list_head;
							row -= 1;
							for (i = 1; p->next != NULL; i++) // 20Ϊ��ֹ��ѭ����������
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

int count_son_visible(struct My_filenode *node) // ����ɼ���Ŀ¼����
{
	if (get_bit(node->flag, 4) == 0) // �������Ŀ¼δչ��
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

// ����ɼ���Ŀ¼����ɼ���Ŀ¼����
int count_son_son_visible(struct My_filenode *node)
{
	if (get_bit(node->flag, 4) == 0) // �������Ŀ¼δչ��
		return 0;
	struct My_filenode *p = node->son_list_head;
	int num = 0;
	if (p == NULL)
		return 0;
	do
	{
		num++;
		if (get_bit(p->flag, 4) == 1) // �����Ŀ¼չ�����ɼ���
			num += count_son_visible(p);
		p = p->next;

	} while (p != NULL);
	return num;
}

int unfold(struct My_filenode *node, int x, int y) // ���>չ��������1��/���𣨷���2��Ŀ¼***������㷨�ο������get_file_path_left�����ﲻ��д��ϸע��***
{
	// ������λ�ö�Ӧ���ļ�
	struct My_filenode *p = node->son_list_head;
	if (p == NULL)
		return 0;
	int row;										  // ���λ��Ϊ�ڼ��У�***֮�󽫲�������***
	int i;											  // y������
	for (i = 80, row = 1; i < 480; i += 10, row += 1) // ��һ����y=80��ʼ
	{
		if (y > i && y < i + 10)
			break;
	}
	do
	{
		if (count_son_son_visible(p) + 1 >= row) // ��һ��Ŀ¼����
		{
			if (row == 1 && get_bit(p->flag, 4) == 0 && x > 20 && x < 30) // һ��Ŀ¼δչ��
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
				row -= 1; // ����һ��Ŀ¼���ڶ���Ŀ¼�в���
				do
				{
					if (count_son_visible(p) + 1 >= row)
					{
						if (row == 1 && get_bit(p->flag, 4) == 0 && x > 30 && x < 40) // ����ö���Ŀ¼δչ��
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
							for (i = 1; i < 20; i++) // 20Ϊ��ֹ��ѭ����������
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

// �۵�����ڵ��������Ŀ¼
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