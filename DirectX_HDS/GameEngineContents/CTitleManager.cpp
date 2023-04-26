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
		GameEngineInput::CreateKey("TitleMenu_Up", 'w');
		GameEngineInput::CreateKey("TitleMenu_Down", 's');
		GameEngineInput::CreateKey("TitleMenu_Select", VK_SPACE);
		GameEngineInput::CreateKey("ChangeLevel_Test", VK_F1);
	}
}

void CTitleManager::Update(float _DeltaTime)
{
	// 임시적용
	if (true == GameEngineInput::IsDown("ChangeLevel_Test"))
	{
		GameEngineCore::ChangeLevel("CTestLevel");
		return;
	}

	FenceRenderMove(_DeltaTime);
}

void CTitleManager::Render(float _DeltaTime)
{
}

void CTitleManager::FenceRenderMove(float _DeltaTime)
{
	float4 StartPoint = { 0 , 350 };
	float4 renderpos = m_FenceRender->GetTransform()->GetLocalPosition();
	if (renderpos.y >= StartPoint.y)
	{
		m_FenceRender->GetTransform()->SetLocalPosition(StartPoint);
		return;
	}

	float4 movepos = renderpos.LerpClamp(renderpos, StartPoint, 1.0f);
	movepos.Normalize();
	m_FenceRender->GetTransform()->AddLocalPosition(movepos * 140 * _DeltaTime);
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
	m_TranslucentBoxRender->GetTransform()->SetLocalScale({ screensize.x / 2.5f , screensize.y / 3.0f });

	// 임시위치 
	m_TranslucentBoxRender->GetTransform()->SetLocalPosition({ 0 , -210.0f });
	
}
