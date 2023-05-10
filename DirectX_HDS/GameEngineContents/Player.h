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
	void ChangeState(PlayerState _State);
	void UpdateState(float _DeltaTime);

	PlayerState m_CurState = PlayerState::IDLE;
	PlayerState m_PrevState = PlayerState::NONE;
	PlayerState m_NextState = PlayerState::NONE;

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