#include <dirent.h>
#ifndef _DIR_PRO_H_
#define _DIR_PRO_H
#ifndef HISTORY_LENGTH
#define HISTORY_LENGTH 10
#endif
#include "include.h"
/************************************************
 *FUNCTION:读取目标目录下文件
 *INPUT:目标目录（绝对路径），用于存放读取结果的file_info结构体，页码指针
 *RETURN:无
 *************************************************/
// void read_dir(char *target, struct file_info *info);
void read_dir(char *target, struct file_info *info, int *page);

/************************************************
 *FUNCTION:撤销目录操作
 *INPUT:操作历史，当前在历史数组中的位置
 *RETURN:1 操作有效；0 操作无效
 *************************************************/
int undo_dir(char history[HISTORY_LENGTH][1024], int *now_history);

/************************************************
 *FUNCTION:反撤销目录操作
 *INPUT:操作历史，当前在历史数组中的位置
 *RETURN:1 操作有效；0 操作无效
 *************************************************/
int anti_undo_dir(char history[HISTORY_LENGTH][1024], int *now_history);

/************************************************
 *FUNCTION:返回上一级目录
 *INPUT:当前路径，操作历史，当前在历史数组中的位置
 *RETURN:1 操作有效；0 操作无效
 *************************************************/
int back(char path[1024], char history[HISTORY_LENGTH][1024], int *now_history);

/************************************************
 *FUNCTION:更新目录操作历史
 *INPUT:操作历史，当前路径
 *RETURN:无
 *************************************************/
void new_history(char history[HISTORY_LENGTH][1024], char path[1024]);

/************************************************
 *FUNCTION: 更改目录
 *INPUT:当前显示的info，鼠标X，鼠标Y，图标大小标志
 *RETURN:返回1选中，返回2确认
 *************************************************/
int change_dir(struct file_info *info, int x, int y,int pic_flag);

/************************************************
 *FUNCTION: 键入进入文件夹
 *INPUT:路径，路径长度限制
 *RETURN:1
 *************************************************/
int keyin_dir(char path[1024], int length);

#endif // _DIR_PRO_H_
