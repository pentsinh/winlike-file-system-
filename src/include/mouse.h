#ifndef _mouse_h_
#define _mouse_h_
#include <time.h>

// void interrupt(*oldTimerInt)(void);// 中断向量表备份
// void interrupt timerISR(void);// 定时器中断服务程序
// void init_timer_interrupt();// 初始化定时器中断

// void wait_and_reset();//子进程函数

// #define DOUBLEPRESS_TIME 6

// enum mousepress_change //状态不变者，为0
// {
// 	PTOP,	  //按下到按下
// 	PTOB,	  //按下到弹起
// 	BTOP,	  //弹起到按下
// 	BTOB = 0, //弹起到弹起
// };

int detect_complete_click(int press, time_t current_press_time); // 是否完成完整点击，服务双击检测
int mouse_press(int x1, int y1, int x2, int y2);				 // 如果在框中点击，则返回1；在框中未点击，则返回2；在框中右键，返回3；在框中双击，返回4；不在框中则返回0
int mouse_press_out(int x1, int y1, int x2, int y2);			 // 如果在框外点击，返回1；否则返回0
void mouse(int, int);											 // 设计鼠标
void mouseinit(void);											 // 初始化
// void mou_pos(int*,int*,int*);//更改鼠标位置
void mread(int *, int *, int *);				// 改坐标不画
void save_bk_mou(int x, int y);					// 存鼠标背景
void clrmous(int x, int y);						// 清除鼠标
void drawmous(int x, int y);					// 画鼠标
void newmouse(int *nx, int *ny, int *nbuttons); // 更新鼠标

///********************************
// * FUNCTION:inittimer
// * DESCRIPTION:初始化定时器，精度18.2分之一秒
// * INPUT:无
// * RETURN:无
// * OTHERS:无
// ********************************/
// void inittimer(void);
//
///********************************
// * FUNCTION:judgetimer
// * DESCRIPTION:判断计时函数
// * INPUT:时间间隔（单位为18.2分之一秒）
// * RETURN:0或者1
// * OTHERS:输入时间间隔（），时间达到或者超过设定值返回1并重置计时器，时间未达到设定值返回0
// ********************************/
// int judgetimer(long interval);
//
///****************************
// * 防止按键连续调用功能（关于长按的适配和按一次随缘调用模块的避免）
// * 传递参数：无
// * 返回值：无
// * ***************************/
// void longpress_fit(void);
//
///**********************************
// * 双击检测函数
// * 最多持续7/9秒，检测是否双击
// * 传递参数：方框坐标
// * 返回值：双击为1，非双击为0
////  * *********************************/
// int testmouse_doublepress(int x1, int y1, int x2, int y2);
//
///********************************
// * 鼠标点击状态变化检测函数
// * 用于检测鼠标状态切换
// * 传递参数：上一个循环鼠标按下状态数据，本次循环鼠标按下状态数据
// * 返回值：0为不变，1为按到不按，2为不按到按
// * ********************************/
// int testmouse_presschange(int press_last, int press_new);

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;

#endif
