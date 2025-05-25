#ifndef _LOAD_H_
#define _LOAD_H_
#include "dirpro.h"
#include "include.h"
/************************************************
 *FUNCTION:界面初始化
 *INPUT:当前路径，将要显示的info，操作历史
 *RETURN:无
 *************************************************/
void load_init(char path[1024], struct file_info *info, char history[HISTORY_LENGTH][1024]);

/************************************************
 *FUNCTION:加载界面
 *INPUT:当前路径，将要显示的info，目录树根，搜索目标，显示模式，偏好，页码，图片大小标志
 *RETURN:无
 *************************************************/
void load_all(char path[1024], struct file_info *info, struct My_filenode *root, char *target, int mode, char preference[3][1024], int page,int pic_flag);

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
 *INPUT:目录树根，偏好
 *RETURN:无
 *************************************************/
void load_left(struct My_filenode *root, char preference[3][1024]);

/************************************************
 *FUNCTION:加载左栏辅助函数，加载出传入地址的所有子目录
 *INPUT:节点，递归层数，当前画笔X，当前画笔Y的地址
 *RETURN:无
 *************************************************/
void load_left_assist(struct My_filenode *p, int layer, int pen_x, int *pen_y);

/************************************************
 *FUNCTION:加载main栏
 *INPUT:将要显示的info，显示模式，页码，图片大小标志
 *RETURN:无
 *************************************************/
void load_main(struct file_info *info, int mode, int page,int pic_flag);

/************************************************
 *FUNCTION:加载一条文件
 *INPUT:左上x，左上y，info指针，图片大小标志
 *RETURN:无
 *************************************************/
void load_file_info(int x, int y, struct file_info *info, int pic_flag);

/************************************************
 *FUNCTION:清空指定矩形区域
 *INPUT:矩形左上X，矩形左上Y，矩形右上X，矩形右上Y，颜色
 *RETURN:无
 *************************************************/
void clearRectangle(int x1, int y1, int x2, int y2, unsigned char color);

/************************************************
 *FUNCTION:下拉菜单
 *INPUT:菜单左上X，菜单左上Y，菜单宽度，单个选项高度，选项数量，字体大小，选项们，亮部颜色，暗部颜色，语言（0中文，1英文）是否有子菜单
 *RETURN:点击选项在msgs中的序号，未选择返回 -1
 *************************************************/
int drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char **msgs, int lightcolor, int darkcolor, int language, int son_menu);

/************************************************
 *FUNCTION:加载中。。。
 *INPUT:缓存指针
 *RETURN:无
 *************************************************/
void loading(void *buffer);

/************************************************
 *FUNCTION:加载完成
 *INPUT:缓存指针
 *RETURN:无
 *************************************************/
void loading_ok(void *buffer);

/************************************************
 *FUNCTION:画新建
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_new(int x, int y);

/************************************************
 *FUNCTION:画剪切剪刀
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_scissor(int x, int y);

/************************************************
 *FUNCTION:画复制
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_copy(int x, int y);

/************************************************
 *FUNCTION:画粘贴
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_paste(int x, int y);

/************************************************
 *FUNCTION:画重命名
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_rename(int x, int y);

/************************************************
 *FUNCTION:画垃圾桶
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_trash(int x, int y);

/************************************************
 *FUNCTION:画排序
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_sort(int x, int y);

/************************************************
 *FUNCTION:画查看
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_check(int x, int y);

/************************************************
 *FUNCTION:画左箭头
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_left(int x, int y);

/************************************************
 *FUNCTION:画右箭头
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_right(int x, int y);

/************************************************
 *FUNCTION:画上箭头
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_up(int x, int y);

/************************************************
 *FUNCTION:画刷新
 *INPUT:左上X，左上Y
 *RETURN:无
 *************************************************/
void draw_refresh(int x, int y);

/************************************************
 *FUNCTION:画各种文件（夹）
 *INPUT:左上X，左上Y，大小（0小，1中）
 *RETURN:无
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
