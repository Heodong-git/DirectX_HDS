#include "PrecompileHeader.h"
#include "ClubLevel_Boss_01.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "StageEditer.h"
#include "PlaySupporter.h"
#include "Boss_HeadHunter.h"
#include "Player.h"
#include "CameraSetter.h"
#include "Hud.h"
#include "Battery.h"
#include "Inven.h"
#include "Timer.h"
#include "Map.h"
#include "Cursor.h"
#include "Platform.h"

#include "GunSmoke_Effect.h"
#include "GunSpark_Effect2.h"

#include "Turret.h"
#include "Turret_Wall.h"

#include "FadeEffect.h"
#include "KatanaFadeEffect.h"
#include "PlaySupporter.h"

#include "Ending_Texture.h"


ClubLevel_Boss_01::ClubLevel_Boss_01()
{
}

ClubLevel_Boss_01::~ClubLevel_Boss_01()
{
}

void ClubLevel_Boss_01::CreateHeadHunter()
{
	m_Appear = true;
	m_HeadHunter = CreateActor<Boss_HeadHunter>(static_cast<int>(RenderOrder::BOSS), "Boss_HeadHunter");
	float4 InitPos = float4{ 358.0f, -263.0f };
	ActorInit(m_HeadHunter, InitPos);
	m_HeadHunter->ChangePhase(BossPhase::SECOND);
}

void ClubLevel_Boss_01::Start()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("katanazero_resources");
	// 그 폴더로 이동
	NewDir.Move("katanazero_resources");
	NewDir.Move("sound");
	NewDir.Move("playlevel");

	// 모든 플레이레벨에서 사용할, 플레이어와 관련된 사운드가 아닌 사운드는 여기서 로드 
	GameEngineSound::Load(NewDir.GetPlusFileName("Full_Confession.mp3").GetFullPath());

	// 코어에서 처음 생성 될 때의 초기화 
	BaseLevel::Start();
	SetLevelType(LevelType::CLUBBOSS1);
	ResourcesLoad();
	ActorLoad();

	// 임시
	SetState(BaseLevel::LevelState::WAIT);
}

// 업데이트에서는, 플레이어가 IDLE 상태로 변경된다면 
// 착지한거고, 그순간에 특정위치에 헤드헌터 생성
// 그냥 바닥에 충돌체 하나 만들어두고, 그 바닥충돌체랑, 플레이어랑 충돌했다면 PLAY 상태로 변경, 
// 리셋은 플레이어위치를 
void ClubLevel_Boss_01::Update(float _DeltaTime)
{
	GameEngineCheck(_DeltaTime);

	if (true == m_GameEnd)
	{
		return;
	}


	if (true == Player::MainPlayer->IsSkill())
	{
		m_BGMPlayer.SetPitch(0.5f);
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		m_BGMPlayer.SetPitch(1.0f);
	}

	BaseLevel::Update(_DeltaTime);
	if (true == m_ColCheckObj->IsUpdate())
	{
		LevelStartCheck();
	}
}

void ClubLevel_Boss_01::LevelStartCheck()
{
	std::shared_ptr<GameEngineCollision> PlayerCol = m_ColCheckObj->GetCollision()->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != PlayerCol)
	{
		m_ColCheckObj->Off();
		SetState(BaseLevel::LevelState::PLAY);
		CreateHeadHunter();
	}
}

void ClubLevel_Boss_01::LevelChangeStart()
{
	GameEngineSound::Play("sound_transition_begin.wav");

	m_BGMPlayer = GameEngineSound::Play("Full_Confession.mp3");
	m_BGMPlayer.SetLoop(-1);
	m_BGMPlayer.SetVolume(0.7f);

	GetFadeEffect()->FadeIn();
	GUISetting();

	// 카메라 피봇세팅
	Push_ResetActor(CreateActor<CameraSetter>());
	CameraSetter::MainCamSetter->CameraSetting();

	std::shared_ptr<Player> NewPlayer = (CreateActor<Player>(static_cast<int>(RenderOrder::PLAYER), "Player"));
	float4 FallPos = { -343.0f, 68.0f };
	float4 InitPos = { -334.0f, -264.0f };
	ActorInit(NewPlayer, InitPos);
	NewPlayer->GetTransform()->SetLocalPosition(FallPos);
	NewPlayer->ChangeState(PlayerState::FALL);

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

void ClubLevel_Boss_01::LevelChangeEnd()
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

void ClubLevel_Boss_01::ResourcesLoad()
{
}

void ClubLevel_Boss_01::ActorLoad()
{
	// 임시로 0번맵 세팅
	m_Map = CreateActor<Map>(static_cast<int>(RenderOrder::MAP));
	m_Map->GetRender()->SetTexture("ClubMap_Boss_01.png");
	m_Map->GetRender()->GetTransform()->SetLocalScale(float4{ 1280.0f, 720.0f });

	m_Map->GetRender()->GetTransform()->SetLocalPosition(float4{ 0.0f, 0.0f, 1.0f });
}

void ClubLevel_Boss_01::CreateObjAndInit()
{
	// 최초 시작시에 플랫폼하나 만들고, 그 플랫폼과 플레이어가 충돌했다면 PLAY 
	{
		m_ColCheckObj = CreateActor<Platform>(static_cast<int>(RenderOrder::PLATFORM), "platform");
		m_ColCheckObj->GetTransform()->SetLocalPosition(float4{ 0.0f , -264.0f });
		m_ColCheckObj->GetCollision()->GetTransform()->SetLocalScale(float4{ 1280.0f, 2.0f });
	}
	/*{
		std::shared_ptr<Turret> Obj = CreateActor<Turret>(static_cast<int>(RenderOrder::MONSTER));
		Obj->GetTransform()->SetWorldPosition(float4{ 0.0f, 0.0f });
	}*/
}

void ClubLevel_Boss_01::KeyUpdate()
{
}

void ClubLevel_Boss_01::CreateKey()
{
}

void ClubLevel_Boss_01::GUISetting()
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

void ClubLevel_Boss_01::GameEngineCheck(float _DeltaTime)
{
	if (true == m_RealEnd)
	{
		return;
	}

	if (true == m_GameEnd)
	{
		if (0.2f >= m_KatanaFadeEffect->GetEffectTime())
		{
			/*PlaySupporter::MainSupporter->g_BlackBoxRender->On();
			PlaySupporter::MainSupporter->g_BlackBoxRender->ColorOptionValue.MulColor.a = 1.0f;
			PlaySupporter::MainSupporter->g_BlackBoxRender->GetTransform()->SetLocalScale(float4{ 1280.0f, 960.0f });
			PlaySupporter::MainSupporter->g_BlackBoxRender->GetTransform()->SetLocalPosition(float4{ 0.0f, 0.0f, -100.0f });*/
			
			

			CreateActor<Ending_Texture>();

			m_RealEnd = true;
			return;
		}
	}

	if (nullptr == m_HeadHunter)
	{
		return;
	}

	// 현재 보스가 노헤드 상태라면 
	if (BossState::NOHEAD == GetBossPtr()->GetCurState())
	{
		m_Duration -= _DeltaTime;
	}

	if (0.0f >= m_Duration && m_GameEnd == false)
	{
		Player::MainPlayer->ChangeState(PlayerState::GAME_END);
		m_GameEnd = true;
		GameEngineSound::Play("sound_transition_end.wav");
		GameEngineSound::Play("song_ending.ogg");
		m_KatanaFadeEffect->EffectOn();
	}
}
