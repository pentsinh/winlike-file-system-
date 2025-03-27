//#include <stdio.h>
#include "include.h"

// 将8位二进制的某一位设为特定值
void set_bit(unsigned char *num, int position, int value)
{
    // 检查 position 是否在有效范围内 (0-7)
    if (position < 0 || position > 7)
    {
        printf("Error: position is out of range (0-7).\n");
        return;
    }

    // 检查 value 是否是 0 或 1
    if (value != 0 && value != 1)
    {
        printf("Error: value must be 0 or 1.\n");
        return;
    }

    // 创建一个掩码，用于设置指定位置的位
    unsigned char mask = 1 << position;

    // 如果 value 是 1，则将指定位置的位设置为 1
    if (value == 1)
    {
        *num |= mask;
    }
    // 如果 value 是 0，则将指定位置的位设置为 0
    else
    {
        *num &= ~mask;
    }
}

unsigned char get_bit(unsigned char num, int position) // 获取八位二制的指定位置的值
{
    if (position < 0 || position >= 8) // 检查位置是否有效
    {
        return 0; // 如果位置无效，返回0
    }
    return (num >> position) & 1; // 右移后与1按位与，得到该位的值
}

// 以二进制输出
void printBinary(unsigned char value)
{
    for (int i = 7; i >= 0; i--)
    {                                         // 从最高位到最低位逐位处理
        unsigned char bit = (value >> i) & 1; // 右移i位后与1按位与，得到第i位的值
        printf("%u", bit);                    // 输出该位的值
    }
}
