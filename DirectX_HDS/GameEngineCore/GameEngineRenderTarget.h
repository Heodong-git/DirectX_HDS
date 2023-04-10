#pragma once
#include "GameEngineTexture.h"

// Ό³Έν :
class GameEngineRenderTarget : public GameEngineResource<GameEngineRenderTarget>
{
public:
	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRenderTarget> Create(const std::string_view& _Name, std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource::Create(_Name);

		NewRenderTarget->Create(_Texture, _Color);

		return NewRenderTarget;
	}

	void Clear();



protected:

private:
	float4 Color = { 0.0f, 0.0f, 0.0f, 0.0f };

	std::shared_ptr<GameEngineTexture> Texture;

	void Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);

};

