#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class BaseLevel : public GameEngineLevel
{
public:
	enum class LevelState
	{
		WAIT,
		PLAY,
	};
public:
	// constrcuter destructer
	BaseLevel();
	~BaseLevel();

	// delete Function
	BaseLevel(const BaseLevel& _Other) = delete;
	BaseLevel(BaseLevel&& _Other) noexcept = delete;
	BaseLevel& operator=(const BaseLevel& _Other) = delete;
	BaseLevel& operator=(BaseLevel&& _Other) noexcept = delete;

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

	inline std::shared_ptr<class Player> GetPlayer()
	{
		return m_Player;
	}

	inline void SetPlayer(std::shared_ptr<class Player>& _Player)
	{
		m_Player = _Player;
	}

	inline void SetBoss(std::shared_ptr<class CBoss_HeadHunter>& _Boss)
	{
		m_Boss = _Boss;
	}

	inline void SetCursor(std::shared_ptr<class Cursor>& _Cursor)
	{
		m_Cursor = _Cursor;
	}


	inline BaseLevel::LevelState GetCurState() const
	{
		return m_CurState;
	}

	void SetState(BaseLevel::LevelState _State)
	{
		m_CurState = _State;
	}
protected:
	// 녹화하고 역재생 해야하는 레벨에서만 재정의한 Start에서 얘를 호출하면 되게 하려고 했는데
	// 그냥 다호출하거나 오버라이딩으로 처리하고, recording == true 인 레벨에서만 녹화 
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override {};

	BaseLevel::LevelState m_CurState = BaseLevel::LevelState::WAIT;

	virtual void DebugSwitch()
	{
		if (true == IsDebug())
		{
			DebugOff();
		}

		else if (false == IsDebug())
		{
			DebugOn();
		}
	}

private:
	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	// 상속받은 모든 level은 부모의 start를 호출하고, start 에서 카메라세팅을 한다. 
	virtual void CameraSetting();

	float4 m_CurMouseLocalPos = {};

	std::shared_ptr<class Player> m_Player = nullptr;
	std::shared_ptr<class CBoss_HeadHunter> m_Boss = nullptr;
	std::shared_ptr<class Cursor> m_Cursor = nullptr;

	bool m_Recording = true;
	bool m_TimeOver = false;

	// 임시, 스테이지의 제한시간
	float m_TimeLimit = 0.0f;
	float m_MaxTimeLimit = 4.0f;
	float m_SaveInterval = 2.0f;
};