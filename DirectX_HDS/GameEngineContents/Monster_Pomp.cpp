#include "PrecompileHeader.h"
#include "Monster_Pomp.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"

#include "Player.h"
#include "SlashHit_Effect.h"
#include "IronDoor.h"
#include "EnemyFollow_Effect.h"

Monster_Pomp::Monster_Pomp()
{
}

Monster_Pomp::~Monster_Pomp()
{
}

void Monster_Pomp::Start()
{
	if (false == GameEngineInput::IsKey("Pomp_DebugSwitch"))
	{
		GameEngineInput::CreateKey("Pomp_DebugSwitch", 'Q');
	}

	// ���������� �� ����
	ComponentSetting();
	// ���ҽ� �ε�
	LoadAndCreateAnimation();

	ChangeState(PompState::IDLE);
}

void Monster_Pomp::Update(float _DeltaTime)
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
	DebugUpdate();
	DoorOpenCheck();
	UpdateState(_DeltaTime);
	ParryingCheck();
	DeathCheck();
}

void Monster_Pomp::Render(float _DeltaTime)
{
}

void Monster_Pomp::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("Pomp_DebugSwitch"))
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

void Monster_Pomp::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::MONSTER));
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f, m_RenderPivot });
	m_MainRender->SetScaleRatio(2.0f);

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::MONSTER));
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, m_ColPivot });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->DebugOff();

	m_ChaseCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHASE);
	m_ChaseCollision->GetTransform()->SetLocalScale(float4{ 250.0f, 80.0f });
	m_ChaseCollision->GetTransform()->SetLocalPosition({ 100.0f, m_ColPivot });
	m_ChaseCollision->SetColType(ColType::OBBBOX3D);
	m_ChaseCollision->DebugOff();

	m_AttCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_ATTACK);
	m_AttCollision->GetTransform()->SetLocalScale(float4{ 25.0f, 70.0f });
	m_AttCollision->GetTransform()->SetLocalPosition({ 0.0f, m_ColPivot });
	m_AttCollision->SetColType(ColType::OBBBOX3D);
	m_AttCollision->Off();

	m_SubCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHECK);
	m_SubCollision->GetTransform()->SetLocalScale(float4{ 50.0f , 50.0f });
	m_SubCollision->GetTransform()->SetLocalPosition({ 0.0f, m_RenderPivot });

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender->GetTransform()->SetLocalScale({ 4, 4 });
	m_DebugRender->Off();
}

void Monster_Pomp::LoadAndCreateAnimation()
{
	// ���⼭ �ʿ��� ���ҽ� �ε� �� �ִϸ��̼� �����
	{
		if (nullptr == GameEngineSprite::Find("pomp_idle"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("katanazero_resources");
			Dir.Move("katanazero_resources");
			Dir.Move("Texture");
			Dir.Move("ClubLevel");
			Dir.Move("pomp");

			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_idle").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_attack").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_walk").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_run").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_hurtground").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_knockdown").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_turn").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_fall").GetFullPath());

			std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
		}
	}

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_idle", .SpriteName = "pomp_idle", .Start = 0, .End = 7 ,
								  .FrameInter = 0.11f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_attack", .SpriteName = "pomp_attack", .Start = 0, .End = 5 ,
								  .FrameInter = 0.07f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_walk", .SpriteName = "pomp_walk", .Start = 0, .End = 9 ,
								  .FrameInter = 0.08f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_run", .SpriteName = "pomp_run", .Start = 0, .End = 9 ,
								  .FrameInter = 0.06f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_hurtground", .SpriteName = "pomp_hurtground", .Start = 0, .End = 14 ,
								  .FrameInter = 0.10f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_knockdown", .SpriteName = "pomp_knockdown", .Start = 0, .End = 21 ,
								  .FrameInter = 0.10f , .Loop = false , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_turn", .SpriteName = "pomp_turn", .Start = 0, .End = 5 ,
							  .FrameInter = 0.08f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_fall", .SpriteName = "pomp_fall", .Start = 0, .End = 12 ,
						  .FrameInter = 0.09f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->SetAnimationStartEvent("pomp_attack", static_cast<size_t>(3), std::bind(&Monster_Pomp::Attack, this));
	m_MainRender->SetAnimationStartEvent("pomp_attack", static_cast<size_t>(5), std::bind(&Monster_Pomp::AttackOff, this));

	m_MainRender->ChangeAnimation("pomp_idle");
}

bool Monster_Pomp::ChaseCheck()
{
	// �÷��̾�� ���� ü�̽��� �浹ü�� �浹�ߴ��� Ȯ�� 
	if (nullptr != m_ChaseCollision)
	{
		std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
		if (nullptr != Col)
		{
			return true;
		}
	}
	return false;
}

void Monster_Pomp::DoorOpenCheck()
{
	std::shared_ptr<GameEngineCollision> OpenEventCol = m_Collision->Collision(ColOrder::DOOR_OPEN_EVENT, ColType::OBBBOX3D, ColType::OBBBOX3D);
	// �浹�ߴٸ� �갡 nullptr �� �ƴҰŰ� 
	if (nullptr != OpenEventCol)
	{
		std::shared_ptr<IronDoor> Door = OpenEventCol->GetActor()->DynamicThis<IronDoor>();
		if (nullptr != Door && IronDoorState::OPEN == Door->GetCurState())
		{
			if (PompState::CHASE != m_CurState)
			{
				ChangeState(PompState::CHASE);
			}
		}
	}
}

bool Monster_Pomp::DoorCollisionCheck()
{
	std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		return true;
	}
	return false;
}

bool Monster_Pomp::PartitionCollisionCheck()
{
	std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::PARTITION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		return true;
	}
	return false;
}

void Monster_Pomp::ParryingCheck()
{
	// ���ݻ��¿��� ���� ���ݰ� �÷��̾��� ������ �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> PlayerAttCol = m_AttCollision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != PlayerAttCol)
	{
		// �÷��̾��� �����浹ü�� ������Ʈ�� false�� ����� 
		PlayerAttCol->Off();
		m_AttCollision->Off();
		// ���� �׷α���·� (�˴ٿ�) 
		ChangeState(PompState::KNOCKDOWN);
		return;
	}
}

void Monster_Pomp::DeathCheck()
{
	// ��ü���� �浹
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		// �����ϴ� ����Ʈ ���� �� ����. 
		// �浹�� �浹ü�� �θ�  �޾ƿ��� 
		GameEngineTransform* colobj = Col->GetTransform()->GetParent();
		std::shared_ptr<SlashHit_Effect> Effect = GetLevel()->CreateActor<SlashHit_Effect>(static_cast<int>(RenderOrder::EFFECT));
		float4 MyPos = GetTransform()->GetLocalPosition();
		Effect->GetTransform()->SetLocalPosition({ MyPos.x, MyPos.y + m_HitEffectPivot });

		m_Collision->Off();
		m_ChaseCollision->Off();

		// �����׾����ϱ� -1 
		GetReturnCastLevel()->DisCount();
		// ���º����� �����ִϸ��̼� 
		ChangeState(PompState::HITGROUND);
	}
}

void Monster_Pomp::Attack()
{
	if (true == m_Direction)
	{
		m_AttCollision->GetTransform()->AddLocalPosition(float4{ 20.0f , 0.0f });
	}

	else if (false == m_Direction)
	{
		m_AttCollision->GetTransform()->AddLocalPosition(float4{ 20.0f , 0.0f });
	}

	m_AttCollision->On();
}

void Monster_Pomp::AttackOff()
{
	m_AttCollision->Off();
	m_AttCollision->GetTransform()->SetLocalPosition(float4{ 0.0f, m_ColPivot });
}


// �������� �÷��̾�� ���� 
void Monster_Pomp::Reset()
{
	// ���� �ʱ� ������ġ�� �̵��ϰ�
	GetTransform()->SetLocalPosition(GetInitPos());
	// ���� ���̵�� �����ϰ� 
	ChangeState(PompState::IDLE);

	// �ʱ�ȭ�ʿ��� ���� ���� �ʱ�ȭ 
	ResetDir();
	m_FollowEffectOn = false;
	m_Collision->On();
	m_ChaseCollision->On();
	m_AttCollision->Off();
	m_HitPos = float4{ 0.0f , 0.0f };
}

inline void Monster_Pomp::ResetDir()
{
	int Random = GameEngineRandom::MainRandom.RandomInt(0, 1);
	if (0 == Random)
	{
		m_Direction = false;
	}
	else if (1 == Random)
	{
		m_Direction = true;
	}
}

void Monster_Pomp::CreateFollowEffect()
{
	if (false == m_FollowEffectOn)
	{
		m_FollowEffectOn = true;
		std::shared_ptr<EnemyFollow_Effect> Effect = GetLevel()->CreateActor<EnemyFollow_Effect>();
		Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4{ 0.0f, 85.0f });
	}
}


void Monster_Pomp::DirCheck()
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

void Monster_Pomp::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
	switch (m_CurState)
	{
	case PompState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case PompState::WALK:
		WalkUpdate(_DeltaTime);
		break;
	case PompState::CHASE:
		ChaseUpdate(_DeltaTime);
		break;
	case PompState::HITGROUND:
		HitGroundUpdate(_DeltaTime);
		break;
	case PompState::TURN:
		TurnUpdate(_DeltaTime);
		break;
	case PompState::ATTACK:
		AttackUpdate(_DeltaTime);
		break;
	case PompState::FALL:
		FallUpdate(_DeltaTime);
		break;
	case PompState::KNOCKDOWN:
		KnockDownUpdate(_DeltaTime);
		break;
	}
}

// state ����, ����� ������ start, ���� ������ end ����
void Monster_Pomp::ChangeState(PompState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	switch (m_NextState)
	{
	case PompState::IDLE:
		IdleStart();
		break;
	case PompState::WALK:
		WalkStart();
		break;
	case PompState::CHASE:
		ChaseStart();
		break;
	case PompState::HITGROUND:
		HitGroundStart();
		break;
	case PompState::TURN:
		TurnStart();
		break;
	case PompState::ATTACK:
		AttackStart();
		break;
	case PompState::FALL:
		FallStart();
		break;
	case PompState::KNOCKDOWN:
		KnockDownStart();
		break;
	}

	// ���� state�� end 
	switch (m_PrevState)
	{
	case PompState::IDLE:
		IdleEnd();
		break;
	case PompState::WALK:
		WalkEnd();
		break;
	case PompState::CHASE:
		ChaseEnd();
		break;
	case PompState::HITGROUND:
		HitGroundEnd();
		break;
	case PompState::TURN:
		TurnEnd();
		break;
	case PompState::ATTACK:
		AttackEnd();
		break;
	case PompState::FALL:
		FallEnd();
		break;
	case PompState::KNOCKDOWN:
		KnockDownEnd();
		break;
	}
}


void Monster_Pomp::IdleStart()
{
	m_MainRender->ChangeAnimation("pomp_idle");
}

void Monster_Pomp::IdleUpdate(float _DeltaTime)
{
	if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		return;
	}

	if (true == ChaseCheck() && false == DoorCollisionCheck())
	{
		ChangeState(PompState::CHASE);
		return;
	}

	// �����ð��� 2�ʰ� �Ѿ��ٸ� 
	if (3.0f <= GetLiveTime())
	{
		ChangeState(PompState::WALK);
		return;
	}
}

void Monster_Pomp::IdleEnd()
{
}

void Monster_Pomp::WalkStart()
{
	m_MainRender->ChangeAnimation("pomp_walk");
	ResetDir();
}

void Monster_Pomp::WalkUpdate(float _DeltaTime)
{
	if (true == ChaseCheck() && false == DoorCollisionCheck())
	{
		ChangeState(PompState::CHASE);
		return;
	}

	if (true == PartitionCollisionCheck())
	{
		if (true == m_Direction)
		{
			m_Direction = false;
			GetTransform()->AddLocalPosition(float4::Left * m_WalkMoveSpeed * _DeltaTime);
			return;
		}

		else if (false == m_Direction)
		{
			m_Direction = true;
			GetTransform()->AddLocalPosition(float4::Right * m_WalkMoveSpeed * _DeltaTime);
			return;
		}
	}

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

void Monster_Pomp::WalkEnd()
{
}

void Monster_Pomp::ChaseStart()
{
	m_MainRender->ChangeAnimation("pomp_run");
	DirCheck();
	CreateFollowEffect();
}

void Monster_Pomp::ChaseUpdate(float _DeltaTime)
{
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

	if (50.0f >= abs(PlayerPos.x - MyPos.x))
	{
		ChangeState(PompState::ATTACK);
		return;
	}

	MoveDir.y = 0.0f;
	MoveDir.Normalize();
	GetTransform()->AddWorldPosition(MoveDir * m_ChaseMoveSpeed * _DeltaTime);
}

void Monster_Pomp::ChaseEnd()
{
}

// �̰� ������
void Monster_Pomp::HitGroundStart()
{
	m_MainRender->ChangeAnimation("pomp_hurtground");
	m_HitPos = GetTransform()->GetLocalPosition();
}

void Monster_Pomp::HitGroundUpdate(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> PartitionCol = m_SubCollision->Collision(ColOrder::PARTITION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	std::shared_ptr<GameEngineCollision> DoorCol = m_SubCollision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (3 <= m_MainRender->GetCurrentFrame() || PartitionCol != nullptr || DoorCol != nullptr)
	{
		// ���߿� �߰��� �� ������ �߰� 
		return;
	}

	// �÷��̾� x�� ���  
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();
	float  FlyingSpeed = m_FlyingSpeed;
	
	float X = abs(MyPos.x - m_HitPos.x);
	if (X >= 100.0f)
	{
		FlyingSpeed *= 0.67f;
	}

	// �̶� ���� x���� �÷��̾��� x�ຸ�� ũ�ٸ� ��������
	// �ƴ϶�� ��������
	if (PlayerPos.x <= MyPos.x)
	{
		// ����
		GetTransform()->AddLocalPosition(float4::Right * FlyingSpeed * _DeltaTime);
	}

	else if (PlayerPos.x > MyPos.x)
	{
		// ���� 
		GetTransform()->AddLocalPosition(float4::Left * FlyingSpeed * _DeltaTime);
	}
}

void Monster_Pomp::HitGroundEnd()
{
	m_HitPos = float4{ 0.0f, 0.0f };
}

void Monster_Pomp::AttackStart()
{
	DirCheck();
	m_MainRender->ChangeAnimation("pomp_attack");
}

void Monster_Pomp::AttackUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
		{
			ChangeState(PompState::IDLE);
			return;
		}
		ChangeState(PompState::CHASE);
		return;
	}

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();
	float4 AttDir = PlayerPos - MyPos;

	if (PlayerPos.x >= MyPos.x)
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
	}

	else
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
	}

}

void Monster_Pomp::AttackEnd()
{
}

void Monster_Pomp::TurnStart()
{
}

void Monster_Pomp::TurnUpdate(float _DeltaTime)
{
}

void Monster_Pomp::TurnEnd()
{
}

void Monster_Pomp::KnockDownStart()
{
	m_MainRender->ChangeAnimation("pomp_knockdown");
}

void Monster_Pomp::KnockDownUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		ChangeState(PompState::IDLE);
		return;
	}
}

void Monster_Pomp::KnockDownEnd()
{
}

void Monster_Pomp::FallStart()
{
}

void Monster_Pomp::FallUpdate(float _DeltaTime)
{
}

void Monster_Pomp::FallEnd()
{
}

