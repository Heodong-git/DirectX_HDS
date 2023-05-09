#include "PrecompileHeader.h"
#include "CPlayManager.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "CKatanaZero_Level.h"
#include "CBattery.h"

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

	/*m_BackGroundRender = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGroundRender->SetPipeLine("2DTexture");
	m_BackGroundRender->SetTexture("BossStage1.png");
	m_BackGroundRender->GetTransform()->SetLocalScale({ screensize.x, screensize.y});*/

	m_HUDRender = CreateComponent<GameEngineSpriteRenderer>();
	m_HUDRender->SetPipeLine("2DTexture");
	m_HUDRender->SetTexture("HUD.png");
	m_HUDRender->GetTransform()->SetLocalScale({ screensize.x , 50.0f });
	m_HUDRender->GetTransform()->SetLocalPosition({ 0 , 338.0f });

	m_MouseLRender = CreateComponent<GameEngineSpriteRenderer>();
	m_MouseLRender->SetPipeLine("2DTexture");
	m_MouseLRender->SetTexture("spr_left_click_1.png");
	m_MouseLRender->GetTransform()->SetLocalScale({ 25, 25 });
	m_MouseLRender->GetTransform()->SetLocalPosition({ 560 , 310 , -1 });

	m_MouseRRender = CreateComponent<GameEngineSpriteRenderer>();
	m_MouseRRender->SetPipeLine("2DTexture");
	m_MouseRRender->SetTexture("spr_right_click_1.png");
	m_MouseRRender->GetTransform()->SetLocalScale({ 25 , 25 });
	m_MouseRRender->GetTransform()->SetLocalPosition({ 610 , 310 , -1 });
}