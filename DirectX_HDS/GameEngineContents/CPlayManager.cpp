#include "PrecompileHeader.h"
#include "CPlayManager.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "CKatanaZero_Level.h"
#include "Battery.h"
#include "CPlayer.h"

CPlayManager* CPlayManager::m_Inst = nullptr;
std::shared_ptr<class CTimer> CPlayManager::m_Timer = nullptr;
std::shared_ptr<class Battery> CPlayManager::m_Battery = nullptr;
std::shared_ptr<class Inven> CPlayManager::m_Inven = nullptr;
std::shared_ptr<class Hud> CPlayManager::m_Hud = nullptr;
std::shared_ptr<class CPlayer> CPlayManager::m_Player = nullptr;
CPlayManager::LEVELTYPE CPlayManager::m_LevelType = CPlayManager::LEVELTYPE::NONE;

CPlayManager::CPlayManager()
{
	CreateRender();
}

CPlayManager::~CPlayManager()
{
	
}


void CPlayManager::CreateRender()
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

void CPlayManager::Update(float _DeltaTime)
{
	if (nullptr != m_Player)
	{
		if (true == m_Player->IsSnail())
		{
			
		}
	}
}

void CPlayManager::CameraSetting()
{

	switch (m_LevelType)
	{
	case CPlayManager::LEVELTYPE::NONE:
		break;
	case CPlayManager::LEVELTYPE::STAGE_01:
	{
		m_CameraPivot = { -360, 34 , 0 };
		m_Player->GetReturnCastLevel()->GetMainCamera()->GetTransform()->AddLocalPosition(m_CameraPivot);
	}
		break;
	case CPlayManager::LEVELTYPE::STAGE_02:
		break;
	default:
		break;
	}
}
