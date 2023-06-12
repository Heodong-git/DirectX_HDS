#pragma once
#include <chrono>
#include <Windows.h>

// Ό³Έν :
class GameEngineTime
{
public:
	static GameEngineTime GlobalTime;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	void Reset();
	float TimeCheck();

	float GetDeltaTime()
	{
		return floatDeltaTime;
	}

	float GetTimeScaleDeltaTime()
	{
		return floatDeltaTime * GlobalTimeScale;
	}

	void SetGlobalTimeScale(float _TimeScale)
	{
		GlobalTimeScale = _TimeScale;
	}

	template<typename EnumType>
	void SetUpdateOrderTimeScale(EnumType _Order, float _Time)
	{
		SetUpdateOrderTimeScale(static_cast<int>(_Order), _Time);
	}

	void SetUpdateOrderTimeScale(int _Order, float _Time)
	{
		UpdateTimeScale[_Order] = _Time;
	}

	void SetAllUpdateOrderTimeScale(float _Time)
	{
		for (std::pair<const int, float>& Pair : UpdateTimeScale)
		{
			Pair.second = _Time;
		}
	}

	float GetUpdateOrderTimeScale(int _Order)
	{
		if (UpdateTimeScale.end() == UpdateTimeScale.find(_Order))
		{
			UpdateTimeScale[_Order] = 1.0f;
		}

		return UpdateTimeScale[_Order];
	}


	template<typename EnumType>
	void SetRenderOrderTimeScale(EnumType _Order, float _Time)
	{
		SetRenderOrderTimeScale(static_cast<int>(_Order), _Time);
	}

	void SetRenderOrderTimeScale(int _Order, float _Time)
	{
		RenderTimeScale[_Order] = _Time;
	}

	void SetAllRenderOrderTimeScale(float _Time)
	{
		for (std::pair<const int, float>& Pair : RenderTimeScale)
		{
			Pair.second = _Time;
		}
	}

	float GetRenderOrderTimeScale(int _Order)
	{
		if (RenderTimeScale.end() == RenderTimeScale.find(_Order))
		{
			RenderTimeScale[_Order] = 1.0f;
		}

		return RenderTimeScale[_Order];
	}

protected:

private:
	__int64 Tick = 0;
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
	double DoubleDeltaTime = 0.0;
	float floatDeltaTime = 0.0;
	float GlobalTimeScale = 1.0f;
	std::map<int, float> UpdateTimeScale;

	std::map<int, float> RenderTimeScale;
};

