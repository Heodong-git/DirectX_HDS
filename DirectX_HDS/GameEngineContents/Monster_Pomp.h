#pragma once
#include "BaseActor.h"

enum class PompState
{
	NONE,
	IDLE,	     // ���̵�
	WALK,	     // �ȱ�
	CHASE,	     // �ٱ� 
	ATTACK,	     // ���� 
	FALL,        // ���ư�
	TURN,		 // �� 
	KNOCKDOWN,	 // �˴ٿ� 
	HITGROUND,	 // ���� 
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

	// ���°� ����
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
	//void CreateEffect();		// ��������Ʈ ����
	void CreateFollowEffect();  // ���߰� ����Ʈ ����
	bool ChaseCheck();			// chase üũ�� �浹ü�� �÷��̾ �浹�ߴ��� Ȯ��
	void DoorOpenCheck();		// ���� ���ȴ�
	bool DoorCollisionCheck();	// �� �浹üũ 
	bool PartitionCollisionCheck();
	void ParryingCheck();		// �и�üũ 
	void DeathCheck();			// ���� �׾����� 
	void CreateHitEffect();
	void CreateSlashHitEffect();

	void Attack();
	void AttackOff();

	float m_HitEffectPivot = 20.0f;

	// ���� 
	float m_RenderPivot = 38.0f;
	float m_ColPivot = 32.0f;
	float4 m_ColScale = { 45.0f, 65.0f , 1.0f };

	// ����
	virtual void Reset() override;
	void ResetDir();

	float4 m_HitPos = {};

	float m_WalkMoveSpeed = 150.0f;
	float m_ChaseMoveSpeed = 250.0f;
	float m_FlyingSpeed = 1500.0f;
	bool m_FollowEffectOn = false;

	// ����
	// + ������ 
	// - ����
	bool m_Direction = false;
	void DirCheck();

	
	// --------------------------------------State ----------------------------------------------
	// ���� ���°��� ���� ������Ʈ 
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
