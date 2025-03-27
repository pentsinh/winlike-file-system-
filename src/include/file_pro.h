#ifndef _PRO_H_
#define _PRO_H_
#include <sys/stat.h>
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
    int num; // 标号
    // int is_chosen;//是否被选中
    char name[13]; // 名称
    // char type[16];   // 类型暂时用英文
    unsigned char flag; // 八位二进制，表示的信息参考枚举变量file
    char path[64];      // 路径**********路径暂时没有值，在做搜索时填补
    char size[16];      // 大小
    char time[32];      // 修改时间
};

// #ifdef __cplusplus
// extern "C"
// {
// #endif

unsigned char get_file_type(char *name);

// #ifdef __cplusplus
// }
// #endif
void get_file_info(char *half_path, char *name, struct file_info *info); // 获取文件信息
// unsigned char get_file_type(char *name);                             // 获取文件类型
unsigned char get_file_type_plus(char *name);       // 进一步获取文件类型
char *get_file_path(char *father_path, char *name); // 获取文件绝对路径

#endif // _PRO_H_
