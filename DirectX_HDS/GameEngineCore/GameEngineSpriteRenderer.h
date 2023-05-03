#pragma once
#include "GameEngineRenderer.h"

// 설명 :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	// 텍스쳐의 크기그대로 세팅
	void SetScaleToTexture(const std::string_view& _Name);
	void SetTexture(const std::string_view& _Name);

	void SetFlipX();
	void SetFlipY();

protected:

private:
	void Start() override;
};

