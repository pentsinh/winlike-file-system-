#ifndef _LOAD_H_
#define _LOAD_H_
void load_init(struct file_info *info); // 界面初始化
void load_all(struct file_info *info);  // 加载界面
void load_top();                        // 加载top栏
void load_head();                       // 加载head栏
void load_left();                       // 加载left栏
// void load_left_assist(struct dir_tree* p, int layer, int pen_x, int* pen_y);//加载左栏辅助函数，加载出传入地址的所以子目录
void load_left_assist(struct My_filenode *p, int layer, int pen_x, int *pen_y); // 加载左栏辅助函数，加载出传入地址的所以子目录
void load_main(struct file_info *info);                                         // 加载main栏
void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color);       // 清空指定矩形区域
#endif                                                                          // !_LOAD_H_
