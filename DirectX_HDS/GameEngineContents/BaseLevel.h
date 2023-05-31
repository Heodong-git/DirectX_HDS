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
		m_LimitTime = 55.0f;
	}

	std::shared_ptr<class FadeEffect> GetFadeEffect()
	{
		return m_FadeEffect;
	}
	
	// 당장떠오르는게 이거밖에 없다 
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
	
	// 몹이 죽을때마다 얘를 호출한다.. 하 개이상해
	// 일단해 
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
	// 몬스터 다죽었나?
	// 생성할때마다 ++ 시켜. 근데 너무 귀찮아. 
	// 베이스액터 초기화위치세팅할때마다 ++ 그냥 레벨마다 설정하면되는거아님?ㅋㅋㅋ 
	int m_MonsterCount = 0;
	int m_MaxMonsterCount = 0;

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
	float m_LimitTime = 55.0f;

	void Push_ResetActor(std::shared_ptr<class BaseActor> _Actor);

	// 리셋이 필요한 액터를 저장, 액터생성시에 초기화해야하는 액터를 자료구조에 저장한다.
	std::vector <std::shared_ptr<class BaseActor>> m_ResetActors = std::vector<std::shared_ptr<class BaseActor>>();

private:
	// 충돌용 액터
	std::shared_ptr<class ColEventObj> m_ColObj = nullptr;

	// Go UI
	std::shared_ptr<class GameEngineActor> m_GoUI = nullptr;

	// 카메라이펙트
	std::shared_ptr<class FadeEffect> m_FadeEffect;
	// 상속받은 모든 level은 부모의 start를 호출하고, start 에서 카메라세팅을 한다. 
	virtual void CameraSetting();

	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	// 마우스
	float4 m_CurMouseLocalPos = {};

	// 그냥 얘를 호출하면 되는거아닌가? 
	virtual void LevelReset();
	void Reset();
	void ResetColObj();
	
	bool m_IsClear = false; 


	// 베이스레벨에서 리셋이라는 함수를 호출하면
	// 액터들을 전부 초기 위치로 되돌려 놓는다. 
	// 음.. 근데 몬스터, 플레이어 정도만 되돌려놓으면 되니까.. 그냥 가지고 있는게 낫나? 
	// 리셋이라는 애만 버추얼로 만들고 상속받은 클래스에서 재정의, 자신이 생성한 액터들의 초기 위치를 들고있다가
	// 그 위치로 전부 이동시킨다. 

	// 그리고 이작업을 하기전에 화면에 띄워야하는게 되감기 
};

// 액터를 생성하면 반드시 vector 에 푸시백해주어야 리셋할 수 있다. 
// 그냥 다넣고 오버라이드 안한애들은 안한대로 초기화 하면되지않을까 어차피몇개안되는데 