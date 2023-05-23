#include "PrecompileHeader.h"
#include "ClubLevel_00.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI 생성시 사용
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

// 컨텐츠
#include "StageEditer.h"
#include "PlayManager.h"
#include "Player.h"
#include "Cursor.h"
#include "Battery.h"
#include "Map.h"

// 아직
#include "Inven.h"
#include "Timer.h"
#include "Hud.h"

ClubLevel_00::ClubLevel_00()
{
}

ClubLevel_00::~ClubLevel_00()
{
}

void ClubLevel_00::Start()
{
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();

	// 필요한 키생성
	// 전부 베이스레벨에 있으면 될거같은데 
	if (false == GameEngineInput::IsKey("ClubLevel_ChangeLevel_ClubBossLevel"))
	{
		GameEngineInput::CreateKey("ClubLevel_ChangeLevel_ClubLevel01", VK_F1);
		GameEngineInput::CreateKey("ClubLevel_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel_ChangeMap", '2');
	}

	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
	ActorLoad();

	// 기본 맵이름은 0번으로. 0번부터 시작할거니까 
	SetLevelType(LevelType::CLUBMAP0);
}

void ClubLevel_00::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel_ChangeLevel_ClubLevel01"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_01");
		return;
	}

	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_00::LevelChangeStart()
{
	//레벨체인지하면서 imgui 를 on 시킬때 포커스가 해제되는중
	//레벨 start 의 기본 인터페이스

	// 필요하다면, GUI On <-- Core에서 초기화 
	m_GUI = GameEngineGUI::FindGUIWindowConvert<StageEditer>("Debug_State");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window가 nullptr 입니다.");
		return;
	}
	
	m_GUI->On();

	// 필요한 액터 생성, 초기화(세팅)
	CreateActor<PlayManager>();
	PlayManager::MainManager->CameraSetting();

	// 레벨의 상태를 변경해주는데 일단 지금은 바로 PLAY 
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_00::LevelChangeEnd()
{
	// 레벨이 종료될 때 , 대기상태로 변경
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_00::ResourcesLoad()
{
	// 맵의 리소스로드 
	{
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Map");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
}

void ClubLevel_00::ActorLoad()
{
	// 맵 
	m_Map = CreateActor<Map>(-10);
	m_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	
	// 플레이어
	CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	Player::MainPlayer->GetTransform()->AddLocalPosition(float4{ -850 , -94 });

	// 플레이어 배터리 
	CreateActor<Battery>(static_cast<int>(RenderOrder::BASEUI), "Battery");

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");
}

void ClubLevel_00::DebugUpdate()
{

}


