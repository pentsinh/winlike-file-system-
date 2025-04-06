#ifndef _PROPERTY_H_
#define _PROPERTY_H_
/************************************************
 *FUNCTION:显示文件（夹）属性
 *NOTICE:两个中有一个为NULL
 *INPUT:文件（夹）绝对路径，指向文件（夹）的file_info结构体的指针
 *RETURN:无
 *************************************************/
void property(char *path, struct file_info *info);
#endif