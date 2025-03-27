/***********
 * 这里为非库函数的函数的头文件汇总
 *************/
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

enum // 模式切换,0为一般，1为搜索
{
    _0to0 = 1,
    _0to1 = 2,
    _1to0 = 3,
    _1to1 = 4

};
#include <stdio.h>    //标准输入输出
#include <dos.h>      //DOS功能调用
#include <conio.h>    //控制台输入输出
#include <string.h>   //字符串处理函数
#include <stdlib.h>   //标准库函数
#include <time.h>     //时间日期相关
#include <dirent.h>   //目录操作相关
#include <direct.h>   //目录操作函数
#include <sys/stat.h> //文件状态查询
#include <graphics.h> //图形操作函数
#include <bios.h>     //BIOS中断调用

#include "hz.h"       //汉字库
#include "mouse.h"    //鼠标库
#include "login.h"    //登陆
#include "load.h"     //加载页面
#include "bit_pro.h"  //按位操作
#include "dir_pro.h"  //目录操作
#include "file_pro.h" //文件操作
#include "srch.h"     //搜索
#include "index.h"    //目录树
#include <IMAGE.h>    //贴图

#endif
