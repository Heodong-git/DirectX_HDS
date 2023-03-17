#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime() 
{
	// 1초를 기준으로한 정수 단위 
	// 시작할때 1번만 정하면 된다.
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);
	Tick = Current.QuadPart - Prev.QuadPart;
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);
	Prev.QuadPart = Current.QuadPart;
	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
