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
 *FUNCTION:下拉菜单
 *NOTICE:原版来自杨征坷学长，此为中文版，点击选项后收起，点击外部收起，菜单增加了x方向的出画面判断（优化掉了一半代码）（改变了x,y的含义），取消record参数，新增son_menu参数
 *INPUT:菜单左上X，菜单左上Y，菜单宽度，单个选项高度，选项数量，字体大小，选项们，亮部颜色，暗部颜色，是否有子菜单
 *RETURN:点击选项在msgs中的序号，未选择返回 -1
 *************************************************/
int drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char **msgs, int lightcolor, int darkcolor, int son_menu);
#endif // !_LOAD_H_
