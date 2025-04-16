#ifndef _INTERACTION_H_
#define _INTERACTION_H_
/************************************************
 *FUNCTION:清除键盘缓冲区
 *INPUT:无
 *RETURN:无
 *************************************************/
void clear_keyboard_buffer();

/************************************************
 *FUNCTION:显示输入框
 *INPUT:输入内容，最大长度，左上角X，左上角Y，字体大小，背景颜色，字体颜色
 *RETURN:无
 *************************************************/
void out_keybd(char *text, int max, int x, int y, int lettersize, int bkcolor, int lettercolor);

/************************************************
 *FUNCTION:绘制4个window
 *INPUT:无
 *RETURN:无
 *************************************************/
void draw_windows(int x, int y, int size);

/************************************************
 *FUNCTION:绘制单个window
 *INPUT:无
 *RETURN:无
 *************************************************/
void draw_window(int x, int y, int size, int color);

/************************************************
 *FUNCTION:获取键盘输入（登陆专用，等待优化）
 *INPUT:输入目标，最大长度
 *RETURN:0：未输入；1：正在输入；2：输入完成
 *************************************************/
int getbuffer_keybd(char *target, int max);

/************************************************
 *FUNCTION:// 计算三点圆弧，原版算法来自github，修改后提高了功能性但是可能降低了可移植性
 *INPUT:点1的x，点1的y，点2的x，点2的y，点3的x，点3的y，用于储存圆弧的数据的数组的头地址
 *RETURN:无
 *************************************************/
void radius_3pts(float x1, float y1, float x2, float y2, float x3, float y3, int *circle);

#endif