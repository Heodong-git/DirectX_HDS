#include "PrecompileHeader.h"
#include "YouCanDoThis.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseLevel.h"

YouCanDoThis::YouCanDoThis()
{
}

YouCanDoThis::~YouCanDoThis()
{
}

void YouCanDoThis::Start()
{
	ComponentSetting();
}

void YouCanDoThis::Update(float _DeltaTime)
{
	if (0.0f >= m_OriginLiveTime)
	{
		// 죽으면 현재 레벨이 뭐냐에 따라서 보이게 
		// 얘는 클리어 상태에서만 생성되니까
		BaseLevel* CurLevel = GetReturnCastLevel();
		LevelType CurLevelType = CurLevel->GetLevelType();

		// 바로 체인지레벨을 하는게 아니라 클리어 화면 액터를 먼저띄우고
		// 일정 시간 뒤에 레벨체인지를 하는걸로 여기서 액터를 만들어 
		// 이제 녹화재생,역재생기능이 생긴다면 얘가죽으면 그녀석이 호출되도록. 
		// 레벨체인지 아니고, 정방향 재생을..
		
		// CurLevel->SetState(BaseLevel::LevelState::RECORDING_PROGRESS);
		
		CurLevel->SetState(BaseLevel::LevelState::RECORDING_PROGRESS_FORWARD);
		this->Death();
		return;


		switch (CurLevelType)
		{
		case LevelType::CLUBMAP0:
			GameEngineCore::ChangeLevel("ClubLevel_01");
			break;
		case LevelType::CLUBMAP1:
			GameEngineCore::ChangeLevel("ClubLevel_02");
			break;
		case LevelType::CLUBMAP2:
			GameEngineCore::ChangeLevel("ClubLevel_03");
			break;
		case LevelType::CLUBMAP3:
			GameEngineCore::ChangeLevel("ClubLevel_04");
			break;
		case LevelType::CLUBMAP4:
			GameEngineCore::ChangeLevel("ClubLevel_Boss");
			break;
		}

		return;
	}

	float OriginDeltaTime = GameEngineTime::GlobalTime.GetDeltaTime();
	m_OriginLiveTime -= OriginDeltaTime;

	if (1.0f > m_MainRender->ColorOptionValue.MulColor.a)
	{
		m_MainRender->ColorOptionValue.MulColor.a += _DeltaTime;
	}
}

void YouCanDoThis::Render(float _DeltaTime)
{
}

void YouCanDoThis::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	m_MainRender->SetTexture("youcandothis.png");
	m_MainRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	m_MainRender->ColorOptionValue.MulColor.a = 0.0f;
}
