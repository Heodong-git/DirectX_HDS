#pragma once
#include "BaseActor.h"

enum class PompState
{
	NONE,
	IDLE,	     // 아이들
	WALK,	     // 걷기
	CHASE,	     // 뛰기 
	HITGROUND,	 // 쳐맞음
	ATTACK,	     // 공격 
	FALL,        // 날아감
	TURN,		 // 턴 
	KNOCKDOWN,	 // 넉다운 
};

// 왜 Pomp인지 모름 , 모히칸악당
class Monster_Pomp : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Pomp();
	~Monster_Pomp();

	// delete Function
	Monster_Pomp(const Monster_Pomp& _Other) = delete;
	Monster_Pomp(Monster_Pomp&& _Other) noexcept = delete;
	Monster_Pomp& operator=(const Monster_Pomp& _Other) = delete;
	Monster_Pomp& operator=(Monster_Pomp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DebugUpdate();

	// 렌더러생성 및 세팅
	void ComponentSetting();

	// 애니메이션 리소스 로드및생성
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;

private:
	float m_HitEffectPivot = 20.0f;

	// 렌더 
	float m_RenderPivot = 38.0f;
	float m_ColPivot = 32.0f;
	float4 m_ColScale = { 45.0f, 65.0f , 1.0f };

	// 리셋
	virtual void Reset() override;
	inline void ResetDir()
	{
		m_Direction = -1;
	}

	// 방향
	// + 오른쪽 
	// - 왼쪽
	int m_Direction = -1;
	void DirCheck();

	// 상태값 변경
	void ChangeState(PompState _State);
	// 현재 상태값에 따른 업데이트 
	void UpdateState(float _DeltaTime);

	PompState m_CurState = PompState::NONE;
	PompState m_PrevState = PompState::NONE;
	PompState m_NextState = PompState::NONE;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void WalkStart();
	void WalkUpdate(float _DeltaTime);
	void WalkEnd();

	void ChaseStart();
	void ChaseUpdate(float _DeltaTime);
	void ChaseEnd();

	void HitGroundStart();
	void HitGroundUpdate(float _DeltaTime);
	void HitGroundEnd();

	void AttackStart();
	void AttackUpdate(float _DeltaTime);
	void AttackEnd();

	void TurnStart();
	void TurnUpdate(float _DeltaTime);
	void TurnEnd(); 

	void KnockDownStart();
	void KnockDownUpdate(float _DeltaTime);
	void KnockDownEnd();

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();

};
