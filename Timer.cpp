#include "Timer.h"
#include <cstdio>
Timer::Timer(void)
{
}

Timer::~Timer(void)
{
}

void Timer::start(){
	ftime(&ts1);//��ʼ��ʱ
}
void Timer::end(){
	ftime(&ts2);//ֹͣ��ʱ
}
TIME_T Timer::getTimer(){
    TIME_T t1,t2;
    TIME_T ti;
    ftime(&ts2);//ֹͣ��ʱ
    t1=(TIME_T)ts1.time*1000+ts1.millitm;
	std::printf("t1=%I64d\n",t1);
    t2=(TIME_T)ts2.time*1000+ts2.millitm;
    std::printf("t2=%I64d\n",t2);
    ti=t2-t1;//��ȡʱ������msΪ��λ��
	return ti;
}