#pragma once
#include <string>
#include <GameEngineBase/GameEngineSerializer.h>
#include "BaseActor.h"

#include <GameEngineCore/GameEngineTexture.h>

enum class PlayerState
{
	NONE,
	IDLE,
	MOVE,
	JUMP,
	SLASH,
};

class Player : public BaseActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Renderer = nullptr;
	float4 m_LocalScale = { 75.0f , 75.0f , 0.0f };
	float  m_MoveSpeed = 500.0f;

	// ���� 
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

	// -------------------------Debug ----------------------------------
	bool m_IsDebug = false;
	inline void DebugSwitch()
	{
		m_IsDebug = !m_IsDebug;
	}

	void DebugUpdate();
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender0 = nullptr;


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