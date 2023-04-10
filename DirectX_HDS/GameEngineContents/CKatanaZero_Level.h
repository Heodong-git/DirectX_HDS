#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 얘한테 일정시간마다 액터정보저장하는 기능이 필요함
class CKatanaZero_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	CKatanaZero_Level();
	~CKatanaZero_Level();

	// delete Function
	CKatanaZero_Level(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level(CKatanaZero_Level&& _Other) noexcept = delete;
	CKatanaZero_Level& operator=(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level& operator=(CKatanaZero_Level&& _Other) noexcept = delete;

	// 제한시간 
	inline void SetTimeLimit(float _Time)
	{
		m_TimeLimit = _Time;
	}

	// 제한시간 반환
	inline float GetTimeLimit()
	{
		return m_TimeLimit;
	}

	// 제한시간 감소 
	inline void TimeDecrease(float _DeltaTime)
	{
		m_TimeLimit -= _DeltaTime;
	}

	// 타임오버
	void TimeOver();
protected:
	void Update(float _DeltaTime);

private:
	// 임시, 스테이지의 제한시간
	float m_TimeLimit = 120.0f;
};