#ifndef _COPA_H_
#define _COPA_H_
#include "include.h"
/************************************************
 *FUNCTION:复制粘贴文件（夹）
 *INPUT:源文件绝对路径，目标所在目录绝对路径
 *RETURN:0 成功；-1 失败
 *************************************************/
int c_p(char *source_path, char *dest_father_path);

/************************************************
 *FUNCTION:复制粘贴文件
 *INPUT:源文件绝对路径，目标所在目录绝对路径
 *RETURN:0 成功；-1 失败
 *************************************************/
int copy_file(const char *source_path, const char *dest_path);

/************************************************
 *FUNCTION:删除文件
 *INPUT:文件绝对路径
 *RETURN:1 成功；0 失败
 *************************************************/
int rm_file(char *file_path);

/************************************************
 *FUNCTION:删除文件（夹）
 *INPUT:文件（夹）绝对路径
 *RETURN:1 成功；0 失败
 *************************************************/
int rm_dir(char *dir_path);
#endif
