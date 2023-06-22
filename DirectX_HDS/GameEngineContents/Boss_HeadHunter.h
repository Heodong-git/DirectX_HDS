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
	IDLE,		// 아이들 2
	RIFLE,		// 라이플 3
	GUN,		// 건(폭발탄) 4 

	MAX,
};


// 설명 :
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
	void ComponentSetting();
	void LoadAndCreateAnimation();
	void LoadSound();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	
	std::shared_ptr<class HeadHunter_RifleEffect> m_Effect = nullptr;

	void CreateRifleEffect();
	float4 m_RifleEffectPivot = float4{ 540.0f , 54.5f };

	void DebugUpdate();
	
	// true = 오른쪽, false = 왼쪽 
	bool m_Dir = false;
	void DirCheck();

	BossPhase m_CurPhase = BossPhase::FIRST;

	// 상태값 변경
	void ChangeState(BossState _State);
	// 현재 상태값에 따른 업데이트 
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
};
