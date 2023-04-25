#include "PrecompileHeader.h"
#include "CTitleUIManager.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


CTitleUIManager::CTitleUIManager()
{
}

CTitleUIManager::~CTitleUIManager()
{
}

void CTitleUIManager::Start()
{
	if (false == GameEngineInput::IsKey("TitleMenu_Up"))
	{
		GameEngineInput::CreateKey("TitleMenu_Up", 'w');
		GameEngineInput::CreateKey("TitleMenu_Down", 's');
		GameEngineInput::CreateKey("TitleMenu_Select", VK_SPACE);
	}
}

void CTitleUIManager::Update(float _DeltaTime)
{
	// 메뉴선택시 
	if (true == GameEngineInput::IsDown("TitleMenu_Select"))
	{
		int a = 0; 
	}


	float4 StartPoint = { 0 , 350 };
	float4 renderpos = m_FenceRender->GetTransform()->GetLocalPosition();
	if (renderpos.y >= StartPoint.y)
	{
		m_FenceRender->GetTransform()->SetLocalPosition(StartPoint);
		return;
	}

	float4 movepos = renderpos.LerpClamp(renderpos, StartPoint, 1.0f);
	movepos.Normalize();
	m_FenceRender->GetTransform()->AddLocalPosition(movepos * 120 * _DeltaTime);
}

void CTitleUIManager::Render(float _DeltaTime)
{
}

void CTitleUIManager::CreateRender()
{
	float4 screensize = GameEngineWindow::GetScreenSize();

	m_KatanaRender = CreateComponent<GameEngineSpriteRenderer>();
	m_KatanaRender->SetPipeLine("2DTexture");
	m_KatanaRender->GetShaderResHelper().SetTexture("DiffuseTex", "spr_titlegraphic_big2_0.png");
	m_KatanaRender->GetTransform()->SetLocalScale(float4{ 400.0f , 200.0f });
	
	/*m_ZERRender = CreateComponent<GameEngineSpriteRenderer>();
	m_ZERRender->SetPipeLine("2DTexture");
	m_ZERRender->GetShaderResHelper().SetTexture("DiffuseTex", "spr_titlegraphic_big2_0.png");
	m_ZERRender->GetTransform()->SetLocalScale(float4{ 400.0f , 200.0f });*/
	//m_ORender = CreateComponent<GameEngineSpriteRenderer>();
	m_FenceRender = CreateComponent<GameEngineSpriteRenderer>();
	m_FenceRender->SetPipeLine("2DTexture");
	m_FenceRender->GetShaderResHelper().SetTexture("DiffuseTex", "spr_title_fence_0.png");
	m_FenceRender->GetTransform()->SetLocalScale({ screensize.x , screensize.y * 2.0f });
	//m_PlantsRender = CreateComponent<GameEngineSpriteRenderer>();
}
