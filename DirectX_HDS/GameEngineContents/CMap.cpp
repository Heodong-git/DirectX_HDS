#include "PrecompileHeader.h"
#include "CMap.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

CMap::CMap()
{
}

CMap::~CMap()
{
}

void CMap::Start()
{
	m_BackGround = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGround->SetPipeLine("2DTexture");
	m_BackGround->SetTexture("background_black.png");
	float4 screensize = GameEngineWindow::GetScreenSize();
	m_BackGround->GetTransform()->SetLocalScale({ screensize.x * 2.0f , screensize.y * 2.0f });
	m_BackGround->GetTransform()->AddLocalPosition(float4{ 0.0f, 0.0f, 0.0f });

	m_MapRender = CreateComponent<GameEngineSpriteRenderer>();
}

