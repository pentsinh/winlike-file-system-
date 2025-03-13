#ifndef _INDEX_H_
#define _INDEX_H_
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
	struct My_filenode *next;
	struct My_filenode *father;		   // ͬһ������ͬһ�����ڵ㣨Ϊ����������һ�����ܣ�
	struct My_filenode *son_list_head; // һ�����ڵ�ӵ��������ͷ�ڵ��ַ
};

// void tree_make(struct dir_tree* tree,int depth);//����Ŀ¼��
void tree_make(struct My_filenode *node, int depth);			  // Ŀ¼������
char *get_node_path(struct My_filenode *node);					  // ��ȡ�ڵ����·��
char *get_file_path(struct My_filenode *node, char *filename);	  // ��ȡĳĿ¼��ĳ�ļ����У��ľ���·��
char *get_file_path_left(struct My_filenode *node, int x, int y); // ������ֱ�ӵ���ļ��У���ȡ�ļ��о���·��
#endif															  // !_INDEX_H_
