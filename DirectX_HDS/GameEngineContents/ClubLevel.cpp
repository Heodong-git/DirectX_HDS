#include "PrecompileHeader.h"
#include "ClubLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI ������ ���
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

// ������
#include "StageEditer.h"
#include "PlayManager.h"
#include "Player.h"
#include "Cursor.h"
#include "Battery.h"
#include "Map.h"

// ����
#include "Inven.h"
#include "Timer.h"
#include "Hud.h"

ClubLevel::ClubLevel()
{
}

ClubLevel::~ClubLevel()
{
}

void ClubLevel::Start()
{
	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();

	// �ʿ��� Ű����
	if (false == GameEngineInput::IsKey("ClubLevel_ChangeLevel_ClubBossLevel"))
	{
		GameEngineInput::CreateKey("ClubLevel_ChangeLevel_ClubBossLevel", VK_F1);
		GameEngineInput::CreateKey("ClubLevel_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel_ChangeMap", '2');
	}

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();

	// �⺻ ���̸��� 0������. 0������ �����ҰŴϱ� 
	SetMapName(MapName::CLUBMAP0);
}

void ClubLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel_ChangeLevel_ClubBossLevel"))
	{
		GameEngineCore::ChangeLevel("ClubBossLevel");
		return;
	}

	if (true == GameEngineInput::IsDown("ClubLevel_DebugSwitch"))
	{
		DebugSwitch();

		if (true == IsDebug())
		{
			ChangeColMap();
			return;
		}

		if (false == IsDebug())
		{
			ChangeMap();
			return;
		}
	}

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel::LevelChangeStart()
{
	//����ü�����ϸ鼭 imgui �� on ��ų�� ��Ŀ���� �����Ǵ���
	//���� start �� �⺻ �������̽�

	// �ʿ��ϴٸ�, GUI On <-- Core���� �ʱ�ȭ 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	m_GUI->On();

	// �ʿ��� ���� ����, �ʱ�ȭ(����)
	CreateActor<PlayManager>();
	PlayManager::MainManager->SetLevelType(PlayManager::LevelName::CLUB);
	PlayManager::MainManager->CameraSetting();

	// ������ ���¸� �������ִµ� �ϴ� ������ �ٷ� PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel::LevelChangeEnd()
{
	// ������ ����� �� , �����·� ����
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel::ResourcesLoad()
{
	// �������� �ʿ��� ���ҽ� �ε�
	// ���Ͱ� �ڱ��ڽ��� ���ҽ��� �ε��ϵ��� �ϴ���.
}

void ClubLevel::ActorLoad()
{
	// �� 
	m_Club_Map = CreateActor<Map>(-10);
	m_Club_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	
	// �÷��̾�
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->AddLocalPosition(float4{ -850 , -94 });

	// �÷��̾� ���͸� 
	CreateActor<Battery>(static_cast<int>(RenderOrder::BASEUI), "Battery");

	// Ŀ�� 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");
}

void ClubLevel::DebugUpdate()
{

}

void ClubLevel::ChangeMap()
{
	if (nullptr == m_Club_Map)
	{
		MsgAssert("���� ���� nullptr �Դϴ�.");
		return;
	}

	switch (m_CurMapName)
	{
	case MapName::CLUBMAP0:
		m_Club_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");
		break;
	case MapName::CLUBMAP1:
		m_Club_Map->GetRender()->SetScaleToTexture("ClubMap_01.png");
		break;
	case MapName::CLUBMAP2:
		m_Club_Map->GetRender()->SetScaleToTexture("ClubMap_02.png");
		break;
	case MapName::CLUBMAP3:
		m_Club_Map->GetRender()->SetScaleToTexture("ClubMap_03.png");
		break;
	case MapName::CLUBMAP4:
		m_Club_Map->GetRender()->SetScaleToTexture("ClubMap_04.png");
		break;
	case MapName::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. �̸��� �����ϼ���.");
		return;
	}
	break;
	}
}

void ClubLevel::ChangeColMap()
{
	if (nullptr == m_Club_Map)
	{
		MsgAssert("���� ���� nullptr �Դϴ�.");
		return;
	}

	switch (m_CurMapName)
	{
	case MapName::CLUBMAP0:
		m_Club_Map->GetRender()->SetScaleToTexture("Club_ColMap_00.png");
		break;
	case MapName::CLUBMAP1:
		m_Club_Map->GetRender()->SetScaleToTexture("Club_ColMap_01.png");
		break;
	case MapName::CLUBMAP2:
		m_Club_Map->GetRender()->SetScaleToTexture("Club_ColMap_02.png");
		break;
	case MapName::CLUBMAP3:
		m_Club_Map->GetRender()->SetScaleToTexture("Club_ColMap_03.png");
		break;
	case MapName::CLUBMAP4:
		m_Club_Map->GetRender()->SetScaleToTexture("Club_ColMap_04.png");
		break;
	case MapName::NONE:
	{
		MsgAssert("���� ���� �̸��� NONE �Դϴ�. �̸��� �����ϼ���.");
		return;
	}
		break;
	}
}
