#include "PrecompileHeader.h"
#include "Monster_Grunt.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Player.h"
#include "SlashHit_Effect.h"
#include "GruntEffect.h"
#include "EnemyFollow_Effect.h"
#include "IronDoor.h"
#include "PixelCollider.h"
#include "HitEffect.h"

Monster_Grunt::Monster_Grunt()
{
}

Monster_Grunt::~Monster_Grunt()
{
}

void Monster_Grunt::BulletCollision()
{
	DeathCheck();
}

void Monster_Grunt::Start()
{
	ComponentSetting();
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
	DebugUpdate();
	DoorOpenCheck();			// ���浹üũ 
	DeathCheck();
	UpdateState(_DeltaTime);

	// ���� �÷��̾��� ���ݰ� �浹�ߴ��� Ȯ�� 
}

void Monster_Grunt::Render(float _DeltaTime)
{
}

void Monster_Grunt::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_DebugSwitch"))
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

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0.0f, m_ColPivot });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->DebugOff();

	m_ChaseCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHASE);
	m_ChaseCollision->GetTransform()->SetLocalScale(float4{ 300.0f, 80.0f });
	m_ChaseCollision->GetTransform()->SetLocalPosition({ 50.0f, m_ColPivot });
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

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale({ 4,  4 });
	m_DebugRender->Off();
}

void Monster_Grunt::LoadAndCreateAnimation()
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
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_forcefall").GetFullPath());

		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
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

	m_MainRender->CreateAnimation({ .AnimationName = "grunt_forcefall", .SpriteName = "grunt_forcefall", .Start = 0, .End = 1 ,
						  .FrameInter = 0.15f , .Loop = false , .ScaleToTexture = true });

	// �ִϸ��̼� �����Ӻ� �̺�Ʈ�߰� 
	m_MainRender->SetAnimationStartEvent("grunt_attack", static_cast<size_t>(5), std::bind(&Monster_Grunt::Attack, this));
	m_MainRender->SetAnimationStartEvent("grunt_attack", static_cast<size_t>(7), std::bind(&Monster_Grunt::AttackOff, this));
	m_MainRender->SetAnimationStartEvent("grunt_attack", static_cast<size_t>(4), std::bind(&Monster_Grunt::CreateEffect, this));
	m_MainRender->ChangeAnimation("grunt_idle");
}

void Monster_Grunt::CreateEffect()
{
	std::shared_ptr<GruntEffect> Effect = GetLevel()->CreateActor<GruntEffect>();
	Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4 { 0.0f, 50.0f});
	if (true == m_Direction)
	{
		Effect->GetTransform()->SetLocalPositiveScaleX();
	}

	else if (false == m_Direction)
	{
		Effect->GetTransform()->SetLocalNegativeScaleX();
	}
}

void Monster_Grunt::CreateFollowEffect()
{
	if (false == m_FollowEffectOn)
	{
		m_FollowEffectOn = true;
		std::shared_ptr<EnemyFollow_Effect> Effect = GetLevel()->CreateActor<EnemyFollow_Effect>();
		Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4{ 0.0f, 85.0f });
		Effect->SetObject(DynamicThis<Monster_Grunt>());
		Effect->SetPivot(float4{ 0.0f, 90.0f });
	}
}

void Monster_Grunt::CreateHitEffect()
{
	std::shared_ptr<HitEffect> Effect = GetLevel()->CreateActor<HitEffect>(static_cast<int>(RenderOrder::EFFECT));
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();
	float4 MoveDir = PlayerPos - MyPos;

	Effect->SetObject(this->DynamicThis<GameEngineObject>());
	if (PlayerPos.x > MyPos.x)
	{
		Effect->GetTransform()->SetLocalPositiveScaleX();
	}

	else if (PlayerPos.x <= MyPos.x)
	{
		
		Effect->GetTransform()->SetLocalNegativeScaleX();
	}
}

void Monster_Grunt::CreateSlashHitEffect()
{
	std::shared_ptr<SlashHit_Effect> Effect = GetLevel()->CreateActor<SlashHit_Effect>(static_cast<int>(RenderOrder::EFFECT));
	Effect->SetObject(DynamicThis<Monster_Grunt>());
	Effect->SetPivot(float4{ 0.0f, 30.0f });
}

bool Monster_Grunt::ChaseCheck()
{
	// ü�̽� üũ�� �浹ü�� Ȯ��
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

void Monster_Grunt::DoorOpenCheck()
{
	// Door �� ����üũ�� �浹ü�� �浹���� ���¿���, ���� OPEN ���·� ����Ǹ� ���� ���º���
	std::shared_ptr<GameEngineCollision> OpenEventCol = m_Collision->Collision(ColOrder::DOOR_OPEN_EVENT, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != OpenEventCol)
	{
		std::shared_ptr<IronDoor> Door = OpenEventCol->GetActor()->DynamicThis<IronDoor>();
		if (nullptr != Door && IronDoorState::OPEN == Door->GetCurState())
		{
			if (GruntState::CHASE != m_CurState)
			{
				ChangeState(GruntState::CHASE);
			}
		}
	}
}

bool Monster_Grunt::DoorCollisionCheck()
{
	std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		return true;
	}
	return false;
}

bool Monster_Grunt::PartitionCollisionCheck()
{
	std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::PARTITION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		return true;
	}
	return false;
}

void Monster_Grunt::DeathCheck()
{
	// ���� �÷��̾��� ���ݰ� �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	std::shared_ptr<GameEngineCollision> BulletCol = m_Collision->Collision(ColOrder::PLAYER_BULLET, ColType::OBBBOX3D, ColType::OBBBOX3D);

	if (nullptr != BulletCol)
	{
		// ���� �浹ü�� off
		// �ִϸ��̼� ������ �����ִϸ��̼�������ȯ 
		m_Collision->Off();
		CreateHitEffect();

		// �����׾����ϱ� -1 
		GetReturnCastLevel()->DisCount();
		ChangeState(GruntState::HITGROUND);
		return;
	}
	// ������ ���Դٴ°� �浹�ߴٴ°Ű� 
	// �׷� �浹�� ���͸� ������Ű�� �������� ȣ�� 
	if (nullptr != Col)
	{
		// ���� �浹ü�� off
		// �ִϸ��̼� ������ �����ִϸ��̼�������ȯ 
		m_Collision->Off();
		CreateHitEffect();
		CreateSlashHitEffect();
		
		// �����׾����ϱ� -1 
		GetReturnCastLevel()->DisCount();
		ChangeState(GruntState::HITGROUND);
		return;
	}
}

// ----------- �ִϸ��̼� �̺�Ʈ�� �߰� �Ǿ����� Attack , AttackOff----------- 
void Monster_Grunt::Attack()
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

void Monster_Grunt::AttackOff()
{
	m_AttCollision->Off();
	m_AttCollision->GetTransform()->SetLocalPosition(float4{ 0.0f, m_ColPivot });
}

void Monster_Grunt::Reset()
{
	// ���� �ʱ� ������ġ�� �̵��ϰ�
	GetTransform()->SetLocalPosition(GetInitPos());
	// ���� ���̵�� �����ϰ� 
	ChangeState(GruntState::IDLE);
	
	// �ʱ�ȭ�ʿ��� ���� ���� �ʱ�ȭ 
	ResetDir();
	m_FollowEffectOn = false;
	m_Collision->On();
	m_ChaseCollision->On();
	m_AttCollision->Off();
	m_HitPos = float4{ 0.0f , 0.0f };
	m_IsDeath = false;
	m_CurrentVerticalVelocity = 0.0f;
}

inline void Monster_Grunt::ResetDir()
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

void Monster_Grunt::DirCheck()
{
	// ����Ƽ��, �װ�Ƽ�� �Լ� ���ÿ� ������ �ƴ϶� ������ Ʈ�������� ����ؾ���
	if (true == m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}
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
	case GruntState::FORCEFALL:
		ForceFallUpdate(_DeltaTime);
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
	case GruntState::FORCEFALL:
		ForceFallStart();
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
	case GruntState::FORCEFALL:
		ForceFallEnd();
		break;
	}
}

void Monster_Grunt::IdleStart()
{
	m_MainRender->ChangeAnimation("grunt_idle");
}

void Monster_Grunt::IdleUpdate(float _DeltaTime)
{
	// �÷��̾ �������¶�� �ƹ��͵� ����. 
	if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		return;
	}

	if (true == ChaseCheck() && false == DoorCollisionCheck())
	{
		ChangeState(GruntState::CHASE);
		return;
	}

	// �����ð��� 2�ʰ� �Ѿ��ٸ� <-- �̰ǹٲ���� 
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

	// �ݹ�Ȯ���� ���ʿ�����
	ResetDir();
}

void Monster_Grunt::WalkUpdate(float _DeltaTime)
{ 
	if (true == ChaseCheck() && false == DoorCollisionCheck())
	{
		ChangeState(GruntState::CHASE);
		return;
	}

	// ��Ƽ�ǰ� �浹�ߴٸ�
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

	// �浹�� ���°� �ƴ϶�� ���� ���Ⱚ�� ���� �̵���Ų��. 
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
	CreateFollowEffect();
	m_MainRender->ChangeAnimation("grunt_run");
}

void Monster_Grunt::ChaseUpdate(float _DeltaTime)
{	
	// chase ���¿��� ���Ʒ�,�׾Ʒ��� ��� ����ȼ��̶�� 

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
		ChangeState(GruntState::ATTACK);
		return;
	}

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
	m_HitPos = GetTransform()->GetLocalPosition();
	m_IsDeath = true;
}

void Monster_Grunt::HitGroundUpdate(float _DeltaTime)
{
	// �̻��¿��� ���� �� �����ݸ����̶� �����ͽ��÷��� ����Ʈ�� �浹�ߴٸ� 
	std::shared_ptr<GameEngineCollision> ExCol = m_SubCollision->Collision(ColOrder::BOSS_EXPLOSION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != ExCol)
	{
		ChangeState(GruntState::FORCEFALL);
		return;
	}

	// �ȼ�üũ �ؾ���
	std::shared_ptr<GameEngineCollision> PartitionCol = m_SubCollision->Collision(ColOrder::PARTITION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	std::shared_ptr<GameEngineCollision> DoorCol = m_SubCollision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (4 <= m_MainRender->GetCurrentFrame() || PartitionCol != nullptr || DoorCol != nullptr ||
		PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition() + float4::Up) ||
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition() + float4::Up))
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

void Monster_Grunt::HitGroundEnd()
{
	m_HitPos = float4{ 0.0f, 0.0f };
	m_IsDeath = false;
}

void Monster_Grunt::AttackStart()
{
	DirCheck();
	m_MainRender->ChangeAnimation("grunt_attack");
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 5.0f });
}

void Monster_Grunt::AttackUpdate(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
		{
			ChangeState(GruntState::IDLE);
			return;
		}
		ChangeState(GruntState::CHASE);
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

void Monster_Grunt::AttackEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -5.0f });
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

void Monster_Grunt::ForceFallStart()
{
	m_MainRender->ChangeAnimation("grunt_forcefall");
	m_CurrentVerticalVelocity = m_JumpPower;
}

void Monster_Grunt::ForceFallUpdate(float _DeltaTime)
{
	m_CurrentVerticalVelocity -= m_GravityPower * _DeltaTime;
	GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);
}

void Monster_Grunt::ForceFallEnd()
{
	m_CurrentVerticalVelocity = 0.0f;
}
