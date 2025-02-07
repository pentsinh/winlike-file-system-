#ifndef _DIR_PRO_H_
	#define _DIR_PRO_H
	#ifndef HISTORY_LENGTH
		#define HISTORY_LENGTH 10
	#endif
	void undo_dir();//撤销目录操作
	void anti_undo_dir();//反撤销目录操作
	void new_history();//更新目录操作历史
#endif // _DIR_PRO_H_
