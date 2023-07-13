#pragma once
#include <string>

#include <GameEngineCore/GameEngineTexture.h>

#include "BaseActor.h"

// �÷��̾� ���°� 
enum class PlayerState
{
	NONE,			// Wait <-- ������ 
	IDLETORUN,		// ���̵� -> ���� ��ȯ 
	IDLE,			// ���̵�
	MOVE,			// ���� 
	ROLL,			// ������ 
	JUMP,			// ����
	SLASH,			// ���� 
	CROUCH,			// ũ���ġ (��ũ����)
	RIGHTFLIP,
	LEFTFLIP,// ��Ÿ�� ������ 
	FALL,			// ���� 
	RIGHTWALL,		// ��Ÿ�� 
	LEFTWALL,
	DOORBREAK,

	
	FORCEFALL,		// ����ü���� ����� state 
	DEATH,			// ���
	EXPLOSION_DEATH,

	RECORDING_PROGRESS,
	RECORDING_PROGRESS_FORWARD,
};


class Player : public BaseActor
{
	friend class PlaySupporter;
	friend class PixelCollider;
	friend class ClubLevel_Boss;
	friend class ClubLevel_Boss_01;
	friend class Boss_HeadHunter;
	friend class Bullet;
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
	const std::shared_ptr<class GameEngineSpriteRenderer> GetRender() const
	{
		return m_Render;
	}

	const std::shared_ptr<class GameEngineCollision> GetCollision() const
	{
		return m_Collision;
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

	inline const std::vector<std::shared_ptr<class GameEngineSpriteRenderer>>& GetDebugRenders()
	{
		return m_DebugRenders;
	}

	inline bool IsInvincibility()
	{
		return m_Invincibility;
	}
	virtual void BulletCollision() override;

	// ����Ʈ���� �Լ��� ���� ��� 
	void CreateSlashEffect();
	void CreateExplosionEffect();
	void CreateHitEffect(std::shared_ptr<class GameEngineCollision> _Col);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	virtual void LevelChangeEnd() override;
private:
	void CreateTrailEffect();
	bool m_TrailEffect = false;

	// �����ִϸ��̼� �̺�Ʈ�߰���
	void FallAnimChange();
	void SlashSoundPlay();

	GameEngineSoundPlayer m_SoundPlayer;
	GameEngineSoundPlayer m_MoveSoundPlayer;
	GameEngineSoundPlayer m_SkillSoundPlayer;
	GameEngineSoundPlayer m_RewindSoundPlayer;

	// Ư�� �浹ü���� �浹üũ
	bool DoorColCheck();		 // �� 
	bool PlatformColCheck();	 // �÷���
	bool LaserColCheck();		 // ������
	bool FanBladeColCheck();	 // �� ���̵� 
	bool HitCheck();			 // ��Ʈüũ 
	bool BossHitCheck();

	void TimeOutCheck();

	// ���� 
	virtual void Reset() override;

	// ���������� �� ����
	void ComponentSetting();

	// �ִϸ��̼� �ε� �� ����
	void LoadAndCreateAnimation();
	void LoadSound();

	// ���콺�� Ŭ������ ���� ��ǥ�� ����
	float4 m_AttackPos = {};
	float4 m_MyOriginPos = {};

	// �̵�
	float  m_MoveSpeed = 400.0f;
	float  m_StartMoveSpeed = 350.0f;
	float  m_AttSpeed = 700.0f;

	void NextPosUpdate();
	std::shared_ptr<GameEngineTransform> m_NextTrans = nullptr;

	// ������ 
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	const float m_RenderPivot = 36.0f;
	const float m_RightRenderPivot = 29.0f;

	// �浹ü 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// ����̵� , ������Ʈ üũ��
	std::shared_ptr<class GameEngineCollision> m_SubCollision = nullptr;
	float4 m_ColScale = { 40.0f , 65.0f , 1.0f };
	float  m_ColPivot = 33.0f;

	// ����üũ, true = ������ , false = ���� 
	bool m_Direction = true; 
	bool m_SlashDir = true;
	void DirCheck();

	float4 m_HitPos = {};

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

	// Flip , 
	float4 m_LeftFlipDir = float4{ -200.0f, 170.0f };
	float4 m_RightFlipDir = float4{ 200.0f , 170.0f };
	const float m_FlipMaxTime = 0.25f;
	float m_FlipTime = 0.25f;

	// wall
	float m_WallPressTime = 0.18f;
	float m_WallPressInitTime = 0.18f;
	float m_WallJumpPower = 0.0f;

	// diagonal
	float m_DiagonalPivot = 5.0f;

	// �߷� 
	const float m_GravityPower = 1000.0f;
	const float m_Ratio = 1.0f;

	// -------------------------Debug ----------------------------------
	void DebugUpdate();
	float4 m_DebugRenderScale = { 4, 4 };
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Bottom = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Bottom_Down = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Left = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Top = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Wall_Right = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Wall_Left = nullptr;

	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> m_DebugRenders = std::vector<std::shared_ptr<class GameEngineSpriteRenderer>>();

	const float m_WallDebugPivotX = 17.0f;
	const float m_WallDebugPivotY = 36.0f;

	bool m_Invincibility = false;

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

	void RightFlipStart();
	void RightFlipUpdate(float _DeltaTime);
	void RightFlipEnd();

	void LeftFlipStart();
	void LeftFlipUpdate(float _DeltaTime);
	void LeftFlipEnd();

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();

	void RightWallStart();
	void RightWallUpdate(float _DeltaTime);
	void RightWallEnd();

	void LeftWallStart();
	void LeftWallUpdate(float _DeltaTime);
	void LeftWallEnd();

	void DoorBreakStart();
	void DoorBreakUpdate(float _DeltaTime);
	void DoorBreakEnd();
	
	void DeathStart();
	void DeathUpdate(float _DeltaTime);
	void DeathEnd();
	
	void NoneStart();
	void NoneUpdate(float _DeltaTime);
	void NoneEnd();

	void ForceFallStart();
	void ForceFallUpdate(float _DeltaTime);
	void ForceFallEnd();

	void ExplosionDeathStart();
	void ExplosionDeathUpdate(float _DeltaTime);
	void ExplosionDeathEnd();

	void RecordingProgressStart();
	void RecordingProgressUpdate(float _DeltaTime);
	void RecordingProgressEnd();

	void RecordingProgress_ForwardStart();
	void RecordingProgress_ForwardUpdate(float _DeltaTime);
	void RecordingProgress_ForwardEnd();
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