#include "PrecompileHeader.h"
#include "GlitchEffect.h"

GlitchEffect::GlitchEffect()
{
}

GlitchEffect::~GlitchEffect()
{
}

void GlitchEffect::Start(GameEngineRenderTarget* _Target)
{
	GlitchUnit = std::make_shared<GameEngineRenderUnit>();
	GlitchUnit->SetMesh("FullRect");
	GlitchUnit->SetPipeLine("OldTV");

	BaseValue.ScreenScale = GameEngineWindow::GetScreenSize();

	GlitchUnit->ShaderResHelper.SetConstantBufferLink("RenderBaseValue", BaseValue);

	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void GlitchEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (true == m_IsUpdate)
	{
		BaseValue.Mouse = GameEngineWindow::GetMousePosition();
		BaseValue.Mouse.z = GameEngineInput::IsPress("EngineMouseLeft");
		BaseValue.Mouse.w = GameEngineInput::IsPress("EngineMouseLeft");

		BaseValue.Time.x += _DeltaTime;
		BaseValue.Time.y = _DeltaTime;

		ResultTarget->Clear();
		GlitchUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
		ResultTarget->Setting();
		GlitchUnit->Render(_DeltaTime);
		GlitchUnit->ShaderResHelper.AllResourcesReset();

		_Target->Clear();
		_Target->Merge(ResultTarget);
	}
}
