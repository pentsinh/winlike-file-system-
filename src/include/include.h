/***********
 * ����Ϊ�ǿ⺯���ĺ�����ͷ�ļ�����
 *************/
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

enum // ģʽ�л�,0Ϊһ�㣬1Ϊ����
{
    _0to0 = 1,
    _0to1 = 2,
    _1to0 = 3,
    _1to1 = 4

};
#include <stdio.h>    //��׼�������
#include <dos.h>      //DOS���ܵ���
#include <conio.h>    //����̨�������
#include <string.h>   //�ַ���������
#include <stdlib.h>   //��׼�⺯��
#include <time.h>     //ʱ���������
#include <dirent.h>   //Ŀ¼�������
#include <direct.h>   //Ŀ¼��������
#include <sys/stat.h> //�ļ�״̬��ѯ
#include <graphics.h> //ͼ�β�������
#include <bios.h>     //BIOS�жϵ���

#include "hz.h"       //���ֿ�
#include "mouse.h"    //����
#include "login.h"    //��½
#include "load.h"     //����ҳ��
#include "bit_pro.h"  //��λ����
#include "dir_pro.h"  //Ŀ¼����
#include "file_pro.h" //�ļ�����
#include "srch.h"     //����
#include "index.h"    //Ŀ¼��
#include <IMAGE.h>    //��ͼ

#endif
