#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}


void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();
	SetPipeLine("2DTexture");
}

void GameEngineSpriteRenderer::SetTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
}

void GameEngineSpriteRenderer::SetFlipX()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.x = -LocalScale.x;
	GetTransform()->SetLocalScale(LocalScale);
}

void GameEngineSpriteRenderer::SetFlipY()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.y = -LocalScale.y;
	GetTransform()->SetLocalScale(LocalScale);
}