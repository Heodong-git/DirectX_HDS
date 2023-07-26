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
		// ������ ���� ������ ���Ŀ� ���� ���̰� 
		// ��� Ŭ���� ���¿����� �����Ǵϱ�
		BaseLevel* CurLevel = GetReturnCastLevel();
		LevelType CurLevelType = CurLevel->GetLevelType();

		// �ٷ� ü���������� �ϴ°� �ƴ϶� Ŭ���� ȭ�� ���͸� ��������
		// ���� �ð� �ڿ� ����ü������ �ϴ°ɷ� ���⼭ ���͸� ����� 
		// ���� ��ȭ���,���������� ����ٸ� �갡������ �׳༮�� ȣ��ǵ���. 
		// ����ü���� �ƴϰ�, ������ �����..
		
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
