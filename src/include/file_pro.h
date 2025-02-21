#ifndef _PRO_H_
#define _PRO_H_
#include <sys/stat.h>
struct file_info {
    int num;//标号
    char name[13];//名称
    char type[16];//类型暂时用英文
    char path[1024];//路径**********路径暂时没有值，在做搜索时填补
    char size[16];//大小
    char time[32];//修改时间
};
void get_file_info(char* name, struct file_info* info);//获取文件信息
char* get_file_type(char* name);//获取文件类型
char* get_file_type_plus(char* name);//进一步获取文件类型
#endif // _PRO_H_
