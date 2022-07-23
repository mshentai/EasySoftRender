#pragma once
#include "Reference.h"
class GameTimer
{
public:
	GameTimer();

	float GetTotalTime() const;// 单位为秒
	float GetDeltaTime() const;// 单位为秒

	void Reset();// 消息循环前调用
	void Start();// 取消暂停时调用
	void Stop();//  暂停时调用
	void Tick();//  每帧调用

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

