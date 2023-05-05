#include "PrecompileHeader.h"
#include "CTimer.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

void CTimer::Start()
{
	m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DTexture");
	m_CaseRender->SetTexture("spr_hud_timer_0.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 230.0f, 40.0f });
	m_CaseRender->GetTransform()->SetLocalPosition({ -10.0f , 338.0f });

	m_GageRender = CreateComponent<GameEngineSpriteRenderer>();
	m_GageRender->SetPipeLine("2DTexture");
	m_GageRender->SetTexture("spr_timer_0.png");
	m_GageRender->GetTransform()->SetLocalScale({ 200.0f, 25.0f });
	m_GageRender->GetTransform()->SetLocalPosition({ 10.0f , 342.0f });

	/*m_GageRender = CreateComponent<GameEngineSpriteRenderer>();
	m_GageRender->SetPipeLine("2DBlinkTexture");
	m_GageRender->GetShaderResHelper().SetTexture("BlinkTex", "spr_timer_0.png");
	m_GageRender->GetTransform()->SetLocalScale({ 200.0f, 25.0f });
	m_GageRender->GetTransform()->SetLocalPosition({ 10.0f , 342.0f });*/

	/*m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DBlinkTexture");
	m_CaseRender->GetShaderResHelper().SetTexture("BlinkTex", "spr_hud_timer_0.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 230.0f, 40.0f });
	m_CaseRender->GetTransform()->SetLocalPosition({ -10.0f , 338.0f });*/
}

void CTimer::Update(float _DeltaTime)
{
}

void CTimer::Render(float _DeltaTime)
{
}
