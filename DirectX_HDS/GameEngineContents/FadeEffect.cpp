#include "PrecompileHeader.h"
#include "FadeEffect.h"

FadeEffect::FadeEffect()
{
}

FadeEffect::~FadeEffect()
{
}

void FadeEffect::Start(GameEngineRenderTarget* _Target)
{
	FadeUnit = std::make_shared<GameEngineRenderUnit>();
	FadeUnit->SetPipeLine("Fade");
	FadeUnit->ShaderResHelper.SetConstantBufferLink("FADEDATA", FadeData);
	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void FadeIn()
{

}

void FadeOut()
{

}

void FadeEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (State == FadeState::NONE)
	{
		return;
	}

	if (State == FadeState::FADEIN && 0.2f <= FadeData.x)
	{
		return;
	}

	if (State == FadeState::FADEIN)
	{
		FadeData.x += _DeltaTime;
	}
	else
	{
		FadeData.x -= _DeltaTime;
	}

	ResultTarget->Clear();
	FadeUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	ResultTarget->Setting();
	FadeUnit->Render(_DeltaTime);
	FadeUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);
}