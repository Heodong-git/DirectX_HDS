#pragma once
#include "GameEngineTexture.h"

// 설명 :
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

		NewRenderTarget->ResCreate(_Texture, _Color);

		return NewRenderTarget;
	}

	void Clear();

	void Setting() override;
	void CreateDepthTexture();
protected:

private:
	float4 Color = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::shared_ptr<GameEngineTexture> Texture;

	// 깊이버퍼용 텍스쳐
	std::shared_ptr<GameEngineTexture> DepthTexture;
	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);
};

