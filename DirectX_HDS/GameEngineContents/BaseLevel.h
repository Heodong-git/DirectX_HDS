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
		RECORDING_STANDBY,	 // ��ȭ���
		RECORDING_PROGRESS,	 // ��ȭ������
		RECORDING_PROGRESS_FORWARD, // ��������� 
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
	
	// ---------------------Stage ���� ----------------------
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
		// ���� ���������̶�� �׳� �������
		if (LevelType::CLUBBOSS0 == m_LevelType)
		{
			return;
		}

		if (0 == m_MonsterCount)
		{
			MsgAssert("�̹� ����ī��Ʈ�� 0 �� ���¿��� DisCount �Ϸ��� �߽��ϴ�.");
			return;
		}

		--m_MonsterCount;
	}

	// ���� ī��Ʈ üũ 
	bool IsClear();

protected:
	virtual void LoadSound() {} ;
	// ���� �Ⱑ������ �ʿ� ���� �� ������ ���ݴ� �������ϱ�.. 
	template<typename ActorType>
	void ActorInit(std::shared_ptr<ActorType>& _Actor, float4& _SetPos)
	{
		if (nullptr == _Actor)
		{
			MsgAssert("���Ͱ� nullptr �Դϴ�. �ʱ�ȭ�� ���͸� Ȯ���ϼ���.");
			return;
		}

		std::shared_ptr<ActorType> Actor = _Actor;
		Actor->GetTransform()->SetLocalPosition(_SetPos);
		Actor->SetInitPos(_SetPos);
		std::shared_ptr<GameEngineActor> UpCast = dynamic_pointer_cast<GameEngineActor>(Actor);
		int Order = UpCast->GetOrder();

		// ���� �����϶��� ī��Ʈ�� �߰���. 
		if (RenderOrder::MONSTER == static_cast<RenderOrder>(Order))
		{
			PlusMonsterCount();
		}

		Push_ResetActor(Actor);
	}

	// ���� ���� ī��Ʈ
	int m_MonsterCount = 0;
	int m_MaxMonsterCount = 0;

	// �������� ���ѽð�
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
	// Ǫ�þ���
	void Push_ResetActor(std::shared_ptr<class BaseActor> _Actor);

	// ������ �ʿ��� ���͸� ����, ���ͻ����ÿ� �ʱ�ȭ�ؾ��ϴ� ���͸� �ڷᱸ���� �����Ѵ�.
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

	// Ű������Ʈ 
	virtual void KeyUpdate() {};

	// ����� ������Ʈ
	virtual void DebugUpdate();

	void RecordingUpdate(float _DeltaTime);
	void ActorReset();

	// ���� Ŭ���� üũ
	void LevelClearCheck();
	void PlayerSkillCheck();

	// �浹�� ����
	std::shared_ptr<class ColEventObj> m_ColObj = nullptr;
	// Go UI
	std::shared_ptr<class GameEngineActor> m_GoUI = nullptr;

	// ī�޶�����Ʈ
	std::shared_ptr<class FadeEffect> m_FadeEffect = nullptr;
	

	// ��ӹ��� ��� level�� �θ��� start�� ȣ���ϰ�, start ���� ī�޶���
	virtual void CameraSetting();

	// ���콺
	float4 m_CurMouseLocalPos = {};
};
