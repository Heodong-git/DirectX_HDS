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
	}

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();
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
	}

	DebugUpdate();
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
	m_Map_Club01 = CreateActor<Map>(-10);
	m_Map_Club01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");
	//m_Map_01->GetRender()->SetAtlasConstantBuffer();

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
	// �ϴ� �ӽ� �ȼ��浹 ������� ���� ���� ����
	if (true == IsDebug())
	{
		m_Map_Club01->GetRender()->SetScaleToTexture("Club_0_ColMap.png");
	}

	else if (false == IsDebug())
	{
		m_Map_Club01->GetRender()->SetScaleToTexture("Club_0.png");
	}
}
