#ifndef _BIT_PRO_H_
#define _BIT_PRO_H_
#include "include.h"

void set_bit(unsigned char *bit, int position, int num); // 将一个八位二进制的制定位置设定为指定值
unsigned char get_bit(unsigned char num, int position);  // 获取八位二制的指定位置的值
void printBinary(unsigned char value);                   // 以二进制输出

#endif
