#include "../Thread.h"
#include "../Mutex.h"
#include <cstdint>

#define MAX_LOOP_COUNT	100

using namespace tdy;

//定义互斥锁
Mutex mutex = Mutex();

void *PrintThread(void *p_data)
{
	long i = (long)(p_data);
	char c = (char)i;
	mutex.LockMutex();
	for (int i = 0; i < MAX_LOOP_COUNT; ++i)
	{
		cout << c;
		cout.flush();
		usleep(1);
	}
	cout << endl;
	mutex.UnlockMutex();
	return (void *)0;
}

int main(void)
{
	Thread tobj = Thread();
	t_thread td1, td2;
	//创建线程
	td1 = tobj.Create(PrintThread, (void *)'a');
	td2 = tobj.Create(PrintThread, (void *)'b');

	//等待线程结束
	tobj.WaitThreadFinish(td1);
	tobj.WaitThreadFinish(td2);
	cout << "end" << endl;
	return 0;
}
