#include "PrecompileHeader.h"
#include "ClubLevel_02.h"
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

#include "StageEditer.h"
#include "CameraSetter.h"
#include "PlaySupporter.h"
#include "Player.h"
#include "Map.h"
#include "Battery.h"
#include "Cursor.h"
#include "Hud.h"
#include "Inven.h"
#include "Timer.h"
#include "Monster_Grunt.h"
#include "Laser.h"
#include "FanBlade.h"

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

	SetLevelType(LevelType::CLUBMAP2);

	// �ʿ��� ���ҽ� �ε�
	ResourcesLoad();
	// ���� �ε� 
	ActorLoad();

	SetState(BaseLevel::LevelState::WAIT);
}

void ClubLevel_02::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_02::LevelChangeStart()
{
	GUISetting();

	// �������ʿ��� ���ʹ� ���� push 
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// �÷��̾� ��ġ����
	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 InitPos = { -900, -511 };
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
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_02.png");


}

void ClubLevel_02::CreateObjAndInit()
{
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -224.0f , -137.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -54.0f , -137.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Laser> NewLaser = CreateActor<Laser>(static_cast<int>(RenderOrder::LASER), "Laser");
		float4 InitPos = float4{ 137.0f, 91.0f };
		ActorInit(NewLaser, InitPos);
	}
	{
		std::shared_ptr<FanBlade> NewFanBlade = CreateActor<FanBlade>(static_cast<int>(RenderOrder::FANBLADE), "FanBlade");
		float4 InitPos = float4{ 634.0f, 144.0f };
		ActorInit(NewFanBlade, InitPos);
	}

}

void ClubLevel_02::KeyUpdate()
{
	if (true == GameEngineInput::IsDown("ClubLevel02_ChangeLevel_ClubLevel03"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_03");
		return;
	}
}

void ClubLevel_02::CreateKey()
{
	// �ʿ��� Ű����
	if (false == GameEngineInput::IsKey("ClubLevel02_ChangeLevel_ClubLevel03"))
	{
		GameEngineInput::CreateKey("ClubLevel02_ChangeLevel_ClubLevel03", VK_F1);
		// GameEngineInput::CreateKey("ClubLevel02_ChangeLevel_ClubLevel01", VK_F2);
		GameEngineInput::CreateKey("ClubLevel02_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel02_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel02_ChangeMap", '2');
	}
}

void ClubLevel_02::GUISetting()
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
