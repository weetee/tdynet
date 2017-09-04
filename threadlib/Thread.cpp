#include "Thread.h"

using namespace tdy;

void *StartThread(void *p_data)
{
	//转换
	StartData *data = (StartData *)p_data;
	// 用给定数据运行函数
	data->m_func(data->m_data);
	//删除数据
	delete data;

	return 0;
}

t_thread Thread::Create(ThreadFunc p_func, void *p_data)
{
	t_thread thread_id;
	// 创建一个新的数据块
	StartData *data = new StartData;
	data->m_func = p_func;
	data->m_data = p_data;
	// 创建线程
	pthread_create(&thread_id, NULL, &StartThread, data);
	// 创建失败
	if (thread_id == 0)
	{
		delete data;
		cout << "Thread Create failed~!" << endl;
		return -1;
	}

	return thread_id;
}