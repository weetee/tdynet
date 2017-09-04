/* 封装一个线程库
** 创建线程
** 杀死线程
** 等待线程完成
** 获得线程ID
** 将线程的控制权交给操作系统
*/

#ifndef TDY_NET_THREAD_H
#define TDY_NET_THREAD_H

#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

typedef pthread_t t_thread;
typedef void* (*ThreadFunc)(void*);

namespace tdy
{

//创建线程需要的数据结构
struct StartData 
{
	ThreadFunc m_func; 	//线程需要调用的函数
	void *m_data;		//线程需要的参数
};

class Thread
{
public:
	Thread(){}
	~Thread(){}

	//创建线程
	t_thread Create(ThreadFunc p_func, void *p_data);

	//获取线程ID
	t_thread GetThreadID()
	{
		return pthread_self();
	}

	//等待线程结束
	void WaitThreadFinish(t_thread p_tid)
	{
		pthread_join(p_tid, NULL);
	}

	//杀死线程
	void KillThread(t_thread &p_tid)
	{
		pthread_cancel(p_tid);
	}

	//告诉系统将当前线程置于睡眠状态
	void YieldThread(int p_seconds = 1)
	{
		usleep(p_seconds);
	}

private:

};

}	// namespace tdy end

#endif //TDY_NET_THREAD_H