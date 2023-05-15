#pragma once
#include <string>
#include <GameEngineBase/GameEngineSerializer.h>
#include "BaseActor.h"

#include <GameEngineCore/GameEngineTexture.h>

enum class PlayerState
{
	NONE,
	ILDETORUN,
	IDLE,
	MOVE,
	JUMP,
	SLASH,
	CROUCH,
	FLIP,
	FALL,
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

	PlayerState GetCurState()
	{
		return m_CurState;
	}

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender() const
	{
		return m_Render;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void FindAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	float4 m_LocalScale = { 100.0f , 75.0f , 0.0f };
	float  m_MoveSpeed = 500.0f;

	// 마우스를 클릭했을 때의 좌표를 저장
	float4 m_AttackPos = {};

	// true = 오른쪽
	bool   m_Direction = true; 
	void DirCheck();

	// 점프관련
	bool m_IsJumping = false;
	float m_JumpPower = 450.0f;
	float m_JumpMoveSpeed = 400.0f;
	float m_CurrentVerticalVelocity = 0.0f;
	float m_FallPower = 800.0f;

	// 중력 
	const float m_GravityPower = 1000.0f;

	// 얘는 필요없을것 같다. 
	void AddGravity(float _DeltaTime)
	{
		switch (m_CurState)
		{
		case PlayerState::ILDETORUN:
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
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender0 = nullptr;

	// bottom left, right 
	// 이게 있어야할듯 
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Left = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender_Right = nullptr;

	std::shared_ptr<class PixelCollider> m_PixelCollider = nullptr;


	// ------------------------- state ----------------------------------
private:
	void ChangeState(PlayerState _State);
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