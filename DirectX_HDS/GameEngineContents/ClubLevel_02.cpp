#include "PrecompileHeader.h"
#include "ClubLevel_02.h"

#include <GameEnginePlatform/GameEngineInput.h>

// GUI ������ ���
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "StageEditer.h"
#include "Map.h"
#include "Player.h"
#include "PlayManager.h"
#include "Battery.h"
#include "Cursor.h"

ClubLevel_02::ClubLevel_02()
{
}

ClubLevel_02::~ClubLevel_02()
{
}

void ClubLevel_02::Start()
{
	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();

	// �ʿ��� Ű����
	if (false == GameEngineInput::IsKey("ClubLevel02_ChangeLevel_ClubLevel03"))
	{
		GameEngineInput::CreateKey("ClubLevel02_ChangeLevel_ClubLevel03", VK_F1);
		// GameEngineInput::CreateKey("ClubLevel02_ChangeLevel_ClubLevel01", VK_F2);
		GameEngineInput::CreateKey("ClubLevel02_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel02_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel02_ChangeMap", '2');
	}


	SetLevelType(LevelType::CLUBMAP2);

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();


	// ������ ���¸� �������ִµ� �ϴ� ������ �ٷ� PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_02::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel02_ChangeLevel_ClubLevel03"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_03");
		return;
	}

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_02::LevelChangeStart()
{
	// �ʿ��ϴٸ�, GUI On <-- Core���� �ʱ�ȭ 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	m_GUI->On();

	PlayManager::MainManager->CameraSetting();

	// �÷��̾� ��ġ����
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->SetLocalPosition(float4{ -900, -511 });

	// �÷��̾� ���͸� 
	CreateActor<Battery>(static_cast<int>(RenderOrder::BASEUI), "Battery");

	// Ŀ�� 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");
}

void ClubLevel_02::LevelChangeEnd()
{
	// ������ ����� �� , �����·� ����
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_02::ResourcesLoad()
{
}

void ClubLevel_02::ActorLoad()
{
	m_Map = CreateActor<Map>(-10);
	m_Map->GetRender()->SetScaleToTexture("ClubMap_02.png");

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("���� �÷��̾ nullptr �Դϴ�.");
		return;
	}
}

void ClubLevel_02::DebugUpdate()
{
}
