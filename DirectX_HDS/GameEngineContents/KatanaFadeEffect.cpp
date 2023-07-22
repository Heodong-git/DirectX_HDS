#include "PrecompileHeader.h"
#include "KatanaFadeEffect.h"

KatanaFadeEffect::KatanaFadeEffect()
{	 
}

KatanaFadeEffect::~KatanaFadeEffect()
{								   
}

void KatanaFadeEffect::Start(GameEngineRenderTarget* _Target)
{
	FadeUnit = std::make_shared<GameEngineRenderUnit>();
	FadeUnit->SetMesh("FullRect");
	FadeUnit->SetPipeLine("KatanaFade");

	BaseValue.ScreenScale = GameEngineWindow::GetScreenSize();

	FadeUnit->ShaderResHelper.SetConstantBufferLink("RenderBaseValue", BaseValue);

	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void KatanaFadeEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	BaseValue.Mouse = GameEngineWindow::GetMousePosition();
	BaseValue.Mouse.z = GameEngineInput::IsPress("EngineMouseLeft");
	BaseValue.Mouse.w = GameEngineInput::IsPress("EngineMouseLeft");

	BaseValue.Time.x += _DeltaTime;
	BaseValue.Time.y = _DeltaTime;

	ResultTarget->Clear();
	FadeUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	ResultTarget->Setting();
	FadeUnit->Render(_DeltaTime);
	FadeUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);
}
