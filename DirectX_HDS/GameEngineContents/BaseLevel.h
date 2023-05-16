#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class BaseLevel : public GameEngineLevel
{
public:
	// ���� ���� ��ŸƮ��, ���ð��� �����ϱ� ���� enum
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

	inline BaseLevel::LevelState GetCurState() const
	{
		return m_CurState;
	}

	void SetState(BaseLevel::LevelState _State)
	{
		m_CurState = _State;
	}

protected:
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
	// ��ӹ��� ��� level�� �θ��� start�� ȣ���ϰ�, start ���� ī�޶����� �Ѵ�. 
	virtual void CameraSetting();

	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	// ���콺
	float4 m_CurMouseLocalPos = {};

	// ��ȭ ���� 2��
	float m_SaveInterval = 2.0f;
};