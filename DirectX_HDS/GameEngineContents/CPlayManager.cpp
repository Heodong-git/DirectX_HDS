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
	m_BackGroundRender->GetTransform()->SetLocalScale({ screensize.x, screensize.y});

	m_HUDRender = CreateComponent<GameEngineSpriteRenderer>();
	m_HUDRender->SetPipeLine("2DTexture");
	m_HUDRender->SetTexture("HUD.png");
	m_HUDRender->GetTransform()->SetLocalScale({ screensize.x , 50.0f });
	m_HUDRender->GetTransform()->SetLocalPosition({ 0 , 338.0f });

	m_TimerRender = CreateComponent<GameEngineSpriteRenderer>();
	m_TimerRender->SetPipeLine("2DTexture");
	m_TimerRender->SetTexture("spr_hud_timer_0.png");
	m_TimerRender->GetTransform()->SetLocalScale({ 230.0f, 40.0f });
	m_TimerRender->GetTransform()->SetLocalPosition({ -10.0f , 338.0f });

	m_TimerGageRender = CreateComponent<GameEngineSpriteRenderer>();
	m_TimerGageRender->SetPipeLine("2DTexture");
	m_TimerGageRender->SetTexture("spr_timer_0.png");
	m_TimerGageRender->GetTransform()->SetLocalScale({ 200.0f, 25.0f });
	m_TimerGageRender->GetTransform()->SetLocalPosition({ 10.0f , 342.0f });

	m_InvenRender = CreateComponent<GameEngineSpriteRenderer>();
	m_InvenRender->SetPipeLine("2DTexture");
	m_InvenRender->SetTexture("Inven_0.png");
	m_InvenRender->GetTransform()->SetLocalScale({ 115, 45 });
	m_InvenRender->GetTransform()->SetLocalPosition({ 564 , 335  });

	m_BatteryRender = CreateComponent<GameEngineSpriteRenderer>();
	m_BatteryRender->SetPipeLine("2DTexture");
	m_BatteryRender->SetTexture("Battery_09.png");
	m_BatteryRender->GetTransform()->SetLocalScale({ 170, 40 });
	m_BatteryRender->GetTransform()->SetLocalPosition({ -560 , 335 });

	m_MouseLRender = CreateComponent<GameEngineSpriteRenderer>();
	m_MouseLRender->SetPipeLine("2DTexture");
	m_MouseLRender->SetTexture("spr_left_click_1.png");
	m_MouseLRender->GetTransform()->SetLocalScale({ 25, 25 });
	m_MouseLRender->GetTransform()->SetLocalPosition({ 560 , 310 });

	m_MouseRRender = CreateComponent<GameEngineSpriteRenderer>();
	m_MouseRRender->SetPipeLine("2DTexture");
	m_MouseRRender->SetTexture("spr_right_click_1.png");
	m_MouseRRender->GetTransform()->SetLocalScale({ 25 , 25 });
	m_MouseRRender->GetTransform()->SetLocalPosition({ 610 , 310 });
}