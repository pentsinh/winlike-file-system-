#ifndef _MSCONTRB_H_
#define _MSCONTRB_H_
/*
鼠标库扩展，不可单独使用
*/

/************************************************
 *FUNCTION:检测完整点击过程
 *INPUT:按键状态，当前点击时间
 *RETURN:0 状态未改变，1 完成一次完整点击
 *************************************************/
int detect_complete_click(int press, time_t current_press_time);

/************************************************
 *FUNCTION:检测鼠标是否在框内
 *INPUT:左上X，左上Y，右下X，右下Y
 *RETURN:1 在，0 不在
 *************************************************/
int detect_m(int x1, int y1, int x2, int y2);

/************************************************
 *FUNCTION:/如果在框外点击
 *INPUT:左上X，左上Y，右下X，右下Y
 *RETURN:1 点击，0未点击
 *************************************************/
int mouse_press_out(int x1, int y1, int x2, int y2);
#endif