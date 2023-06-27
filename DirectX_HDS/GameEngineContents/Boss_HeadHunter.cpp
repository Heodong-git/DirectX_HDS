#include "PrecompileHeader.h"
#include "Boss_HeadHunter.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "PixelCollider.h"
#include "Player.h"

#include "HeadHunter_RifleEffect.h"
#include "TeleportEffect.h"
#include "GunSpark_Effect.h"

#include "Monster_Gangster.h"
#include "Monster_Grunt.h"
#include "Monster_Pomp.h"

#include "Remote_Mine.h"

#include "BaseLevel.h"

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

	// �ܼ��ϰ� ���� ��ȯ��ġ�� 1������ 4������ �־��ش�.
	m_SummonsPoss.reserve(4);

	float4 Gate1Pos = float4 { -453.0f, -203.0f};
	float4 Gate2Pos = float4 { -161.0f, -203.0f};
	float4 Gate3Pos = float4 { 180.0f, -203.0f};
	float4 Gate4Pos = float4 { 440.0f, -203.0f};

	m_SummonsPoss.push_back(Gate1Pos);
	m_SummonsPoss.push_back(Gate2Pos);
	m_SummonsPoss.push_back(Gate3Pos);
	m_SummonsPoss.push_back(Gate4Pos);
}

void Boss_HeadHunter::Update(float _DeltaTime)
{
	DebugUpdate();
	HurtCheck(_DeltaTime);

	if (true == m_Summons && false == m_SummonsEndCheck)
	{
		SummonsMonstersUpdate(_DeltaTime);
	}
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
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_jump").GetFullPath());

	}

	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_idle", .SpriteName = "headhunter_idle", .Start = 0, .End = 11 ,
									  .FrameInter = 0.09f , .Loop = true , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_intro", .SpriteName = "headhunter_intro", .Start = 0, .End = 2 ,
									  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_takeout_rifle", .SpriteName = "headhunter_takeout_rifle", .Start = 0, .End = 7 ,
								  .FrameInter = 0.055f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_roll", .SpriteName = "headhunter_roll", .Start = 0, .End = 6 ,
							  .FrameInter = 0.055f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_recover", .SpriteName = "headhunter_recover", .Start = 0, .End = 3 ,
							  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->CreateAnimation({ .AnimationName = "headhunter_jump", .SpriteName = "headhunter_jump", .Start = 0, .End = 2 ,
							  .FrameInter = 0.09f , .Loop = false , .ScaleToTexture = true });

	// 

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

void Boss_HeadHunter::CreateTpEffect()
{
	std::shared_ptr<TeleportEffect> Effect = GetLevel()->CreateActor<TeleportEffect>();
	Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

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
	GetTransform()->SetLocalPosition(GetInitPos());
	ChangeState(BossState::INTRO);

	// ����Ÿ�Կ����� first , second �� 
	if (LevelType::CLUBBOSS0 == GetReturnCastLevel()->GetLevelType())
	{
		m_CurPhase = BossPhase::FIRST;
		m_Phase1_HitCount = 3;
	}

	if (LevelType::CLUBBOSS1 == GetReturnCastLevel()->GetLevelType())
	{
		m_CurPhase = BossPhase::SECOND;
		m_Phase2_HitCount = 4;
	}

	m_IdleDuration = 0.25f;

	m_Summons = false;
	m_SummonsEndCheck = false;
	// m_SecondSummons = false;

	// �������� ���͵� �� ����ó��
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

	// ������ 0�� �ƴ϶�� ���� ������ �����Ǿ��ٴ� �ǹ��̰�, ������ ������ ���� ����ó���Ѵ�. 
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
}

void Boss_HeadHunter::HurtCheck(float _DeltaTime)
{
	// ���� �÷��̾��� ���ݰ� �浹�ߴٸ�.
	std::shared_ptr<GameEngineCollision> Player_AttCol = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Player_AttCol)
	{
		// ���� �÷��̾��� ���ݰ� �浹�ߴٸ� Hurt ���·� ��ȯ
		// 1. �浹�ߴٸ� �ٷ� �浹ü off,
		// 2. hurt state�� ��ȯ
		m_Collision->Off();

		if (LevelType::CLUBBOSS0 == GetReturnCastLevel()->GetLevelType())
		{
			--m_Phase1_HitCount;
		}

		if (LevelType::CLUBBOSS1 == GetReturnCastLevel()->GetLevelType())
		{
			--m_Phase2_HitCount;
		}
		// ���⼭ 

		// �÷��̾� x�� ���  
		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		float4 MyPos = GetTransform()->GetWorldPosition();
		m_HitPos = GetTransform()->GetLocalPosition();
		// �÷��̾�� �� ��ġ�� x���� ũ�ٸ� 
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

void Boss_HeadHunter::SummonsMonstersUpdate(float _DeltaTime)
{
	size_t DeathCount = 0;
	for (size_t i = 0; i < m_SummonsMonsters.size(); ++i)
	{
		// �ݺ��ؼ� ���鼭 isdeath �� true �� ��츦 üũ�Ѵ�. 
		if (true == m_SummonsMonsters[i]->DeathCheck())
		{
			++DeathCount;
		}
	}

	// �׸��� ����ī��Ʈ ���� ���� ���͸� On ������ 
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
		// ���Ⱑ pomp 
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
	// �÷��̾� x�� ���  
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();

	// �÷��̾�� �� ��ġ�� x���� ũ�ٸ� 
	if (PlayerPos.x <= MyPos.x)
	{
		m_Dir = false;
	}

	else if (PlayerPos.x > MyPos.x)
	{
		m_Dir = true;
	}
}

void Boss_HeadHunter::SummonsMonsters()
{
	
	// ��ȯ���¸� true�� ����
	m_Summons = true;

	// ���� 8���� �����ؼ� ������ ���� ������,
	m_SummonsMonsters.reserve(8);

	// �׷�Ʈ 
	std::shared_ptr<Monster_Grunt> Monster = GetLevel()->CreateActor<Monster_Grunt>();
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
	Monster->GetTransform()->SetLocalPosition(m_SummonsPoss[RandomValue]);
	Monster->ChangeState(GruntState::CHASE);
	m_SummonsMonsters.push_back(Monster->DynamicThis<BaseActor>());

	std::shared_ptr<Monster_Grunt> Monster2 = GetLevel()->CreateActor<Monster_Grunt>();
	// ������ġ
	int Value = RandomValue + 1;
	if (Value >= static_cast<int>(m_SummonsPoss.size()))
	{
		Value = 0;
	}

	Monster2->GetTransform()->SetLocalPosition(m_SummonsPoss[Value]);
	Monster2->ChangeState(GruntState::CHASE);
	m_SummonsMonsters.push_back(Monster2->DynamicThis<BaseActor>());

	// ������ 
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
	}

	// ���� state�� end 
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
	}
}

void Boss_HeadHunter::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
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
	}
}

// ������ ��������� ��Ʈ�η� ����, �����̵� �ִϸ��̼����� ���� 
void Boss_HeadHunter::IntroStart()
{
	// �̶� ����, �������°� ������¿��ٸ� ���������� �̾����Ű�.
	// ������ ��ġ�� �ٽ� ��Ÿ���� ��������. 

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


// ���̵���� ���Խ� ���ð��� �����, �� �ð��� �ʰ��ϰ� �Ǹ� �ٷ� RIPLE ���·� ����,
// �׳� 1�ʵڿ� 
// �ƴϸ� �ܼ��ϰ� �÷��̾�� �浹�ϰ� �Ǹ� �ٷ� �����û��·� ����. 
void Boss_HeadHunter::IdleStart()
{
	m_Collision->On();
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_idle");
}

void Boss_HeadHunter::IdleUpdate(float _DeltaTime)
{
	// ���� ����� 1������ �� ����� ����,  
	if (BossPhase::FIRST == m_CurPhase)
	{
		// �������°� ������¿��ٸ�, �ٷ� rifle ���·� ��ȯ 
		if (BossState::TRANSPARENCY == m_PrevState)
		{
			ChangeState(BossState::RIFLE);
			return;
		}

		if (0.0f >= m_IdleDuration)
		{
			// ���̵����ӽð��� 1�ʸ� ������� ��� ������ ���·� ����
			ChangeState(BossState::RIFLE);
			return;
		}

		// ���⼭ �ִϸ��̼��� ����Ǹ��� �ƴ϶�, �����ϰ� ������ ���·� ����
		if (true == m_MainRender->IsAnimationEnd())
		{
			ChangeState(BossState::RIFLE);
			return;
		}
	}

	if (BossPhase::SECOND == m_CurPhase)
	{
		// �������°� ������¿��ٸ�, �ٷ� rifle ���·� ��ȯ 
		if (BossState::TRANSPARENCY == m_PrevState)
		{
			ChangeState(BossState::RIFLE);
			return;
		}

		if (0.0f >= m_IdleDuration)
		{
			// ���̵����ӽð��� 1�ʸ� ������� ��� ������ ���·� ����
			ChangeState(BossState::RIFLE);
			return;
		}

		// ���⼭ �ִϸ��̼��� ����Ǹ��� �ƴ϶�, �����ϰ� ������ ���·� ����
		if (true == m_MainRender->IsAnimationEnd())
		{
			ChangeState(BossState::RIFLE);
			return;
		}
	}

	m_IdleDuration -= _DeltaTime;
	ChangeDir();
	DirCheck();
}

void Boss_HeadHunter::IdleEnd()
{
	m_IdleDuration = 0.25f;
}

void Boss_HeadHunter::RifleStart()
{
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_takeout_rifle");
}

// ������ �ִϸ��̼��� ����Ǹ� �ϴ� ����. 
void Boss_HeadHunter::RifleUpdate(float _DeltaTime)
{
	// ����Ʈ�� ���� 
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

	// ��������� �������̶�� 
	if (true == m_Dir)
	{
	
		m_NextTrans->AddLocalPosition(float4::Right * m_RollSpeed * _DeltaTime);
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + m_DebugPivot))
		{
			// �ؽ�ƮƮ������ �̵�Ű�ð�, �̵��� ��ġ�� ����϶��� ���� �̵��Ѵ�.
			GetTransform()->AddLocalPosition(float4::Right * m_RollSpeed * _DeltaTime);
		}
	}

	else if (false == m_Dir)
	{
		m_NextTrans->AddLocalPosition(float4::Left * m_RollSpeed * _DeltaTime);
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_DebugPivot.x, m_DebugPivot.y }))
		{
			// �ؽ�ƮƮ������ �̵�Ű�ð�, �̵��� ��ġ�� ����϶��� ���� �̵��Ѵ�.
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
	// �����Ҷ� �÷��̾� ��ġx, ����ġ x�� ��, ������ ���Ѵ�.
	ChangeDir();
	DirCheck();
	m_MainRender->ChangeAnimation("headhunter_hurt");
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -10.0f });
}

void Boss_HeadHunter::HurtUpdate(float _DeltaTime)
{
	// Ư����ġ�� �����ߴٸ� return �ϴ� �׳� �����ε�, 9���������̶�� 
	if (1.0f <= m_Ratio)
	{
		if (true == m_MainRender->IsAnimationEnd())
		{
			PixelCollider::PixelCol->GroundCheck(this);
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

	// ���⿡ ����
	if (true == m_Dir)
	{
		float4 MovePos = float4::Lerp(m_HitPos, m_MiddlePos, m_Ratio * 2.0f);
		float4 MovePos2 = float4::Lerp(m_MiddlePos, m_HitEndPos, m_Ratio);
		float4 MovePos3 = float4::Lerp(MovePos, MovePos2, m_Ratio);

		m_NextTrans->SetWorldPosition(MovePos3);
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_DebugPivot.x, m_DebugPivot.y }))
		{
			// 
			// �ؽ�ƮƮ������ �̵�Ű�ð�, �̵��� ��ġ�� ����϶��� ���� �̵��Ѵ�.
			GetTransform()->SetWorldPosition(MovePos3);
		}

		// ���� ������  �ȼ��̶�� �Ʒ��θ� �̵���Ų��. 
		// ���� ������  �ȼ��̶�� �Ʒ��θ� �̵���Ų��. 
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
			// �ؽ�ƮƮ������ �̵�Ű�ð�, �̵��� ��ġ�� ����϶��� ���� �̵��Ѵ�.
			GetTransform()->SetWorldPosition(MovePos3);
		}

		// ���� ������  �ȼ��̶�� �Ʒ��θ� �̵���Ų��. 
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + m_DebugPivot) && 
				 PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition()))
		{
			GetTransform()->AddLocalPosition(float4::Down * 20.0f * _DeltaTime);
		}
	}
}

void Boss_HeadHunter::HurtEnd()
{
	// �� ���°� ����� �� �浹ü�� on
	m_Collision->On();
	m_HitPos = {};
	m_HitEndPos = {};
	m_MainPos = {};
	m_Ratio = 0.0f;
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 10.0f });
}

void Boss_HeadHunter::RecoverStart()
{
	// �����Ҷ� �÷��̾� ��ġx, ����ġ x�� ��, ������ ���Ѵ�.
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -10.0f });
	m_MainRender->ChangeAnimation("headhunter_recover");
}

void Boss_HeadHunter::RecoverUpdate(float _DeltaTime)
{
	// �ڷ���Ʈ ����Ʈ�� �����ϰ� ���� ���⼭ ���̵��� �ƴ϶� ���� ���·� ����. 
	// ������¿����� ���ð� 3�ʸ� ������, ������ ��ġ�� �ٽ� �����Ѵ�? 
	if (true == m_MainRender->IsAnimationEnd())
	{
		CreateTpEffect();

		// ������� ���� ��� �ҰŴ� 
		ChangeState(BossState::TRANSPARENCY);
		return;
	}
}

void Boss_HeadHunter::RecoverEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 10.0f });
	// test
	// m_MainRender->Off();
}

// �ϴ� �������, ��������϶� �ð����� ������Ű��, 
// �����ð��� �ʰ��ϸ�
// ������ ��ġ�� ����� �ϵ��� 
// ��Ʈ�ο��� �������°� Ʈ���� ��¼�����ٸ�.. ���� ���� 
void Boss_HeadHunter::TransparencyStart()
{
	// �̶� �浹ü�� off
	m_Collision->Off();
}

// ���̺�� ���̺��� ������ �ϰ�, �������ʹ� ������� ���� �� ������state �� ������ �ǳ� 

// ������� �����ϸ� ���͸� �ѹ��� �� �����ΰ�, Off ����,
// �տ� ���� ���͵��� ������°� �ɶ����� ������Ʈ�� on, chase ���·� �����Ѵ�. �̰� �³� 
void Boss_HeadHunter::TransparencyUpdate(float _DeltaTime)
{
	if (BossPhase::FIRST == m_CurPhase)
	{
		if (0 == m_Phase1_HitCount)
		{
			// 2������ ��ȯ, 
			ChangeState(BossState::CHANGEPHASE);
			return;
		}

		// 4�� �ڿ� �����
		if (0.0f >= m_TransDuration)
		{
			int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
			GetTransform()->SetLocalPosition(m_SummonsPoss[RandomValue]);
			ChangeState(BossState::INTRO);
			return;
		}

		m_TransDuration -= _DeltaTime;
		// ���� 1������, ù��° ��ȯ�� ������� �ʾҴٸ�.
		if (false == m_Summons)
		{
			SummonsMonsters();
		}

		return;
	}

	// �����̵� �� 2�������� ���� 
	if (BossPhase::SECOND == m_CurPhase)
	{
		if (3 == m_Phase2_HitCount)
		{
			// �Ѵ�¾�����, ��������ž ��ȯ���� 
			return;
		}

		ChangeState(BossState::JUMP);
		return;
	}
	
	// ���� ���ӽð��� 4�ʰ� �����ٸ�, ��Ÿ�� ��ġ����, �� ��Ʈ�� ���·� ��ȯ 
}

void Boss_HeadHunter::TransparencyEnd()
{
	// ������� ����� �浹ü on 
	m_Collision->On();
	m_TransDuration = 3.0f;
}

void Boss_HeadHunter::ChangePhaseStart()
{
	// ���� ����ֵ� �������� ����
	m_Collision->Off();
}

// ���� �ð� ������ �̶�� ������ �־ �ǰ� �ȳ־ �ɰŰ��� 
void Boss_HeadHunter::ChangePhaseUpdate(float _DeltaTime)
{
	if (BossPhase::FIRST == m_CurPhase)
	{
		m_Mines.reserve(m_MineCount);
		float4 MinePos = { -600.0f, -202.0f};
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

		m_CurPhase = BossPhase::SECOND;
	}
}

void Boss_HeadHunter::ChangePhaseEnd()
{
	m_Collision->On();
}

// ������ �����ؾߵǳ�? 
// �浹ü�� �����, ���̵� ���³�, Ư�� ���¿��� �ǰݽÿ�
// ���浹ü�� �ش��ϴ� ����? 
void Boss_HeadHunter::JumpStart()
{
	m_MainRender->ChangeAnimation("headhunter_jump");
}

void Boss_HeadHunter::JumpUpdate(float _DeltaTime)
{
	int a = 0;
}

void Boss_HeadHunter::JumpEnd()
{
}

// ��ǻ� ����ü���� �ؾߵǳ� 
void Boss_HeadHunter::ReAppearStart()
{
}

void Boss_HeadHunter::ReAppearUpdate(float _DeltaTime)
{
}

void Boss_HeadHunter::ReAppearEnd()
{
}