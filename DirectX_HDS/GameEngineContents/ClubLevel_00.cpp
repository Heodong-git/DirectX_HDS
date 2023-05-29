#include "PrecompileHeader.h"
#include "ClubLevel_00.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI 생성시 사용
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

// 컨텐츠
#include "CameraSetter.h"
#include "Cursor.h"
#include "Player.h"
#include "PlaySupporter.h"
#include "Monster_Gangster.h"
#include "Monster_Pomp.h"
#include "Monster_Grunt.h"
#include "StageEditer.h"
#include "Battery.h"
#include "Map.h"
#include "Inven.h"
#include "Timer.h"
#include "Hud.h"
#include "FadeEffect.h"
#include "IronDoor.h"

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

	// 기본 맵이름은 0번으로. 0번부터 시작할거니까 
	SetLevelType(LevelType::CLUBMAP0);

	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
	ActorLoad();

	// 카메라 이펙트 생성
	// 이런 꼴로 사용 
	// m_FadeEffect = GetLastTarget()->CreateEffect<FadeInOut_Effect>();
}

void ClubLevel_00::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ClubLevel_ChangeLevel_ClubLevel01"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_01");
		return;
	}


	// 업데이트의 경우 BaseLevel::LevelState::WAIT 가 PLAY 일때만 업데이트 하고 레벨이 필요한 함수를 호출하도록 할거
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
	CreateActor<CameraSetter>();
	CameraSetter::MainCamSetter->CameraSetting();

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

// 00 레벨에서만 스타트에서 
void ClubLevel_00::ActorLoad()
{
	// 맵 
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	
	// 플레이어
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	NewPlayer->GetTransform()->AddLocalPosition(PlayerSetPos);
	
	// HUD
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");

	// 플레이어 배터리 
	CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery");

	// 커서 
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// 타이머
	CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer");

	// 인벤
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	std::shared_ptr<Monster_Gangster> NewGangster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
	NewGangster->GetTransform()->SetLocalPosition({ 0.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });

	{
		std::shared_ptr<Monster_Pomp> NewPomp = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		NewPomp->GetTransform()->SetLocalPosition({ -202.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
	}
	{
		std::shared_ptr<Monster_Pomp> NewPomp = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		NewPomp->GetTransform()->SetLocalPosition({ 252.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
	}
	{
		std::shared_ptr<Monster_Grunt> NewGrunt = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		NewGrunt->GetTransform()->SetLocalPosition({ -474.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
	}
	{
		std::shared_ptr<Monster_Grunt> NewGrunt = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		NewGrunt->GetTransform()->SetLocalPosition({ 404.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
	}
	{
		std::shared_ptr<Monster_Grunt> NewGrunt = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		NewGrunt->GetTransform()->SetLocalPosition({ 524.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y });
	}

	std::shared_ptr<IronDoor> NewDoor = CreateActor<IronDoor>(static_cast<int>(RenderOrder::DOOR), "IronDoor");
	NewDoor->GetTransform()->SetLocalPosition({ -67.0f , Player::MainPlayer->GetTransform()->GetLocalPosition().y});
	// 플레이서포터
	CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter");
}

void ClubLevel_00::DebugUpdate()
{
}

void ClubLevel_00::LevelReset()
{
	// 플레이어
	Player::MainPlayer->GetTransform()->SetLocalPosition(PlayerSetPos);
	// 얘는 여기서 바꾸면 안돼 
	// 녹화된 장면을 전부 보여주고 바꾸거나 해야할듯? 
	Player::MainPlayer->ResetDir();
	Player::MainPlayer->ChangeState(PlayerState::IDLE);
	Player::MainPlayer->ResetSlowLimitTime();

	// 카메라위치초기화 
	GetMainCamera()->GetTransform()->SetLocalPosition(CameraSetter::MainCamSetter->m_CameraPivots[0]);

	// 레벨상태변경
	SetState(BaseLevel::LevelState::PLAY);

	// 타이머리셋 
	SetLimitTime();
}