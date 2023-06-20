#pragma once
#include "BaseActor.h"

enum class GangsterState
{
	NONE,
	IDLE,	 // 아이들
	WALK,	 // 걷기
	CHASE,	 // 뛰기 
	HITGROUND,	 // 쳐맞음
	AIM,	 // 공격 
};

// 갱스터 
class Monster_Gangster : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Gangster();
	~Monster_Gangster();

	// delete Function
	Monster_Gangster(const Monster_Gangster& _Other) = delete;
	Monster_Gangster(Monster_Gangster&& _Other) noexcept = delete;
	Monster_Gangster& operator=(const Monster_Gangster& _Other) = delete;
	Monster_Gangster& operator=(Monster_Gangster&& _Other) noexcept = delete;

	virtual void BulletCollision() override;

	void SetDir(const bool _Dir)
	{
		m_Direction = _Dir;
	}
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
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;

	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_ChaseCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_SubCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_AimCollision = nullptr;
	
private:
	// void CreateEffect();		// 공격이펙트 생성
	void CreateFollowEffect();  // 적발견 이펙트 생성
	void CreateFireEffect();	// 
	void CreateBullet();
	void CreateHitEffect();
	void CreateSlashHitEffect();

	bool AimRangeCheck();
	bool ChaseCheck();			// chase 체크용 충돌체와 플레이어가 충돌했는지 확인
	void DoorOpenCheck();		// 문이 열렸니
	bool DoorCollisionCheck();	// 문 충돌체크 
	bool PartitionCollisionCheck();
	void DeathCheck();			// 내가 죽었는지 

	float m_HitEffectPivot = 20.0f;
	float m_RenderPivot = 38.0f;
	float m_ColPivot = 33.0f;
	float4 m_ColScale = { 45.0f, 65.0f , 1.0f };

	float m_WalkMoveSpeed = 100.0f;
	float m_ChaseMoveSpeed = 150.0f;
	float m_ShotCoolTime = 0.57f;
	float m_FireTime = 0.0f;
	int m_FireCount = 0;
	float m_FlyingSpeed = 800.0f;

	float4 m_HitPos = float4{ 0.0f, 0.0f };


	bool m_FollowEffectOn = false;

	// 리셋
	virtual void Reset() override;
	void ResetDir();
	

	bool m_Direction = false;
	void DirCheck();

	// 상태값 변경
	void ChangeState(GangsterState _State);
	// 현재 상태값에 따른 업데이트 
	void UpdateState(float _DeltaTime);

	GangsterState m_CurState = GangsterState::NONE;
	GangsterState m_PrevState = GangsterState::NONE;
	GangsterState m_NextState = GangsterState::NONE;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void WalkStart();
	void WalkUpdate(float _DeltaTime);
	void WalkEnd();
	
	void ChaseStart();
	void ChaseUpdate(float _DeltaTime);
	void ChaseEnd();

	void AimStart();
	void AimUpdate(float _DeltaTime);
	void AimEnd();

	void TurnStart();
	void TurnUpdate(float _DeltaTime);
	void TurnEnd();

	void HitGroundStart();
	void HitGroundUpdate(float _DeltaTime);
	void HitGroundEnd();

	
};
