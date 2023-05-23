#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class LevelType
{
	CLUBMAP0 = 0,
	CLUBMAP1,
	CLUBMAP2,
	CLUBMAP3,
	CLUBMAP4,


	NONE = 99,
};

class BaseLevel : public GameEngineLevel
{
public:
	// 레벨 리얼 스타트와, 대기시간을 구분하기 위한 enum
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

	LevelType GetLevelType()
	{
		return m_LevelType;
	}

	void SetLevelType(const LevelType& _Type)
	{
		m_LevelType = _Type;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override {};

	// 현재 맵 상태 
	BaseLevel::LevelState m_CurState = BaseLevel::LevelState::WAIT;

	// 현재 맵이름
	LevelType m_LevelType = LevelType::NONE;

	// 디버그 
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

	void ChangeMap();
	void ChangeColMap();
	void DebugCamera();

	std::shared_ptr<class Map> m_Map = nullptr;

private:
	// 상속받은 모든 level은 부모의 start를 호출하고, start 에서 카메라세팅을 한다. 
	virtual void CameraSetting();

	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	// 마우스
	float4 m_CurMouseLocalPos = {};

	// 녹화 간격 2초
	float m_SaveInterval = 2.0f;
};