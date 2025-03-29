#ifndef _LOAD_H_
#define _LOAD_H_
#include "dir_pro.h"
/************************************************
 *FUNCTION:界面初始化
 *INPUT:当前路径，将要显示的info，操作历史
 *RETURN:无
 *************************************************/
void load_init(char path[1024], struct file_info *info, char history[HISTORY_LENGTH][1024]);

/************************************************
 *FUNCTION:加载界面
 *INPUT:当前路径，将要显示的info，目录树根，搜索目标，显示模式
 *RETURN:无
 *************************************************/
void load_all(char path[1024], struct file_info *info, struct My_filenode *root, char *target, int mode);

/************************************************
 *FUNCTION:加载top栏
 *INPUT:当前路径，搜索目标，模式
 *RETURN:无
 *************************************************/
void load_top(char path[1024], char *target, int mode);

/************************************************
 *FUNCTION:加载head栏
 *INPUT:显示模式
 *RETURN:无
 *************************************************/
void load_head(int mode);

/************************************************
 *FUNCTION:加载left栏
 *INPUT:目录树根
 *RETURN:无
 *************************************************/
void load_left(struct My_filenode *root);

/************************************************
 *FUNCTION:加载左栏辅助函数，加载出传入地址的所有子目录
 *INPUT:节点，递归层数，当前画笔X，当前画笔Y的地址
 *RETURN:无
 *************************************************/
void load_left_assist(struct My_filenode *p, int layer, int pen_x, int *pen_y);

/************************************************
 *FUNCTION:加载main栏
 *INPUT:将要显示的info，显示模式
 *RETURN:无
 *************************************************/
void load_main(struct file_info *info, int mode);

/************************************************
 *FUNCTION:清空指定矩形区域
 *INPUT:矩形左上X，矩形左上Y，矩形右上X，矩形右上Y，颜色
 *RETURN:无
 *************************************************/
void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color);

/************************************************
 *FUNCTION:显示下拉菜单
 *INPUT:点击X，点击Y，单个选项的高度，选项们
 *RETURN:无
 *************************************************/
void pull_list(int x, int y, int height, char menu[8][16]);
#endif // !_LOAD_H_
