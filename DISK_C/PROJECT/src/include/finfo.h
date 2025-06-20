#ifndef _PRO_H_
#define _PRO_H_
#include <sys/stat.h>

#define INFO_LENGTH 10
#include "include.h"
// 文件类型枚举
enum file
{
    THIS_PC = 0, // 此电脑
    C_DISK = 1,  // C盘
    FOLD = 2,    // 目录,***DIR已经在DIRENT.H中被定义为了一种自定义类型***
    // 以下为文件类型
    TXT = 3,
    C = 4,
    CPP = 5,
    H = 6,
    OBJ = 7,
    EXE = 8,
    JPG = 9,
    PNG = 10,
    DOC = 11,
    XLS = 12,
    PPT = 13,
    PDF = 14,
    OTHER = 15,
    IS_OPEN = 16,
    H_NODE = 32, // 头节点，0010 0000
    IS_DIR = 64, // 判断文件状态，0100 0000
    SELECT = 128 // 判断选中，1000 0000
};
struct file_info
{
    int num;            // 标号从1开始
    char name[13];      // 名称
    unsigned char flag; // 八位二进制，表示的信息参考枚举变量file
    char path[64];      // 路径**********路径暂时没有值，在做搜索时填补
    char size[16];      // 大小
    char time[32];      // 修改时间
    int sons;           // 包含项目数量
};

/************************************************
 *FUNCTION:获取文件类型
 *INPUT:文件绝对路径
 *RETURN:八位二进制，参考枚举类型enum file
 *************************************************/
unsigned char get_file_type(char *name);

/************************************************
 *FUNCTION:获取文件信息
 *INPUT:文件所在目录，文件名，用于存放信息的info
 *RETURN:无
 *************************************************/
void get_file_info(char *half_path, char *name, struct file_info *info);

/************************************************
 *FUNCTION:进一步获取文件类型，辅助get_file_info
 *INPUT:文件名
 *RETURN:八位二进制，参考枚举类型enum file
 *************************************************/
unsigned char get_file_type_plus(char *name);

/************************************************
 *FUNCTION:获取文件绝对路径
 *INPUT:文件所在目录，文件名
 *RETURN:文件绝对路径
 *************************************************/
char *get_file_path(char *father_path, char *name);

/************************************************
 *FUNCTION:初始化info
 *INPUT:info链
 *RETURN:无
 *************************************************/
void info_init(struct file_info *info);

/************************************************
 *FUNCTION:格式化时间转换为时间戳
 *INPUT:格式化的时间
 *RETURN:时间戳
 *************************************************/
time_t formatted_tm_to_stamp(char *formatted_time);

/************************************************
 *FUNCTION:获取有效info数量，而不是序号
 *INPUT:info链
 *RETURN:数量
 *************************************************/
int get_info_num(struct file_info *info);

/************************************************
 *FUNCTION:获取点击位置的文件标号
 *INPUT:点击X，点击Y，info链，图标大小标志
 *RETURN:标号，返回-1表示点击位置没有文件
 *************************************************/
int get_file_num(int x, int y, struct file_info *info,int pic_flag);

/************************************************
 *FUNCTION:判断info链中是否有已经选中的文件
 *INPUT:info链
 *RETURN:第一个被选中的文件的标号，返回0表示没有文件被选中
 *************************************************/
int is_selected(struct file_info *info);

/************************************************
 *FUNCTION:计算包含项目数量
 *INPUT:文件夹绝对路径
 *RETURN:数量
 *************************************************/
int count_sons(char *path);

/************************************************
 *FUNCTION:计算传入文件所在目录
 *INPUT:文件夹绝对路径
 *RETURN:路径
 *************************************************/
char *get_father_path(char *path);

/************************************************
 *FUNCTION:从绝对路径获取文件名
 *INPUT:文件夹绝对路径
 *RETURN:文件名
 *************************************************/
char *path_to_name(char *path);

/************************************************
 *FUNCTION:全选
 *INPUT:info链
 *RETURN:无
 *************************************************/
void select_all(struct file_info *info);

/************************************************
 *FUNCTION:全不选
 *INPUT:info链
 *RETURN:无
 *************************************************/
void unselect_all(struct file_info *info);

/************************************************
 *FUNCTION:按名称选中
 *INPUT:info链，名字
 *RETURN:无
 *************************************************/
void select_name(struct file_info *info, char *name);
#endif // _PRO_H_
