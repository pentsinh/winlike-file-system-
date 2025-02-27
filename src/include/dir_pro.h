#include <dirent.h>
#include <direct.h> 
#ifndef _DIR_PRO_H_
#define _DIR_PRO_H
#ifndef HISTORY_LENGTH
#define HISTORY_LENGTH 10
#endif
//Ŀ¼���ṹ��
struct dir_tree {
	char name[13];//����
	char path[1024];//��ǰ�ļ���·������������
	struct dir_tree* branch[10];//��֦����Ŀ¼��
};
void read_dir(DIR* dir, struct dirent* entry, struct file_info* info);//��ȡ��ǰĿ¼���ļ�
void undo_dir();//����Ŀ¼����
void anti_undo_dir();//������Ŀ¼����
void back();//������һ��Ŀ¼
void new_history();//����Ŀ¼������ʷ
int change_dir(struct file_info* info, int x, int y);//����Ŀ¼.����1ѡ�У�����2ȷ��

void tree_make(struct dir_tree* tree);//����Ŀ¼��
#endif // _DIR_PRO_H_
