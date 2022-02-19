#include "GameTimer.h"

GameTimer::GameTimer() : mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0), mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

float GameTimer::GetTotalTime() const
{
	//��������ͣʱ����ȥ��Ҫ�����������ͣ�ǵ���ʱ��
	if (mStopped)
		return (float)(((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	else
		return (float)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
}

float GameTimer::GetDeltaTime() const
{
	return (float)mDeltaTime;
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	if (mStopped)
	{
		//�ۻ���ͣʱ��
		mPausedTime += startTime - mStopTime;
		//��Ϊ�������¿�ʼ��ʱ����� mPrevTime ��ֵ�Ͳ���ȷ�ˣ�Ҫ��������Ϊ��ǰʱ��
		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	//���������ͣ״̬�Թ��������
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//��¼��ͣʱ�䣬��������ͣ״̬�ı�־
		mStopTime = currTime;
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	//��ǰ֡����һ֮֡���ʱ���
	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	//Ϊ������һ֡��׼��
	mPrevTime = mCurrTime;

	//ȷ����Ϊ��ֵ���������������ڵ�ģʽ���л�����һ����������mDeltaTime��Ϊ��ֵ��
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}