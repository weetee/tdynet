#ifndef TDY_NET_MUTEX_H
#define TDY_NET_MUTEX_H

#include <unistd.h>
#include <pthread.h>
#include <iostream>

using namespace std;

namespace tdy 
{

class Mutex
{
protected:
	pthread_mutex_t m_mutex;
public:
	Mutex()
	{
		pthread_mutex_init(&m_mutex, 0);
	}
	~Mutex()
	{
		pthread_mutex_destroy(&m_mutex);
	}

	void LockMutex()
	{
		pthread_mutex_lock(&m_mutex);
	}

	void UnlockMutex()
	{
		pthread_mutex_unlock(&m_mutex);
	}
};

}	// namespace tdy end


#endif //TDY_NET_MUTEX_H