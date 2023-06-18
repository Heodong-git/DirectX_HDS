#pragma once
#include "BaseActor.h"

enum class GruntState
{
	NONE,
	IDLE,		// ���̵�
	WALK,		// �ȱ�
	CHASE,		// �ٱ� 
	ATTACK,		// ����
	FALL,		// ���ư�
	HITGROUND,	// �ĸ���
	TURN,		// �ڵ��� 
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

	// �����ȯ 
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
	void CreateEffect();		// ��������Ʈ ����
	void CreateFollowEffect();  // ���߰� ����Ʈ ����

	bool ChaseCheck();			// chase üũ�� �浹ü�� �÷��̾ �浹�ߴ��� Ȯ��
	void DoorOpenCheck();		// ���� ���ȴ�
	bool DoorCollisionCheck();	// �� �浹üũ 
	bool PartitionCollisionCheck();
	void DeathCheck();			// ���� �׾����� 


	// �ٿ 
	 
	 
	// �ִϸ��̼������ӿ� �߰� 
	void Attack();
	void AttackOff();

	// ��Ʈ����Ʈ �Ǻ�
	float m_HitEffectPivot = 20.0f;

	// ���� 
	float m_RenderPivot = 38.0f;
	float m_ColPivot = 32.0f;
	float4 m_ColScale = { 45.0f, 65.0f , 1.0f };

	// --------------------- ���� �� ���Խ��Ѿ��� �ʱ�ȭ�� ---------------------------
	virtual void Reset() override;
	void ResetDir();

	// ���ݴ����� ���� ��ġ 
	float4 m_HitPos = {};

	// �ɷ�ġ
	float m_ChaseMoveSpeed = 250.0f;
	float m_WalkMoveSpeed = 100.0f;
	float m_FlyingSpeed = 1000.0f;

	// ���߰� ����Ʈ ��� Ȯ�ο� ���� 
	bool m_FollowEffectOn = false;

	// true = ������ , false = ���� 
	bool m_Direction = false;
	void DirCheck();


	// -------------------------------------- State -----------------------------------------------
	void UpdateState(float _DeltaTime);

	GruntState m_CurState = GruntState::NONE;
	GruntState m_PrevState = GruntState::NONE;
	GruntState m_NextState = GruntState::NONE;

	// ���̵�
	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	// ��ũ 
	void WalkStart();
	void WalkUpdate(float _DeltaTime);
	void WalkEnd();

	// �� 
	void ChaseStart();
	void ChaseUpdate(float _DeltaTime);
	void ChaseEnd();

	// ���� 
	void HitGroundStart();
	void HitGroundUpdate(float _DeltaTime);
	void HitGroundEnd();

	// ���� 
	void AttackStart();
	void AttackUpdate(float _DeltaTime);
	void AttackEnd();

	// �ڵ��� 
	void TurnStart();
	void TurnUpdate(float _DeltaTime);
	void TurnEnd();

	// ���� 
	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();
};
