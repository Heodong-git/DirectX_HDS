#include "PrecompileHeader.h"
#include "Boss_HeadHunter.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "HeadHunter_RifleEffect.h"

#include "PixelCollider.h"
#include "Player.h"
#include "TeleportEffect.h"
#include "GunSpark_Effect.h"

Boss_HeadHunter::Boss_HeadHunter()
{
}

Boss_HeadHunter::~Boss_HeadHunter()
{
}

void Boss_HeadHunter::Start()
{
	ComponentSetting();
	LoadAndCreateAnimation();

	ChangeState(BossState::INTRO);
}

void Boss_HeadHunter::Update(float _DeltaTime)
{
	DebugUpdate();
	HurtCheck(_DeltaTime);
	NextTransUpdate();
	UpdateState(_DeltaTime);
}

void Boss_HeadHunter::Render(float _DeltaTime)
{
}

void Boss_HeadHunter::NextTransUpdate()
{
	m_NextTrans->SetLocalPosition(GetTransform()->GetWorldPosition());
}

void Boss_HeadHunter::ComponentSetting()
{
	m_NextTrans = std::make_shared<GameEngineTransform>();

	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BOSS);
	m_MainRender->GetTransform()->SetLocalPosition(float4{ 0.0f, 42.0f });

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BOSS);
	m_Collision->GetTransform()->SetLocalPosition(float4{ 0.0f, 37.0f });
	m_Collision->GetTransform()->SetLocalScale(float4{ 30.0f, 75.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);

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
		
	}

	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_idle", .SpriteName = "headhunter_idle", .Start = 0, .End = 11 ,
									  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_intro", .SpriteName = "headhunter_intro", .Start = 0, .End = 2 ,
									  .FrameInter = 0.08f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_takeout_rifle", .SpriteName = "headhunter_takeout_rifle", .Start = 0, .End = 7 ,
								  .FrameInter = 0.055f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_roll", .SpriteName = "headhunter_roll", .Start = 0, .End = 6 ,
							  .FrameInter = 0.055f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_recover", .SpriteName = "headhunter_recover", .Start = 0, .End = 3 ,
							  .FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });

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
	
	m_MainRender->SetAnimationStartEvent("headhunter_takeout_rifle", static_cast<size_t>(5), std::bind(&Boss_HeadHunter::CreateRifleEffect, this));
	m_MainRender->ChangeAnimation("headhunter_idle");
	m_MainRender->SetScaleRatio(2.0f);
}

void Boss_HeadHunter::LoadSound()
{
}

void Boss_HeadHunter::CreateRifleEffect()
{
	float4 MyPos = GetTransform()->GetLocalPosition();
	m_Effect = GetLevel()->CreateActor<HeadHunter_RifleEffect>();
	m_Effect->SetActor(DynamicThis<Boss_HeadHunter>());
	if (true == m_Dir)
	{
		m_Effect->GetTransform()->SetLocalPosition(MyPos + float4{ m_RifleEffectPivot.x , m_RifleEffectPivot.y });
	}
	
	else if (false == m_Dir)
	{
		m_Effect->GetTransform()->SetLocalPosition(MyPos + float4{ -m_RifleEffectPivot.x, m_RifleEffectPivot.y});
	}
}

void Boss_HeadHunter::Reset()
{
	GetTransform()->SetLocalPosition(GetInitPos());
	ChangeState(BossState::INTRO);
	m_HitCount = 9;
}

void Boss_HeadHunter::HurtCheck(float _DeltaTime)
{
	// 내가 플레이어의 공격과 충돌했다면.
	std::shared_ptr<GameEngineCollision> Player_AttCol = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Player_AttCol)
	{
		// 내가 플레이어의 공격과 충돌했다면 Hurt 상태로 전환
		// 1. 충돌했다면 바로 충돌체 off,
		// 2. hurt state로 전환
		m_Collision->Off();
		--m_HitCount;

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
		

		m_MiddlePos = m_HitPos + float4{ (m_HitEndPos.x - m_HitPos.x) / 2.0f , 25.0f };
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
	case BossState::ROLL:
		RollStart();
		break;
	case BossState::HURT:
		HurtStart();
		break;
	case BossState::RECOVER:
		RecoverStart();
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
	case BossState::ROLL:
		RollEnd();
		break;
	case BossState::HURT:
		HurtEnd();
		break;
	case BossState::RECOVER:
		RecoverEnd();
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
	case BossState::ROLL:
		RollUpdate(_DeltaTime);
		break;
	case BossState::HURT:
		HurtUpdate(_DeltaTime);
		break;
	case BossState::RECOVER:
		RecoverUpdate(_DeltaTime);
		break;
	}
}

// 보스가 만들어지면 인트로로 진입, 순간이동 애니메이션으로 등장 
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
	// 현재 페이즈가 1페이즈 일 경우의 동작,  
	if (BossPhase::FIRST == m_CurPhase)
	{
		if (true == m_MainRender->IsAnimationEnd())
		{
			ChangeState(BossState::RIFLE);
			return;
		}
		// 아이들일 경우 랜덤한 스테이트로 변경하도록.
	/*	int RandomStateValue = GameEngineRandom::MainRandom.RandomInt(static_cast<int>(BossState::RIFLE), static_cast<int>(BossState::MAX) - 1);
		ChangeState(static_cast<BossState>(RandomStateValue));
		ChangeState(BossState::RIFLE);*/
		return;
	}

	ChangeDir();
	DirCheck();
}

void Boss_HeadHunter::IdleEnd()
{
}

void Boss_HeadHunter::RifleStart()
{
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_takeout_rifle");
}

// 라이플 애니메이션이 종료되면 일단 퍼즈. 
void Boss_HeadHunter::RifleUpdate(float _DeltaTime)
{
	// 이펙트가 제거 
	if (true == m_MainRender->IsAnimationEnd() && true == m_Effect->IsDeath())
	{ 
		m_Effect = nullptr;
		ChangeState(BossState::ROLL);
		return;
	}
}

void Boss_HeadHunter::RifleEnd()
{
}

void Boss_HeadHunter::GunStart()
{
}

void Boss_HeadHunter::GunUpdate(float _DeltaTime)
{
}

void Boss_HeadHunter::GunEnd()
{
}

void Boss_HeadHunter::RollStart()
{
	m_Collision->Off();
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_roll");
}

void Boss_HeadHunter::RollUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(BossState::IDLE);
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
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_hurt");
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -10.0f });
}

void Boss_HeadHunter::HurtUpdate(float _DeltaTime)
{
	// 특정위치에 도달했다면 return 일단 그냥 리턴인데, 9번프레임이라면 
	if (1.0f <= m_Ratio)
	{
		if (true == m_MainRender->IsAnimationEnd())
		{
			ChangeState(BossState::RECOVER);
			return;
		}
		
		return;
	}

	m_Ratio += _DeltaTime / 0.5f ;
	if (1.0f <= m_Ratio)
	{
		m_Ratio = 1.0f;
	}

	// 방향에 따라서.
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
	}
}

void Boss_HeadHunter::HurtEnd()
{
	// 이 상태가 종료될 때 충돌체를 on
	m_Collision->On();
	m_HitPos = {};
	m_HitEndPos = {};
	m_MainPos = {};
	m_Ratio = 0.0f;
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 10.0f });
}

void Boss_HeadHunter::RecoverStart()
{
	// 시작할때 플레이어 위치x, 내위치 x를 비교, 방향을 정한다.
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -10.0f });
	m_MainRender->ChangeAnimation("headhunter_recover");
}

void Boss_HeadHunter::RecoverUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		std::shared_ptr<TeleportEffect> Effect = GetLevel()->CreateActor<TeleportEffect>();
		Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		ChangeState(BossState::IDLE);
		return;
	}
}

void Boss_HeadHunter::RecoverEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 10.0f });
}
