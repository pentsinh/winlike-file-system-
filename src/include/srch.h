#ifndef _SRCH_H_
#define _SRCH_H_

/************************************************
 *FUNCTION:搜索模式下，从键盘读取输入
 *INPUT:搜索目标，用于存放搜索结果的info，用于指向被loading遮挡图像的指针
 *RETURN:返回1：有输入；返回0：无输入
 *************************************************/
int srch_input(char target[16], struct file_info *info, void *buffer);

/************************************************
 *FUNCTION:启动搜索！！！
 *INPUT:搜索路径，目标，将要存入info的位置，用于存放信息的info数组,递归深度
 *RETURN:无
 *************************************************/
void srch(char *path, char *target, int *position, struct file_info *info, int depth);

/************************************************
 *FUNCTION:将搜索内容输出
 *INPUT:当前路径，用于存放搜索结果的info，目录树根，搜索目标
 *RETURN:无
 *************************************************/
void srch_output(char *path, struct file_info *info, struct My_filenode *root, char *target);
#endif // !_SRCH_H_
