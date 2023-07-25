#include "PrecompileHeader.h"
#include "Boss_HeadHunter.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "PixelCollider.h"
#include "Player.h"
#include "HeadHunter_RifleEffect.h"
#include "TeleportEffect.h"
#include "GunSpark_Effect.h"
#include "Monster_Gangster.h"
#include "Monster_Grunt.h"
#include "Monster_Pomp.h"
#include "Remote_Mine.h"
#include "FadeEffect.h"
#include "Turret_Wall.h"
#include "Turret.h"
#include "Bullet.h"
#include "Trail_Effect.h"
#include "PlaySupporter.h"
#include "ClubLevel_Boss_01.h"
#include "BloodEffect.h"

Boss_HeadHunter* Boss_HeadHunter::m_MainBoss = nullptr;

Boss_HeadHunter::Boss_HeadHunter()
{
	m_MainBoss = this;
}

Boss_HeadHunter::~Boss_HeadHunter()
{
}

void Boss_HeadHunter::Start()
{
	ComponentSetting();
	LoadAndCreateAnimation();
	SummonsSetting();
	CeilingPointInit();
	FireAngleInit();
	ChangeState(BossState::INTRO);
}

void Boss_HeadHunter::Update(float _DeltaTime)
{
	m_RecordingFrame = !m_RecordingFrame;
	m_TrailEffect = !m_TrailEffect;

	if (true == Player::MainPlayer->IsSkill())
	{
		m_SoundPlayer.SetPitch(0.5f);
		m_TurretSoundPlayer.SetPitch(0.5f);
	}

	else if (false == Player::MainPlayer->IsSkill())
	{
		m_SoundPlayer.SetPitch(1.0f);
		m_TurretSoundPlayer.SetPitch(1.0f);
	}

	// 레벨의 상태를 체크한다. 
	BaseLevel::LevelState CurState = GetLevelState();
	if (BaseLevel::LevelState::RECORDING_PROGRESS == CurState &&
		BossState::RECORDING_PROGRESS != m_CurState)
	{
		ChangeState(BossState::RECORDING_PROGRESS);
		return;
	}

	DebugUpdate();

	// 이건 위에 있어야 맞지. 근데 일단 보류 
	if (true == m_RotaitionFire)
	{
		RotaitionFireUpdate(_DeltaTime);
	}

	HitUpdate(_DeltaTime);
	if (true == m_Summons && false == m_SummonsEndCheck)
	{
		SummonsMonstersUpdate(_DeltaTime);
	}
	NextTransUpdate();
	UpdateState(_DeltaTime);

	if (BossState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_MainRender.get());
		}
	}
}

void Boss_HeadHunter::CreateTrailEffect()
{
	if (false == m_TrailEffect)
	{
		return;
	}
	// 이펙트 생성시 텍스쳐 이름을 받아오고, 
	std::string TexName = m_MainRender->GetTexName();
	std::shared_ptr<GameEngineTexture> Tex = m_MainRender->GetCurTexture();
	if (nullptr != Tex)
	{
		float4 TexSize = Tex->GetScale();
		// 잔상 이펙트 액터 생성 
		std::weak_ptr<Trail_Effect> Effect = GetLevel()->CreateActor<Trail_Effect>();

		// 이펙트의 위치 세팅
		Effect.lock()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		Effect.lock()->SetTexture(TexName, TexSize, TrailType::BOSS);
	}
}

void Boss_HeadHunter::RotaitionFireSoundPlay()
{
	m_SoundPlayer = GameEngineSound::Play("headhunter_rotaitionfire.wav");
}

void Boss_HeadHunter::HitSoundPlay()
{
	int RandomValue = CreateRandomValue(3);
	switch (RandomValue)
	{
	case 1:
		m_SoundPlayer = GameEngineSound::Play("sound_voiceboss_huntress_hurt_1.wav");
		break;
	case 2:
		m_SoundPlayer = GameEngineSound::Play("sound_voiceboss_huntress_hurt_2.wav");
		break;
	case 3:
		m_SoundPlayer = GameEngineSound::Play("sound_voiceboss_huntress_hurt_3.wav");
		break;
	}

}

void Boss_HeadHunter::WallJumpSoundPlay()
{
	int RandomValue = CreateRandomValue(3);
	switch (RandomValue)
	{
	case 1:
		m_SoundPlayer = GameEngineSound::Play("sound_voiceboss_huntress_walljump_1.wav");
		break;
	case 2:
		m_SoundPlayer = GameEngineSound::Play("sound_voiceboss_huntress_walljump_2.wav");
		break;
	case 3:
		m_SoundPlayer = GameEngineSound::Play("sound_voiceboss_huntress_walljump_3.wav");
		break;
	}
}

// -179, -1 
// 개수는 18개 
// 10도당 하나 
// 어느쪽으로 먼저나가냐가 그거니까
// 벡터에 담아두고 우측으로 쏠때는 정방향, 좌측으로쏠때는 역방향으로 진행한다. 

void Boss_HeadHunter::RotaitionFireUpdate(float _DeltaTime)
{
	// 벡터에 발사각도 저장해두고, 사용 일단 임시
	if (0.0f >= m_RotaitionFireTime)
	{
		bool Check = m_Dir;

		if (true == m_Dir)
		{
			// 쿨타임 0.02초로 초기화
			m_RotaitionFireTime = 0.008f;

			if (m_CurFireAngleCount >= 18)
			{
				return;
			}
			// 불릿 오브젝트생성
			std::weak_ptr<Bullet> Obj = GetLevel()->CreateActor<Bullet>();
			Obj.lock()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
			Obj.lock()->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, m_vecFireAngle[m_CurFireAngleCount] });
			float4 Dir = float4::AngleToDirection2DToDeg(Obj.lock()->GetTransform()->GetLocalRotation().z);
			Obj.lock()->SetMoveDir(Dir);
			Obj.lock()->ChangeColOrder(static_cast<int>(ColOrder::BOSS_ATTACK));

			std::weak_ptr<GunSpark_Effect> Effect = GetLevel()->CreateActor<GunSpark_Effect>();
			Effect.lock()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
			Effect.lock()->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, m_vecFireAngle[m_CurFireAngleCount] });

			++m_CurFireAngleCount;
			return;
		}

		if (false == m_Dir)
		{
			// 쿨타임 0.02초로 초기화
			m_RotaitionFireTime = 0.008f;

			if (m_CurFireAngleCount_Reverse < 0 || m_CurFireAngleCount_Reverse > 17)
			{
				return;
			}
			// 불릿 오브젝트생성
			std::weak_ptr<Bullet> Obj = GetLevel()->CreateActor<Bullet>();
			Obj.lock()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
			Obj.lock()->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, m_vecFireAngle[m_CurFireAngleCount_Reverse] });
			float4 Dir = float4::AngleToDirection2DToDeg(Obj.lock()->GetTransform()->GetLocalRotation().z);
			Obj.lock()->SetMoveDir(Dir);
			Obj.lock()->ChangeColOrder(static_cast<int>(ColOrder::BOSS_ATTACK));

			std::weak_ptr<GunSpark_Effect> Effect = GetLevel()->CreateActor<GunSpark_Effect>();
			Effect.lock()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
			Effect.lock()->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, m_vecFireAngle[m_CurFireAngleCount_Reverse] });

			--m_CurFireAngleCount_Reverse;
			return;
		}

	}

	m_RotaitionFireTime -= _DeltaTime;
}

void Boss_HeadHunter::NextTransUpdate()
{
	m_NextTrans->SetLocalPosition(GetTransform()->GetWorldPosition());
}

void Boss_HeadHunter::ComponentSetting()
{
	// NextPos로 사용
	m_NextTrans = std::make_shared<GameEngineTransform>();

	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BOSS);
	m_MainRender->GetTransform()->SetLocalPosition(m_MainRenderOriginPos);

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BOSS);
	m_Collision->GetTransform()->SetLocalPosition(float4{ 0.0f, 37.0f });
	m_Collision->GetTransform()->SetLocalScale(float4{ 30.0f, 75.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);

	m_AttCollision = CreateComponent<GameEngineCollision>(ColOrder::BOSS_ATTACK);
	m_AttCollision->GetTransform()->SetLocalScale(float4{ 90.0f, 70.0f });
	m_AttCollision->Off();
	m_AttCollision->SetColType(ColType::OBBBOX3D);

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 4.0f , 4.0f });
	m_DebugRender->Off();

	m_DebugRender_Right = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Right->GetTransform()->SetLocalPosition(m_DebugPivot);
	m_DebugRender_Right->GetTransform()->SetLocalScale(float4{ 4.0f , 4.0f });
	m_DebugRender_Right->Off();
}

void Boss_HeadHunter::LoadAndCreateAnimation()
{
	if (nullptr == GameEngineSprite::Find("headhunter_idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("headhunter");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_idle").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_intro").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_takeout_rifle").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_roll").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_hurt").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_recover").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_jump").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_teleportin_sweep").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_sweep").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_teleportout_sweep").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_dash").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_dash_end_ground").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_teleportin_ceiling").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_teleportout_ceiling").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_teleportout_rifle_ground").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_teleportin_rifle_ground").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_teleportin_wall_idle").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_jump_rifle").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_jump_rifle_land").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_takeout_gun").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_gun_shot").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_death_land").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_moribund").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_nohead").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_rush_ready").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_rush").GetFullPath());

		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("sound");
		Dir.Move("headhunter");

		// 이펙트사운드
		GameEngineSound::Load(Dir.GetPlusFileName("headhunter_rotaitionfire.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("headhunter_lockon.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("headhunter_rifle_shot_01.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("headhunter_rifle_shot_02.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("headhunter_rifle_shot_03.wav").GetFullPath());

		// 마인설치사운드
		GameEngineSound::Load(Dir.GetPlusFileName("sound_boss_huntressbomb_armed_01.wav").GetFullPath());

		// 히트사운드
		GameEngineSound::Load(Dir.GetPlusFileName("sound_voiceboss_huntress_hurt_1.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_voiceboss_huntress_hurt_2.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_voiceboss_huntress_hurt_3.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_boss_huntress_vanish_01.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_boss_huntressbeam_circle_01.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_boss_huntressknife_prep_01.wav").GetFullPath());

		// 점프사운드 
		GameEngineSound::Load(Dir.GetPlusFileName("sound_boss_huntress_jump_01.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_voiceboss_huntress_walljump_1.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_voiceboss_huntress_walljump_2.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_voiceboss_huntress_walljump_3.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_turret_deploy.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_turretdie.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_walkthroughdoorway.wav").GetFullPath());
		GameEngineSound::Load(Dir.GetPlusFileName("sound_head_1.wav").GetFullPath());


		// 브금하나넣어 
		GameEngineSound::Load(Dir.GetPlusFileName("song_ending.ogg").GetFullPath());
	}

	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_idle", .SpriteName = "headhunter_idle", .Start = 0, .End = 11 ,
									  .FrameInter = 0.09f , .Loop = true , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_intro", .SpriteName = "headhunter_intro", .Start = 0, .End = 2 ,
									  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_takeout_rifle", .SpriteName = "headhunter_takeout_rifle", .Start = 0, .End = 14 ,
								  .FrameInter = 0.055f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_roll", .SpriteName = "headhunter_roll", .Start = 0, .End = 6 ,
									.FrameInter = 0.055f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_recover", .SpriteName = "headhunter_recover", .Start = 0, .End = 3 ,
							  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_jump", .SpriteName = "headhunter_jump", .Start = 0, .End = 2 ,
							  .FrameInter = 0.09f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_teleportin_sweep", .SpriteName = "headhunter_teleportin_sweep", .Start = 0, .End = 3 ,
							  .FrameInter = 0.15f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_sweep", .SpriteName = "headhunter_sweep", .Start = 0, .End = 17 ,
							  .FrameInter = 0.08f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_teleportout_sweep", .SpriteName = "headhunter_teleportout_sweep", .Start = 0, .End = 2 ,
							  .FrameInter = 0.08f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_dash", .SpriteName = "headhunter_dash", .Start = 0, .End = 1 ,
							  .FrameInter = 0.08f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_teleportin_ceiling", .SpriteName = "headhunter_teleportin_ceiling", .Start = 0, .End = 3 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_teleportout_ceiling", .SpriteName = "headhunter_teleportout_ceiling", .Start = 0, .End = 3 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_teleportout_rifle_ground", .SpriteName = "headhunter_teleportout_rifle_ground", .Start = 0, .End = 3 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_teleportin_rifle_ground", .SpriteName = "headhunter_teleportin_rifle_ground", .Start = 0, .End = 3 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_teleportin_wall_idle", .SpriteName = "headhunter_teleportin_wall_idle", .Start = 0, .End = 6 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_jump_rifle", .SpriteName = "headhunter_jump_rifle", .Start = 0, .End = 6 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_jump_rifle_land", .SpriteName = "headhunter_jump_rifle_land", .Start = 0, .End = 3 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_takeout_gun", .SpriteName = "headhunter_takeout_gun", .Start = 0, .End = 6 ,
							  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_gun_shot", .SpriteName = "headhunter_gun_shot", .Start = 0, .End = 7 ,
							  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_death_land", .SpriteName = "headhunter_death_land", .Start = 0, .End = 7 ,
							  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_moribund", .SpriteName = "headhunter_moribund", .Start = 0, .End = 18 ,
							 .FrameInter = 0.15f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_rush_ready", .SpriteName = "headhunter_rush_ready", .Start = 0, .End = 7 ,
							  .FrameInter = 0.08f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_rush", .SpriteName = "headhunter_rush", .Start = 0, .End = 1 ,
							  .FrameInter = 1.0f , .Loop = true , .ScaleToTexture = true });

	// 0.17 , false 
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_nohead", .SpriteName = "headhunter_nohead", .Start = 0, .End = 5 ,
							  .FrameInter = 0.17f , .Loop = false , .ScaleToTexture = true });

	{
		std::vector<float> vFrameTime = std::vector<float>();
		vFrameTime.push_back(0.1f);
		vFrameTime.push_back(0.1f);
		vFrameTime.push_back(0.15f);
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.05f);
		vFrameTime.push_back(0.05f);
		vFrameTime.push_back(0.05f);
		vFrameTime.push_back(0.05f);

		AnimationParameter Para = {};
		Para.AnimationName = "headhunter_hurt";
		Para.SpriteName = "headhunter_hurt";
		Para.Start = 0;
		Para.End = 9;
		Para.FrameTime = vFrameTime;
		Para.Loop = false;
		Para.ScaleToTexture = true;

		m_MainRender->CreateAnimation(Para);
	}
	{
		std::vector<float> vFrameTime = std::vector<float>();
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.07f);
		vFrameTime.push_back(0.1f);
		vFrameTime.push_back(0.1f);
		vFrameTime.push_back(0.1f);
		vFrameTime.push_back(0.1f);
		vFrameTime.push_back(0.1f);

		AnimationParameter Para = {};
		Para.AnimationName = "headhunter_dash_end_ground";
		Para.SpriteName = "headhunter_dash_end_ground";
		Para.Start = 0;
		Para.End = 9;
		Para.FrameTime = vFrameTime;
		Para.Loop = false;
		Para.ScaleToTexture = true;

		m_MainRender->CreateAnimation(Para);
	}

	m_MainRender->SetAnimationStartEvent("headhunter_takeout_rifle", static_cast<size_t>(5), std::bind(&Boss_HeadHunter::CreateRifleEffect, this));
	// m_MainRender->SetAnimationStartEvent("headhunter_takeout_rifle", static_cast<size_t>(11), std::bind(&Boss_HeadHunter::RifleShotSoundPlay, this));
	m_MainRender->SetAnimationStartEvent("headhunter_dash_end_ground", static_cast<size_t>(0), std::bind(&Boss_HeadHunter::AttCollisionOn, this));
	m_MainRender->SetAnimationStartEvent("headhunter_dash_end_ground", static_cast<size_t>(3), std::bind(&Boss_HeadHunter::AttCollisionOff, this));
	m_MainRender->SetAnimationStartEvent("headhunter_jump_rifle", static_cast<size_t>(2), std::bind(&Boss_HeadHunter::RotaitionFireSoundPlay, this));

	m_MainRender->ChangeAnimation("headhunter_idle");
	m_MainRender->SetScaleRatio(2.0f);
}

// 사운드 생성후, 저장해놓아야함 
void Boss_HeadHunter::LoadSound()
{
}

void Boss_HeadHunter::AttCollisionOn()
{
	m_AttCollision->On();
	// 내가 우측을 보고 있다면 
	if (true == m_Dir)
	{
		m_AttCollision->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4 { 15.0f, 10.0f });
	}

	else if (false == m_Dir)
	{
		m_AttCollision->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4 { -15.0f, 10.0f });
	}
}


void Boss_HeadHunter::AttCollisionOff()
{
	m_AttCollision->Off();
}

void Boss_HeadHunter::CreateRifleEffect()
{
	float4 MyPos = GetTransform()->GetLocalPosition();
	m_Effect = GetLevel()->CreateActor<HeadHunter_RifleEffect>(static_cast<int>(RenderOrder::BOSS_EFFECT));
	m_Effect.lock()->GetTransform()->SetLocalPosition(float4{ 0.0f, 0.0f, -150.0f });
	m_Effect.lock()->SetActor(DynamicThis<Boss_HeadHunter>());

	if (BossState::RIFLE == m_CurState)
	{
		m_Effect.lock()->SetType(RifleEffectType::NORMAL);
	}

	if (BossState::TELEPORTIN_CEILING == m_CurState)
	{
		m_Effect.lock()->SetType(RifleEffectType::CEILING_FIRE);
		m_Effect.lock()->GetTransform()->SetLocalPosition(MyPos + float4{ 0.0f, -520.0f, -150.0f});
		m_Effect.lock()->GetTransform()->SetLocalRotation(float4{ 0.0f , 0.0f, -90.0f });
		return;
	}

	// 현재 텔레포트 라이플 상태라면 반대로 
	if (BossState::TELEPORTIN_RIFLE == m_CurState)
	{
		m_Effect.lock()->SetType(RifleEffectType::NORMAL);
		if (false == m_Dir)
		{
			m_Effect.lock()->GetTransform()->SetLocalPosition(MyPos + float4{ m_RifleEffectPivot.x, m_RifleEffectPivot.y - 11.0f, -150.0f });
		}

		else if (true == m_Dir)
		{
			m_Effect.lock()->GetTransform()->SetLocalPosition(MyPos + float4{ -m_RifleEffectPivot.x, m_RifleEffectPivot.y - 11.0f, -150.0f });
		}

		return;
	}

	if (true == m_Dir)
	{
		m_Effect.lock()->GetTransform()->SetLocalPosition(MyPos + float4{ m_RifleEffectPivot.x, m_RifleEffectPivot.y, 1.0f });
	}

	else if (false == m_Dir)
	{
		m_Effect.lock()->GetTransform()->SetLocalPosition(MyPos + float4{ -m_RifleEffectPivot.x, m_RifleEffectPivot.y, 1.0f });
	}
}

void Boss_HeadHunter::CreateSweepEffect()
{
	m_SweepEffect = GetLevel()->CreateActor<HeadHunter_RifleEffect>();
	m_SweepEffect.lock()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4 { 3.0f, 47.0f, -5.0f });
	m_SweepEffect.lock()->SetType(RifleEffectType::SWEEP);
}

void Boss_HeadHunter::CreateTpEffect()
{
	m_SoundPlayer = GameEngineSound::Play("sound_boss_huntress_vanish_01.wav");
	std::shared_ptr<TeleportEffect> Effect = GetLevel()->CreateActor<TeleportEffect>(static_cast<int>(RenderOrder::BOSS_TP_EFFECT));
	Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4 { 0.0f, 0.0f, -100.0f });
	if (true == m_Dir)
	{
		Effect->GetTransform()->SetLocalNegativeScaleX();
	}

	else if (false == m_Dir)
	{
		Effect->GetTransform()->SetLocalPositiveScaleX();
	}
}

void Boss_HeadHunter::Reset()
{
	ResetPhase();
	ResetEffect();
	ResetSummons();
	GetTransform()->SetLocalPosition(GetInitPos());
	ChangeState(BossState::INTRO);

	m_MainRender->GetTransform()->SetLocalPosition(m_MainRenderOriginPos);
	m_CurFireAngleCount = 0;
	m_IdleDuration = 0.25f;
	m_IsDoubleSweep = false;
	m_TpInStart = false;
	m_TpCount = 0;
	m_NoHeadStatePos = float4::Zero;
}

void Boss_HeadHunter::ResetPhase()
{
	// 레벨타입에따라서 first , second 로 
	if (LevelType::CLUBBOSS0 == GetReturnCastLevel()->GetLevelType())
	{
		m_CurPhase = BossPhase::FIRST;
		m_Phase1_HitCount = 3;
	}

	if (LevelType::CLUBBOSS1 == GetReturnCastLevel()->GetLevelType())
	{
		m_CurPhase = BossPhase::SECOND;
		m_Phase2_HitCount = 5;
	}
}

// 흠 이거 일단 하지말아봐 
// 어차피 안죽어있지않나 ?? 
void Boss_HeadHunter::ResetEffect()
{
	if (nullptr != m_Effect.lock())
	{
		m_Effect.lock()->Death();
		m_Effect.lock() = nullptr;
	}

	if (nullptr != m_SweepEffect.lock())
	{
		m_SweepEffect.lock()->Death();
		m_SweepEffect.lock() = nullptr;
	}
}

void Boss_HeadHunter::ResetSummons()
{
	m_SetMine = false;
	m_Summons = false;
	m_SummonsEndCheck = false;
	m_IsTurretSummons = false;

	// 만들어놨던 액터들 다 데스처리
	if (0 != m_SummonsMonsters.size())
	{
		for (size_t i = 0; i < m_SummonsMonsters.size(); ++i)
		{
			if (nullptr != m_SummonsMonsters[i])
			{
				m_SummonsMonsters[i]->Death();
			}
		}
		m_SummonsMonsters.clear();
	}

	// 마인이 0이 아니라면 현재 마인이 생성되었다는 의미이고, 생성된 마인을 전부 데스처리한다. 
	if (0 != m_Mines.size())
	{
		for (size_t i = 0; i < m_Mines.size(); ++i)
		{
			if (nullptr != m_Mines[i])
			{
				m_Mines[i]->Death();
			}
		}
		m_Mines.clear();
	}

	if (nullptr != m_TurretWall.lock())
	{
		m_TurretWall.lock()->Death();
		m_TurretWall.lock() = nullptr;

		if (nullptr != m_Turret_First.lock())
		{
			m_Turret_First.lock()->Death();
			m_Turret_First.lock() = nullptr;
		}

		if (nullptr != m_Turret_Second.lock())
		{
			m_Turret_Second.lock()->Death();
			m_Turret_Second.lock() = nullptr;
		}

	}
}

void Boss_HeadHunter::HitUpdate(float _DeltaTime)
{
	if (BossState::NOHEAD == m_CurState)
	{
		return;
	}


	if (true == m_AttCollision->IsUpdate())
	{
		m_AttCollision->Off();
	}

	// 내가 플레이어의 공격과 충돌했다면.
	std::shared_ptr<GameEngineCollision> Player_AttCol = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Player_AttCol)
	{

		HitSoundPlay();
		float RandomValue = GameEngineRandom::MainRandom.RandomFloat(35.0f, 60.0f);
		std::weak_ptr<BloodEffect> Blood_Effect = GetLevel()->CreateActor<BloodEffect>();
		Blood_Effect.lock()->SetType(BloodType::NORMAL);
		Blood_Effect.lock()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4 { 0.0f, RandomValue });


		// 충돌했는데 내가 모리번드상태라면 
		if (BossState::MORIBUND == m_CurState)
		{
			ChangeState(BossState::NOHEAD);
			return;
		}

		// 내가 플레이어의 공격과 충돌했다면 Hurt 상태로 전환
		// 1. 충돌했다면 바로 충돌체 off,
		// 2. hurt state로 전환
		m_Collision->Off();

		if (LevelType::CLUBBOSS0 == GetReturnCastLevel()->GetLevelType())
		{
			--m_Phase1_HitCount;
		}

		if (LevelType::CLUBBOSS1 == GetReturnCastLevel()->GetLevelType())
		{
			--m_Phase2_HitCount;
		}
		// 여기서 

		// 플레이어 x축 계산  
		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		float4 MyPos = GetTransform()->GetWorldPosition();
		m_HitPos = GetTransform()->GetLocalPosition();
		// 플레이어보다 내 위치의 x값이 크다면 
		if (PlayerPos.x <= MyPos.x)
		{
			m_HitEndPos = m_HitPos + float4{ 100.0f, 0.0f};
		}

		else if (PlayerPos.x > MyPos.x)
		{
			m_HitEndPos = m_HitPos + float4{ -100.0f, 0.0f};
		}


		m_MiddlePos = m_HitPos + float4{ (m_HitEndPos.x - m_HitPos.x) / 2.0f, 25.0f };
		ChangeState(BossState::HURT);
		return;
	}
}

void Boss_HeadHunter::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_debugswitch"))
	{
		DebugSwitch();

		if (true == IsDebug())
		{

			m_DebugRender->On();
			m_DebugRender_Right->On();
		}

		else if (false == IsDebug())
		{

			m_DebugRender->Off();
			m_DebugRender_Right->Off();
		}
	}
}

void Boss_HeadHunter::SummonsSetting()
{
	// 단순하게 몬스터 소환위치만 1번부터 4번까지 넣어준다.
	m_SummonsPoss.reserve(4);

	float4 Gate1Pos = float4{ -453.0f, -203.0f };
	float4 Gate2Pos = float4{ -161.0f, -203.0f };
	float4 Gate3Pos = float4{ 180.0f, -203.0f };
	float4 Gate4Pos = float4{ 440.0f, -203.0f };

	m_SummonsPoss.push_back(Gate1Pos);
	m_SummonsPoss.push_back(Gate2Pos);
	m_SummonsPoss.push_back(Gate3Pos);
	m_SummonsPoss.push_back(Gate4Pos);
}

void Boss_HeadHunter::SummonsMonstersUpdate(float _DeltaTime)
{
	size_t DeathCount = 0;
	for (size_t i = 0; i < m_SummonsMonsters.size(); ++i)
	{
		// 반복해서 돌면서 isdeath 가 true 일 경우를 체크한다. 
		if (true == m_SummonsMonsters[i]->DeathCheck())
		{
			++DeathCount;
		}
	}

	// 그리고 데스카운트 값에 따라서 몬스터를 On 시켜줘 
	if (2 == DeathCount)
	{
		{
			std::shared_ptr<Monster_Gangster> Gangster = m_SummonsMonsters[2]->DynamicThis<Monster_Gangster>();
			m_SummonsMonsters[2]->On();
		}
		{
			std::shared_ptr<Monster_Gangster> Gangster = m_SummonsMonsters[3]->DynamicThis<Monster_Gangster>();
			m_SummonsMonsters[3]->On();
		}
	}

	if (4 == DeathCount && false == m_SummonsEndCheck)
	{
		m_SummonsEndCheck = true;
		// 여기가 pomp 
		{
			std::shared_ptr<Monster_Pomp> Pomp = m_SummonsMonsters[4]->DynamicThis<Monster_Pomp>();
			Pomp->ChangeState(PompState::CHASE);
			Pomp->On();
		}

		{
			std::shared_ptr<Monster_Pomp> Pomp = m_SummonsMonsters[5]->DynamicThis<Monster_Pomp>();
			Pomp->ChangeState(PompState::CHASE);
			Pomp->On();
		}
	}
}

void Boss_HeadHunter::DirCheck()
{
	if (true == m_Dir)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	else if (false == m_Dir)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
}

void Boss_HeadHunter::ChangeDir()
{
	// 플레이어 x축 계산  
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();

	// 플레이어보다 내 위치의 x값이 크다면 
	if (PlayerPos.x <= MyPos.x)
	{
		m_Dir = false;
	}

	else if (PlayerPos.x > MyPos.x)
	{
		m_Dir = true;
	}
}

bool Boss_HeadHunter::PlayerLiveCheck()
{
	// 데스상태 또는 NONE 상태라면 return 
	PlayerState State = Player::MainPlayer->GetCurState();
	if (PlayerState::DEATH == State || PlayerState::NONE == State ||
		PlayerState::EXPLOSION_DEATH == State)
	{
		return false;
	}

	size_t Count = 0;
	for (size_t i = 0; i < m_Mines.size(); ++i)
	{
		if (nullptr != m_Mines[i])
		{
			// 하나라도 false 라면 return; 
			if (false == m_Mines[i]->IsDeath())
			{
				return false;
			}
			// 그게 아니라면 카운트를 더해주고, 
			// 최종 카운트가 마인카운트와 동일하다면 마인이 모두 데스상태라는 의미, 플레이어를 강제로 forcefall 상태로 변경 
			++Count;
		}
	}

	if (m_MineCount == Count)
	{
		return true;
	}

	return false;
}

void Boss_HeadHunter::FireAngleInit()
{
	m_vecFireAngle.reserve(m_FireAngleCount);
	float Angle = 0.0f;
	for (size_t i = 0; i < m_FireAngleCount; ++i)
	{
		m_vecFireAngle.push_back(Angle);
		Angle -= 10.0f;
	}

	m_FireAngleCount_Reverse = m_vecFireAngle.size() - 1;
}

void Boss_HeadHunter::SummonsMonsters()
{
	// 소환상태를 true로 변경
	m_Summons = true;
	// 몬스터 8개를 생성해서 저장할 벡터 리저브,
	m_SummonsMonsters.reserve(8);

	// 그런트 
	std::shared_ptr<Monster_Grunt> Monster = GetLevel()->CreateActor<Monster_Grunt>();
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
	Monster->GetTransform()->SetLocalPosition(m_SummonsPoss[RandomValue]);
	Monster->ChangeState(GruntState::CHASE);
	m_SummonsMonsters.push_back(Monster->DynamicThis<BaseActor>());

	std::shared_ptr<Monster_Grunt> Monster2 = GetLevel()->CreateActor<Monster_Grunt>();
	// 다음위치
	int Value = RandomValue + 1;
	if (Value >= static_cast<int>(m_SummonsPoss.size()))
	{
		Value = 0;
	}

	Monster2->GetTransform()->SetLocalPosition(m_SummonsPoss[Value]);
	Monster2->ChangeState(GruntState::CHASE);
	m_SummonsMonsters.push_back(Monster2->DynamicThis<BaseActor>());

	// 갱스터 
	std::shared_ptr<Monster_Gangster> NewGangster = GetLevel()->CreateActor<Monster_Gangster>();
	RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
	NewGangster->GetTransform()->SetLocalPosition(m_SummonsPoss[RandomValue]);
	NewGangster->ChangeState(GangsterState::CHASE);
	NewGangster->Off();
	m_SummonsMonsters.push_back(NewGangster->DynamicThis<BaseActor>());

	std::shared_ptr<Monster_Gangster> NewGangster1 = GetLevel()->CreateActor<Monster_Gangster>();
	Value = RandomValue + 1;
	if (Value >= static_cast<int>(m_SummonsPoss.size()))
	{
		Value = 0;
	}
	NewGangster1->GetTransform()->SetLocalPosition(m_SummonsPoss[Value]);
	NewGangster1->ChangeState(GangsterState::CHASE);
	NewGangster1->Off();
	m_SummonsMonsters.push_back(NewGangster1->DynamicThis<BaseActor>());

	// pomp 
	std::shared_ptr<Monster_Pomp> NewPomp = GetLevel()->CreateActor<Monster_Pomp>();
	RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
	NewPomp->GetTransform()->SetLocalPosition(m_SummonsPoss[RandomValue]);
	NewPomp->Off();
	m_SummonsMonsters.push_back(NewPomp->DynamicThis<BaseActor>());

	std::shared_ptr<Monster_Pomp> NewPomp1 = GetLevel()->CreateActor<Monster_Pomp>();
	Value = RandomValue + 1;
	if (Value >= static_cast<int>(m_SummonsPoss.size()))
	{
		Value = 0;
	}
	NewPomp1->GetTransform()->SetLocalPosition(m_SummonsPoss[Value]);
	NewPomp1->Off();
	m_SummonsMonsters.push_back(NewPomp1->DynamicThis<BaseActor>());
}

void Boss_HeadHunter::CreateTurretWall()
{
	m_TurretWall = GetLevel()->CreateActor<Turret_Wall>();
	m_TurretWall.lock()->GetTransform()->SetWorldPosition(m_TurretWallPos);
}

void Boss_HeadHunter::CreateTurret()
{
	m_TurretSoundPlayer = GameEngineSound::Play("sound_turret_deploy.wav");

	// 터렛 두마리 생성, 위치는 ? 
	m_Turret_First = GetLevel()->CreateActor<Turret>();
	m_Turret_First.lock()->SetType(TurretType::WALL);
	m_Turret_First.lock()->GetTransform()->SetWorldPosition(m_Turret_FirstPos);
	m_Turret_Second = GetLevel()->CreateActor<Turret>();
	m_Turret_Second.lock()->SetType(TurretType::WALL);
	m_Turret_Second.lock()->GetTransform()->SetWorldPosition(m_Turret_SecondPos);
}


void Boss_HeadHunter::CeilingPointInit()
{
	m_vecCeilingPos.reserve(4);

	// 여기서 하나씩 
	float4 CeilingPos1 = float4{ -435.0f, 112.0f };
	float4 CeilingPos2 = float4{ -237.0f, 112.0f };
	float4 CeilingPos3 = float4{ 233.0f, 112.0f };
	float4 CeilingPos4 = float4{ 434.0f, 112.0f };

	m_vecCeilingPos.push_back(CeilingPos1);
	m_vecCeilingPos.push_back(CeilingPos2);
	m_vecCeilingPos.push_back(CeilingPos3);
	m_vecCeilingPos.push_back(CeilingPos4);
}

const float4& Boss_HeadHunter::CeilingPointShuffle()
{
	std::random_device rd;
	std::shuffle(m_vecCeilingPos.begin(), m_vecCeilingPos.end(), rd);
	return m_vecCeilingPos[0];
}

void Boss_HeadHunter::ChangeState(BossState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	// start 
	switch (m_NextState)
	{
	case BossState::INTRO:
		IntroStart();
		break;
	case BossState::IDLE:
		IdleStart();
		break;
	case BossState::RIFLE:
		RifleStart();
		break;
	case BossState::GUN:
		GunStart();
		break;
	case BossState::GUN_SHOT:
		GunShotStart();
		break;
	case BossState::ROLL:
		RollStart();
		break;
	case BossState::HURT:
		HurtStart();
		break;
	case BossState::RECOVER:
		RecoverStart();
		break;
	case BossState::TRANSPARENCY:
		TransparencyStart();
		break;
	case BossState::REAPPEAR:
		ReAppearStart();
		break;
	case BossState::CHANGEPHASE:
		ChangePhaseStart();
		break;
	case BossState::JUMP:
		JumpStart();
		break;
	case BossState::TELEPORTIN_SWEEP:
		TpSweepInStart();
		break;
	case BossState::SWEEP:
		SweepStart();
		break;
	case BossState::TELEPORTOUT_SWEEP:
		TpSweepOutStart();
		break;
	case BossState::TURRET_SUMMONS:
		TurretSummonsStart();
		break;
	case BossState::DASH:
		DashStart();
		break;
	case BossState::DASH_END:
		DashEndStart();
		break;
	case BossState::TELEPORTIN_CEILING:
		TpInCeilingStart();
		break;
	case BossState::TELEPORTOUT_CEILING:
		TpOutCeilingStart();
		break;
	case BossState::TELEPORTIN_RIFLE:
		TpInRifleStart();
		break;
	case BossState::TELEPORTOUT_RIFLE:
		TpOutRifleStart();
		break;
	case BossState::TELEPORTIN_WALL:
		TpInWallStart();
		break;
	case BossState::JUMP_RIFLE:
		JumpRifleStart();
		break;
	case BossState::JUMP_RIFLE_LAND:
		JumpRifleLandStart();
		break;
	case BossState::MORIBUND:
		MoribundStart();
		break;
	case BossState::NOHEAD:
		NoHeadStart();
		break;
	case BossState::RECORDING_PROGRESS:
		RecordingProgressStart();
		break;
	case BossState::RUSH:
		RushStart();
		break;
	case BossState::RUSH_READY:
		RushReadyStart();
		break;
	case BossState::RUSH_END:
		RushEndStart();
		break;
	}

	// 이전 state의 end 
	switch (m_PrevState)
	{
	case BossState::INTRO:
		IntroEnd();
		break;
	case BossState::IDLE:
		IdleEnd();
		break;
	case BossState::RIFLE:
		RifleEnd();
		break;
	case BossState::GUN:
		GunEnd();
		break;
	case BossState::GUN_SHOT:
		GunShotEnd();
		break;
	case BossState::ROLL:
		RollEnd();
		break;
	case BossState::HURT:
		HurtEnd();
		break;
	case BossState::RECOVER:
		RecoverEnd();
		break;
	case BossState::TRANSPARENCY:
		TransparencyEnd();
		break;
	case BossState::REAPPEAR:
		ReAppearEnd();
		break;
	case BossState::CHANGEPHASE:
		ChangePhaseEnd();
		break;
	case BossState::JUMP:
		JumpEnd();
		break;
	case BossState::TELEPORTIN_SWEEP:
		TpSweepInEnd();
		break;
	case BossState::SWEEP:
		SweepEnd();
		break;
	case BossState::TELEPORTOUT_SWEEP:
		TpSweepOutEnd();
		break;
	case BossState::TURRET_SUMMONS:
		TurretSummonsEnd();
		break;
	case BossState::DASH:
		DashEnd();
		break;
	case BossState::DASH_END:
		DashEndEnd();
		break;
	case BossState::TELEPORTIN_CEILING:
		TpInCeilingEnd();
		break;
	case BossState::TELEPORTOUT_CEILING:
		TpOutCeilingEnd();
		break;
	case BossState::TELEPORTIN_RIFLE:
		TpInRifleEnd();
		break;
	case BossState::TELEPORTOUT_RIFLE:
		TpOutRifleEnd();
		break;
	case BossState::TELEPORTIN_WALL:
		TpInWallEnd();
		break;
	case BossState::JUMP_RIFLE:
		JumpRifleEnd();
		break;
	case BossState::JUMP_RIFLE_LAND:
		JumpRifleLandEnd();
		break;
	case BossState::MORIBUND:
		MoribundEnd();
		break;
	case BossState::NOHEAD:
		NoHeadEnd();
		break;
	case BossState::RECORDING_PROGRESS:
		RecordingProgressEnd();
		break;
	case BossState::RUSH:
		RushEnd();
		break;
	case BossState::RUSH_READY:
		RushReadyEnd();
		break;
	case BossState::RUSH_END:
		RushEndEnd();
		break;
	}
}

void Boss_HeadHunter::UpdateState(float _DeltaTime)
{
	// 현재 상태의 update 호출 
	switch (m_CurState)
	{
	case BossState::INTRO:
		IntroUpdate(_DeltaTime);
		break;
	case BossState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case BossState::RIFLE:
		RifleUpdate(_DeltaTime);
		break;
	case BossState::GUN:
		GunUpdate(_DeltaTime);
		break;
	case BossState::GUN_SHOT:
		GunShotUpdate(_DeltaTime);
		break;
	case BossState::ROLL:
		RollUpdate(_DeltaTime);
		break;
	case BossState::HURT:
		HurtUpdate(_DeltaTime);
		break;
	case BossState::RECOVER:
		RecoverUpdate(_DeltaTime);
		break;
	case BossState::TRANSPARENCY:
		TransparencyUpdate(_DeltaTime);
		break;
	case BossState::REAPPEAR:
		ReAppearUpdate(_DeltaTime);
		break;
	case BossState::CHANGEPHASE:
		ChangePhaseUpdate(_DeltaTime);
		break;
	case BossState::JUMP:
		JumpUpdate(_DeltaTime);
		break;
	case BossState::TELEPORTIN_SWEEP:
		TpSweepInUpdate(_DeltaTime);
		break;
	case BossState::SWEEP:
		SweepUpdate(_DeltaTime);
		break;
	case BossState::TELEPORTOUT_SWEEP:
		TpSweepOutUpdate(_DeltaTime);
		break;
	case BossState::TURRET_SUMMONS:
		TurretSummonsUpdate(_DeltaTime);
		break;
	case BossState::DASH:
		DashUpdate(_DeltaTime);
		break;
	case BossState::DASH_END:
		DashEndUpdate(_DeltaTime);
		break;
	case BossState::TELEPORTIN_CEILING:
		TpInCeilingUpdate(_DeltaTime);
		break;
	case BossState::TELEPORTOUT_CEILING:
		TpOutCeilingUpdate(_DeltaTime);
		break;
	case BossState::TELEPORTIN_RIFLE:
		TpInRifleUpdate(_DeltaTime);
		break;
	case BossState::TELEPORTOUT_RIFLE:
		TpOutRifleUpdate(_DeltaTime);
		break;
	case BossState::TELEPORTIN_WALL:
		TpInWallUpdate(_DeltaTime);
		break;
	case BossState::JUMP_RIFLE:
		JumpRifleUpdate(_DeltaTime);
		break;
	case BossState::JUMP_RIFLE_LAND:
		JumpRifleLandUpdate(_DeltaTime);
		break;
	case BossState::MORIBUND:
		MoribundUpdate(_DeltaTime);
		break;
	case BossState::NOHEAD:
		NoHeadUpdate(_DeltaTime);
		break;
	case BossState::RECORDING_PROGRESS:
		RecordingProgressUpdate(_DeltaTime);
		break;
	case BossState::RUSH:
		RushUpdate(_DeltaTime);
		break;
	case BossState::RUSH_READY:
		RushReadyUpdate(_DeltaTime);
		break;
	case BossState::RUSH_END:
		RushEndUpdate(_DeltaTime);
		break;
	}
}

// 리셋시 인트로로 초기화할지 생각좀.
void Boss_HeadHunter::IntroStart()
{
	m_Dir = false;
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_intro");
}

void Boss_HeadHunter::IntroUpdate(float _DeltaTime)
{
	if (m_MainRender->IsAnimationEnd())
	{
		ChangeState(BossState::IDLE);
		return;
	}
}

void Boss_HeadHunter::IntroEnd()
{
}

void Boss_HeadHunter::IdleStart()
{
	m_Collision->On();
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_idle");
}


void Boss_HeadHunter::IdleUpdate(float _DeltaTime)
{
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	ChangeDir();
	DirCheck();

	// 1페이즈 동작  
	// 1. 일반라이플패턴
	// 2. 점프라이플패턴 
	if (BossPhase::FIRST == m_CurPhase)
	{
		if (0.0f >= m_IdleDuration)
		{
			int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 1);

			if (0 == RandomValue)
			{
				ChangeState(BossState::RIFLE);
				return;
			}

			else if ((1 == RandomValue))
			{
				ChangeState(BossState::JUMP);
				return;
			}
		}
	}

	// 2페이즈 동작 
	if (BossPhase::SECOND == m_CurPhase)
	{
		if (0.0f >= m_IdleDuration)
		{
			int RandomValue = CreateRandomValue(4);
			switch (RandomValue)
			{
			case 1:
				ChangeState(BossState::TELEPORTIN_RIFLE);
				break;
			case 2:
				ChangeState(BossState::RIFLE);
				break;
			case 3:
				ChangeState(BossState::JUMP);
				break;
			case 4:
				ChangeState(BossState::RUSH_READY);
				break;
			}
			return;
		}
	}

	m_IdleDuration -= _DeltaTime;
}

void Boss_HeadHunter::IdleEnd()
{
	m_IdleDuration = 0.25f;
}

void Boss_HeadHunter::RifleStart()
{
	GameEngineSound::Play("headhunter_lockon.wav");
	// CreateRifleEffect();
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_takeout_rifle");
}

void Boss_HeadHunter::RifleUpdate(float _DeltaTime)
{
	CreateTrailEffect();
	// 애니메이션이 종료되었거나, 이펙트가 데스상태라면
	if (true == m_MainRender->IsAnimationEnd() && EffectState::DEATH == m_Effect.lock()->GetCurState())
	{
		if (BossPhase::FIRST == m_CurPhase)
		{
			m_Effect.lock() = nullptr;
			int RandomValue = CreateRandomValue(2);
			switch (RandomValue)
			{
			case 1:
				ChangeState(BossState::ROLL);
				break;
			case 2:
				ChangeState(BossState::TELEPORTIN_WALL);
				break;
			default:
			{
				MsgAssert("이상한 랜덤값이 반환 되었습니다. CreateRandomValue 함수를 확인하세요.");
				break;
			}
			}
			return;
		}


		if (BossPhase::SECOND == m_CurPhase)
		{
			m_Effect.lock() = nullptr;
			int RandomValue = CreateRandomValue(4);
			switch (RandomValue)
			{
			case 1:
				ChangeState(BossState::ROLL);
				break;
			case 2:
				ChangeState(BossState::TELEPORTIN_WALL);
				break;
			case 3:
				ChangeState(BossState::TELEPORTIN_CEILING);
				break;
			case 4:
				ChangeState(BossState::JUMP);
				break;
			default:
			{
				MsgAssert("이상한 랜덤값이 반환 되었습니다. CreateRandomValue 함수를 확인하세요.");
				break;
			}
			}
			return;
		}
	}
}

void Boss_HeadHunter::RifleEnd()
{
	if (nullptr != m_Effect.lock())
	{
		m_Effect.lock()->Death();
		m_Effect.lock() = nullptr;
	}
}

// -------------------- Gun 보류 ---------------------------
void Boss_HeadHunter::GunStart()
{
	m_MainRender->ChangeAnimation("headhunter_takeout_gun");
}

void Boss_HeadHunter::GunUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(BossState::GUN_SHOT);
		return;
	}
}

void Boss_HeadHunter::GunEnd()
{
}

void Boss_HeadHunter::GunShotStart()
{
	m_MainRender->ChangeAnimation("headhunter_gun_shot");

	m_GunShot_StandardPos = m_MainRender->GetTransform()->GetLocalPosition();
}

void Boss_HeadHunter::GunShotUpdate(float _DeltaTime)
{
	size_t CurFrame = m_MainRender->GetCurrentFrame();
	switch (CurFrame)
	{
	case 0:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos);
		break;
	case 1:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos + float4 { 4.0f, 0.0f });
		break;
	case 2:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos + float4 { 19.0f, 0.0f });
		break;
	case 3:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos + float4 { 19.0f, 2.0f });
		break;
	case 4:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos + float4 { 19.0f, 2.0f });
		break;
	case 5:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos + float4 { 5.0f, 2.0f });
		break;
	case 6:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos + float4 { 0.0f, 0.0f });
		break;
	case 7:
		m_MainRender->GetTransform()->SetLocalPosition(m_GunShot_StandardPos + float4 { 0.0f, 0.0f });
		break;
		//case 2:
		//	GetTransform()->SetWorldPosition(m_GunShot_StandardPos + float4{ -20.0f, 0.0f, 0.0f });
		//	break;
		//case 3:
		//	GetTransform()->SetWorldPosition(m_GunShot_StandardPos + float4{ -20.0f, 0.0f, 0.0f });
		//	break;
	}


	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(BossState::IDLE);
		return;
	}
}

void Boss_HeadHunter::GunShotEnd()
{
	m_MainRender->GetTransform()->SetLocalPosition(float4{ 0.0f, 42.0f });
}

// -------------------- Gun 보류 ---------------------------

void Boss_HeadHunter::RollStart()
{
	m_Collision->Off();
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_roll");
}

void Boss_HeadHunter::RollUpdate(float _DeltaTime)
{
	CreateTrailEffect();
	// 애니메이션 종료시 idle 
	if (true == m_MainRender->IsAnimationEnd())
	{
		int RandomValue = CreateRandomValue(2);
		switch (RandomValue)
		{
		case 1:
			ChangeState(BossState::IDLE);
			break;
		case 2:
			ChangeState(BossState::JUMP);
			break;
		}
		return;
	}

	// 진행방향이 오른쪽이라면 
	if (true == m_Dir)
	{
		m_NextTrans->AddLocalPosition(float4::Right * m_RollSpeed * _DeltaTime);
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + m_DebugPivot))
		{
			// 넥스트트랜스를 이동키시고, 이동한 위치가 흰색일때만 내가 이동한다.
			GetTransform()->AddLocalPosition(float4::Right * m_RollSpeed * _DeltaTime);
		}
	}

	else if (false == m_Dir)
	{
		m_NextTrans->AddLocalPosition(float4::Left * m_RollSpeed * _DeltaTime);
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_DebugPivot.x, m_DebugPivot.y }))
		{
			// 넥스트트랜스를 이동키시고, 이동한 위치가 흰색일때만 내가 이동한다.
			GetTransform()->AddLocalPosition(float4::Left * m_RollSpeed * _DeltaTime);
		}
	}
}

void Boss_HeadHunter::RollEnd()
{
	m_Collision->On();
}

void Boss_HeadHunter::HurtStart()
{
	// 시작할때 플레이어 위치x, 내위치 x를 비교, 방향을 정한다.
	ChangeDir();

	if (BossPhase::SECOND == m_CurPhase && 0 == m_Phase2_HitCount)
	{
		if (true == m_Dir)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}

		else if (false == m_Dir)
		{
			GetTransform()->SetLocalPositiveScaleX();
		}

		m_MainRender->ChangeAnimation("headhunter_death_land");
		return;
	}

	// 그게 아닐 경우 일반 히트애니메이션 
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_hurt");
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -10.0f });
}

void Boss_HeadHunter::HurtUpdate(float _DeltaTime)
{
	CreateTrailEffect();
	// 특정위치에 도달했다면 return 일단 그냥 리턴인데, 9번프레임이라면 
	if (1.0f <= m_Ratio)
	{
		if (true == m_MainRender->IsAnimationEnd())
		{
			// 2페이즈, 히트 카운트가 0 이라면 빈사상태로 변경
			if (BossPhase::SECOND == m_CurPhase && 0 == m_Phase2_HitCount)
			{
				// 여기서 찐데스 상태로 변경
				PixelCollider::PixelCol->GroundCheck(this);
				ChangeState(BossState::MORIBUND);
				return;
			}

			// 일반적인 경우 리커버 상태로 전환 
			PixelCollider::PixelCol->GroundCheck(this);
			ChangeState(BossState::RECOVER);
		}

		return;
	}

	m_Ratio += _DeltaTime / 0.5f;
	if (1.0f <= m_Ratio)
	{
		m_Ratio = 1.0f;
	}

	// 방향에 따라서
	if (true == m_Dir)
	{
		float4 MovePos = float4::Lerp(m_HitPos, m_MiddlePos, m_Ratio * 2.0f);
		float4 MovePos2 = float4::Lerp(m_MiddlePos, m_HitEndPos, m_Ratio);
		float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

		m_NextTrans->SetWorldPosition(MovePos3);
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_DebugPivot.x, m_DebugPivot.y }))
		{
			// 
			// 넥스트트랜스를 이동키시고, 이동한 위치가 흰색일때만 내가 이동한다.
			GetTransform()->SetWorldPosition(MovePos3);
		}

		// 만약 검은색  픽셀이라면 아래로만 이동시킨다. 
		// 만약 검은색  픽셀이라면 아래로만 이동시킨다. 
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_DebugPivot.x, m_DebugPivot.y }) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition()))
		{
			GetTransform()->AddLocalPosition(float4::Down * 20.0f * _DeltaTime);
		}
	}
	else if (false == m_Dir)
	{
		float4 MovePos = float4::Lerp(m_HitPos, m_MiddlePos, m_Ratio);
		float4 MovePos2 = float4::Lerp(m_MiddlePos, m_HitEndPos, m_Ratio);
		float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

		m_NextTrans->SetWorldPosition(MovePos3);
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + m_DebugPivot))
		{
			// 넥스트트랜스를 이동키시고, 이동한 위치가 흰색일때만 내가 이동한다.
			GetTransform()->SetWorldPosition(MovePos3);
		}

		// 만약 검은색  픽셀이라면 아래로만 이동시킨다. 
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + m_DebugPivot) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition()))
		{
			GetTransform()->AddLocalPosition(float4::Down * 20.0f * _DeltaTime);
		}
	}
}

void Boss_HeadHunter::HurtEnd()
{
	m_HitPos = {};
	m_HitEndPos = {};
	m_MainPos = {};
	m_Ratio = 0.0f;
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 10.0f });
}

void Boss_HeadHunter::RecoverStart()
{
	m_Collision->Off();
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -10.0f });
	m_MainRender->ChangeAnimation("headhunter_recover");
}

void Boss_HeadHunter::RecoverUpdate(float _DeltaTime)
{
	CreateTrailEffect();
	if (true == m_MainRender->IsAnimationEnd())
	{
		CreateTpEffect();
		ChangeState(BossState::TRANSPARENCY);
		return;
	}
}

void Boss_HeadHunter::RecoverEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 10.0f });
}

void Boss_HeadHunter::TransparencyStart()
{
	// 이때 충돌체를 off
	m_Collision->Off();
}

// 리커버 상태 종료시 무조건 투명상태, 
void Boss_HeadHunter::TransparencyUpdate(float _DeltaTime)
{
	if (BossPhase::FIRST == m_CurPhase)
	{
		if (false == m_Summons)
		{
			SummonsMonsters();
		}

		if (0 == m_Phase1_HitCount)
		{
			// 2페이즈 전환, 
			ChangeState(BossState::CHANGEPHASE);
			return;
		}

		// 4초 뒤에 재등장
		if (0.0f >= m_TransDuration)
		{
			int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
			GetTransform()->SetLocalPosition(m_SummonsPoss[RandomValue]);
			ChangeState(BossState::INTRO);
			return;
		}

		m_TransDuration -= _DeltaTime;
		return;
	}

	// 순간이동 후 2페이즈의 로직 
	if (BossPhase::SECOND == m_CurPhase)
	{
		if (4 == m_Phase2_HitCount)
		{
			GetTransform()->SetWorldPosition(m_TeleportPos);
			ChangeState(BossState::TURRET_SUMMONS);
			return;
		}

		if (4 != m_Phase2_HitCount)
		{
			int RandomValue = CreateRandomValue(3);
			switch (RandomValue)
			{
			case 1:
				CeilingPointShuffle();
				ChangeState(BossState::TELEPORTIN_CEILING);
				break;
			case 2:
			{
				float4 Pos = float4{ -250.0f, 112.0f };
				GetTransform()->SetWorldPosition(Pos);
				ChangeState(BossState::TELEPORTIN_SWEEP);
				break;
			}
			case 3:
				ChangeState(BossState::TELEPORTIN_RIFLE);
				break;
			}
			return;
		}
	}
}

void Boss_HeadHunter::TransparencyEnd()
{
	m_Collision->On();
	m_TransDuration = 3.0f;
}

void Boss_HeadHunter::ChangePhaseStart()
{
	m_MainRender->Off();
	m_Collision->Off();
}

void Boss_HeadHunter::ChangePhaseUpdate(float _DeltaTime)
{
	if (BossPhase::FIRST == m_CurPhase)
	{
		if (true == PlayerLiveCheck())
		{
			Player::MainPlayer->ChangeState(PlayerState::FORCEFALL);

			m_CurPhase = BossPhase::SECOND;
			return;
		}
	}

	if (BossPhase::FIRST == m_CurPhase && false == m_SetMine)
	{
		GameEngineSound::Play("sound_boss_huntressbomb_armed_01.wav");

		m_SetMine = true;
		m_Mines.reserve(m_MineCount);
		float4 MinePos = { -600.0f, -202.0f };
		float XPos = 0.0f;
		float LimitTime = 0.3f;
		for (size_t i = 0; i < m_MineCount; i++)
		{
			std::shared_ptr<Remote_Mine> Mine = GetLevel()->CreateActor<Remote_Mine>();
			Mine->GetTransform()->SetWorldPosition(float4{ MinePos.x + XPos, MinePos.y });

			Mine->AddTimeLimit(LimitTime);
			XPos += 60.0f;
			LimitTime += 0.1f;
			m_Mines.push_back(Mine);
		}
	}
}

void Boss_HeadHunter::ChangePhaseEnd()
{
	m_MainRender->On();
	m_Collision->On();
}

// 보류 
void Boss_HeadHunter::JumpStart()
{
	int RandomValue = CreateRandomValue(2);
	switch (RandomValue)
	{
	case 1:
		m_Dir = true;
		break;
	case 2:
		m_Dir = false;
		break;
	}

	m_Collision->Off();
	GameEngineSound::Play("sound_boss_huntress_jump_01.wav");
	m_JumpStartPos = GetTransform()->GetLocalPosition();
	m_MainRender->ChangeAnimation("headhunter_jump");
}

void Boss_HeadHunter::JumpUpdate(float _DeltaTime)
{
	CreateTrailEffect();

	m_Ratio += _DeltaTime / 0.5f;
	if (1.0f <= m_Ratio)
	{
		m_Ratio = 1.0f;
	}

	// 왼쪽벽일때의 로직
	if (true == m_Dir)
	{
		// 중간지점, 도착지점을 정해야함 
		float4 MiddlePos = float4{ -451.0f, -96.0f };
		float4 EndPos = m_TeleportLeftWallPos;

		float4 MovePos = float4::Lerp(m_JumpStartPos, MiddlePos, m_Ratio * 2.0f);
		float4 MovePos2 = float4::Lerp(MiddlePos, EndPos, m_Ratio);
		float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

		GetTransform()->SetWorldPosition(MovePos3);
		float4 Check = GetTransform()->GetWorldPosition();

		if (EndPos == GetTransform()->GetWorldPosition())
		{
			ChangeState(BossState::JUMP_RIFLE);
			return;
		}

		return;
	}

	// 우측벽 
	if (false == m_Dir)
	{
		// 중간지점, 도착지점을 정해야함 
		float4 MiddlePos = float4{ 451.0f, -96.0f };
		float4 EndPos = m_TeleportRightWallPos;

		float4 MovePos = float4::Lerp(m_JumpStartPos, MiddlePos, m_Ratio * 2.0f);
		float4 MovePos2 = float4::Lerp(MiddlePos, EndPos, m_Ratio);
		float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

		GetTransform()->SetWorldPosition(MovePos3);

		float4 Check = GetTransform()->GetWorldPosition();

		if (EndPos == GetTransform()->GetWorldPosition())
		{
			ChangeState(BossState::JUMP_RIFLE);
			return;
		}

		return;
	}

}

void Boss_HeadHunter::JumpEnd()
{
	m_Ratio = 0.0f;
	m_JumpStartPos = float4::Zero;
}

void Boss_HeadHunter::TpSweepInStart()
{
	if (true == m_IsDoubleSweep)
	{
		float4 Pos = float4{ -250.0f, 112.0f };
		int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 1);
		if (0 == RandomValue)
		{
			GetTransform()->SetWorldPosition(Pos + float4 { 120.0f, 0.0f});
		}

		else if (1 == RandomValue)
		{
			GetTransform()->SetWorldPosition(Pos + float4 { -120.0f, 0.0f });
		}
	}

	m_Dir = true;
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_teleportin_sweep");
}

void Boss_HeadHunter::TpSweepInUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(BossState::SWEEP);
		return;
	}
}

void Boss_HeadHunter::TpSweepInEnd()
{

}

void Boss_HeadHunter::SweepStart()
{
	m_SoundPlayer = GameEngineSound::Play("sound_boss_huntressbeam_circle_01.wav");
	m_SoundPlayer.SetPitch(1.0f);
	CreateSweepEffect();
	m_MainRender->ChangeAnimation("headhunter_sweep");
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 0.0f, -10.0f });
}

void Boss_HeadHunter::SweepUpdate(float _DeltaTime)
{
	CreateTrailEffect();
	if (true == m_MainRender->IsAnimationEnd())
	{
		if (nullptr != m_SweepEffect.lock())
		{
			// 얘를 죽이지않아야함 
			// 여기서 애니메이션이 종료되면, 

			m_SweepEffect.lock()->EffectDeath();
			// m_SweepEffect = nullptr;
		}

		if (2 == m_Phase2_HitCount || 1 == m_Phase2_HitCount)
		{
			if (false == m_IsDoubleSweep)
			{
				m_IsDoubleSweep = true;
				ChangeState(BossState::TELEPORTIN_SWEEP);
				return;
			}
		}
		ChangeState(BossState::TELEPORTOUT_SWEEP);
		return;
	}

	m_SweepEffect.lock()->GetTransform()->AddLocalRotation(float4{ 0.0f, 0.0f, -10.0f } *m_SweepRotSpeed * _DeltaTime);
}

// 스윕 이후 레이저 이펙트의 충돌체가 남아있긴한데 치트가 아니면 플레이어가 그 위치로 이동할 일이 없으니까
// 일단 그냥 냅둠 
void Boss_HeadHunter::SweepEnd()
{
	m_SoundPlayer.SetPitch(1.0f);
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 0.0f, 10.0f });
	/*if (nullptr != m_SweepEffect.lock())
	{
		m_SweepEffect.lock()->EffectDeath();
	}*/
}

void Boss_HeadHunter::TpSweepOutStart()
{
	m_MainRender->ChangeAnimation("headhunter_teleportout_sweep");
}

void Boss_HeadHunter::TpSweepOutUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		m_MainRender->Off();

		int RandomValue = CreateRandomValue(2);
		switch (RandomValue)
		{
		case 1:
			ChangeState(BossState::DASH);
			break;
		case 2:
			ChangeState(BossState::TELEPORTIN_RIFLE);
			break;
		}
		return;
	}
}

void Boss_HeadHunter::TpSweepOutEnd()
{
	// ?? 이게왜있지?? 
	if (BossState::TELEPORTIN_RIFLE != m_NextState)
	{
		if (nullptr != m_Effect.lock())
		{
			m_Effect.lock()->Death();
			m_Effect.lock() = nullptr;
		}
	}
	m_MainRender->On();
}

void Boss_HeadHunter::TurretSummonsStart()
{
	m_PhaseDuration = m_TurretSummons_Duration;
	CreateTurretWall();
}

// 얜냅둬 
void Boss_HeadHunter::TurretSummonsUpdate(float _DeltaTime)
{
	m_PhaseDuration -= _DeltaTime;
	if (0.0f >= m_PhaseDuration)
	{
		ChangeState(BossState::TELEPORTIN_SWEEP);
		return;
	}

	if (true == m_TurretWall.lock()->GetRender()->IsAnimationEnd() && false == m_IsTurretSummons)
	{
		m_IsTurretSummons = true;
		CreateTurret();
		return;
	}
}

void Boss_HeadHunter::TurretSummonsEnd()
{
	m_PhaseDuration = 0.0f;
}

void Boss_HeadHunter::DashStart()
{
	m_Collision->Off();
	if (BossState::TELEPORTOUT_SWEEP == m_PrevState)
	{
		ChangeDir();
		DirCheck();
	}
	m_MainRender->ChangeAnimation("headhunter_dash");
}

// 대시 종료시 ~~~ 
// 여기부터 다시 
void Boss_HeadHunter::DashUpdate(float _DeltaTime)
{
	CreateTrailEffect();
	if (true == m_MainRender->IsAnimationEnd())
	{
		GetTransform()->SetWorldPosition(m_DashPos);
		ChangeState(BossState::DASH_END);
	}
}

void Boss_HeadHunter::DashEnd()
{
	if (BossState::TELEPORTIN_RIFLE != m_CurState)
	{
		GetTransform()->SetWorldPosition(float4{ -68.0f, -264.0f });
	}
}

void Boss_HeadHunter::DashEndStart()
{
	m_Collision->On();
	GameEngineSound::Play("sound_boss_huntressknife_prep_01.wav");
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_dash_end_ground");
}

void Boss_HeadHunter::DashEndUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		int RandomValue = CreateRandomValue(3);
		switch (RandomValue)
		{
		case 1:
			ChangeState(BossState::IDLE);
			break;
		case 2:
			ChangeState(BossState::TELEPORTIN_RIFLE);
			break;
		case 3:
			ChangeState(BossState::JUMP);
			break;
		}

		return;
	}
}

void Boss_HeadHunter::DashEndEnd()
{

}

void Boss_HeadHunter::TpInCeilingStart()
{
	// 애니메이션 변경하고 
	m_MainRender->ChangeAnimation("headhunter_teleportin_ceiling");
	m_Dir = false;
	DirCheck();

	// 첫텔레포트라면 
	if (false == m_TpInStart)
	{
		GameEngineSound::Play("headhunter_lockon.wav");
		m_TpInStart = true;
		++m_TpCount;
		m_TpCeilingPos = m_vecCeilingPos[0];
		GetTransform()->SetWorldPosition(m_vecCeilingPos[0]);
		CreateRifleEffect();
		return;
	}

	if (1 == m_TpCount)
	{
		GameEngineSound::Play("headhunter_lockon.wav");
		++m_TpCount;
		GetTransform()->SetWorldPosition(m_vecCeilingPos[1]);
		CreateRifleEffect();
		return;
	}

	if (2 == m_TpCount)
	{
		GameEngineSound::Play("headhunter_lockon.wav");
		++m_TpCount;
		GetTransform()->SetWorldPosition(m_vecCeilingPos[2]);
		CreateRifleEffect();
		return;
	}

	if (3 == m_TpCount)
	{
		GameEngineSound::Play("headhunter_lockon.wav");
		++m_TpCount;
		GetTransform()->SetWorldPosition(m_vecCeilingPos[3]);
		CreateRifleEffect();
		return;
	}
}

void Boss_HeadHunter::TpInCeilingUpdate(float _DeltaTime)
{
	size_t check = m_MainRender->GetCurrentFrame();

	// 업데이트에서는 
	// 애니메이션이 종료 되었다면
	if (true == m_MainRender->IsAnimationEnd() || 3 <= check)
	{
		ChangeState(BossState::TELEPORTOUT_CEILING);
		return;
	}
}

void Boss_HeadHunter::TpInCeilingEnd()
{
}

void Boss_HeadHunter::TpOutCeilingStart()
{
	m_MainRender->ChangeAnimation("headhunter_teleportout_ceiling");
}

void Boss_HeadHunter::TpOutCeilingUpdate(float _DeltaTime)
{
	size_t FrameCheck = m_MainRender->GetCurrentFrame();
	if (true == m_MainRender->IsAnimationEnd())
	{
		if (4 == m_TpCount)
		{
			m_TpCount = 0;
			m_TpInStart = false;

			// 여기서 스윕을 하던지, 다시 한번더 텔레포트를 쓰던지 ㅇㅇ
			ChangeState(BossState::TELEPORTIN_SWEEP);
			return;
		}

		ChangeState(BossState::TELEPORTIN_CEILING);
		return;
	}
}

void Boss_HeadHunter::TpOutCeilingEnd()
{
}

void Boss_HeadHunter::TpInRifleStart()
{
	// 여기서 왼쪽아니면 오른쪽 위치로 세팅
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -7.0f });
	m_MainRender->ChangeAnimation("headhunter_teleportin_rifle_ground");
	GameEngineSound::Play("headhunter_lockon.wav");

	// 여기서 한번바꾸고 
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, 2);

	if (1 == RandomValue)
	{
		m_Dir = false;
		GetTransform()->SetWorldPosition(m_TpRifleRightPos);
		GetTransform()->SetLocalPositiveScaleX();
		CreateRifleEffect();
	}

	else if (2 == RandomValue)
	{
		m_Dir = true;
		GetTransform()->SetWorldPosition(m_TpRifleLeftPos);
		GetTransform()->SetLocalNegativeScaleX();
		CreateRifleEffect();
	}
}

void Boss_HeadHunter::TpInRifleUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		// 라이플 애니메이션이 끝나자마자 벽타기, 회전사격 상태로 전환 
		ChangeState(BossState::TELEPORTOUT_RIFLE);
		return;
	}
}

void Boss_HeadHunter::TpInRifleEnd()
{
	// 애니메이션이 끝났을때 죽이는게 아니라 여기서 죽임.
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 7.0f });
}

void Boss_HeadHunter::TpOutRifleStart()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -7.0f });
	m_MainRender->ChangeAnimation("headhunter_teleportout_rifle_ground");
}

void Boss_HeadHunter::TpOutRifleUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		if (BossPhase::FIRST == m_CurPhase)
		{
			ChangeState(BossState::TELEPORTIN_WALL);
			return;
		}

		if (BossPhase::SECOND == m_CurPhase)
		{
			int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 2);
			if (0 == RandomValue)
			{
				ChangeState(BossState::TELEPORTIN_WALL);
				return;
			}

			else if (1 == RandomValue)
			{
				ChangeState(BossState::TELEPORTIN_CEILING);
				return;
			}

			else if (2 == RandomValue)
			{
				ChangeState(BossState::JUMP);
				return;
			}
		}
	}
}

void Boss_HeadHunter::TpOutRifleEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 7.0f });
}

// 
void Boss_HeadHunter::TpInWallStart()
{
	m_Collision->Off();
	m_MainRender->ChangeAnimation("headhunter_teleportin_wall_idle");
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, 2);
	if (1 == RandomValue)
	{
		// 일단 왼쪽부터 
		m_Dir = false;

		GetTransform()->SetWorldPosition(m_TeleportRightWallPos);
		GetTransform()->SetLocalNegativeScaleX();
	}

	else if (2 == RandomValue)
	{
		m_Dir = true;


		GetTransform()->SetWorldPosition(m_TeleportLeftWallPos);
		GetTransform()->SetLocalPositiveScaleX();
	}
}

void Boss_HeadHunter::TpInWallUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		// 점프샷으로 전환 
		ChangeState(BossState::JUMP_RIFLE);
		return;
	}
}

void Boss_HeadHunter::TpInWallEnd()
{

}

void Boss_HeadHunter::JumpRifleStart()
{

	WallJumpSoundPlay();
	m_MainRender->ChangeAnimation("headhunter_jump_rifle");
	if (true == m_Dir)
	{
		// 왼쪽벽 
		GetTransform()->SetLocalPositiveScaleX();
	}

	else if (false == m_Dir)
	{
		// 오른쪽벽 
		GetTransform()->SetLocalNegativeScaleX();
	}

	m_Collision->Off();
}

void Boss_HeadHunter::JumpRifleUpdate(float _DeltaTime)
{
	CreateTrailEffect();
	// ??
	if (m_FireAngleCount == m_CurFireAngleCount)
	{
		m_CurFireAngleCount = 0;
		m_RotaitionFireTime = 0.008f;
		m_RotaitionFire = false;
		return;
	}

	if (m_CurFireAngleCount_Reverse == 0)
	{
		m_CurFireAngleCount_Reverse = m_FireAngleCount_Reverse;
		m_RotaitionFireTime = 0.008f;
		m_RotaitionFire = false;
		return;
	}

	if (1 == m_MainRender->GetCurrentFrame())
	{
		m_RotaitionFire = true;
	}

	// 이거 그대로 긁어다가 점프 
	m_Ratio += _DeltaTime;
	if (1.0f <= m_Ratio)
	{
		m_Ratio = 1.0f;
	}

	if (BossPhase::FIRST == m_CurPhase)
	{
		// 왼쪽벽일때의 로직
		if (true == m_Dir)
		{
			// 중간지점, 도착지점을 정해야함 
			float4 MiddlePos = float4{ -19.0f, 402.0f };
			float4 EndPos = float4{ 301.0f, -203.0f };

			float4 MovePos = float4::Lerp(m_TeleportLeftWallPos, MiddlePos, m_Ratio);
			float4 MovePos2 = float4::Lerp(MiddlePos, EndPos, m_Ratio);
			float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

			GetTransform()->SetWorldPosition(MovePos3);

			float4 Check = GetTransform()->GetWorldPosition();

			if (EndPos == GetTransform()->GetWorldPosition())
			{
				ChangeState(BossState::JUMP_RIFLE_LAND);
				return;
			}

			return;
		}

		// 우측벽 
		if (false == m_Dir)
		{
			// 중간지점, 도착지점을 정해야함 
			float4 MiddlePos = float4{ 19.0f, 402.0f };
			float4 EndPos = float4{ -301.0f, -203.0f };

			float4 MovePos = float4::Lerp(m_TeleportRightWallPos, MiddlePos, m_Ratio);
			float4 MovePos2 = float4::Lerp(MiddlePos, EndPos, m_Ratio);
			float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

			GetTransform()->SetWorldPosition(MovePos3);

			float4 Check = GetTransform()->GetWorldPosition();

			if (EndPos == GetTransform()->GetWorldPosition())
			{
				ChangeState(BossState::JUMP_RIFLE_LAND);
				return;
			}

			return;
		}
	}

	// 이게 2페이즈 로직
	if (BossPhase::SECOND == m_CurPhase)
	{
		// 왼쪽벽일때의 로직
		if (true == m_Dir)
		{
			// 중간지점, 도착지점을 정해야함 
			float4 MiddlePos = float4{ -19.0f, 402.0f };
			float4 EndPos = float4{ 301.0f, -263.0f };

			float4 MovePos = float4::Lerp(m_TeleportLeftWallPos, MiddlePos, m_Ratio);
			float4 MovePos2 = float4::Lerp(MiddlePos, EndPos, m_Ratio);
			float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

			GetTransform()->SetWorldPosition(MovePos3);

			float4 Check = GetTransform()->GetWorldPosition();

			if (EndPos == GetTransform()->GetWorldPosition())
			{
				ChangeState(BossState::JUMP_RIFLE_LAND);
				return;
			}

			return;
		}

		// 우측벽 
		if (false == m_Dir)
		{
			// 중간지점, 도착지점을 정해야함 
			float4 MiddlePos = float4{ 19.0f, 402.0f };
			float4 EndPos = float4{ -301.0f, -263.0f };

			float4 MovePos = float4::Lerp(m_TeleportRightWallPos, MiddlePos, m_Ratio);
			float4 MovePos2 = float4::Lerp(MiddlePos, EndPos, m_Ratio);
			float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

			GetTransform()->SetWorldPosition(MovePos3);

			float4 Check = GetTransform()->GetWorldPosition();

			if (EndPos == GetTransform()->GetWorldPosition())
			{
				ChangeState(BossState::JUMP_RIFLE_LAND);
				return;
			}

			return;
		}
	}

}

void Boss_HeadHunter::JumpRifleEnd()
{

	m_Ratio = 0.0f;
	m_CurFireAngleCount = 0;
	m_CurFireAngleCount_Reverse = m_FireAngleCount_Reverse;
	m_RotaitionFire = false;
}

void Boss_HeadHunter::JumpRifleLandStart()
{
	m_Collision->On();
	m_MainRender->ChangeAnimation("headhunter_jump_rifle_land");
}

void Boss_HeadHunter::JumpRifleLandUpdate(float _DeltaTime)
{
	CreateTrailEffect();

	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(BossState::IDLE);
		return;
	}
}

void Boss_HeadHunter::JumpRifleLandEnd()
{

}

void Boss_HeadHunter::MoribundStart()
{
	if (false == m_Collision->IsUpdate())
	{
		m_Collision->On();
	}

	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -35.0f });
	m_MainRender->ChangeAnimation("headhunter_moribund");

	ClubLevel_Boss_01* CurLevel = dynamic_cast<ClubLevel_Boss_01*>(GetReturnCastLevel());
	if (nullptr != CurLevel)
	{
		CurLevel->BGMOff();
	}
}

void Boss_HeadHunter::MoribundUpdate(float _DeltaTime)
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float4 MyPos = GetTransform()->GetLocalPosition();

	float4 MovePos = PlayerPos - MyPos;

	float X = MyPos.x - PlayerPos.x;
	if (abs(X) >= 10.0f)
	{
		// 만약 애니메이션 퍼즈상태라면 다시 off
		if (true == m_MainRender->IsPause())
		{
			m_MainRender->SetAnimPauseOff();
		}

		ChangeDir();
		DirCheck();
		GetTransform()->AddLocalPosition(MovePos.NormalizeReturn() * 2.0f * _DeltaTime);
	}

	else if (abs(X) < 10.0f)
	{
		m_MainRender->SetAnimPauseOn();
	}
}

void Boss_HeadHunter::MoribundEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 35.0f });
}

void Boss_HeadHunter::NoHeadStart()
{
	GameEngineSound::Play("sound_head_1.wav");
	m_Collision->Off();
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -42.0f });
	m_MainRender->ChangeAnimation("headhunter_nohead");
	m_NoHeadStatePos = GetTransform()->GetWorldPosition();
}

// 나중에 필요한거 있으면 
void Boss_HeadHunter::NoHeadUpdate(float _DeltaTime)
{
	size_t Size = m_MainRender->GetCurrentFrame();
	switch (Size)
	{
	case 0:
		GetTransform()->SetWorldPosition(m_NoHeadStatePos + float4 { 0.0f, 9.0f});
		break;
	case 1:
		GetTransform()->SetWorldPosition(m_NoHeadStatePos + float4 { 0.0f, 10.0f });
		break;
	case 2:
		GetTransform()->SetWorldPosition(m_NoHeadStatePos + float4 { 0.0f, 10.0f });
		break;
	case 3:
		GetTransform()->SetWorldPosition(m_NoHeadStatePos + float4 { 0.0f, 10.0f });
		break;
	case 4:
		GetTransform()->SetWorldPosition(m_NoHeadStatePos + float4 { 0.0f, 1.5f});
		break;
	case 5:
		GetTransform()->SetWorldPosition(m_NoHeadStatePos);
		break;
	default:
		break;
	}
}

void Boss_HeadHunter::NoHeadEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 42.0f });
	m_NoHeadStatePos = float4::Zero;
}

void Boss_HeadHunter::RecordingProgressStart()
{
}

void Boss_HeadHunter::RecordingProgressUpdate(float _DeltaTime)
{
	// 레코딩이 종료 되었다면 아이들로 전환. 
	if (true == m_Recording_Complete)
	{
		m_Recording_Complete = false;
		Reset();
		ChangeState(BossState::IDLE);
		return;
	}

	// 여기서 역재생을 수행하고, 
	Reverse(m_MainRender.get());
}

void Boss_HeadHunter::RecordingProgressEnd()
{
}

void Boss_HeadHunter::RushStart()
{
	// 이거 끝나면 대쉬엔드 그라운드 
	//m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -19.0f });
	m_MainRender->ChangeAnimation("headhunter_rush");

	m_OriginPos = GetTransform()->GetWorldPosition();
}

void Boss_HeadHunter::RushUpdate(float _DeltaTime)
{
	CreateTrailEffect();

	// 이때 플레이어와 충돌하면 데스상태로 만듬 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER, ColType::OBBBOX2D, ColType::OBBBOX2D);
	if (nullptr != Col)
	{
		PlaySupporter::MainSupporter->CameraShakeOn();
		Player::MainPlayer->ChangeState(PlayerState::EXPLOSION_DEATH);
		Player::MainPlayer->CreateExplosionEffect();
		return;
	}


	m_Ratio += _DeltaTime * m_RushRatio;
	if (1.0f <= m_Ratio)
	{
		m_Ratio = 1.0f;
		ChangeState(BossState::RUSH_END);
		return;
	}
	// 전방으로 돌진하는 로직 
	// 왼쪽벽일때의 로직
	if (true == m_Dir)
	{
		float4 EndPos = m_RightRush_EndPos;
		float4 MovePos = float4::Lerp(m_OriginPos, EndPos, m_Ratio);
		GetTransform()->SetWorldPosition(MovePos);
		float4 Check = GetTransform()->GetWorldPosition();
		return;
	}

	// 우측벽 
	if (false == m_Dir)
	{
		float4 EndPos = m_LeftRush_EndPos;
		float4 MovePos = float4::Lerp(m_OriginPos, EndPos, m_Ratio);
		GetTransform()->SetWorldPosition(MovePos);
		float4 Check = GetTransform()->GetWorldPosition();
		return;
	}

 	
}

void Boss_HeadHunter::RushEnd()
{
	//m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 19.0f });
	m_Ratio = 0.0f;

}


void Boss_HeadHunter::RushReadyStart()
{
	m_MainRender->ChangeAnimation("headhunter_rush_ready");
	m_OriginPos = GetTransform()->GetWorldPosition();
}


void Boss_HeadHunter::RushReadyUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(BossState::RUSH);
		return;
	}

	size_t CurFrame = m_MainRender->GetCurrentFrame();
	if (CurFrame >= 5)
	{
		GetTransform()->SetWorldPosition(m_OriginPos + float4{ 0.0f, -12.0f});
	}

	else if (CurFrame < 5)
	{
		GetTransform()->SetWorldPosition(m_OriginPos);
	}

	
}

void Boss_HeadHunter::RushReadyEnd()
{
	GetTransform()->SetWorldPosition(m_OriginPos);
	
}

void Boss_HeadHunter::RushEndStart()
{
	m_MainRender->ChangeAnimation("headhunter_dash_end_ground");
}

void Boss_HeadHunter::RushEndUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		m_OriginPos = float4::Zero;
		ChangeState(BossState::IDLE);
		return;
	}
}

void Boss_HeadHunter::RushEndEnd()
{
}

// 사실상 레벨체인지 해야되네 
void Boss_HeadHunter::ReAppearStart()
{
}

void Boss_HeadHunter::ReAppearUpdate(float _DeltaTime)
{
}

void Boss_HeadHunter::ReAppearEnd()
{
}