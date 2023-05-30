#include "PrecompileHeader.h"
#include "Monster_Gangster.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"

#include "Player.h"

Monster_Gangster::Monster_Gangster()
{
}

Monster_Gangster::~Monster_Gangster()
{
}

void Monster_Gangster::Start()
{
	if (false == GameEngineInput::IsKey("gangster_DebugSwitch"))
	{
		GameEngineInput::CreateKey("gangster_DebugSwitch", 'Q');
	}
	// ���������� �� ����
	ComponentSetting();
	// ���ҽ� �ε�
	LoadAndCreateAnimation();

	// aim ������Ʈ�� ����Ǹ� ����Ȯ���ؼ� �̹�������������� ������ �ϴ� ���
	// m_GunRender->SetTexture("gangster_gun_left.png");

	ChangeState(GangsterState::IDLE);
}

void Monster_Gangster::Update(float _DeltaTime)
{
	// ���� �÷��̾��� ���ݰ� �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	// ������ ���Դٴ°� �浹�ߴٴ°Ű� 
	// �׷� �浹�� ���͸� ������Ű�� �������� ȣ�� 
	if (nullptr != Col)
	{
		// ���� �浹ü�� off
		// �ִϸ��̼� ������ �����ִϸ��̼�������ȯ 
		m_Collision->Off();
		
		// �����׾����ϱ� -1 
		GetReturnCastLevel()->DisCount();
		ChangeState(GangsterState::HITGROUND);
	}

	UpdateState(_DeltaTime);
	DebugUpdate();
}

void Monster_Gangster::Render(float _DeltaTime)
{
}

void Monster_Gangster::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("gangster_debugswitch"))
	{
		DebugSwitch();
	}

	if (true == IsDebug())
	{
		m_DebugRender->On();
	}

	else if (false == IsDebug())
	{
		m_DebugRender->Off();
	}
}

void Monster_Gangster::ComponentSetting()
{
	float4 MyPos = GetTransform()->GetLocalPosition();
	
	// ������, �浹ü ����
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f , 38.0f});
	// m_MainRender->GetTransform()->SetLocalScale({ 200.0f , 200.0f });
	m_MainRender->SetScaleRatio(2.0f);

	// �ѷ��� ���� �Ѥ� ��.. �̹�����������  
	m_GunRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	// �Ǻ��߰��ؾ��� 
	m_GunRender->GetTransform()->SetLocalPosition(MyPos);
	m_GunRender->GetTransform()->SetLocalScale({ 54.0f , 12.0f });
	m_GunRender->Off();

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
	m_Collision->GetTransform()->SetLocalScale({ 50.0f, 50.0f });
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, 50.0f });

	// ����׷��� ����
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale({ 4, 4 });
}

void Monster_Gangster::LoadAndCreateAnimation()
{
	// ���⼭ �ʿ��� ���ҽ� �ε� �� �ִϸ��̼� �����
	{
		if (nullptr == GameEngineSprite::Find("gangster_idle"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("katanazero_resources");
			Dir.Move("katanazero_resources");
			Dir.Move("Texture");
			Dir.Move("ClubLevel");
			Dir.Move("gangster");
			
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_idle").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_walk").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_hitground").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_run").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_turn").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_gun").GetFullPath());

			std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
		}
	}
	
	m_MainRender->CreateAnimation({ .AnimationName = "gangster_idle", .SpriteName = "gangster_idle", .Start = 0, .End = 7 ,
								  .FrameInter = 0.12f , .Loop = true , .ScaleToTexture = true});

	m_MainRender->CreateAnimation({ .AnimationName = "gangster_walk", .SpriteName = "gangster_walk", .Start = 0, .End = 7 ,
								  .FrameInter = 0.1f , .Loop = true ,.ScaleToTexture = true });
	
	m_MainRender->CreateAnimation({ .AnimationName = "gangster_hitground", .SpriteName = "gangster_hitground", .Start = 0, .End = 13 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "gangster_run", .SpriteName = "gangster_run", .Start = 0, .End = 9 ,
								  .FrameInter = 0.065f , .Loop = true ,.ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "gangster_turn", .SpriteName = "gangster_turn", .Start = 0, .End = 5 ,
								  .FrameInter = 0.09f , .Loop = true ,.ScaleToTexture = true });

	m_MainRender->ChangeAnimation("gangster_idle");
}

void Monster_Gangster::Reset()
{
	// ���� �ʱ� ������ġ�� �̵�
	GetTransform()->SetLocalPosition(GetInitPos());
	if (false == m_Collision->IsUpdate())
	{
		m_Collision->On();
	}
	ChangeState(GangsterState::IDLE);
	ResetDir();
}

void Monster_Gangster::DirCheck()
{
	// ����Ƽ��, �װ�Ƽ�� �Լ� ���ÿ� ������ �ƴ϶� ������ Ʈ�������� ����ؾ��� ���� 
	// ����üũ 
	// ������ 
	if (0 < m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	// ���� 
	else if (0 > m_Direction)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
}

// -------------------------------------------- State ----------------------------------------------------

void Monster_Gangster::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
	switch (m_CurState)
	{
	case GangsterState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case GangsterState::WALK:
		WalkUpdate(_DeltaTime);
		break;
	case GangsterState::CHASE:
		ChaseUpdate(_DeltaTime);
		break;
	case GangsterState::HITGROUND:
		HitGroundUpdate(_DeltaTime);
		break;
	case GangsterState::AIM:
		AimUpdate(_DeltaTime);
		break;
	}
}


// state ����, ����� ������ start, ���� ������ end ����
void Monster_Gangster::ChangeState(GangsterState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	//WALK,	 // �ȱ�
	//	CHASE,	 // �ٱ� 
	//	HIT,	 // �ĸ���
	//	AIM,	 // ���� 
	
	// start 
	switch (m_NextState)
	{
	case GangsterState::IDLE:
		IdleStart();
		break;
	case GangsterState::WALK:
		WalkStart();
		break;
	case GangsterState::CHASE:
		ChaseStart();
		break;
	case GangsterState::HITGROUND:
		HitGroundStart();
		break;
	case GangsterState::AIM:
		AimStart();
		break;
	}

	// ���� state�� end 
	switch (m_PrevState)
	{
	case GangsterState::IDLE:
		IdleEnd();
		break;
	case GangsterState::WALK:
		WalkEnd();
		break;
	case GangsterState::CHASE:
		ChaseEnd();
		break;
	case GangsterState::HITGROUND:
		HitGroundEnd();
		break;
	case GangsterState::AIM:
		AimEnd();
		break;
	}
}

void Monster_Gangster::IdleStart()
{
	m_MainRender->GetTransform()->AddLocalPosition({ 0.0f , 10.f });
	m_MainRender->ChangeAnimation("gangster_idle");
	DirCheck();
}

void Monster_Gangster::IdleUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(GangsterState::WALK);
		return;
	}

	DirCheck();
}

void Monster_Gangster::IdleEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition({ 0.0f , -10.f });
}

void Monster_Gangster::WalkStart()
{
	m_MainRender->ChangeAnimation("gangster_run");
	DirCheck();
}

void Monster_Gangster::WalkUpdate(float _DeltaTime)
{
	DirCheck();
	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(GangsterState::IDLE);
		return;
	}

}

void Monster_Gangster::WalkEnd()
{
}

void Monster_Gangster::ChaseStart()
{
}

void Monster_Gangster::ChaseUpdate(float _DeltaTime)
{
}

void Monster_Gangster::ChaseEnd()
{
}

void Monster_Gangster::AimStart()
{
}

void Monster_Gangster::AimUpdate(float _DeltaTime)
{
}

void Monster_Gangster::AimEnd()
{
}

void Monster_Gangster::TurnStart()
{
}

void Monster_Gangster::TurnUpdate(float _DeltaTime)
{
}

void Monster_Gangster::TurnEnd()
{
}

void Monster_Gangster::HitGroundStart()
{
	DirCheck();
	m_MainRender->ChangeAnimation("gangster_hitground");
}

void Monster_Gangster::HitGroundUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		int a = 0;
	}
}

void Monster_Gangster::HitGroundEnd()
{
}
