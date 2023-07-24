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
	if (0 > m_EffectTime)
	{
		m_IsUpdate = false;
		m_EffectTime = 1.2f;
		m_Complete = true;
		return;
	}


	if (true == m_IsUpdate)
	{
		m_EffectTime -= _DeltaTime;
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
					  
	
}
