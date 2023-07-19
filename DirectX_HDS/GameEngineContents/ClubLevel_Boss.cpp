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

#include "GunSmoke_Effect.h"
#include "GunSpark_Effect2.h"

#include "FadeEffect.h"

// test
#include "BloodEffect.h"
#include "DistotionEffect.h"

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
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("katanazero_resources");
	// 그 폴더로 이동
	NewDir.Move("katanazero_resources");
	NewDir.Move("sound");
	NewDir.Move("playlevel");

	// 모든 플레이레벨에서 사용할, 플레이어와 관련된 사운드가 아닌 사운드는 여기서 로드 
	GameEngineSound::Load(NewDir.GetPlusFileName("All_For_Now.mp3").GetFullPath());

	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();
	SetLevelType(LevelType::CLUBBOSS0);
	ResourcesLoad();
	ActorLoad();
	SetState(BaseLevel::LevelState::WAIT);
}

void ClubLevel_Boss::Update(float _DeltaTime)
{
	if (true == Player::MainPlayer->IsSkill())
	{
		m_BGMPlayer.SetPitch(0.5f);
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		m_BGMPlayer.SetPitch(1.0f);
	}

	LevelChangeUpdate();
	BaseLevel::Update(_DeltaTime);
}

void ClubLevel_Boss::LevelChangeStart()
{
	GameEngineSound::Play("sound_transition_begin.wav");

	m_BGMPlayer = GameEngineSound::Play("All_For_Now.mp3");
	m_BGMPlayer.SetLoop(-1);
	m_BGMPlayer.SetVolume(0.7f);

	GetFadeEffect()->FadeIn();
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
}

void ClubLevel_Boss::LevelChangeEnd()
{
	m_BGMPlayer.Stop();
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

	{
		// 테스트용 이펙트 
	/*	std::shared_ptr<BloodEffect> Effect = CreateActor<BloodEffect>(static_cast<int>(RenderOrder::EFFECT), "Blood_Effect");
		Effect->GetTransform()->SetLocalPosition(float4{ 0.0f , 0.0f });
		Effect->SetType(BloodType::FIRST);*/
	}
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

// 플레이어 치트상태일때 안들어옴 ㅇㅇ 
void ClubLevel_Boss::LevelChangeUpdate()
{
	// 레벨체인지 충돌체에 닿으면 익스플로전데스로 변경인데. 
	std::shared_ptr<GameEngineCollision> PlayerCol = m_LevelChangePlatform->GetCollision()->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != PlayerCol)
	{
		// Player::MainPlayer->ChangeState(PlayerState::EXPLOSION_DEATH);
		GameEngineCore::ChangeLevel("ClubLevel_Boss_01");
		return;
	}
}
