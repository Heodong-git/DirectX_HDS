#include "PrecompileHeader.h"
#include "CPlayManager.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

CPlayManager::CPlayManager()
{
}

CPlayManager::~CPlayManager()
{
}



// 플레이레벨에서 사용할 UI생성 
void CPlayManager::Start()
{
	CreateRender();
}

void CPlayManager::Update(float _DeltaTime)
{
}

void CPlayManager::Render(float _DeltaTime)
{
}

void CPlayManager::CreateRender()
{
	float4 screensize = GameEngineWindow::GetScreenSize();

	m_BackGroundRender = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGroundRender->SetPipeLine("2DTexture");
	m_BackGroundRender->SetTexture("BossStage1.png");
	m_BackGroundRender->GetTransform()->SetLocalScale(screensize);
	//m_BackGroundRender->GetTransform()->SetLocalPosition();

	m_HUDRender = CreateComponent<GameEngineSpriteRenderer>();
	m_HUDRender->SetPipeLine("2DTexture");
	m_HUDRender->SetTexture("HUD.png");
	m_HUDRender->GetTransform()->SetLocalScale({ screensize.x , 50.0f });
	m_HUDRender->GetTransform()->SetLocalPosition({ 0 , 338.0f });
}