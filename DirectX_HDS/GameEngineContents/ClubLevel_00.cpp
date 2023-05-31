#include "PrecompileHeader.h"
#include "ClubLevel_00.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// GUI 생성시
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineCore.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

// 컨텐츠
#include "CameraSetter.h"
#include "PlaySupporter.h"
#include "Player.h"
#include "Cursor.h"
#include "Battery.h"
#include "Timer.h"
#include "Inven.h"
#include "Hud.h"
#include "Map.h"
#include "Monster_Gangster.h"
#include "Monster_Pomp.h"
#include "Monster_Grunt.h"
#include "StageEditer.h"
#include "IronDoor.h"
#include "FadeEffect.h"

ClubLevel_00::ClubLevel_00()
{
}

ClubLevel_00::~ClubLevel_00()
{
}

// 레벨 Start 기본 인터페이스 
void ClubLevel_00::Start()
{
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();

	// 기본 맵이름은 0번으로. 0번부터 시작할거니까 
	SetLevelType(LevelType::CLUBMAP0);
	// 필요한 리소스 로드
	ResourcesLoad();
	// 액터 로드 
	ActorLoad();
}

void ClubLevel_00::Update(float _DeltaTime)
{
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_00::LevelChangeStart()
{
	// 카메라 피봇세팅
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// 세팅 후 레벨을 PLAY 상태로 변경
	SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_00::LevelChangeEnd()
{
	SetState(BaseLevel::LevelState::WAIT);

	// GUI Off 
	// GUI 를 사용중이라면 Off
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_00::ResourcesLoad()
{
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

// 액터로드 기본 인터페이스 
// 초기화 필요한 액터는 Push_ResetActor
void ClubLevel_00::ActorLoad()
{
	// 맵을 생성하고, 사용할 텍스쳐세팅 
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_00.png");

	// 플레이어
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player");
	float4 InitPos = { -850 , -94 };
	ActorInit(NewPlayer, InitPos);

	// UI 
	CreateActor<Hud>(static_cast<int>(RenderOrder::UI), "Hud");
	Push_ResetActor(CreateActor<Battery>(static_cast<int>(RenderOrder::UI), "Battery"));
	Push_ResetActor(CreateActor<Timer>(static_cast<int>(RenderOrder::UI), "Timer"));
	CreateActor<Inven>(static_cast<int>(RenderOrder::UI), "Inven");

	// 서포터, 커서
	Push_ResetActor(CreateActor<PlaySupporter>(static_cast<int>(RenderOrder::UI), "PlaySupporter"));
	CreateActor<Cursor>(static_cast<int>(RenderOrder::CURSOR), "Cursor");

	// 플레이어, UI를 제외한 오브젝트 생성 및 초기화 
	CreateObjAndInit();
}

void ClubLevel_00::CreateObjAndInit()
{
	{
		std::shared_ptr<Monster_Gangster> Monster = CreateActor<Monster_Gangster>(static_cast<int>(RenderOrder::MONSTER), "Gangster");
		float4 InitPos = float4{ 584.0f , -94.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Pomp> Monster = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		float4 InitPos = { -202.0f , -94.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Pomp> Monster = CreateActor<Monster_Pomp>(static_cast<int>(RenderOrder::MONSTER), "Pomp");
		float4 InitPos = { -1.0f , -94.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { -474.0f , -94.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 70.0f , -94.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<Monster_Grunt> Monster = CreateActor<Monster_Grunt>(static_cast<int>(RenderOrder::MONSTER), "Grunt");
		float4 InitPos = { 344.0f , -94.0f };
		ActorInit(Monster, InitPos);
	}
	{
		std::shared_ptr<IronDoor> Door = CreateActor<IronDoor>(static_cast<int>(RenderOrder::DOOR), "IronDoor");
		float4 InitPos = { -67.0f , -94.0f };
		ActorInit(Door, InitPos);
	}
}

void ClubLevel_00::CreateKey()
{
	if (false == GameEngineInput::IsKey("ClubLevel_ChangeLevel_ClubLevel01"))
	{
		GameEngineInput::CreateKey("ClubLevel_ChangeLevel_ClubLevel01", VK_F1);
		GameEngineInput::CreateKey("ClubLevel_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("ClubLevel_ChangeColMap", '1');
		GameEngineInput::CreateKey("ClubLevel_ChangeMap", '2');
	}
}

void ClubLevel_00::KeyUpdate()
{
	if (true == GameEngineInput::IsDown("ClubLevel_ChangeLevel_ClubLevel01"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_01");
		return;
	}
}

void ClubLevel_00::GUISetting()
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
