#pragma once
#include <string>
#include <GameEngineBase/GameEngineSerializer.h>
#include "CKatanaZero_Actor.h"

enum class PLAYERSTATE
{
	NONE,
	IDLE,
	MOVE,
	JUMP,
	SLASH,
};

class CPlayer : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CPlayer();
	~CPlayer();

	// delete Function
	CPlayer(const CPlayer& _Other) = delete;
	CPlayer(CPlayer&& _Other) noexcept = delete;
	CPlayer& operator=(const CPlayer& _Other) = delete;
	CPlayer& operator=(CPlayer&& _Other) noexcept = delete;

	inline bool IsSnail() const
	{
		return m_Snail;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void ChangeState(PLAYERSTATE _State);
	void UpdateState(float _DeltaTime);

	PLAYERSTATE m_CurState = PLAYERSTATE::IDLE;
	PLAYERSTATE m_PrevState = PLAYERSTATE::NONE;
	PLAYERSTATE m_NextState = PLAYERSTATE::NONE;

	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer;
	float4 m_LocalScale = { 75.0f , 75.0f , 0.0f };
	float  m_MoveSpeed = 500.0f;

	// 이걸 곱해주는게 맞나
	float  m_SlashMoveRange = 10.0f;
	bool   m_Snail = false;

	
	// ------------------------- state ----------------------------------
private:
	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void SlashStart();
	void SlashUpdate(float _DeltaTime);
	void SlashEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();
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