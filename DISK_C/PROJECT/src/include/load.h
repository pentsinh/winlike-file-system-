#ifndef _LOAD_H_
#define _LOAD_H_
#include "dirpro.h"
#include "include.h"
/************************************************
 *FUNCTION:�����ʼ��
 *INPUT:��ǰ·������Ҫ��ʾ��info��������ʷ
 *RETURN:��
 *************************************************/
void load_init(char path[1024], struct file_info *info, char history[HISTORY_LENGTH][1024]);

/************************************************
 *FUNCTION:���ؽ���
 *INPUT:��ǰ·������Ҫ��ʾ��info��Ŀ¼����������Ŀ�꣬��ʾģʽ��ƫ�ã�ҳ�룬ͼƬ��С��־
 *RETURN:��
 *************************************************/
void load_all(char path[1024], struct file_info *info, struct My_filenode *root, char *target, int mode, char preference[3][1024], int page,int pic_flag);

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
 *INPUT:Ŀ¼������ƫ��
 *RETURN:��
 *************************************************/
void load_left(struct My_filenode *root, char preference[3][1024]);

/************************************************
 *FUNCTION:���������������������س������ַ��������Ŀ¼
 *INPUT:�ڵ㣬�ݹ��������ǰ����X����ǰ����Y�ĵ�ַ
 *RETURN:��
 *************************************************/
void load_left_assist(struct My_filenode *p, int layer, int pen_x, int *pen_y);

/************************************************
 *FUNCTION:����main��
 *INPUT:��Ҫ��ʾ��info����ʾģʽ��ҳ�룬ͼƬ��С��־
 *RETURN:��
 *************************************************/
void load_main(struct file_info *info, int mode, int page,int pic_flag);

/************************************************
 *FUNCTION:����һ���ļ�
 *INPUT:����x������y��infoָ�룬ͼƬ��С��־
 *RETURN:��
 *************************************************/
void load_file_info(int x, int y, struct file_info *info, int pic_flag);

/************************************************
 *FUNCTION:���ָ����������
 *INPUT:��������X����������Y����������X����������Y����ɫ
 *RETURN:��
 *************************************************/
void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color);

/************************************************
 *FUNCTION:�����˵�
 *INPUT:�˵�����X���˵�����Y���˵���ȣ�����ѡ��߶ȣ�ѡ�������������С��ѡ���ǣ�������ɫ��������ɫ�����ԣ�0���ģ�1Ӣ�ģ��Ƿ����Ӳ˵�
 *RETURN:���ѡ����msgs�е���ţ�δѡ�񷵻� -1
 *************************************************/
int drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char **msgs, int lightcolor, int darkcolor, int language, int son_menu);

/************************************************
 *FUNCTION:�����С�����
 *INPUT:����ָ��
 *RETURN:��
 *************************************************/
void loading(void *buffer);

/************************************************
 *FUNCTION:�������
 *INPUT:����ָ��
 *RETURN:��
 *************************************************/
void loading_ok(void *buffer);

/************************************************
 *FUNCTION:���½�
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_new(int x, int y);

/************************************************
 *FUNCTION:�����м���
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_scissor(int x, int y);

/************************************************
 *FUNCTION:������
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_copy(int x, int y);

/************************************************
 *FUNCTION:��ճ��
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_paste(int x, int y);

/************************************************
 *FUNCTION:��������
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_rename(int x, int y);

/************************************************
 *FUNCTION:������Ͱ
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_trash(int x, int y);

/************************************************
 *FUNCTION:������
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_sort(int x, int y);

/************************************************
 *FUNCTION:���鿴
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_check(int x, int y);

/************************************************
 *FUNCTION:�����ͷ
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_left(int x, int y);

/************************************************
 *FUNCTION:���Ҽ�ͷ
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_right(int x, int y);

/************************************************
 *FUNCTION:���ϼ�ͷ
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_up(int x, int y);

/************************************************
 *FUNCTION:��ˢ��
 *INPUT:����X������Y
 *RETURN:��
 *************************************************/
void draw_refresh(int x, int y);

/************************************************
 *FUNCTION:�������ļ����У�
 *INPUT:����X������Y����С��0С��1�У�
 *RETURN:��
 *************************************************/
void draw_file(int x, int y, int flag);
void draw_txt(int x, int y, int flag);
void draw_c(int x, int y, int flag);
void draw_cpp(int x, int y, int flag);
void draw_exe(int x, int y, int flag);
void draw_jpg(int x, int y, int flag);
void draw_png(int x, int y, int flag);
void draw_doc(int x, int y, int flag);
void draw_xls(int x, int y, int flag);
void draw_ppt(int x, int y, int flag);
void draw_pdf(int x, int y, int flag);
void draw_h(int x, int y, int flag);
void draw_obj(int x, int y, int flag);
void draw_other(int x, int y, int flag);
#endif // !_LOAD_H_
