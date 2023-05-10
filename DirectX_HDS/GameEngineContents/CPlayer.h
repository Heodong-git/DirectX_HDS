#pragma once
#include <string>
#include <GameEngineBase/GameEngineSerializer.h>
#include "CKatanaZero_Actor.h"

#include <GameEngineCore/GameEngineTexture.h>

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

	std::shared_ptr<class GameEngineSpriteRenderer>& GetRender()
	{
		return m_Renderer;
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

	bool   m_Snail = false;
	
	// Pixel Collider 
	void Gravity(float _DeltaTime);

	GameEnginePixelColor GetPixelColor(float4 _Pos);
	GameEnginePixelColor m_Black = { static_cast<char>(0), static_cast<char>(0), static_cast<char>(0), static_cast<char>(160) };
	GameEnginePixelColor m_White = { static_cast<char>(255), static_cast<char>(255), static_cast<char>(255), static_cast<char>(255) };
	
	bool IsBlackPixel(GameEnginePixelColor _Pixel)
	{
		return m_Black == _Pixel;
	}

	bool IsWhitePixel(GameEnginePixelColor _Pixel)
	{
		return m_White == _Pixel;
	}

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