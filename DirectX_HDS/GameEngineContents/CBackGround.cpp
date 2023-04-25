#include "PrecompileHeader.h"
#include "CBackGround.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::Start()
{
	m_BackGroundRender = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGroundRender->SetPipeLine("2DTexture");
	m_BackGroundRender->SetTexture("spr_title_background.png");
	float4 screensize = GameEngineWindow::GetScreenSize();
	// юс╫ц
	m_BackGroundRender->GetTransform()->SetLocalScale({screensize.x , screensize.y * 2.0f});
}

void CBackGround::Update(float _DeltaTime)
{
	float4 renderpos = m_BackGroundRender->GetTransform()->GetLocalPosition();
	if (renderpos.y >= m_StartPoint.y)
	{
		m_BackGroundRender->GetTransform()->SetLocalPosition(m_StartPoint);
		return;
	}

	float4 movepos = renderpos.LerpClamp(renderpos, m_StartPoint, 1.0f);
	movepos.Normalize();
	m_BackGroundRender->GetTransform()->AddLocalPosition(movepos * m_MoveSpeed * _DeltaTime);
}

void CBackGround::Render(float _DeltaTime)
{
}
