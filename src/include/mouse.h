#ifndef _mouse_h_
#define _mouse_h_
#include <time.h>

int detect_mouse(int x1, int y1, int x2, int y2);                // 检测鼠标是否在框内
int detect_complete_click(int press, time_t current_press_time); // 是否完成完整点击，服务双击检测
int mouse_press(int x1, int y1, int x2, int y2);                 // 如果在框中点击，则返回1；在框中未点击，则返回2；在框中右键，返回3；在框中双击，返回4；不在框中则返回0
int mouse_press_out(int x1, int y1, int x2, int y2);             // 如果在框外点击，返回1；否则返回0
void mouse(int, int);                                            // 设计鼠标
void mouseinit(void);                                            // 初始化
// void mou_pos(int*,int*,int*);//更改鼠标位置
void mread(int *, int *, int *);                // 改坐标不画
void save_bk_mou(int x, int y);                 // 存鼠标背景
void clrmous(int x, int y);                     // 清除鼠标
void drawmous(int x, int y);                    // 画鼠标
void newmouse(int *nx, int *ny, int *nbuttons); // 更新鼠标

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;

#endif
