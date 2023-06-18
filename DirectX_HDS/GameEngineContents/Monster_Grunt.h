#pragma once
#include "BaseActor.h"

enum class GruntState
{
	NONE,
	IDLE,		// 아이들
	WALK,		// 걷기
	CHASE,		// 뛰기 
	ATTACK,		// 공격
	FALL,		// 날아감
	HITGROUND,	// 쳐맞음
	TURN,		// 뒤돌기 
};

class Monster_Grunt : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Grunt();
	~Monster_Grunt();

	// delete Function
	Monster_Grunt(const Monster_Grunt& _Other) = delete;
	Monster_Grunt(Monster_Grunt&& _Other) noexcept = delete;
	Monster_Grunt& operator=(const Monster_Grunt& _Other) = delete;
	Monster_Grunt& operator=(Monster_Grunt&& _Other) noexcept = delete;

	void ChangeState(GruntState _State);

	// 방향반환 
	const bool GetDir() const
	{
		return m_Direction;
	}

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
	void CreateEffect();		// 공격이펙트 생성
	void CreateFollowEffect();  // 적발견 이펙트 생성

	bool ChaseCheck();			// chase 체크용 충돌체와 플레이어가 충돌했는지 확인
	void DoorOpenCheck();		// 문이 열렸니
	bool DoorCollisionCheck();	// 문 충돌체크 
	bool PartitionCollisionCheck();
	void DeathCheck();			// 내가 죽었는지 


	// 바운스 
	 
	 
	// 애니메이션프레임에 추가 
	void Attack();
	void AttackOff();

	// 히트이펙트 피봇
	float m_HitEffectPivot = 20.0f;

	// 렌더 
	float m_RenderPivot = 38.0f;
	float m_ColPivot = 32.0f;
	float4 m_ColScale = { 45.0f, 65.0f , 1.0f };

	// --------------------- 리셋 시 포함시켜야할 초기화값 ---------------------------
	virtual void Reset() override;
	void ResetDir();

	// 공격당했을 때의 위치 
	float4 m_HitPos = {};

	// 능력치
	float m_ChaseMoveSpeed = 250.0f;
	float m_WalkMoveSpeed = 100.0f;
	float m_FlyingSpeed = 1000.0f;

	// 적발견 이펙트 출력 확인용 변수 
	bool m_FollowEffectOn = false;

	// true = 오른쪽 , false = 왼쪽 
	bool m_Direction = false;
	void DirCheck();


	// -------------------------------------- State -----------------------------------------------
	void UpdateState(float _DeltaTime);

	GruntState m_CurState = GruntState::NONE;
	GruntState m_PrevState = GruntState::NONE;
	GruntState m_NextState = GruntState::NONE;

	// 아이들
	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	// 워크 
	void WalkStart();
	void WalkUpdate(float _DeltaTime);
	void WalkEnd();

	// 런 
	void ChaseStart();
	void ChaseUpdate(float _DeltaTime);
	void ChaseEnd();

	// 맞음 
	void HitGroundStart();
	void HitGroundUpdate(float _DeltaTime);
	void HitGroundEnd();

	// 공격 
	void AttackStart();
	void AttackUpdate(float _DeltaTime);
	void AttackEnd();

	// 뒤돌기 
	void TurnStart();
	void TurnUpdate(float _DeltaTime);
	void TurnEnd();

	// 낙하 
	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();
};
