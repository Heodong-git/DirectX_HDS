#pragma once
#include "BaseActor.h"

enum class GangsterState
{
	NONE,
	IDLE,	 // ���̵�
	WALK,	 // �ȱ�
	CHASE,	 // �ٱ� 
	HITGROUND,	 // �ĸ���
	AIM,	 // ���� 
};

// ������ 
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
	std::shared_ptr<class GameEngineSpriteRenderer> m_GunRender = nullptr;

	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;

	
private:
	// ����
	// + ������ 
	// - ����
	int m_Direction = -1;
	void DirCheck();

	// ���°� ����
	void ChangeState(GangsterState _State);
	// ���� ���°��� ���� ������Ʈ 
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
