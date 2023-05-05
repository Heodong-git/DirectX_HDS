#include "PrecompileHeader.h"
#include "CInven.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "CKatanaZero_Level.h"

CInven::CInven()
{
}

CInven::~CInven()
{
}

void CInven::Start()
{
	m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DBlinkTexture");
	m_CaseRender->GetShaderResHelper().SetTexture("BlinkTex", "Inven_0.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 115, 45 });
	m_CaseRender->GetTransform()->SetLocalPosition({ 564 , 335 });
}

void CInven::Update(float _DeltaTime)
{
	// ������ play ���°� �ƴ϶�� ������Ʈ���� ���� 
	if (ELEVEL_STATE::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}
}

void CInven::Render(float _DeltaTime)
{
}
