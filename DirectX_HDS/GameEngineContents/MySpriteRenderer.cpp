#include "PrecompileHeader.h"
#include "MySpriteRenderer.h"

MySpriteRenderer::MySpriteRenderer()
{
}

MySpriteRenderer::~MySpriteRenderer()
{
}

void MySpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	SetPipeLine("My2DTexture");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;

	AColor.r = 1.0f;
	AColor.a = 1.0f;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue);
	GetShaderResHelper().SetConstantBufferLink("TestColor", AColor);
}
