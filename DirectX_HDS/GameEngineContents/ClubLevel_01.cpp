#include "PrecompileHeader.h"
#include "ClubLevel_01.h"

#include <GameEnginePlatform/GameEngineInput.h>

// GUI 생성시 사용
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "StageEditer.h"
#include "Map.h"
#include "Player.h"
#include "CameraSetter.h"
#include "Battery.h"
#include "Cursor.h"
#include "Hud.h"
#include "PlaySupporter.h"
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

	// 필요한 키생성
	if (false == GameEngineInput::IsKey("ClubLevel01_ChangeLevel_ClubLevel02"))
	{
		GameEngineInput::CreateKey("ClubLevel01_ChangeLevel_ClubLevel02", VK_F1);
		//GameEngineInput::CreateKey("ClubLevel01_ChangeLevel_ClubLevel00", VK_F2);
		GameEngineInput::CreateKey("ClubLevel01_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel01_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel01_ChangeMap", '2');
	}

	// 기본 맵이름은 0번으로. 0번부터 시작할거니까 
	SetLevelType(LevelType::CLUBMAP1);

	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
	ActorLoad();

	// 레벨의 상태를 변경해주는데 일단 지금은 바로 PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_01::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel01_ChangeLevel_ClubLevel02"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_02");
		return;
	}

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_01::LevelChangeStart()
{
	// 필요하다면, GUI On <-- Core에서 초기화 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();

	// 리셋이필요한 액터는 전부 push 
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// 플레이어 위치세팅
	Push_ResetActor(CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	Player::MainPlayer->GetTransform()->SetLocalPosition(m_PlayerSetPos);

	// HUD
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");

	// 플레이어 배터리 
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// 플레이서포터
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));

	// 타이머
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));

	// 인벤
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	{
		std::shared_ptr<Monster_Gangster> NewMonster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = { -228.0f , 34.0f };
		NewMonster->GetTransform()->SetLocalPosition(InitPos);
		NewMonster->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewMonster);
	}
	{
		std::shared_ptr<Monster_Grunt> NewMonster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -348.0f , 34.0f };
		NewMonster->GetTransform()->SetLocalPosition(InitPos);
		NewMonster->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewMonster);
	}
	{
		std::shared_ptr<Monster_Grunt> NewMonster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 493.0f , 32.0f };
		NewMonster->GetTransform()->SetLocalPosition(InitPos);
		NewMonster->SetInitPos(InitPos);
		PlusMonsterCount();
		Push_ResetActor(NewMonster);
	}
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
	m_Map = CreateActor<Map>(-10);
	m_Map->GetRender()->SetScaleToTexture("ClubMap_01.png");

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("현재 플레이어가 nullptr 입니다.");
		return;
	}
}

void ClubLevel_01::DebugUpdate()
{
}