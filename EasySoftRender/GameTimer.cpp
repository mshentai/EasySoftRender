#include "GameTimer.h"

GameTimer::GameTimer() : mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0), mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

float GameTimer::GetTotalTime() const
{
	//将所有暂停时间略去，要留心如果在暂停是的总时间
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
		//累积暂停时间
		mPausedTime += startTime - mStopTime;
		//因为我们重新开始计时，因此 mPrevTime 的值就不正确了，要将它重置为当前时间
		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	//如果处于暂停状态略过下面操作
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//记录暂停时间，并设置暂停状态的标志
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

	//当前帧和上一帧之间的时间差
	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	//为计算下一帧做准备
	mPrevTime = mCurrTime;

	//确保不为负值。如果处理器进入节电模式或切换到另一个处理器，mDeltaTime会为负值。
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}