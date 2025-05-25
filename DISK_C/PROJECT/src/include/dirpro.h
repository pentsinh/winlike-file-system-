#include <dirent.h>
#ifndef _DIR_PRO_H_
#define _DIR_PRO_H
#ifndef HISTORY_LENGTH
#define HISTORY_LENGTH 10
#endif
#include "include.h"
/************************************************
 *FUNCTION:��ȡĿ��Ŀ¼���ļ�
 *INPUT:Ŀ��Ŀ¼������·���������ڴ�Ŷ�ȡ�����file_info�ṹ�壬ҳ��ָ��
 *RETURN:��
 *************************************************/
// void read_dir(char *target, struct file_info *info);
void read_dir(char *target, struct file_info *info, int *page);

/************************************************
 *FUNCTION:����Ŀ¼����
 *INPUT:������ʷ����ǰ����ʷ�����е�λ��
 *RETURN:1 ������Ч��0 ������Ч
 *************************************************/
int undo_dir(char history[HISTORY_LENGTH][1024], int *now_history);

/************************************************
 *FUNCTION:������Ŀ¼����
 *INPUT:������ʷ����ǰ����ʷ�����е�λ��
 *RETURN:1 ������Ч��0 ������Ч
 *************************************************/
int anti_undo_dir(char history[HISTORY_LENGTH][1024], int *now_history);

/************************************************
 *FUNCTION:������һ��Ŀ¼
 *INPUT:��ǰ·����������ʷ����ǰ����ʷ�����е�λ��
 *RETURN:1 ������Ч��0 ������Ч
 *************************************************/
int back(char path[1024], char history[HISTORY_LENGTH][1024], int *now_history);

/************************************************
 *FUNCTION:����Ŀ¼������ʷ
 *INPUT:������ʷ����ǰ·��
 *RETURN:��
 *************************************************/
void new_history(char history[HISTORY_LENGTH][1024], char path[1024]);

/************************************************
 *FUNCTION: ����Ŀ¼
 *INPUT:��ǰ��ʾ��info�����X�����Y��ͼ���С��־
 *RETURN:����1ѡ�У�����2ȷ��
 *************************************************/
int change_dir(struct file_info *info, int x, int y,int pic_flag);

/************************************************
 *FUNCTION: ��������ļ���
 *INPUT:·����·����������
 *RETURN:1
 *************************************************/
int keyin_dir(char path[1024], int length);

#endif // _DIR_PRO_H_
