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
#include "PlayManager.h"
#include "Battery.h"
#include "Cursor.h"
#include "Hud.h"
#include "CameraMovement.h"
#include "Timer.h"
#include "Inven.h"

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

// 나머지는 레벨체인지스타트에서 ㅇㅇ 
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

	PlayManager::MainManager->CameraSetting();

	// 플레이어 위치세팅
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->SetLocalPosition(float4{ -538, -252 });

	// HUD
	CreateActor<Hud>(static_cast<int>(RenderOrder::BASEUI), "Hud");

	// 플레이어 배터리 
	CreateActor<Battery>(static_cast<int>(RenderOrder::BASEUI), "Battery");

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// 카메라
	CreateActor<CameraMovement>(static_cast<int>(RenderOrder::CAMERA), "CameraMovement");

	// 타이머
	CreateActor<Timer>(static_cast<int>(RenderOrder::BASEUI), "Timer");

	// 인벤
	CreateActor<Inven>(static_cast<int>(RenderOrder::BASEUI), "Inven");
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
