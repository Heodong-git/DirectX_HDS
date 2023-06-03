#pragma once
#include <string>
#include <GameEngineCore/GameEngineTexture.h>
#include "BaseActor.h"

// 플레이어 상태값 
enum class PlayerState
{
	NONE,			// None
	IDLETORUN,		// 아이들 -> 무브 전환 
	IDLE,			// 아이들
	MOVE,			// 무브 
	ROLL,			// 구르기 
	JUMP,			// 점프
	SLASH,			// 공격 
	CROUCH,			// 크라우치 (웅크리기)
	FLIP,			// 벽타고 구르기 
	FALL,			// 낙하 
	RIGHTWALL,		// 벽타기 
	LEFTWALL,
	DEATH,			// 쥬금
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

	// 현재 State 반환
	inline const PlayerState GetCurState() const
	{
		return m_CurState;
	}

	// 플레이어의 메인렌더러 반환 
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
	
	// 삭제보류 
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

	// 렌더러생성 및 세팅
	void ComponentSetting();

	// 애니메이션 로드 및 생성
	void LoadAndCreateAnimation();

	// 마우스를 클릭했을 때의 좌표를 저장
	float4 m_AttackPos = {};
	float4 m_MyOriginPos = {};

	// 콜리전 크기 (임시) 
	float4 m_ColScale = { 75.0f , 75.0f , 0.0f };
	float  m_MoveSpeed = 500.0f;
	float  m_StartMoveSpeed = 400.0f;
	float  m_AttSpeed = 700.0f;

	std::shared_ptr<GameEngineTransform> m_NextTrans = nullptr;

	// 렌더러 
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	// 충돌체 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// 방향체크, true = 오른쪽 , false = 왼쪽 
	bool m_Direction = true; 
	bool m_SlashDir = true;
	void DirCheck();

	// 점프
	bool m_IsJumping = false;					// 점프상태인지
	float m_JumpPower = 450.0f;					// 점프하는 힘 
	float m_JumpMoveSpeed = 400.0f;				// 점프중 이동속도  
	float m_CurrentVerticalVelocity = 0.0f;	    // 현재 점프파워  
	float m_FallPower = 700.0f;					// 낙하하는 힘 
	float m_MaxJumpHeight = 95.0f;				// 최대점프높이
	float m_JumpCutLine = 0.0f;

	// Roll 
	float4 m_RollEndPos = { 0.0f , 0.0f };
	bool m_RightRoll = false;
	bool m_LeftRoll = false;
	float m_RollSpeed = 800.0f;
	float4 m_LeftRollDir =  float4 {-200.0f , 0.0f};
	float4 m_RightRollDir = float4 { 200.0f , 0.0f};

	// 중력 
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
	// 스킬 사용가능 시간 
	float m_SkillLimitTime = 9.0f;
	// 스킬 사용 중간에 값을 저장할 변수
	float m_LimitTimeValue = 0.0f;
	// 현재 배터리가 모두 소모된 상태에서 재충전될 때 사용할 변수
	bool m_BatteryCharge = false;
	// 현재 스킬의 사용 여부를 확인할 변수 
	bool m_IsSkill = false;

	// skill
	void SkillUpdate(float _DeltaTime);
	void Slow();
	void SlowReset();

	// ------------------------- state ----------------------------------
private:
	// 상태값 변경
	void ChangeState(PlayerState _State);
	// 현재 상태값에 따른 업데이트 
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

// 파일입출력이 필수다. 
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