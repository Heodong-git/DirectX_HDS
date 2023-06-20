#pragma once
#include "BaseActor.h"

enum class PompState
{
	NONE,
	IDLE,	     // 아이들
	WALK,	     // 걷기
	CHASE,	     // 뛰기 
	ATTACK,	     // 공격 
	FALL,        // 날아감
	TURN,		 // 턴 
	KNOCKDOWN,	 // 넉다운 
	HITGROUND,	 // 데스 
};

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

	// 상태값 변경
	void ChangeState(PompState _State);
	virtual void BulletCollision() override;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DebugUpdate();
	void ComponentSetting();
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;

	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_ChaseCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_AttCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_SubCollision = nullptr;

private:
	//void CreateEffect();		// 공격이펙트 생성
	void CreateFollowEffect();  // 적발견 이펙트 생성
	bool ChaseCheck();			// chase 체크용 충돌체와 플레이어가 충돌했는지 확인
	void DoorOpenCheck();		// 문이 열렸니
	bool DoorCollisionCheck();	// 문 충돌체크 
	bool PartitionCollisionCheck();
	void ParryingCheck();		// 패링체크 
	void DeathCheck();			// 내가 죽었는지 
	void CreateHitEffect();
	void CreateSlashHitEffect();

	void Attack();
	void AttackOff();

	float m_HitEffectPivot = 20.0f;

	// 렌더 
	float m_RenderPivot = 38.0f;
	float m_ColPivot = 32.0f;
	float4 m_ColScale = { 45.0f, 65.0f , 1.0f };

	// 리셋
	virtual void Reset() override;
	void ResetDir();

	float4 m_HitPos = {};

	float m_WalkMoveSpeed = 150.0f;
	float m_ChaseMoveSpeed = 250.0f;
	float m_FlyingSpeed = 1500.0f;
	bool m_FollowEffectOn = false;

	// 방향
	// + 오른쪽 
	// - 왼쪽
	bool m_Direction = false;
	void DirCheck();

	
	// --------------------------------------State ----------------------------------------------
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
