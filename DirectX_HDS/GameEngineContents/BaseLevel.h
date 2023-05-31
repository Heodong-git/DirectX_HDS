#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class LevelType
{
	CLUBMAP0 = 0,
	CLUBMAP1,
	CLUBMAP2,
	CLUBMAP3,
	CLUBMAP4,

	CLUBBOSS0, 

	TITLE = 98,
	NONE = 99,
};

class BaseLevel : public GameEngineLevel
{
	friend class PlaySupporter;

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
		m_LimitTime = 55.0f;
	}

	// ---------------------Effect----------------------------
	std::shared_ptr<class FadeEffect> GetFadeEffect()
	{
		return m_FadeEffect;
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
	virtual void LevelReset();
	void Reset();
	void ResetColObj();
	bool m_IsClear = false;

	// 맵의 몬스터 카운트
	int m_MonsterCount = 0;
	int m_MaxMonsterCount = 0;

	// 스테이지 제한시간
	float m_LimitTime = 55.0f;

	void Start() override;
	void Update(float _DeltaTime);

	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	void LevelChangeStart() override;
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
	void DebugCamera();
	
	std::shared_ptr<class Map> m_Map = nullptr;

	// 푸시액터
	void Push_ResetActor(std::shared_ptr<class BaseActor> _Actor);
	// 리셋이 필요한 액터를 저장, 액터생성시에 초기화해야하는 액터를 자료구조에 저장한다.
	std::vector <std::shared_ptr<class BaseActor>> m_ResetActors = std::vector<std::shared_ptr<class BaseActor>>();

private:
	// 디버그 업데이트
	void DebugUpdate();

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