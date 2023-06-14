#pragma once
#include "BaseActor.h"

enum class GruntState
{
	NONE,
	IDLE,		// ���̵�
	WALK,		// �ȱ�
	CHASE,		// �ٱ� 
	HITGROUND,	// �ĸ���
	ATTACK,		// ����
	FALL,		// ���ư�
	TURN,		// �ڵ��� 
};

// ������
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DebugUpdate();

	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� ���ҽ� �ε�׻���
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;


	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineCollision> m_ChaseCollision = nullptr;
	
private:
	bool ChaseRangeCheck();

	// ��Ʈ����Ʈ �Ǻ�
	float m_HitEffectPivot = 20.0f;

	// �ɷ�ġ
	float m_MoveSpeed = 200.0f;

	// ���� 
	float m_RenderPivot = 38.0f;
	float m_ColPivot = 32.0f;
	float4 m_ColScale = { 45.0f, 65.0f , 1.0f };

	// ����
	virtual void Reset() override;
	inline void ResetDir()
	{
		m_Direction = -1;
	}
	// ����
	// + ������ 
	// - ����
	int m_Direction = -1;
	void DirCheck();

	// ���°� ����
	void ChangeState(GruntState _State);
	// ���� ���°��� ���� ������Ʈ 
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
