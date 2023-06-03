#pragma once
#include <string>
#include <GameEngineCore/GameEngineTexture.h>
#include "BaseActor.h"

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
	RIGHTWALL,		// ��Ÿ�� 
	LEFTWALL,
	DEATH,			// ���
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
	inline const PlayerState GetCurState() const
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

	inline void ResetDir()
	{
		m_Direction = true;
	}
	
	// �������� 
	inline const float GetRenderPivot() const
	{
		return m_RenderPivot;
	}

	inline const float4 GetAttackPos() const
	{
		return m_AttackPos;
	}

	const float GetSkillLimitTime() const
	{
		return m_SkillLimitTime;
	}

	inline bool IsSkill() const
	{
		return m_IsSkill;
	}

	inline void ResetSkillLimitTime()
	{
		m_SkillLimitTime = 9.0f;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	virtual void Reset() override;

	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� �ε� �� ����
	void LoadAndCreateAnimation();

	// ���콺�� Ŭ������ ���� ��ǥ�� ����
	float4 m_AttackPos = {};
	float4 m_MyOriginPos = {};

	// �ݸ��� ũ�� (�ӽ�) 
	float4 m_ColScale = { 75.0f , 75.0f , 0.0f };
	float  m_MoveSpeed = 500.0f;
	float  m_StartMoveSpeed = 400.0f;
	float  m_AttSpeed = 700.0f;

	std::shared_ptr<GameEngineTransform> m_NextTrans = nullptr;

	// ������ 
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	// �浹ü 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// ����üũ, true = ������ , false = ���� 
	bool m_Direction = true; 
	bool m_SlashDir = true;
	void DirCheck();

	// ����
	bool m_IsJumping = false;					// ������������
	float m_JumpPower = 450.0f;					// �����ϴ� �� 
	float m_JumpMoveSpeed = 400.0f;				// ������ �̵��ӵ�  
	float m_CurrentVerticalVelocity = 0.0f;	    // ���� �����Ŀ�  
	float m_FallPower = 700.0f;					// �����ϴ� �� 
	float m_MaxJumpHeight = 95.0f;				// �ִ���������
	float m_JumpCutLine = 0.0f;

	// Roll 
	float4 m_RollEndPos = { 0.0f , 0.0f };
	bool m_RightRoll = false;
	bool m_LeftRoll = false;
	float m_RollSpeed = 800.0f;
	float4 m_LeftRollDir =  float4 {-200.0f , 0.0f};
	float4 m_RightRollDir = float4 { 200.0f , 0.0f};

	// �߷� 
	const float m_GravityPower = 1000.0f;

	// -------------------------Debug ----------------------------------
	void DebugUpdate();
	float4 m_DebugRenderScale = { 10, 10 };
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Bottom = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Bottom_Down = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Left = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Top = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_WallRight = nullptr;

	float m_RenderPivot = 36.0f;

	// -------------------------------------------------------------------
	// -------------------------skill value----------------------------
	// ��ų ��밡�� �ð� 
	float m_SkillLimitTime = 9.0f;
	// ��ų ��� �߰��� ���� ������ ����
	float m_LimitTimeValue = 0.0f;
	// ���� ���͸��� ��� �Ҹ�� ���¿��� �������� �� ����� ����
	bool m_BatteryCharge = false;
	// ���� ��ų�� ��� ���θ� Ȯ���� ���� 
	bool m_IsSkill = false;

	// skill
	void SkillUpdate(float _DeltaTime);
	void Slow();
	void SlowReset();

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

	void RightWallStart();
	void RightWallUpdate(float _DeltaTime);
	void RightWallEnd();

	void LeftWallStart();
	void LeftWallUpdate(float _DeltaTime);
	void LeftWallEnd();
	
	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
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