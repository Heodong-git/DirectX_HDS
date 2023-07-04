#include "PrecompileHeader.h"
#include "DistotionEffect.h"

DistotionEffect::DistotionEffect()
{
}

DistotionEffect::~DistotionEffect()
{
}

void DistotionEffect::Start(GameEngineRenderTarget* _Target)
{
	BlurUnit = std::make_shared<GameEngineRenderUnit>();
	BlurUnit->SetMesh("FullRect");
	BlurUnit->SetPipeLine("OldTV");

	BaseValue.ScreenScale = GameEngineWindow::GetScreenSize();

	BlurUnit->ShaderResHelper.SetConstantBufferLink("RenderBaseValue", BaseValue);

	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void DistotionEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (true == m_IsUpdate)
	{
		BaseValue.Mouse = GameEngineWindow::GetMousePosition();
		BaseValue.Mouse.z = GameEngineInput::IsPress("EngineMouseLeft");
		BaseValue.Mouse.w = GameEngineInput::IsPress("EngineMouseLeft");

		BaseValue.Time.x += _DeltaTime;
		BaseValue.Time.y = _DeltaTime;

		ResultTarget->Clear();
		BlurUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
		ResultTarget->Setting();
		BlurUnit->Render(_DeltaTime);
		BlurUnit->ShaderResHelper.AllResourcesReset();

		_Target->Clear();
		_Target->Merge(ResultTarget);
	}
}
