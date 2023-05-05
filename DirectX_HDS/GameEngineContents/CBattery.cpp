#include "PrecompileHeader.h"
#include "CBattery.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "CKatanaZero_Level.h"

CBattery::CBattery()
{
}

CBattery::~CBattery()
{
}

void CBattery::Start()
{
	m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DBlinkTexture");
	m_CaseRender->GetShaderResHelper().SetTexture("BlinkTex", "Battery_09.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 170, 40 });
	m_CaseRender->GetTransform()->SetLocalPosition({ -560 , 335 });
}

void CBattery::Update(float _DeltaTime)
{
	// ������ play ���°� �ƴ϶�� ������Ʈ���� ���� 
	if (ELEVEL_STATE::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}
}

void CBattery::Render(float _DeltaTime)
{
}
