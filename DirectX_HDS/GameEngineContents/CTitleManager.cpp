#include "PrecompileHeader.h"
#include "CTitleManager.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

CTitleManager::CTitleManager()
{
}

CTitleManager::~CTitleManager()
{
	
}

void CTitleManager::Start()
{
	if (false == GameEngineInput::IsKey("TitleMenu_Up"))
	{
		GameEngineInput::CreateKey("TitleMenu_Up", 'W');
		GameEngineInput::CreateKey("TitleMenu_Up_2", VK_UP);
		GameEngineInput::CreateKey("TitleMenu_Down", 'S');
		GameEngineInput::CreateKey("TitleMenu_Down_2", VK_DOWN);
		GameEngineInput::CreateKey("TitleMenu_Select", VK_SPACE);
		GameEngineInput::CreateKey("TitleMenu_Select_Enter", VK_RETURN);
		GameEngineInput::CreateKey("Title_ChangeLevel", VK_F1);
	}

	// 메뉴추가 
	m_vecMenu.reserve(static_cast<int>(EMENU_TYPE::MAX));
	for (size_t i = 0; i < static_cast<size_t>(EMENU_TYPE::MAX); i++)
	{
		m_vecMenu.push_back(static_cast<EMENU_TYPE>(i));
	}
	m_CurMenu = m_vecMenu[m_CurIdx];
}

void CTitleManager::Update(float _DeltaTime)
{
	if (false == m_Arrive)
	{
		FenceRenderMove(_DeltaTime);
	}

	if (true == m_Arrive)
	{
		MenuUpdate(_DeltaTime);
	}
}

void CTitleManager::Render(float _DeltaTime)
{
}

void CTitleManager::MenuUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("TitleMenu_Select") ||
		true == GameEngineInput::IsDown("TitleMenu_Select_Enter"))
	{
		switch (m_CurMenu)
		{
		case EMENU_TYPE::NEWGAME:
			GameEngineCore::ChangeLevel("TutorialLevel");
			break;
		case EMENU_TYPE::SETTING:
			break;
		case EMENU_TYPE::EXIT:
			break;
		}
	}

	if (true == GameEngineInput::IsDown("TitleMenu_Up") ||
		true == GameEngineInput::IsDown("TitleMenu_Up_2"))
	{
		// 현재 메뉴가 뉴게임으로 선택되어 있을 경우 return 
		if (EMENU_TYPE::NEWGAME == m_CurMenu)	
		{
			return;
		}
		else
		{
			--m_CurIdx;
			m_CurMenu = m_vecMenu[m_CurIdx];
		}
	}

	if (true == GameEngineInput::IsDown("TitleMenu_Down") ||
		true == GameEngineInput::IsDown("TitleMenu_Down_2"))
	{
		if (EMENU_TYPE::EXIT == m_CurMenu)
		{
			return;
		}

		else
		{
			++m_CurIdx;
			m_CurMenu = m_vecMenu[m_CurIdx];
		}
	}
}

void CTitleManager::FenceRenderMove(float _DeltaTime)
{
	float4 StartPoint = { 0 , 350 };
	float4 renderpos = m_FenceRender->GetTransform()->GetLocalPosition();
	if (renderpos.y >= StartPoint.y)
	{
		m_FenceRender->GetTransform()->SetLocalPosition(StartPoint);
		if (false == m_Arrive)
		{
			m_Arrive = true;
		}
		return;
	}

	float4 movepos = renderpos.LerpClamp(renderpos, StartPoint, 1.0f);
	movepos.Normalize();
	m_FenceRender->GetTransform()->AddLocalPosition(movepos * 210 * _DeltaTime);
}

void CTitleManager::CreateRender()
{
	float4 screensize = GameEngineWindow::GetScreenSize();
	
	// ZERTextRender 
	m_ZERRender = CreateComponent<GameEngineSpriteRenderer>();
	m_ZERRender->SetPipeLine("2DTexture");
	m_ZERRender->SetTexture("spr_titlegraphic_big_1.png");
	m_ZERRender->GetTransform()->SetLocalScale(float4{ 350.0f , 200.0f });
	m_ZERRender->GetTransform()->SetLocalPosition(float4{ -55.0f , 30.0f });

	// KatanaTexRender 
	m_KatanaRender = CreateComponent<GameEngineSpriteRenderer>();
	m_KatanaRender->SetPipeLine("2DTexture");
	m_KatanaRender->SetTexture("spr_titlegraphic_big2_0.png");
	m_KatanaRender->GetTransform()->SetLocalScale(float4{ 350.0f , 170.0f });
	m_KatanaRender->GetTransform()->SetLocalPosition(float4{ 0.0f , 100.0f });
	
	// OTexRender
	m_ORender = CreateComponent<GameEngineSpriteRenderer>();
	m_ORender->SetPipeLine("2DTexture");
	m_ORender->SetTexture("spr_titlegraphic_big_2.png");
	m_ORender->GetTransform()->SetLocalScale(float4{ 130.0f , 200.0f });
	m_ORender->GetTransform()->SetLocalPosition(float4{ 160.0f , 30.0f });
	
	// FenceRender 
	m_FenceRender = CreateComponent<GameEngineSpriteRenderer>();
	m_FenceRender->SetPipeLine("2DTexture");
	m_FenceRender->SetTexture("spr_title_fence_0.png");
	m_FenceRender->GetTransform()->SetLocalScale({ screensize.x , screensize.y * 2.0f });

	// PlantsRender
	m_PlantsRender = CreateComponent<GameEngineSpriteRenderer>();
	m_PlantsRender->SetPipeLine("2DTexture");
	m_PlantsRender->SetTexture("spr_title_plants_0.png");
	m_PlantsRender->GetTransform()->SetLocalScale({ screensize.x , screensize.y / 1.5f});

	float plantsrenderYmove = -(screensize.y / 6.0f);
	m_PlantsRender->GetTransform()->SetLocalPosition({ 0 , plantsrenderYmove });

	m_TranslucentBoxRender = CreateComponent<GameEngineSpriteRenderer>();
	m_TranslucentBoxRender->SetPipeLine("2DTexture");
	m_TranslucentBoxRender->SetTexture("background_black.png");
	m_TranslucentBoxRender->GetTransform()->SetLocalScale({ screensize.x / 2.5f , screensize.y / 4.0f });

	// 임시위치 
	m_TranslucentBoxRender->GetTransform()->SetLocalPosition({ 0 , -210.0f });

	m_NewGameTextRender = CreateComponent<GameEngineSpriteRenderer>();
	m_NewGameTextRender->SetPipeLine("2DTexture");
	m_NewGameTextRender->SetTexture("newgame_text.png");
	m_NewGameTextRender->GetTransform()->SetLocalScale({ 150 , 25 });
	m_NewGameTextRender->GetTransform()->SetLocalPosition(m_TextRenderOriginPos);

	m_SettingTextRender = CreateComponent<GameEngineSpriteRenderer>();
	m_SettingTextRender->SetPipeLine("2DTexture");
	m_SettingTextRender->SetTexture("setting_text.png");
	m_SettingTextRender->GetTransform()->SetLocalScale({ 50 , 25 });
	m_SettingTextRender->GetTransform()->SetLocalPosition(m_TextRenderOriginPos + float4 { 0, -50});

	m_ExitTextRender = CreateComponent<GameEngineSpriteRenderer>();
	m_ExitTextRender->SetPipeLine("2DTexture");
	m_ExitTextRender->SetTexture("exit_text.png");
	m_ExitTextRender->GetTransform()->SetLocalScale({ 50 , 27 });
	m_ExitTextRender->GetTransform()->SetLocalPosition(m_TextRenderOriginPos + float4 { 0, -100});

	m_TransparencyBoxRender = CreateComponent<GameEngineSpriteRenderer>();
	m_TransparencyBoxRender->SetPipeLine("2DTexture");
	m_TransparencyBoxRender->SetTexture("exit_text.png");
	m_TransparencyBoxRender->GetTransform()->SetLocalScale({500, 30});
	// m_TransparencyBoxRender->GetTransform()->SetLocalPosition(m_TextRenderOriginPos + float4{ 0,0 });
}
