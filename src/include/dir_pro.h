#include <dirent.h>
#include <direct.h> 
#ifndef _DIR_PRO_H_
#define _DIR_PRO_H
#ifndef HISTORY_LENGTH
#define HISTORY_LENGTH 10
#endif
void read_dir(DIR* dir, struct dirent* entry, struct file_info* info);//读取当前目录下文件
void undo_dir();//撤销目录操作
void anti_undo_dir();//反撤销目录操作
void back();//返回上一级目录
void new_history();//更新目录操作历史
int change_dir(struct file_info* info, int x, int y);//更改目录.返回1选中，返回2确认
#endif // _DIR_PRO_H_
