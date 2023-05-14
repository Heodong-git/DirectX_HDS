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

	// ���ѽð� 
	inline void SetTimeLimit(float _Time)
	{
		m_TimeLimit = _Time;
	}

	// ���ѽð� ��ȯ
	inline float GetTimeLimit()
	{
		return m_TimeLimit;
	}

	// ���ѽð� ���� 
	inline void TimeIncrease(float _DeltaTime)
	{
		m_TimeLimit += _DeltaTime;
	}

	// Level�� ���鶧 ��ȭ�� �ʿ���� ������ �̰� ȣ���ؼ� false�� �����. 
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
	// ��ȭ�ϰ� ����� �ؾ��ϴ� ���������� �������� Start���� �긦 ȣ���ϸ� �ǰ� �Ϸ��� �ߴµ�
	// �׳� ��ȣ���ϰų� �������̵����� ó���ϰ�, recording == true �� ���������� ��ȭ 
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

	// ��ӹ��� ��� level�� �θ��� start�� ȣ���ϰ�, start ���� ī�޶����� �Ѵ�. 
	virtual void CameraSetting();

	float4 m_CurMouseLocalPos = {};

	std::shared_ptr<class Player> m_Player = nullptr;
	std::shared_ptr<class CBoss_HeadHunter> m_Boss = nullptr;
	std::shared_ptr<class Cursor> m_Cursor = nullptr;

	bool m_Recording = true;
	bool m_TimeOver = false;

	// �ӽ�, ���������� ���ѽð�
	float m_TimeLimit = 0.0f;
	float m_MaxTimeLimit = 4.0f;
	float m_SaveInterval = 2.0f;
};