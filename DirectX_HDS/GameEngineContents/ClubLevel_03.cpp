#include "PrecompileHeader.h"
#include "ClubLevel_03.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PlaySupporter.h"
#include "StageEditer.h"
#include "Player.h"
#include "CameraSetter.h"
#include "Hud.h"
#include "Battery.h"
#include "Inven.h"
#include "Timer.h"
#include "Map.h"
#include "Cursor.h"

#include "Monster_Grunt.h"
#include "Monster_Gangster.h"
#include "Monster_Pomp.h"
#include "Partition.h"



ClubLevel_03::ClubLevel_03()
{
}

ClubLevel_03::~ClubLevel_03()
{
}

void ClubLevel_03::Start()
{
	// �ھ�� ó�� ���� �� ���� �ʱ�ȭ 
	BaseLevel::Start();

	SetLevelType(LevelType::CLUBMAP3);

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();

	SetState(BaseLevel::LevelState::WAIT);
}

void ClubLevel_03::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_03::LevelChangeStart()
{
	GUISetting();

	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// �÷��̾� ��ġ����
	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 InitPos = { -646.0f, 491.0f };
	ActorInit(NewPlayer, InitPos);

	// UI 
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	// ������, Ŀ��
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	CreateObjAndInit();

	// ������ ���¸� �������ִµ� �ϴ� ������ �ٷ� PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_03::LevelChangeEnd()
{
	// ������ ����� �� , �����·� ����
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_03::ResourcesLoad()
{
}

void ClubLevel_03::ActorLoad()
{
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_03.png");
}

void ClubLevel_03::KeyUpdate()
{
	if (true == GameEngineInput::IsDown("ClubLevel03_ChangeLevel_ClubLevel04"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_04");
		return;
	}
}

void ClubLevel_03::CreateKey()
{
	// �ʿ��� Ű����
	if (false == GameEngineInput::IsKey("ClubLevel03_ChangeLevel_ClubLevel04"))
	{
		GameEngineInput::CreateKey("ClubLevel03_ChangeLevel_ClubLevel04", VK_F1);
		GameEngineInput::CreateKey("ClubLevel03_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel03_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel03_ChangeMap", '2');
	}
}

void ClubLevel_03::CreateObjAndInit()
{
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -424.0f, 176.0f};
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -174.0f , 176.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { 360.20f, 176.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { -247.71f, -170.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Pomp> Monster = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		float4 InitPos = { 164.2f, -170.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { 365.5f , -170.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 150.8f , -516.2f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { 329.61f, -516.2f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -709.0f , 173.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 573.0f , 173.0f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -640.0f , -172.2f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 673.0f  , -172.2f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { -710.0f  , -518.93f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 743.0f  , -518.93f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 36.0f  , -172.2f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 36.0f  , -518.2f };
		ActorInit(PartitionObj, InitPos);
	}
	{
		std::shared_ptr<Partition> PartitionObj = CreateActor<Partition>(static_cast<int>(RenderOrder::DEBUG), "Partition");
		float4 InitPos = { 36.0f  , 171.2f };
		ActorInit(PartitionObj, InitPos);
	}
}

void ClubLevel_03::GUISetting()
{
	// �ʿ��ϴٸ�, GUI On <-- Core���� �ʱ�ȭ 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	m_GUI->On();
}
