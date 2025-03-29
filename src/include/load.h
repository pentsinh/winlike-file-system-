#ifndef _LOAD_H_
#define _LOAD_H_
#include "dir_pro.h"
/************************************************
 *FUNCTION:�����ʼ��
 *INPUT:��ǰ·������Ҫ��ʾ��info��������ʷ
 *RETURN:��
 *************************************************/
void load_init(char path[1024], struct file_info *info, char history[HISTORY_LENGTH][1024]);

/************************************************
 *FUNCTION:���ؽ���
 *INPUT:��ǰ·������Ҫ��ʾ��info��Ŀ¼����������Ŀ�꣬��ʾģʽ
 *RETURN:��
 *************************************************/
void load_all(char path[1024], struct file_info *info, struct My_filenode *root, char *target, int mode);

/************************************************
 *FUNCTION:����top��
 *INPUT:��ǰ·��������Ŀ�꣬ģʽ
 *RETURN:��
 *************************************************/
void load_top(char path[1024], char *target, int mode);

/************************************************
 *FUNCTION:����head��
 *INPUT:��ʾģʽ
 *RETURN:��
 *************************************************/
void load_head(int mode);

/************************************************
 *FUNCTION:����left��
 *INPUT:Ŀ¼����
 *RETURN:��
 *************************************************/
void load_left(struct My_filenode *root);

/************************************************
 *FUNCTION:���������������������س������ַ��������Ŀ¼
 *INPUT:�ڵ㣬�ݹ��������ǰ����X����ǰ����Y�ĵ�ַ
 *RETURN:��
 *************************************************/
void load_left_assist(struct My_filenode *p, int layer, int pen_x, int *pen_y);

/************************************************
 *FUNCTION:����main��
 *INPUT:��Ҫ��ʾ��info����ʾģʽ
 *RETURN:��
 *************************************************/
void load_main(struct file_info *info, int mode);

/************************************************
 *FUNCTION:���ָ����������
 *INPUT:��������X����������Y����������X����������Y����ɫ
 *RETURN:��
 *************************************************/
void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color);

/************************************************
 *FUNCTION:��ʾ�����˵�
 *INPUT:���X�����Y������ѡ��ĸ߶ȣ�ѡ����
 *RETURN:��
 *************************************************/
void pull_list(int x, int y, int height, char menu[8][16]);
#endif // !_LOAD_H_
