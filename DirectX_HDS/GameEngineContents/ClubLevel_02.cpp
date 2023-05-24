#include "PrecompileHeader.h"
#include "ClubLevel_02.h"

#include <GameEnginePlatform/GameEngineInput.h>

// GUI 생성시 사용
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
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();

	// 필요한 키생성
	if (false == GameEngineInput::IsKey("ClubLevel02_ChangeLevel_ClubLevel03"))
	{
		GameEngineInput::CreateKey("ClubLevel02_ChangeLevel_ClubLevel03", VK_F1);
		// GameEngineInput::CreateKey("ClubLevel02_ChangeLevel_ClubLevel01", VK_F2);
		GameEngineInput::CreateKey("ClubLevel02_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel02_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel02_ChangeMap", '2');
	}


	SetLevelType(LevelType::CLUBMAP2);

	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
	ActorLoad();


	// 레벨의 상태를 변경해주는데 일단 지금은 바로 PLAY 
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
	// 필요하다면, GUI On <-- Core에서 초기화 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	m_GUI->On();

	PlayManager::MainManager->CameraSetting();

	// 플레이어 위치세팅
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->SetLocalPosition(float4{ -900, -511 });

	// 플레이어 배터리 
	CreateActor<Battery>(static_cast<int>(RenderOrder::BASEUI), "Battery");

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");
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
	m_Map = CreateActor<Map>(-10);
	m_Map->GetRender()->SetScaleToTexture("ClubMap_02.png");

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("현재 플레이어가 nullptr 입니다.");
		return;
	}
}

void ClubLevel_02::DebugUpdate()
{
}
