#pragma once
#include "BaseActor.h"

enum class BossPhase
{
	FIRST,
	SECOND,
};

enum class BossState
{
	NONE,
	INTRO,
	IDLE,		// ���̵� 2
	RIFLE,		// ������ 3
	GUN,		// ��(����ź) 4 
	ROLL,		// ȸ��(������) 5
	MAX,
};


// ���� :
class Boss_HeadHunter : public BaseActor
{
public:
	// constrcuter destructer
	Boss_HeadHunter();
	~Boss_HeadHunter();

	// delete Function
	Boss_HeadHunter(const Boss_HeadHunter& _Other) = delete;
	Boss_HeadHunter(Boss_HeadHunter&& _Other) noexcept = delete;
	Boss_HeadHunter& operator=(const Boss_HeadHunter& _Other) = delete;
	Boss_HeadHunter& operator=(Boss_HeadHunter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void NextTransUpdate();

	void ComponentSetting();
	void LoadAndCreateAnimation();
	void LoadSound();

	// next trans 
	std::shared_ptr<GameEngineTransform> m_NextTrans = nullptr;
	const float4 m_DebugPivot = float4{ 30.0f, 42.0f };

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	
	std::shared_ptr<class HeadHunter_RifleEffect> m_Effect = nullptr;

	void CreateRifleEffect();
	float4 m_RifleEffectPivot = float4{ 540.0f , 54.5f };

	float m_RollSpeed = 500.0f; 

	void DebugUpdate();
	
	// true = ������, false = ���� 
	bool m_Dir = false;
	void DirCheck();
	void ChangeDir();

	BossPhase m_CurPhase = BossPhase::FIRST;

	// ���°� ����
	void ChangeState(BossState _State);
	// ���� ���°��� ���� ������Ʈ 
	void UpdateState(float _DeltaTime);

	BossState m_CurState = BossState::IDLE;
	BossState m_PrevState = BossState::NONE;
	BossState m_NextState = BossState::NONE;

	void IntroStart();
	void IntroUpdate(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void RifleStart();
	void RifleUpdate(float _DeltaTime);
	void RifleEnd();

	void GunStart();
	void GunUpdate(float _DeltaTime);
	void GunEnd();

	void RollStart();
	void RollUpdate(float _DeltaTime);
	void RollEnd();
};
