#include "PrecompileHeader.h"
#include "ClubLevel_01.h"

#include <GameEnginePlatform/GameEngineInput.h>

// GUI 생성시 사용
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

#include "PlaySupporter.h"
#include "Player.h"
#include "CameraSetter.h"
#include "StageEditer.h"
#include "Map.h"
#include "Battery.h"
#include "Cursor.h"
#include "Hud.h"
#include "Timer.h"
#include "Inven.h"
#include "Monster_Gangster.h"
#include "Monster_Grunt.h"

ClubLevel_01::ClubLevel_01()
{
}

ClubLevel_01::~ClubLevel_01()
{
}

void ClubLevel_01::Start()
{
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();

	// 기본 맵이름은 0번으로. 0번부터 시작할거니까 
	SetLevelType(LevelType::CLUBMAP1);

	// 필요한 리소스 로드
	ResourcesLoad();

	// 액터 로드 
	ActorLoad();

	SetState(BaseLevel::LevelState::WAIT);
}

void ClubLevel_01::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_01::LevelChangeStart()
{
	GUISetting();

	// 리셋이필요한 액터는 전부 push 
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// 플레이어 위치세팅
	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 InitPos = { -538, -252 };
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

void ClubLevel_01::LevelChangeEnd()
{
	// 레벨이 종료될 때 , 대기상태로 변경
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_01::ResourcesLoad()
{
}

void ClubLevel_01::ActorLoad()
{
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_01.png");
}

void ClubLevel_01::CreateObjAndInit()
{
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { -228.0f , 34.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -348.0f , 34.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 493.0f , 32.0f };
		ActorInit(Monster, InitPos);
	}
}

void ClubLevel_01::KeyUpdate()
{
	if (true == GameEngineInput::IsDown("ClubLevel01_ChangeLevel_ClubLevel02"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_02");
		return;
	}
}

void ClubLevel_01::CreateKey()
{
	if (false == GameEngineInput::IsKey("ClubLevel01_ChangeLevel_ClubLevel02"))
	{
		GameEngineInput::CreateKey("ClubLevel01_ChangeLevel_ClubLevel02", VK_F1);
		GameEngineInput::CreateKey("ClubLevel01_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel01_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel01_ChangeMap", '2');
	}
}

void ClubLevel_01::GUISetting()
{
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();
}