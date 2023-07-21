#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineTransform.h>

enum class LevelType
{
	CLUBMAP0 = 0,
	CLUBMAP1,
	CLUBMAP2,
	CLUBMAP3,
	CLUBMAP4,

	CLUBBOSS0, 
	CLUBBOSS1,

	TITLE = 98,
	NONE = 99,
};

class BaseLevel : public GameEngineLevel
{
	friend class PlaySupporter;
	friend class YouCanDoThis;


public:
	enum class LevelState
	{
		WAIT,
		PLAY,
		RECORDING_STANDBY,	 // 녹화대기
		RECORDING_PROGRESS,	 // 녹화진행중
		RECORDING_PROGRESS_FORWARD, // 정방향재생 
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

	// -----------------State----------------------
	inline BaseLevel::LevelState GetCurState() const
	{
		return m_CurState;
	}

	void SetState(BaseLevel::LevelState _State)
	{
		m_CurState = _State;
	}

	// ----------------LevelType---------------------
	LevelType GetLevelType()
	{
		return m_LevelType;
	}

	void SetLevelType(const LevelType& _Type)
	{
		m_LevelType = _Type;
	}

	// --------------------LimitTime------------------------
	const inline float GetLimitTime() const
	{
		return m_LimitTime;
	}

	inline void SetLimitTime()
	{
		m_LimitTime = 110.0f;
	}

	inline void SetLimitTime(float _Time)
	{
		m_LimitTime = _Time;
	}

	// ---------------------Effect----------------------------
	std::shared_ptr<class FadeEffect> GetFadeEffect()
	{
		return m_FadeEffect;
	}

	std::shared_ptr<class GlitchEffect> GetGlitchEffect()
	{
		return m_GlitchEffect;
	}
	
	// ---------------------Stage 관련 ----------------------
	inline void PlusMonsterCount()
	{
		++m_MonsterCount;
		++m_MaxMonsterCount;
	}

	const int GetMonsterCount()
	{
		return m_MonsterCount;
	}

	inline void ResetMonsterCount()
	{
		m_MonsterCount = m_MaxMonsterCount;
	}
	
	inline void DisCount()
	{
		// 만약 보스레벨이라면 그냥 실행안함
		if (LevelType::CLUBBOSS0 == m_LevelType)
		{
			return;
		}

		if (0 == m_MonsterCount)
		{
			MsgAssert("이미 몬스터카운트가 0 인 상태에서 DisCount 하려고 했습니다.");
			return;
		}

		--m_MonsterCount;
	}

	// 몬스터 카운트 체크 
	bool IsClear();

protected:
	virtual void LoadSound() {} ;
	// 뭔가 기가막히게 필요 없는 듯 하지만 조금더 편해지니까.. 
	template<typename ActorType>
	void ActorInit(std::shared_ptr<ActorType>& _Actor, float4& _SetPos)
	{
		if (nullptr == _Actor)
		{
			MsgAssert("액터가 nullptr 입니다. 초기화할 액터를 확인하세요.");
			return;
		}

		std::shared_ptr<ActorType> Actor = _Actor;
		Actor->GetTransform()->SetLocalPosition(_SetPos);
		Actor->SetInitPos(_SetPos);
		std::shared_ptr<GameEngineActor> UpCast = dynamic_pointer_cast<GameEngineActor>(Actor);
		int Order = UpCast->GetOrder();

		// 내가 몬스터일때만 카운트를 추가해. 
		if (RenderOrder::MONSTER == static_cast<RenderOrder>(Order))
		{
			PlusMonsterCount();
		}

		Push_ResetActor(Actor);
	}

	// 맵의 몬스터 카운트
	int m_MonsterCount = 0;
	int m_MaxMonsterCount = 0;

	// 스테이지 제한시간
	float m_LimitTime = 110.0f;

	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override {};
	void LevelChangeEnd() override {};

	BaseLevel::LevelState m_CurState = BaseLevel::LevelState::WAIT;
	LevelType m_LevelType = LevelType::NONE;

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
	
	std::shared_ptr<class Map> m_Map = nullptr;
	// 푸시액터
	void Push_ResetActor(std::shared_ptr<class BaseActor> _Actor);

	// 리셋이 필요한 액터를 저장, 액터생성시에 초기화해야하는 액터를 자료구조에 저장한다.
	std::vector <std::shared_ptr<class BaseActor>>& GetResetActors()
	{
		return m_ResetActors;
	}
	std::vector <std::shared_ptr<class BaseActor>> m_ResetActors = std::vector<std::shared_ptr<class BaseActor>>();
	
	GameEngineSoundPlayer m_SoundPlayer;
	
	std::shared_ptr<class DistotionEffect> m_DistotionEffect = nullptr;
	std::shared_ptr<class GlitchEffect> m_GlitchEffect = nullptr;

private:
	const float m_RecordingTimeScale = 10.0f;
	const float m_TimeScale = 1.0f;
	virtual void LevelReset();
	void Reset();
	void ResetColObj();
	void ResetSound();
	bool m_IsClear = false;

	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	virtual void GUISetting() {};
	virtual void CreateKey() {};

	// 키업데이트 
	virtual void KeyUpdate() {};

	// 디버그 업데이트
	virtual void DebugUpdate();

	void RecordingUpdate(float _DeltaTime);
	void ActorReset();

	// 레벨 클리어 체크
	void LevelClearCheck();
	void PlayerSkillCheck();

	// 충돌용 액터
	std::shared_ptr<class ColEventObj> m_ColObj = nullptr;
	// Go UI
	std::shared_ptr<class GameEngineActor> m_GoUI = nullptr;

	// 카메라이펙트
	std::shared_ptr<class FadeEffect> m_FadeEffect = nullptr;
	

	// 상속받은 모든 level은 부모의 start를 호출하고, start 에서 카메라세팅
	virtual void CameraSetting();

	// 마우스
	float4 m_CurMouseLocalPos = {};
};
