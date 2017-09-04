#ifndef TDY_NET_TIMER_H
#define TDY_NET_TIMER_H

#include <sys/time.h>
#include <stdint.h>
#include <iostream>
#include <string>

using namespace std;

namespace tdy
{
	//获取毫秒时间
	int64_t GetTimeMS()
	{
		struct timeval t;
		gettimeofday(&t, 0);

		int64_t ms;
		ms = t.tv_sec * 1000;	//转换为毫秒
		ms += (t.tv_usec / 1000);
		return ms;
	}

	int64_t GetTimeS()
	{
		return GetTimeMS() / 1000;
	}

	//返回时间格式如：20170902
	string GetCurrentDate()
	{
		char str[9];
		time_t now = time(NULL);
		struct tm *local = localtime(&now);
		strftime(str, 9, "%Y%m%d", local);
		return str;
	}

	class Timer
	{
	public:
		Timer()
		{
			m_init_time = 0;
			m_start_time = 0;
		}

		void Reset(int64_t p_time_passed = 0)
		{
			m_start_time = p_time_passed;
			m_init_time = GetTimeMS();
		}

	protected:
		int64_t m_init_time;
		int64_t m_start_time;
	}

}	//namespace tdy end

#endif //TDY_NET_TIMER_H