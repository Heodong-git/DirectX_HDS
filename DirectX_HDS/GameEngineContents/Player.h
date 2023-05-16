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
	JUMP,			// ����
	SLASH,			// ���� 
	CROUCH,			// ũ���ġ (��ũ����)
	FLIP,			// ȸ��ȸ����
	FALL,			// ���� 
};

class Player : public BaseActor
{
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

	const bool GetDir() const
	{
		return m_Direction;
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
	// �ȼ�üũ
	std::shared_ptr<class PixelCollider> m_PixelCollider = nullptr;

	// ����üũ, true = ������ , false = ���� 
	bool   m_Direction = true; 
	void DirCheck();

	// ����
	bool m_IsJumping = false;					// ������������
	float m_JumpPower = 450.0f;					// �����ϴ� �� 
	float m_JumpMoveSpeed = 400.0f;				// ������ �̵��ӵ�  
	float m_CurrentVerticalVelocity = 0.0f;	    // ���� �����Ŀ�  
	float m_FallPower = 800.0f;					// �����ϴ� �� 

	// Flip
	bool m_RightFlip = false;
	bool m_LeftFlip = false;
	float m_FlipSpeed = 700.0f;

	// �߷� 
	const float m_GravityPower = 1000.0f;

	// ��� �ʿ������ ����. �ϴ� ���� 
	void AddGravity(float _DeltaTime)
	{
		switch (m_CurState)
		{
		case PlayerState::IDLETORUN:
			break;
		case PlayerState::IDLE:
			break;
		case PlayerState::MOVE:
			break;
		case PlayerState::JUMP:
			GetTransform()->AddLocalPosition(float4::Down * m_GravityPower * _DeltaTime);
			break;
		case PlayerState::SLASH:
			GetTransform()->AddLocalPosition(float4::Down * m_GravityPower * _DeltaTime);
			break;
		case PlayerState::CROUCH:
			break;
		case PlayerState::FLIP:
			break;
		case PlayerState::FALL:
			GetTransform()->AddLocalPosition(float4::Down * m_GravityPower * _DeltaTime);
			break;
		}
	}
	

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