#ifndef _PRO_H_
#define _PRO_H_
#include <sys/stat.h>
// �ļ�����ö��
enum file
{
    THIS_PC = 0, // �˵���
    C_DISK = 1,  // C��
    FOLD = 2,    // Ŀ¼,***DIR�Ѿ���DIRENT.H�б�����Ϊ��һ���Զ�������***
    // ����Ϊ�ļ�����
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
    H_NODE = 32, // ͷ�ڵ㣬0010 0000
    IS_DIR = 64, // �ж��ļ�״̬��0100 0000
    SELECT = 128 // �ж�ѡ�У�1000 0000
};
struct file_info
{
    int num; // ���
    // int is_chosen;//�Ƿ�ѡ��
    char name[13]; // ����
    // char type[16];   // ������ʱ��Ӣ��
    unsigned char flag; // ��λ�����ƣ���ʾ����Ϣ�ο�ö�ٱ���file
    char path[64];      // ·��**********·����ʱû��ֵ����������ʱ�
    char size[16];      // ��С
    char time[32];      // �޸�ʱ��
};

// #ifdef __cplusplus
// extern "C"
// {
// #endif

unsigned char get_file_type(char *name);

// #ifdef __cplusplus
// }
// #endif
void get_file_info(char *half_path, char *name, struct file_info *info); // ��ȡ�ļ���Ϣ
// unsigned char get_file_type(char *name);                             // ��ȡ�ļ�����
unsigned char get_file_type_plus(char *name);       // ��һ����ȡ�ļ�����
char *get_file_path(char *father_path, char *name); // ��ȡ�ļ�����·��

#endif // _PRO_H_
