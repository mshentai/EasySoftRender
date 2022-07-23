#pragma once
#include "Reference.h"
class GameTimer
{
public:
	GameTimer();

	float GetTotalTime() const;// ��λΪ��
	float GetDeltaTime() const;// ��λΪ��

	void Reset();// ��Ϣѭ��ǰ����
	void Start();// ȡ����ͣʱ����
	void Stop();//  ��ͣʱ����
	void Tick();//  ÿ֡����

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

