#ifndef _SRCH_H_
#define _SRCH_H_

int srch_input(char target[16], struct file_info *info);                               // 搜索模式下，从键盘读取输入，返回1：有输入；返回0：无输入
void srch(char *path, char *target, int *position, struct file_info *info, int depth); // 启动搜索！！！参数：搜索路径，目标，将要存入info的位置，用于存放信息的info数组,递归深度
void srch_output(struct file_info *info, char *target);                                // 将搜索内容输出
#endif                                                                                 // !_SRCH_H_
