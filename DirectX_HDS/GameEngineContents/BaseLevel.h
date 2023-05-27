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
	friend class CameraMovement;

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

	const inline float GetLimitTime() const
	{
		return m_LimitTime;
	}

	inline void SetLimitTime()
	{
		m_LimitTime = 3.0f;
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

	// 디버그, 맵관련 
	void ChangeMap();
	void ChangeColMap();
	void DebugCamera();

	std::shared_ptr<class Map> m_Map = nullptr;

	// 스테이지 제한시간
	float m_LimitTime = 3.0f;
private:
	// 상속받은 모든 level은 부모의 start를 호출하고, start 에서 카메라세팅을 한다. 
	virtual void CameraSetting();

	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	// 마우스
	float4 m_CurMouseLocalPos = {};

	virtual void ActorReset() {};
	// 베이스레벨에서 리셋이라는 함수를 호출하면
	// 액터들을 전부 초기 위치로 되돌려 놓는다. 
	// 음.. 근데 몬스터, 플레이어 정도만 되돌려놓으면 되니까.. 그냥 가지고 있는게 낫나? 
	// 리셋이라는 애만 버추얼로 만들고 상속받은 클래스에서 재정의, 자신이 생성한 액터들의 초기 위치를 들고있다가
	// 그 위치로 전부 이동시킨다. 

	// 그리고 이작업을 하기전에 화면에 띄워야하는게 되감기 
};