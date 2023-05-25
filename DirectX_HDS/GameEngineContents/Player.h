#pragma once
#include <string>
#include <GameEngineBase/GameEngineSerializer.h>
#include "BaseActor.h"

#include <GameEngineCore/GameEngineTexture.h>

// �÷��̾� ���°� 
enum class PlayerState
{
	NONE,			// None
	IDLETORUN,		// ���̵� -> ���� ��ȯ 
	IDLE,			// ���̵�
	MOVE,			// ���� 
	ROLL,			// ������ 
	JUMP,			// ����
	SLASH,			// ���� 
	CROUCH,			// ũ���ġ (��ũ����)
	FLIP,			// ��Ÿ�� ������ 
	FALL,			// ���� 
};

class Player : public BaseActor
{
	friend class PixelCollider;

public:
	static Player* MainPlayer;

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	// ���� State ��ȯ
	PlayerState GetCurState()
	{
		return m_CurState;
	}

	// �÷��̾��� ���η����� ��ȯ 
	std::shared_ptr<class GameEngineSpriteRenderer> GetRender() const
	{
		return m_Render;
	}

	inline const bool GetDir() const
	{
		return m_Direction;
	}
	
	inline const float GetRenderPivot() const
	{
		return m_RenderPivot;
	}

	inline const float4 GetAttackPos() const
	{
		return m_AttackPos;
	}

	const float GetSlowLimitTime() const
	{
		return m_SlowLimitTime;
	}

	inline bool IsSlowSkill() const
	{
		return m_IsSlowSkill;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� �ε� �� ����
	void LoadAndCreateAnimation();

	// ���콺�� Ŭ������ ���� ��ǥ�� ����
	float4 m_AttackPos = {};

	// ���ÿ����� ũ�� (�ӽ�) 
	float4 m_LocalScale = { 75.0f , 75.0f , 0.0f };
	float  m_MoveSpeed = 500.0f;
	float  m_StartMoveSpeed = 400.0f;

	// ������ 
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	// �浹ü 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// ����üũ, true = ������ , false = ���� 
	bool   m_Direction = true; 
	void DirCheck();

	// ����
	bool m_IsJumping = false;					// ������������
	float m_JumpPower = 450.0f;					// �����ϴ� �� 
	float m_JumpMoveSpeed = 400.0f;				// ������ �̵��ӵ�  
	float m_CurrentVerticalVelocity = 0.0f;	    // ���� �����Ŀ�  
	float m_FallPower = 700.0f;					// �����ϴ� �� 

	// Flip
	bool m_RightRoll = false;
	bool m_LeftRoll = false;
	float m_RollSpeed = 900.0f;

	// �߷� 
	const float m_GravityPower = 1000.0f;

	// ������ ��Ÿ�� ������� ������ ���� 
	float m_GlobalCoolDown = 0.3f; 

	

	// -------------------------Debug ----------------------------------
	void DebugUpdate();

	// bottom 
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Bottom = nullptr;

	// left, right 
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Left = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;

	// top
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Top = nullptr;

	float4 m_DebugRenderScale = { 4, 4 };
	float m_RenderPivot = 36.0f;

	// -------------------------------------------------------------------
	// -------------------------skill value----------------------------
	float m_SlowLimitTime = 9.0f;
	// skill 
	void SkillUpdate(float _DeltaTime);
	void Slow();
	void SlowReset();

	bool m_IsSlowSkill = false;
	// ------------------------- state ----------------------------------
private:
	// ���°� ����
	void ChangeState(PlayerState _State);
	// ���� ���°��� ���� ������Ʈ 
	void UpdateState(float _DeltaTime);

	PlayerState m_CurState = PlayerState::IDLE;
	PlayerState m_PrevState = PlayerState::NONE;
	PlayerState m_NextState = PlayerState::NONE;

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void IdleToRunStart();
	void IdleToRunUpdate(float _DeltaTime);
	void IdleToRunEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void SlashStart();
	void SlashUpdate(float _DeltaTime);
	void SlashEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void CrouchStart();
	void CrouchUpdate(float _DeltaTime);
	void CrouchEnd();

	void RollStart();
	void RollUpdate(float _DeltaTime);
	void RollEnd();

	void FlipStart();
	void FlipUpdate(float _DeltaTime);
	void FlipEnd();

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();
};

// ����������� �ʼ���. 
/*void TestSave(GameEngineSerializer _Ser)
	{
		_Ser.Write(TestName);
		_Ser.Write(TestAtt);
		_Ser.Write(TestDef);
	}

	void TestLoad(GameEngineSerializer _Ser)
	{
		_Ser.Read(TestName);
		_Ser.Read(TestAtt);
		_Ser.Read(TestDef);
	}*/