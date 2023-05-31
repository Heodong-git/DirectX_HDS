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
	
	// ���嶰�����°� �̰Źۿ� ���� 
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
	
	// ���� ���������� �긦 ȣ���Ѵ�.. �� ���̻���
	// �ϴ��� 
	inline void DisCount()
	{
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
	// ���� ���׾���?
	// �����Ҷ����� ++ ����. �ٵ� �ʹ� ������. 
	// ���̽����� �ʱ�ȭ��ġ�����Ҷ����� ++ �׳� �������� �����ϸ�Ǵ°žƴ�?������ 
	int m_MonsterCount = 0;
	int m_MaxMonsterCount = 0;

	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override {};

	// ���� �� ���� 
	BaseLevel::LevelState m_CurState = BaseLevel::LevelState::WAIT;

	// ���� ���̸�
	LevelType m_LevelType = LevelType::NONE;

	// ����� 
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

	// �����, �ʰ��� 
	void ChangeMap();
	void ChangeColMap();
	void DebugCamera();

	std::shared_ptr<class Map> m_Map = nullptr;

	// �������� ���ѽð�
	float m_LimitTime = 55.0f;

	void Push_ResetActor(std::shared_ptr<class BaseActor> _Actor);

	// ������ �ʿ��� ���͸� ����, ���ͻ����ÿ� �ʱ�ȭ�ؾ��ϴ� ���͸� �ڷᱸ���� �����Ѵ�.
	std::vector <std::shared_ptr<class BaseActor>> m_ResetActors = std::vector<std::shared_ptr<class BaseActor>>();

private:
	// �浹�� ����
	std::shared_ptr<class ColEventObj> m_ColObj = nullptr;

	// Go UI
	std::shared_ptr<class GameEngineActor> m_GoUI = nullptr;

	// ī�޶�����Ʈ
	std::shared_ptr<class FadeEffect> m_FadeEffect;
	// ��ӹ��� ��� level�� �θ��� start�� ȣ���ϰ�, start ���� ī�޶����� �Ѵ�. 
	virtual void CameraSetting();

	virtual void ResourcesLoad() {};
	virtual void ActorLoad() {};

	// ���콺
	float4 m_CurMouseLocalPos = {};

	// �׳� �긦 ȣ���ϸ� �Ǵ°žƴѰ�? 
	virtual void LevelReset();
	void Reset();
	void ResetColObj();
	
	bool m_IsClear = false; 


	// ���̽��������� �����̶�� �Լ��� ȣ���ϸ�
	// ���͵��� ���� �ʱ� ��ġ�� �ǵ��� ���´�. 
	// ��.. �ٵ� ����, �÷��̾� ������ �ǵ��������� �Ǵϱ�.. �׳� ������ �ִ°� ����? 
	// �����̶�� �ָ� ���߾�� ����� ��ӹ��� Ŭ�������� ������, �ڽ��� ������ ���͵��� �ʱ� ��ġ�� ����ִٰ�
	// �� ��ġ�� ���� �̵���Ų��. 

	// �׸��� ���۾��� �ϱ����� ȭ�鿡 ������ϴ°� �ǰ��� 
};

// ���͸� �����ϸ� �ݵ�� vector �� Ǫ�ù����־�� ������ �� �ִ�. 
// �׳� �ٳְ� �������̵� ���Ѿֵ��� ���Ѵ�� �ʱ�ȭ �ϸ���������� �����Ǹ�ȵǴµ� 