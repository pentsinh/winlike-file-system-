#ifndef _SORT_H_
#define _SORT_H
#include "include.h"
/************************************************
 *FUNCTION:给info排序
 *INPUT:将要显示的info，排序模式（0name，1date，2type，3size），升序或降序(1/-1)
 *RETURN:无
 *************************************************/
void sort(struct file_info *info, unsigned char sort_mode, int UpOrDown);

/************************************************
 *FUNCTION:交换info
 *INPUT:dddd
 *RETURN:无
 *************************************************/
void swp_info(struct file_info *info_1, struct file_info *info_2);
#endif