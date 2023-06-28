#include "PrecompileHeader.h"
#include "ClubLevel_Boss.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Boss_HeadHunter.h"
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
#include "SlidingDoor.h"
#include "ColEventObj.h"
#include "Platform.h"

// test
#include "GunSpark_Effect2.h"
#include "GunSmoke_Effect.h"

ClubLevel_Boss::ClubLevel_Boss()
{
}

ClubLevel_Boss::~ClubLevel_Boss()
{
}

void ClubLevel_Boss::CreateHeadHunter()
{
	m_Appear = true;
	std::shared_ptr<Boss_HeadHunter> Boss = CreateActor<Boss_HeadHunter>(static_cast<int>(RenderOrder::BOSS), "Boss_HeadHunter");
	float4 InitPos = float4{ 358.0f, -203.0f };
	ActorInit(Boss, InitPos);
}

void ClubLevel_Boss::Start()
{
	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();
	SetLevelType(LevelType::CLUBBOSS0);
	ResourcesLoad();
	ActorLoad();
	SetState(BaseLevel::LevelState::WAIT);
}

void ClubLevel_Boss::Update(float _DeltaTime)
{
	LevelChangeUpdate();
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_Boss::LevelChangeStart()
{
	GUISetting();

	// 카메라 피봇세팅
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	// 플레이어 위치세팅
	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 InitPos = { -453.0f, -203.0f };
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
	// SetState(BaseLevel::LevelState::PLAY);
}

void ClubLevel_Boss::LevelChangeEnd()
{
	SetState(BaseLevel::LevelState::WAIT);

	Player::MainPlayer->Death();

	// GUI Off 
	// GUI 를 사용중이라면 Off
	if (nullptr != m_GUI)
	{
		m_GUI->Off();
	}
}

void ClubLevel_Boss::ResourcesLoad()
{

}

void ClubLevel_Boss::ActorLoad()
{
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetScaleToTexture("ClubMap_Boss_00.png");
	m_Map->GetRender()->GetTransform()->SetLocalScale(float4{1344.0f, 580.0f});
}

void ClubLevel_Boss::CreateObjAndInit()
{
	{
		std::shared_ptr<SlidingDoor> Door = CreateActor<SlidingDoor>(static_cast<int>(RenderOrder::DOOR), "SlidingDoor");
		float4 InitPos = float4{ -558.0f, -25.0f };
		ActorInit(Door, InitPos);
	}
	{
		std::shared_ptr<SlidingDoor> Door = CreateActor<SlidingDoor>(static_cast<int>(RenderOrder::DOOR), "SlidingDoor");
		float4 InitPos = float4{ -528.0f, -25.0f };
		ActorInit(Door, InitPos);
	}
	{
		std::shared_ptr<SlidingDoor> Door = CreateActor<SlidingDoor>(static_cast<int>(RenderOrder::DOOR), "SlidingDoor");
		float4 InitPos = float4{ 558.0f, -25.0f };
		ActorInit(Door, InitPos);
	}
	{
		std::shared_ptr<SlidingDoor> Door = CreateActor<SlidingDoor>(static_cast<int>(RenderOrder::DOOR), "SlidingDoor");
		float4 InitPos = float4{ 528.0f, -25.0f };
		ActorInit(Door, InitPos);
	}
	{
		// -348 , - 200
		std::shared_ptr<ColEventObj> Obj = CreateActor<ColEventObj>(static_cast<int>(RenderOrder::DOOR), "ColEventObj");
		float4 InitPos = float4{ -380.0f, -203.0f };
		ActorInit(Obj, InitPos);
	}
	{
		std::shared_ptr<Platform> NewPlatform = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		NewPlatform->GetTransform()->SetLocalPosition(float4{ -544.0f , -207.0f });
		NewPlatform->GetCollision()->GetTransform()->SetLocalScale(float4{ 100.0f, 1.0f });
	}
	{
		std::shared_ptr<Platform> NewPlatform = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		NewPlatform->GetTransform()->SetLocalPosition(float4{ 544.0f , -207.0f });
		NewPlatform->GetCollision()->GetTransform()->SetLocalScale(float4{ 100.0f, 1.0f });
	}
	{
		m_LevelChangePlatform = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		m_LevelChangePlatform->GetTransform()->SetLocalPosition(float4{ 0.0f , -480.0f });
		m_LevelChangePlatform->GetCollision()->GetTransform()->SetLocalScale(float4{ 1280.0f, 1.0f });
	}

	//{
	//	// 테스트용 이펙트 
	//	std::shared_ptr<GunSmoke_Effect> Effect = CreateActor<GunSmoke_Effect>(static_cast<int>(RenderOrder::EFFECT), "GunSmoke_Effect");
	//	Effect->GetTransform()->SetLocalPosition(float4{ 0.0f , 0.0f });
	//	Effect->SetType(EffectType::SECOND);
	//}
}

void ClubLevel_Boss::KeyUpdate()
{
	if (true == GameEngineInput::IsDown("LevelChange_Boss01"))
	{
		GameEngineCore::ChangeLevel("ClubLevel_Boss_01");
		return;
	}
}

void ClubLevel_Boss::CreateKey()
{
	if (false == GameEngineInput::IsKey("LevelChange_Boss01"))
	{
		GameEngineInput::CreateKey("LevelChange_Boss01", VK_F1);
		return;
	}
}

void ClubLevel_Boss::GUISetting()
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

void ClubLevel_Boss::LevelChangeUpdate()
{
	std::shared_ptr<GameEngineCollision> PlayerCol = m_LevelChangePlatform->GetCollision()->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != PlayerCol)
	{
		GameEngineCore::ChangeLevel("ClubLevel_Boss_01");
		return;
	}
}
