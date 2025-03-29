#ifndef _BIT_PRO_H_
#define _BIT_PRO_H_

/************************************************
 *FUNCTION:将一个八位二进制的制定位置设定为指定值
 *INPUT:八位二进制的地址，要修改的位置（从第0位开始），目标值
 *RETURN:无
 *************************************************/
void set_bit(unsigned char *bit, int position, int num);

/************************************************
 *FUNCTION:获取八位二制的指定位置的值
 *INPUT:八位二进制，位置（从第0位开始）
 *RETURN:0或1
 *************************************************/
unsigned char get_bit(unsigned char num, int position);

/************************************************
 *FUNCTION:以二进制输出（用于测试）
 *INPUT:八位二进制
 *RETURN:无
 *************************************************/
void printBinary(unsigned char value);

#endif
