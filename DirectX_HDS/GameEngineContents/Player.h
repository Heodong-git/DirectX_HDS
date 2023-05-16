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
	JUMP,			// 점프
	SLASH,			// 공격 
	CROUCH,			// 크라우치 (웅크리기)
	FLIP,			// 회전회오리
	FALL,			// 낙하 
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

	const bool GetDir() const
	{
		return m_Direction;
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
	// 픽셀체크
	std::shared_ptr<class PixelCollider> m_PixelCollider = nullptr;

	// 방향체크, true = 오른쪽 , false = 왼쪽 
	bool   m_Direction = true; 
	void DirCheck();

	// 점프
	bool m_IsJumping = false;					// 점프상태인지
	float m_JumpPower = 450.0f;					// 점프하는 힘 
	float m_JumpMoveSpeed = 400.0f;				// 점프중 이동속도  
	float m_CurrentVerticalVelocity = 0.0f;	    // 현재 점프파워  
	float m_FallPower = 800.0f;					// 낙하하는 힘 

	// Flip
	bool m_RightFlip = false;
	bool m_LeftFlip = false;
	float m_FlipSpeed = 700.0f;

	// 중력 
	const float m_GravityPower = 1000.0f;

	// 얘는 필요없을것 같다. 일단 보류 
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