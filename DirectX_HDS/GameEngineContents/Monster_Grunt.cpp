#include "PrecompileHeader.h"
#include "Monster_Grunt.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Player.h"

#include "SlashHit_Effect.h"

Monster_Grunt::Monster_Grunt()
{
}

Monster_Grunt::~Monster_Grunt()
{
}

void Monster_Grunt::Start()
{
	if (false == GameEngineInput::IsKey("Grunt_DebugSwitch"))
	{
		GameEngineInput::CreateKey("Grunt_DebugSwitch", 'Q');
	}

	// ���������� �� ����
	ComponentSetting();
	// ���ҽ� �ε�
	LoadAndCreateAnimation();

	ChangeState(GruntState::IDLE);
}

void Monster_Grunt::Update(float _DeltaTime)
{
	if (true == Player::MainPlayer->IsSkill())
	{
		m_MainRender->ColorOptionValue.MulColor.r = 0.2f;
		m_MainRender->ColorOptionValue.MulColor.g = 0.2f;
		m_MainRender->ColorOptionValue.MulColor.b = 0.3f;
	}
	else
	{
		m_MainRender->ColorOptionValue.MulColor.r = 1.0f;
		m_MainRender->ColorOptionValue.MulColor.g = 1.0f;
		m_MainRender->ColorOptionValue.MulColor.b = 1.0f;
	}

	DirCheck();

	// ���� �÷��̾��� ���ݰ� �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	// �浹�ߴٸ� �갡 nullptr �� �ƴҰŰ� 
	if (nullptr != Col)
	{
		// �浹�� �浹ü�� �θ�  �޾ƿ��� 
		GameEngineTransform* colobj = Col->GetTransform()->GetParent();
		// �̰� �����ؾ��ҵ� 
		std::shared_ptr<SlashHit_Effect> Effect = GetLevel()->CreateActor<SlashHit_Effect>(static_cast<int>(RenderOrder::EFFECT));
		float4 MyPos = GetTransform()->GetLocalPosition();
		Effect->GetTransform()->SetLocalPosition({ MyPos.x, MyPos.y + m_HitEffectPivot });

		m_Collision->Off();
		m_ChaseCollision->Off();

		// �����׾����ϱ� -1 
		GetReturnCastLevel()->DisCount();
		// ���º����� �����ִϸ��̼� 
		ChangeState(GruntState::HITGROUND);
	}

	UpdateState(_DeltaTime);
	DebugUpdate();
}

void Monster_Grunt::Render(float _DeltaTime)
{
}

void Monster_Grunt::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("gangster_debugswitch"))
	{
		DebugSwitch();

		if (nullptr != m_Collision)
		{
			if (true == m_Collision->IsDebug())
			{
				m_Collision->DebugOff();
			}

			else
			{
				m_Collision->DebugOn();
			}
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
}

void Monster_Grunt::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_MainRender->GetTransform()->SetLocalPosition({ 0, m_RenderPivot });
	m_MainRender->SetScaleRatio(2.0f);

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0.0f, m_ColPivot });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->DebugOff();

	m_ChaseCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHASE);
	m_ChaseCollision->GetTransform()->SetLocalScale(float4{ 200.0f, 0.5f });
	m_ChaseCollision->GetTransform()->SetLocalPosition({ 100.0f, m_ColPivot });
	m_ChaseCollision->SetColType(ColType::OBBBOX3D);
	m_ChaseCollision->DebugOff();

	// ����׷���
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale({ 4,  4 });
	m_DebugRender->Off();
}

void Monster_Grunt::LoadAndCreateAnimation()
{
	// ���⼭ �ʿ��� ���ҽ� �ε� �� �ִϸ��̼� �����
	{
		if (nullptr == GameEngineSprite::Find("grunt_idle"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("katanazero_resources");
			Dir.Move("katanazero_resources");
			Dir.Move("Texture");
			Dir.Move("ClubLevel");
			Dir.Move("grunt");

			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_idle").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_walk").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_hurtground").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_run").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_attack").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_turn").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_fall").GetFullPath());

			std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
		}
	}

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_idle", .SpriteName = "grunt_idle", .Start = 0, .End = 7 ,
								  .FrameInter = 0.12f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_attack", .SpriteName = "grunt_attack", .Start = 0, .End = 7 ,
							  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_fall", .SpriteName = "grunt_fall", .Start = 0, .End = 12 ,
							  .FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_hurtground", .SpriteName = "grunt_hurtground", .Start = 0, .End = 15 ,
							  .FrameInter = 0.10f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_run", .SpriteName = "grunt_run", .Start = 0, .End = 9 ,
							  .FrameInter = 0.06f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_turn", .SpriteName = "grunt_turn", .Start = 0, .End = 7 ,
							  .FrameInter = 0.08f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_walk", .SpriteName = "grunt_walk", .Start = 0, .End = 9 ,
							  .FrameInter = 0.08f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->ChangeAnimation("grunt_idle");
}

bool Monster_Grunt::ChaseRangeCheck()
{
	// �÷��̾�� ���� ü�̽��� �浹ü�� �浹�ߴ��� Ȯ�� 
	if (nullptr != m_ChaseCollision)
	{
		std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::PLAYER , ColType::OBBBOX3D, ColType::OBBBOX3D);
		if (nullptr != Col)
		{
			return true;
		}
	}

	return false;
}


void Monster_Grunt::Reset()
{
	// ���� �ʱ� ������ġ�� �̵�
	GetTransform()->SetLocalPosition(GetInitPos());
	ChangeState(GruntState::IDLE);
	if (false == m_Collision->IsUpdate())
	{
		m_Collision->On();
		m_ChaseCollision->On();
	}
	ResetDir();
}


void Monster_Grunt::DirCheck()
{
	// ����Ƽ��, �װ�Ƽ�� �Լ� ���ÿ� ������ �ƴ϶� ������ Ʈ�������� ����ؾ��� ���� 
	// ����üũ 
	// ������ 
	if (true == m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	// ���� 
	else if (false == m_Direction)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
}

// -------------------------------------------- State ----------------------------------------------------

void Monster_Grunt::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
	switch (m_CurState)
	{
	case GruntState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case GruntState::WALK:
		WalkUpdate(_DeltaTime);
		break;
	case GruntState::CHASE:
		ChaseUpdate(_DeltaTime);
		break;
	case GruntState::HITGROUND:
		HitGroundUpdate(_DeltaTime);
		break;
	case GruntState::FALL:
		FallUpdate(_DeltaTime);
		break;
	case GruntState::TURN:
		TurnUpdate(_DeltaTime);
		break;
	case GruntState::ATTACK:
		AttackUpdate(_DeltaTime);
		break;
	}
}

// state ����, ����� ������ start, ���� ������ end ����
void Monster_Grunt::ChangeState(GruntState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	switch (m_NextState)
	{
	case GruntState::IDLE:
		IdleStart();
		break;
	case GruntState::WALK:
		WalkStart();
		break;
	case GruntState::CHASE:
		ChaseStart();
		break;
	case GruntState::HITGROUND:
		HitGroundStart();
		break;
	case GruntState::FALL:
		FallStart();
		break;
	case GruntState::TURN:
		TurnStart();
		break;
	case GruntState::ATTACK:
		AttackStart();
		break;
	}

	// ���� state�� end 
	switch (m_PrevState)
	{
	case GruntState::IDLE:
		IdleEnd();
		break;
	case GruntState::WALK:
		WalkEnd();
		break;
	case GruntState::CHASE:
		ChaseEnd();
		break;
	case GruntState::HITGROUND:
		HitGroundEnd();
		break;
	case GruntState::FALL:
		FallEnd();
		break;
	case GruntState::TURN:
		TurnEnd();
		break;
	case GruntState::ATTACK:
		AttackEnd();
		break;
	}
}


void Monster_Grunt::IdleStart()
{
	m_MainRender->ChangeAnimation("grunt_idle");
}

void Monster_Grunt::IdleUpdate(float _DeltaTime)
{
	if (true == ChaseRangeCheck())
	{
		ChangeState(GruntState::CHASE);
		return;
	}

	// �����ð��� 2�ʰ� �Ѿ��ٸ� 
	if (3.0f <= GetLiveTime())
	{
		ChangeState(GruntState::WALK);
		return;
	}
}

void Monster_Grunt::IdleEnd()
{
}

void Monster_Grunt::WalkStart()
{
	m_MainRender->ChangeAnimation("grunt_walk");

	// ���⼭ ���ʿ������� �����ϰ� ���� 
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1,2);

	if (1 == RandomValue)
	{
		m_Direction = true;
	}

	else if (2 == RandomValue)
	{
		m_Direction = false;
	}
}

void Monster_Grunt::WalkUpdate(float _DeltaTime)
{
	if (true == ChaseRangeCheck())
	{
		ChangeState(GruntState::CHASE);
		return;
	}

	// �̶� ��Ƽ���̳�, ���� �浹�ߴٸ� ���� ��������� �����Ѵ�. 
	if (true == m_Direction)
	{
		GetTransform()->AddLocalPosition(float4::Right * m_WalkMoveSpeed * _DeltaTime);
		return;
	}

	else if (false == m_Direction)
	{
		GetTransform()->AddLocalPosition(float4::Left * m_WalkMoveSpeed * _DeltaTime);
		return;
	}
}

void Monster_Grunt::WalkEnd()
{
}

void Monster_Grunt::ChaseStart()
{
	DirCheck();
	m_MainRender->ChangeAnimation("grunt_run");
}

void Monster_Grunt::ChaseUpdate(float _DeltaTime)
{
	// �̷��� �Ѿư��ٰ� �÷��̾ ���� �� �� ������ �Ǹ� ���� ������Ʈ�� ��ȯ 
	// �ϴ� �Ѿư��� 
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();
	float4 MoveDir = PlayerPos - MyPos;

	// �̶� x ���� ������ ũ�ٸ�
	if (PlayerPos.x > MyPos.x)
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();

	}
	else if (PlayerPos.x <= MyPos.x)
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
	}

	// ����, �÷��̾ ���ݹ��� �ȿ� �ִٸ� Attack State �� ����

	MoveDir.y = 0.0f;
	MoveDir.Normalize();
	GetTransform()->AddWorldPosition(MoveDir * m_ChaseMoveSpeed * _DeltaTime);
}

void Monster_Grunt::ChaseEnd()
{
}

void Monster_Grunt::HitGroundStart()
{
	DirCheck();
	m_MainRender->ChangeAnimation("grunt_hurtground");
}

void Monster_Grunt::HitGroundUpdate(float _DeltaTime)
{
}

void Monster_Grunt::HitGroundEnd()
{
}

void Monster_Grunt::AttackStart()
{
}

void Monster_Grunt::AttackUpdate(float _DeltaTime)
{
}

void Monster_Grunt::AttackEnd()
{
}

void Monster_Grunt::TurnStart()
{
}

void Monster_Grunt::TurnUpdate(float _DeltaTime)
{
}

void Monster_Grunt::TurnEnd()
{
}

void Monster_Grunt::FallStart()
{
}

void Monster_Grunt::FallUpdate(float _DeltaTime)
{
}

void Monster_Grunt::FallEnd()
{
}
