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
		this->Death();

		// ������ ���� ������ ���Ŀ� ���� ���̰� 
		// ��� Ŭ���� ���¿����� �����Ǵϱ�
		BaseLevel* CurLevel = GetReturnCastLevel();
		LevelType CurLevelType = CurLevel->GetLevelType();

		// �ٷ� ü���������� �ϴ°� �ƴ϶� Ŭ���� ȭ�� ���͸� ��������
		// ���� �ð� �ڿ� ����ü������ �ϴ°ɷ� ���⼭ ���͸� ����� 
		// ���� ��ȭ���,���������� ����ٸ� �갡������ �׳༮�� ȣ��ǵ���. 
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
			GameEngineCore::ChangeLevel("ClubLevel_05");
			break;
		}
	}

	float OriginDeltaTime = GameEngineTime::GlobalTime.GetDeltaTime();
	m_OriginLiveTime -= OriginDeltaTime;
}

void YouCanDoThis::Render(float _DeltaTime)
{
}

void YouCanDoThis::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	m_MainRender->SetTexture("youcandothis.png");
	m_MainRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
}
