#ifndef _INDEX_H_
#define _INDEX_H_
//Ŀ¼���ṹ��
struct dir_tree {
	char name[13];//����
	char path[1024];//��ǰ�ļ���·������������
	struct dir_tree* branch[10];//��֦����Ŀ¼��
	int is_branch_on;//��Ŀ¼�Ƿ�ɼ�
};

void tree_make(struct dir_tree* tree);//����Ŀ¼��

#endif // !_INDEX_H_


