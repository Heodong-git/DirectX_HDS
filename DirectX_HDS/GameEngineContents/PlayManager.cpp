#include "PrecompileHeader.h"
#include "PlayManager.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "BaseLevel.h"
#include "Battery.h"

PlayManager* PlayManager::m_Inst = nullptr;
std::shared_ptr<class Timer> PlayManager::m_Timer = nullptr;
std::shared_ptr<class Battery> PlayManager::m_Battery = nullptr;
std::shared_ptr<class Inven> PlayManager::m_Inven = nullptr;
std::shared_ptr<class Hud> PlayManager::m_Hud = nullptr;
PlayManager::LevelName PlayManager::m_LevelName = PlayManager::LevelName::NONE;

PlayManager::PlayManager()
{
	CreateRender();
}

PlayManager::~PlayManager()
{
	
}


void PlayManager::CreateRender()
{
	float4 screensize = GameEngineWindow::GetScreenSize();

	/*m_BackGroundRender = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGroundRender->SetPipeLine("2DTexture");
	m_BackGroundRender->SetTexture("BossStage1.png");
	m_BackGroundRender->GetTransform()->SetLocalScale({ screensize.x, screensize.y});*/

	/*m_HUDRender = CreateComponent<GameEngineSpriteRenderer>();
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
	m_MouseRRender->GetTransform()->SetLocalPosition({ 610 , 310 , -1 });*/
}

void PlayManager::Update(float _DeltaTime)
{
}

void PlayManager::CameraSetting()
{

	switch (m_LevelName)
	{
	case PlayManager::LevelName::NONE:
		break;
	case PlayManager::LevelName::CLUB:
	{
		m_CameraPivot = { -360, 34 , 0 };
		if (nullptr != Player::MainPlayer)
		{
			Player::MainPlayer->GetReturnCastLevel()->GetMainCamera()->GetTransform()->AddLocalPosition(m_CameraPivot);
		}
		
	}
		break;
	case PlayManager::LevelName::CLUBBOSS:
		break;
	default:
		break;
	}
}
