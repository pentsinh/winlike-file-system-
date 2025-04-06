#ifndef _PRO_H_
#define _PRO_H_
#include <sys/stat.h>

#define INFO_LENGTH 10

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
    int num;            // ��Ŵ�1��ʼ
    char name[13];      // ����
    unsigned char flag; // ��λ�����ƣ���ʾ����Ϣ�ο�ö�ٱ���file
    char path[64];      // ·��**********·����ʱû��ֵ����������ʱ�
    char size[16];      // ��С
    char time[32];      // �޸�ʱ��
    int sons;           // ������Ŀ����
};

/************************************************
 *FUNCTION:��ȡ�ļ�����
 *INPUT:�ļ�����·��
 *RETURN:��λ�����ƣ��ο�ö������enum file
 *************************************************/
unsigned char get_file_type(char *name);

/************************************************
 *FUNCTION:��ȡ�ļ���Ϣ
 *INPUT:�ļ�����Ŀ¼���ļ��������ڴ����Ϣ��info
 *RETURN:��
 *************************************************/
void get_file_info(char *half_path, char *name, struct file_info *info);

/************************************************
 *FUNCTION:��һ����ȡ�ļ����ͣ�����get_file_info
 *INPUT:�ļ���
 *RETURN:��λ�����ƣ��ο�ö������enum file
 *************************************************/
unsigned char get_file_type_plus(char *name);

/************************************************
 *FUNCTION:��ȡ�ļ�����·��
 *INPUT:�ļ�����Ŀ¼���ļ���
 *RETURN:�ļ�����·��
 *************************************************/
char *get_file_path(char *father_path, char *name);

/************************************************
 *FUNCTION:��ʼ��info
 *INPUT:info��
 *RETURN:��
 *************************************************/
void info_init(struct file_info *info);

/************************************************
 *FUNCTION:��ʽ��ʱ��ת��Ϊʱ���
 *INPUT:��ʽ����ʱ��
 *RETURN:ʱ���
 *************************************************/
time_t formatted_tm_to_stamp(char *formatted_time);

/************************************************
 *FUNCTION:��ȡ��Чinfo���������������
 *INPUT:info��
 *RETURN:����
 *************************************************/
int get_info_num(struct file_info *info);

/************************************************
 *FUNCTION:��ȡ���λ�õ��ļ����
 *INPUT:���X�����Y��info��
 *RETURN:��ţ�����-1��ʾ���λ��û���ļ�
 *************************************************/
int get_file_num(int x, int y, struct file_info *info);

/************************************************
 *FUNCTION:�ж�info�����Ƿ����Ѿ�ѡ�е��ļ�
 *INPUT:info��
 *RETURN:��һ����ѡ�е��ļ��ı�ţ�����0��ʾû���ļ���ѡ��
 *************************************************/
int is_selected(struct file_info *info);

/************************************************
 *FUNCTION:���������Ŀ����
 *INPUT:�ļ��о���·��
 *RETURN:����
 *************************************************/
int count_sons(char *path);

#endif // _PRO_H_
