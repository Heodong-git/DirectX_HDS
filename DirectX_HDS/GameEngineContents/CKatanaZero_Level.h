#pragma once
#include <GameEngineCore/GameEngineLevel.h>

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
	inline void TimeIncrease(float _DeltaTime)
	{
		m_TimeLimit += _DeltaTime;
	}

	// Level을 만들때 녹화가 필요없는 레벨은 이걸 호출해서 false로 만든다. 
	inline void RecodingOff()
	{
		m_Recording = false;
	}

	inline bool GetRecordUse()
	{
		return m_Recording;
	}

	inline bool IsTimeOver() const
	{
		return m_TimeOver;
	}

	std::shared_ptr<class CBoss_HeadHunter> GetBoss()
	{
		return m_Boss;
	}

	std::shared_ptr<class CPlayer> GetPlayer()
	{
		return m_Player;
	}

	void SetPlayer(std::shared_ptr<class CPlayer> _Player)
	{
		m_Player = _Player;
	}

	void SetBoss(std::shared_ptr<class CBoss_HeadHunter> _Boss)
	{
		m_Boss = _Boss;
	}

	void SetMouse(std::shared_ptr<class CMouse> _Mouse)
	{
		m_Mouse = _Mouse;
	}

	std::shared_ptr<class CMouse> GetMouse()
	{
		return m_Mouse;
	}

protected:
	// 녹화하고 역재생 해야하는 레벨에서만 재정의한 Start에서 얘를 호출하면 되게 하려고 했는데
	// 그냥 다호출하거나 오버라이딩으로 처리하고, recording == true 인 레벨에서만 녹화 
	void Start() override;
	void Update(float _DeltaTime);


private:
	std::shared_ptr<class CPlayer> m_Player = nullptr;
	std::shared_ptr<class CBoss_HeadHunter> m_Boss = nullptr;
	std::shared_ptr<class CMouse> m_Mouse = nullptr;

	bool m_Wait = true;
	bool m_Playing = false; 

	// 타임오버
	void TimeOver();

	// 역재생
	void ReversePlay(float _DeltaTime);

	bool m_Recording = true;
	bool m_TimeOver = false;

	// 임시, 스테이지의 제한시간
	float m_TimeLimit = 0.0f;
	float m_MaxTimeLimit = 4.0f;
	float m_SaveInterval = 2.0f;
};