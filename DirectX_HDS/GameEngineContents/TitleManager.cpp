#include "PrecompileHeader.h"
#include "TitleManager.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BaseLevel.h"

TitleManager::TitleManager()
{
}

TitleManager::~TitleManager()
{
	
}

void TitleManager::Start()
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

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("sound");
		NewDir.Move("playlevel");

		// 모든 플레이레벨에서 사용할, 플레이어와 관련된 사운드가 아닌 사운드는 여기서 로드 
		GameEngineSound::Load(NewDir.GetPlusFileName("picksound.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("electricsound1.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("electricsound2.wav").GetFullPath());
	}

	// 메뉴추가 
	m_vecMenu.reserve(static_cast<int>(EMENU_TYPE::MAX));
	for (size_t i = 0; i < static_cast<size_t>(EMENU_TYPE::MAX); i++)
	{
		m_vecMenu.push_back(static_cast<EMENU_TYPE>(i));
	}
	m_CurMenu = m_vecMenu[m_CurIdx];
}

void TitleManager::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Title_ChangeLevel"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_00");
		return;
	}

	if (EMENU_TYPE::CHANGE == m_CurMenu)
	{
		m_BoxFlashingTime -= _DeltaTime;

		// 애니메이션 추가전임시 
		if (m_BoxFlashingTime >= 0.5f)
		{
			m_MenuSelectBoxRender->Off();
		}

		else if (m_BoxFlashingTime < 0.5f && m_BoxFlashingTime >= 0.4f)
		{
			m_MenuSelectBoxRender->On();
		}

		else if (m_BoxFlashingTime < 0.4f && m_BoxFlashingTime >= 0.3f)
		{
			m_MenuSelectBoxRender->Off();
		}
		
		else if (m_BoxFlashingTime < 0.3f && m_BoxFlashingTime >= 0.2f)
		{
			m_MenuSelectBoxRender->On();
		}

		else if (m_BoxFlashingTime < 0.2f && m_BoxFlashingTime >= 0.1f)
		{
			m_MenuSelectBoxRender->Off();
		}

		else
		{
			m_MenuSelectBoxRender->On();
		}

		if (m_BoxFlashingTime < 0.0f)
		{
			GameEngineCore::ChangeLevel("ClubLevel_00");
			m_CurMenu = EMENU_TYPE::NEWGAME;
			m_BoxFlashingTime = 0.0f; 
		}

	}
	// 현재 메뉴가 뉴게임인상태에서 스페이스바가 눌렸다면 
	if (BaseLevel::LevelState::PLAY == GetReturnCastLevel()->GetCurState())
	{
		MenuUpdate(_DeltaTime);
		BlinkRender();
		return;
	}

	// 할일을 모두 마치면 레벨을 PLAY 상태로 변경
	if (true == m_TextMoveArrive && true == m_BoxMoveArrive)
	{
		if (false == m_AllRenderArrive)
		{
			m_AllRenderArrive = true;
			GetReturnCastLevel()->SetState(BaseLevel::LevelState::PLAY);
			return;
		}
	}

	// 텍스트 이동
	if (false == m_TextMoveArrive)
	{
		TextMove(_DeltaTime);

		if (true == m_FenceArrive && true == m_KatanaArrive && true == m_ZERArrive && true == m_OArrive)
		{
			if (false == m_TextMoveArrive)
			{
				m_TextMoveArrive = true;
			}
		}
	}

	// 위쪽 텍스트의 이동이 완료되고, 투명박스 이동이 완료되지 않았을 경우, 무브 
	if (false == m_BoxMoveArrive && true == m_TextMoveArrive)
	{
		BoxRenderMove(_DeltaTime);
	}

	BlinkRender();
}

void TitleManager::Render(float _DeltaTime)
{
}

void TitleManager::MenuUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("TitleMenu_Select") ||
		true == GameEngineInput::IsDown("TitleMenu_Select_Enter"))
	{
		m_PickSound = GameEngineSound::Play("picksound.wav");
		switch (m_CurMenu)
		{
		case EMENU_TYPE::NEWGAME:
			m_CurMenu = EMENU_TYPE::CHANGE;
			// GameEngineCore::ChangeLevel("TutorialLevel");
			break;
		case EMENU_TYPE::SETTING:
			break;
		case EMENU_TYPE::EXIT:
			GameEngineWindow::AppOff();
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
			switch (m_CurMenu)
			{
			case EMENU_TYPE::SETTING:
				m_MenuSelectBoxRender->GetTransform()->SetLocalPosition(m_MenuStartPos);
				break;
			case EMENU_TYPE::EXIT:
				m_MenuSelectBoxRender->GetTransform()->SetLocalPosition(m_MenuMiddlePos);
				break;
			}

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
			switch (m_CurMenu)
			{
			case EMENU_TYPE::NEWGAME:
				m_MenuSelectBoxRender->GetTransform()->SetLocalPosition(m_MenuMiddlePos);
				break;
			case EMENU_TYPE::SETTING:
				m_MenuSelectBoxRender->GetTransform()->SetLocalPosition(m_MenuEndPos);
				break;
			}

			++m_CurIdx;
			m_CurMenu = m_vecMenu[m_CurIdx];
		}
	}
}

void TitleManager::FenceRenderMove(float _DeltaTime)
{
	float4 StartPoint = { 0 , 350 };
	float4 renderpos = m_FenceRender->GetTransform()->GetLocalPosition();
	if (renderpos.y >= StartPoint.y)
	{
		m_FenceRender->GetTransform()->SetLocalPosition(StartPoint);
		if (false == m_FenceArrive)
		{
			m_FenceArrive = true;
		}
		return;
	}

	float4 movepos = renderpos.LerpClamp(renderpos, StartPoint, 1.0f);
	movepos.Normalize();
	m_FenceRender->GetTransform()->AddLocalPosition(movepos * 360 * _DeltaTime);
}

void TitleManager::KatanaRenderMove(float _DeltaTime)
{
	float4 CurKatanaRenderPos = m_KatanaRender->GetTransform()->GetLocalPosition();
	// 지정위치를 넘어섰다면
	if (CurKatanaRenderPos.y >= m_KatanaRenderPos.y)
	{
		m_KatanaRender->GetTransform()->SetLocalPosition(m_KatanaRenderPos);
		if (false == m_KatanaArrive)
		{
			m_KatanaArrive = true;
		}

		return;
	}

	float4 movepos = CurKatanaRenderPos.LerpClamp(CurKatanaRenderPos, m_KatanaRenderPos, 1.0f);
	movepos.Normalize();
	m_KatanaRender->GetTransform()->AddLocalPosition(movepos * 150.0f * _DeltaTime);
}

void TitleManager::ZERRenderMove(float _DeltaTime)
{
	float4 RenderPos = m_ZERRender->GetTransform()->GetLocalPosition();
	if (RenderPos.y >= m_ZERRenderPos.y)
	{
		m_ZERRender->GetTransform()->SetLocalPosition(m_ZERRenderPos);
		if (false == m_ZERArrive)
		{
			m_ZERArrive = true;
		}

		return;
	}

	// 여기서 y축만 움직여야함 
	float4 movepos = RenderPos.LerpClamp(RenderPos, m_ZERRenderPos, 1.0f);
	movepos.x = 0.0f;
	movepos.Normalize();
	m_ZERRender->GetTransform()->AddLocalPosition(movepos * 150.0f * _DeltaTime);
}

void TitleManager::ORenderMove(float _DeltaTime)
{
	float4 RenderPos = m_ORender->GetTransform()->GetLocalPosition();
	if (RenderPos.y >= m_ORenderPos.y)
	{
		m_ORender->GetTransform()->SetLocalPosition(m_ORenderPos);
		if (false == m_OArrive)
		{
			m_OArrive = true;
		}

		return;
	}

	// 여기서 y축만 움직여야함 
	float4 movepos = RenderPos.LerpClamp(RenderPos, m_ORenderPos, 1.0f);
	movepos.x = 0.0f;
	movepos.Normalize();
	m_ORender->GetTransform()->AddLocalPosition(movepos * 150.0f * _DeltaTime);
}

void TitleManager::BoxRenderMove(float _DeltaTime)
{
	float4 RenderPos = m_TranslucentBoxRender->GetTransform()->GetLocalPosition();
	if (RenderPos.y >= m_TranslucentBoxRenderPos.y)
	{
		m_TranslucentBoxRender->GetTransform()->SetLocalPosition(m_TranslucentBoxRenderPos);
		if (false == m_BoxMoveArrive)
		{
			m_BoxMoveArrive = true;
			TextMenuOn();
		}

		return;
	}

	// 여기서 y축만 움직여야함 
	float4 movepos = RenderPos.LerpClamp(RenderPos, m_TranslucentBoxRenderPos, 1.0f);
	movepos.x = 0.0f;
	movepos.Normalize();
	m_TranslucentBoxRender->GetTransform()->AddLocalPosition(-movepos * 600.0f * _DeltaTime);
}

void TitleManager::TextMove(float _DeltaTime)
{
	if (false == m_FenceArrive)
	{
		FenceRenderMove(_DeltaTime);
	}

	if (false == m_KatanaArrive)
	{
		KatanaRenderMove(_DeltaTime);
	}

	if (false == m_ZERArrive)
	{
		ZERRenderMove(_DeltaTime);
	}

	if (false == m_OArrive)
	{
		ORenderMove(_DeltaTime);
	}
}

void TitleManager::TextMenuOn()
{
	m_NewGameTextRender->On();
	m_SettingTextRender->On();
	m_ExitTextRender->On();
	m_MenuSelectBoxRender->On();
}

void TitleManager::BlinkRender()
{
	// 그냥 간단하게. 
	int Random = GameEngineRandom::MainRandom.RandomInt(1, 600);
	if (Random == 1)
	{
		m_ElectricSound = GameEngineSound::Play("electricsound1.wav");
		m_ORender->Off();
	}
	else
	{
		
		m_ORender->On();
	}

	Random = GameEngineRandom::MainRandom.RandomInt(1, 600);
	if (Random == 1)
	{
		m_ElectricSound = GameEngineSound::Play("electricsound2.wav");
		m_ZERRender->Off();
	}
	else
	{
		m_ZERRender->On();
	}
}

void TitleManager::CreateRender()
{
	float4 screensize = GameEngineWindow::GetScreenSize();
	
	// ZERTextRender 
	m_ZERRender = CreateComponent<GameEngineSpriteRenderer>();
	m_ZERRender->SetTexture("spr_titlegraphic_big_1.png");
	m_ZERRender->GetTransform()->SetLocalScale(float4{ 350.0f , 200.0f });
	m_ZERRender->GetTransform()->SetLocalPosition(float4{ m_ZERRenderPos.x , m_ZERRenderPos.y - 150.0f });

	// KatanaTexRender 
	m_KatanaRender = CreateComponent<GameEngineSpriteRenderer>();
	m_KatanaRender->SetTexture("spr_titlegraphic_big2_0.png");
	m_KatanaRender->GetTransform()->SetLocalScale(float4{ 350.0f , 170.0f });
	m_KatanaRender->GetTransform()->SetLocalPosition(float4{ m_KatanaRenderPos.x , m_KatanaRenderPos.y - 150.0f });
	
	// OTexRender
	m_ORender = CreateComponent<GameEngineSpriteRenderer>();
	m_ORender->SetTexture("spr_titlegraphic_big_2.png");
	// 반투명텍스쳐사용시
	/*m_ORender->SetPipeLine("2DBlinkTexture");
	m_ORender->GetShaderResHelper().SetTexture("BlinkTex", "spr_titlegraphic_big_2.png");*/
	m_ORender->GetTransform()->SetLocalScale(float4{ 130.0f , 200.0f });
	m_ORender->GetTransform()->SetLocalPosition(float4 { m_ORenderPos.x, m_ORenderPos.y - 150.0f });
	

	m_FenceRender = CreateComponent<GameEngineSpriteRenderer>();
	m_FenceRender->SetTexture("spr_title_fence_0.png");
	m_FenceRender->GetTransform()->SetLocalScale({ screensize.x , screensize.y * 2.0f });

	m_PlantsRender = CreateComponent<GameEngineSpriteRenderer>();
	m_PlantsRender->GetTransform()->SetLocalScale({ screensize.x , screensize.y / 1.5f});

	float plantsrenderYmove = -(screensize.y / 6.0f);
	m_PlantsRender->GetTransform()->SetLocalPosition({ 0 , plantsrenderYmove });
	m_PlantsRender->CreateAnimation({ .AnimationName = "Plants_Anim", .SpriteName = "Plants_Anim", .Start = 0, .End = 11 ,
									  .FrameInter = 0.15f , .Loop = true});
	m_PlantsRender->ChangeAnimation("Plants_Anim");

	m_TranslucentBoxRender = CreateComponent<GameEngineSpriteRenderer>();
	m_TranslucentBoxRender->SetPipeLine("2DTranslucentTexture");
	m_TranslucentBoxRender->GetShaderResHelper().SetTexture("TranslucentTex", "background_black.png");
	m_TranslucentBoxRender->SetAtlasConstantBuffer();
	m_TranslucentBoxRender->SetColorConstantBuffer();
	m_TranslucentBoxRender->GetTransform()->SetLocalScale({ screensize.x / 2.5f , screensize.y / 4.0f });
	m_TranslucentBoxRender->GetTransform()->SetLocalPosition(float4{ m_TranslucentBoxRenderPos.x, m_TranslucentBoxRenderPos.y - 270.0f });

	m_NewGameTextRender = CreateComponent<GameEngineSpriteRenderer>();
	m_NewGameTextRender->SetTexture("newgame_text.png");
	m_NewGameTextRender->GetTransform()->SetLocalScale({ 150 , 25 });
	m_NewGameTextRender->GetTransform()->SetLocalPosition(m_TextRenderOriginPos);
	m_NewGameTextRender->Off();

	m_SettingTextRender = CreateComponent<GameEngineSpriteRenderer>();
	m_SettingTextRender->SetTexture("setting_text.png");
	m_SettingTextRender->GetTransform()->SetLocalScale({ 50 , 25 });
	m_SettingTextRender->GetTransform()->SetLocalPosition(m_TextRenderOriginPos + float4 { 0, -50});
	m_SettingTextRender->Off();

	m_ExitTextRender = CreateComponent<GameEngineSpriteRenderer>();
	m_ExitTextRender->SetTexture("exit_text.png");
	m_ExitTextRender->GetTransform()->SetLocalScale({ 50 , 27 });
	m_ExitTextRender->GetTransform()->SetLocalPosition(m_TextRenderOriginPos + float4 { 0, -100});
	m_ExitTextRender->Off();

	m_MenuSelectBoxRender = CreateComponent<GameEngineSpriteRenderer>();
	m_MenuSelectBoxRender->SetTexture("menu_white_bar.png");
	m_MenuSelectBoxRender->ColorOptionValue.MulColor.a = 0.2f;
	m_MenuSelectBoxRender->GetTransform()->SetLocalScale({450, 30});
	m_MenuSelectBoxRender->GetTransform()->SetLocalPosition(float4 { 0 , -160});
	m_MenuSelectBoxRender->Off();

	// 새게임 . -160
	// 설정 . -210 
	// 종료 . -260
}
