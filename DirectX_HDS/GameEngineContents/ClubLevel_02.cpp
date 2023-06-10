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
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();

	SetLevelType(LevelType::CLUBMAP2);

	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
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

	// 리셋이필요한 액터는 전부 push 
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// 플레이어 위치세팅
	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 InitPos = { -900, -511 };
	ActorInit(NewPlayer, InitPos);

	// UI 
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	// 서포터, 커서
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	CreateObjAndInit();

	// 레벨의 상태를 변경해주는데 일단 지금은 바로 PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_02::LevelChangeEnd()
{
	// 레벨이 종료될 때 , 대기상태로 변경
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
	// 필요한 키생성
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
	// 필요하다면, GUI On <-- Core에서 초기화 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();
}
