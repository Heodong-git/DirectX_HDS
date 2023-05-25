#pragma once
#include <string>
#include <GameEngineBase/GameEngineSerializer.h>
#include "BaseActor.h"

#include <GameEngineCore/GameEngineTexture.h>

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
	PlayerState GetCurState()
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
	// 렌더러생성 및 세팅
	void ComponentSetting();

	// 애니메이션 로드 및 생성
	void LoadAndCreateAnimation();

	// 마우스를 클릭했을 때의 좌표를 저장
	float4 m_AttackPos = {};

	// 로컬에서의 크기 (임시) 
	float4 m_LocalScale = { 75.0f , 75.0f , 0.0f };
	float  m_MoveSpeed = 500.0f;
	float  m_StartMoveSpeed = 400.0f;

	// 렌더러 
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	// 충돌체 
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	// 방향체크, true = 오른쪽 , false = 왼쪽 
	bool   m_Direction = true; 
	void DirCheck();

	// 점프
	bool m_IsJumping = false;					// 점프상태인지
	float m_JumpPower = 450.0f;					// 점프하는 힘 
	float m_JumpMoveSpeed = 400.0f;				// 점프중 이동속도  
	float m_CurrentVerticalVelocity = 0.0f;	    // 현재 점프파워  
	float m_FallPower = 700.0f;					// 낙하하는 힘 

	// Flip
	bool m_RightRoll = false;
	bool m_LeftRoll = false;
	float m_RollSpeed = 900.0f;

	// 중력 
	const float m_GravityPower = 1000.0f;

	// 공격의 쿨타임 여기부터 만들자 ㅇㅇ 
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