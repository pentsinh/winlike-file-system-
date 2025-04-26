#ifndef _INDEX_H_
#define _INDEX_H_
#include "include.h"
// Ŀ¼���ṹ��
struct dir_tree
{
	char name[13];				 // ����
	char path[1024];			 // ��ǰ�ļ���·������������
	struct dir_tree *branch[10]; // ��֦����Ŀ¼��
	int is_branch_on;			 // ��Ŀ¼�Ƿ�ɼ�
};

struct My_filenode
{
	unsigned char flag;
	char name[13];
	// char *time; // �޸�����
	// char *size; // ��С
	struct My_filenode *next;
	struct My_filenode *father;		   // ͬһ������ͬһ�����ڵ㣨Ϊ����������һ�����ܣ�
	struct My_filenode *son_list_head; // һ�����ڵ�ӵ��������ͷ�ڵ��ַ
};

/************************************************
 *FUNCTION:Ŀ¼������
 *INPUT:Ŀ¼���ĸ����ݹ��������
 *RETURN:��
 *************************************************/
void tree_make(struct My_filenode *node, int depth);

/************************************************
 *FUNCTION:��ȡ�ڵ����·��
 *INPUT:Ŀ��ڵ�
 *RETURN:����·��
 *************************************************/
char *get_node_path(struct My_filenode *node);

/************************************************
 *FUNCTION: ��ȡĳĿ¼��ĳ�ļ����У��ľ���·��
 *INPUT:Ŀ¼�ڵ㣬Ŀ¼�µ��ļ���
 *RETURN:����·��
 *************************************************/
char *get_file_path_node(struct My_filenode *node, char *filename);

/************************************************
 *FUNCTION:������ֱ�ӵ���ļ��У���ȡ�ļ�·��#####�����������չ������Ŀ¼��ǰ��#####
 *INPUT:Ŀ¼���ĸ������X�����Y
 *RETURN:�ļ��о���·��
 *************************************************/
char *get_file_path_left(struct My_filenode *node, int x, int y);

/************************************************
 *FUNCTION:����ɼ���Ŀ¼����
 *INPUT:Ŀ¼�ڵ�
 *RETURN:�ɼ���Ŀ¼����
 *************************************************/
int count_son_visible(struct My_filenode *node);

/************************************************
 *FUNCTION:����ɼ���Ŀ¼����ɼ���Ŀ¼����
 *INPUT:Ŀ¼�ڵ�
 *RETURN:�ɼ���Ŀ¼����ɼ���Ŀ¼����
 *************************************************/
int count_son_son_visible(struct My_filenode *node);

/************************************************
 *FUNCTION:���>չ��Ŀ¼
 *INPUT:Ŀ¼���ĸ������X�����Y
 *RETURN:����1��չ��������2������
 *************************************************/
int unfold(struct My_filenode *node, int x, int y);

/************************************************
 *FUNCTION:�۵�����ڵ��������Ŀ¼
 *INPUT:Ŀ¼�ڵ�
 *RETURN:��
 *************************************************/
void fold_sonlist(struct My_filenode *node);

#endif // !_INDEX_H_
