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
struct dir_tree tree;//Ŀ¼�������ڼ����������Լ�ͨ���������ٶ�λ

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
	tree->is_branch_on = 0;
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
