#ifndef _LOAD_H_
#define _LOAD_H_
void load_init(struct file_info *info); // �����ʼ��
void load_all(struct file_info *info);  // ���ؽ���
void load_top();                        // ����top��
void load_head();                       // ����head��
void load_left();                       // ����left��
// void load_left_assist(struct dir_tree* p, int layer, int pen_x, int* pen_y);//���������������������س������ַ��������Ŀ¼
void load_left_assist(struct My_filenode *p, int layer, int pen_x, int *pen_y); // ���������������������س������ַ��������Ŀ¼
void load_main(struct file_info *info);                                         // ����main��
void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color);       // ���ָ����������
#endif                                                                          // !_LOAD_H_
