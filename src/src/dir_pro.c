//2.5	Ŀ¼����ģ�����ͨ����δ���Թ���




#include <stdio.h>
#include <dirent.h>
#include <direct.h> 
#include "include.h"

char history[HISTORY_LENGTH][1024] = { 0 };//Ŀ¼������¼
extern char path[1024];
void undo_dir()
{

}
void anti_undo_dir()
{

}
void new_history()
{	
	int i;	
	for (i = HISTORY_LENGTH; i > 1; i--)
		strcpy(history[i - 1], history[i - 2]);
	strcpy(history[0], path);
}
