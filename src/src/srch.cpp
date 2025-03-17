#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <bios.h>
#include <string.h>
#include "include.h"

// 搜索
void srch_input(char target[16])
{
    getbuffer_keybd(target);
    
}
int srch(char *target)
{
}
void srch_output()
{
}

static void getbuffer_keybd(char target[16])
{
    union REGS regs;    // 用于读取键盘缓冲区
    static int num = 0; // 正在输入的位置在target中的位置
    // char ch;//这次输入的字符
    if (bioskey(1) == 0)
    {
        return;
    }
    else if (num < 16)
    {
        regs.h.ah = 0x00;
        int86(0x16, &regs, &regs); // 获取16位寄存器的后八位ASCII码
        // ch = regs.h.al;
        if (regs.h.al == 0x08) // 退格
        {
            target[num] = 0;
            if (num != 0)
                num -= 1;
        }
        else if (num < 16 - 1) // 最大长度为16-1
        {

            target[num] = regs.h.al;
            num = num + 1;
        }
        else if (num < 16 && regs.h.al == 0x0D) // 只有回车才可以占据第16个位置
        {

            target[num] = regs.h.al;
            num = 0;
        }
    }
}