#ifndef _PRO_H_
#define _PRO_H_
#include <sys/stat.h>
struct file_info {
    int num;//���
    char name[13];//����
    char type[16];//������ʱ��Ӣ��
    char path[1024];//·��**********·����ʱû��ֵ����������ʱ�
    char size[16];//��С
    char time[32];//�޸�ʱ��
};
void get_file_info(char* name, struct file_info* info);//��ȡ�ļ���Ϣ
char* get_file_type(char* name);//��ȡ�ļ�����
char* get_file_type_plus(char* name);//��һ����ȡ�ļ�����
#endif // _PRO_H_
