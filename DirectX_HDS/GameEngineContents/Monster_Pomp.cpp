#include "PrecompileHeader.h"
#include "Monster_Pomp.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "PixelCollider.h"

#include "Player.h"
#include "SlashHit_Effect.h"
#include "IronDoor.h"
#include "EnemyFollow_Effect.h"
#include "HitEffect.h"

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

	// 렌더러생성 및 세팅
	ComponentSetting();
	// 리소스 로드
	LoadAndCreateAnimation();

	ChangeState(PompState::IDLE);
}

void Monster_Pomp::Update(float _DeltaTime)
{
	m_RecordingFrame = !m_RecordingFrame;
	// 레벨의 상태를 체크한다. 
	BaseLevel::LevelState CurState = GetLevelState();
	if (BaseLevel::LevelState::RECORDING_PROGRESS == CurState &&
		PompState::RECORDING_PROGRESS != m_CurState)
	{
		ChangeState(PompState::RECORDING_PROGRESS);
		return;
	}

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
	DeathCheck();
	ParryingCheck();
	UpdateState(_DeltaTime);

	if (PompState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_MainRender.get());
		}
	}

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
	if (nullptr == m_MainRender)
	{
		m_MainRender = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::MONSTER));
		m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::MONSTER));
		m_ChaseCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHASE);
		m_AttCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_ATTACK);
		m_SubCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHECK);
		m_DebugRender = CreateComponent<GameEngineSpriteRenderer>();

		m_Collision->DebugOff();
		m_ChaseCollision->DebugOff();
		m_AttCollision->Off();
		m_DebugRender->Off();
	}

	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f, m_RenderPivot });
	m_MainRender->SetScaleRatio(2.0f);

	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, m_ColPivot });
	m_Collision->SetColType(ColType::OBBBOX3D);

	m_ChaseCollision->GetTransform()->SetLocalScale(float4{ 250.0f, 80.0f });
	m_ChaseCollision->GetTransform()->SetLocalPosition({ 100.0f, m_ColPivot });
	m_ChaseCollision->SetColType(ColType::OBBBOX3D);

	m_AttCollision->GetTransform()->SetLocalScale(float4{ 25.0f, 70.0f });
	m_AttCollision->GetTransform()->SetLocalPosition({ 0.0f, m_ColPivot });
	m_AttCollision->SetColType(ColType::OBBBOX3D);

	m_SubCollision->GetTransform()->SetLocalScale(float4{ 50.0f , 50.0f });
	m_SubCollision->GetTransform()->SetLocalPosition({ 0.0f, m_RenderPivot });

	m_DebugRender->GetTransform()->SetLocalScale({ 4, 4 });
}

void Monster_Pomp::LoadAndCreateAnimation()
{
	// 여기서 필요한 리소스 로드 후 애니메이션 만들어
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
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("pomp_forcefall").GetFullPath());

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

	m_MainRender->CreateAnimation({ .AnimationName = "pomp_forcefall", .SpriteName = "pomp_forcefall", .Start = 0, .End = 1 ,
						  .FrameInter = 0.15f , .Loop = true , .ScaleToTexture = true });

	m_MainRender->SetAnimationStartEvent("pomp_attack", static_cast<size_t>(3), std::bind(&Monster_Pomp::Attack, this));
	m_MainRender->SetAnimationStartEvent("pomp_attack", static_cast<size_t>(5), std::bind(&Monster_Pomp::AttackOff, this));

	m_MainRender->ChangeAnimation("pomp_idle");
}

bool Monster_Pomp::ChaseCheck()
{
	// 플레이어와 나의 체이스용 충돌체가 충돌했는지 확인 
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
	// 충돌했다면 얘가 nullptr 이 아닐거고 
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
	// 공격상태에서 나의 공격과 플레이어의 공격이 충돌했다면 
	std::shared_ptr<GameEngineCollision> PlayerAttCol = m_AttCollision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != PlayerAttCol)
	{
		// 플레이어의 공격충돌체의 업데이트를 false로 만들고 
		PlayerAttCol->Off();
		m_AttCollision->Off();
		// 나는 그로기상태로 (넉다운) 
		ChangeState(PompState::KNOCKDOWN);
		return;
	}
}

void Monster_Pomp::DeathCheck()
{
	// 내가 플레이어의 공격과 충돌했다면 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);
	std::shared_ptr<GameEngineCollision> BulletCol = m_Collision->Collision(ColOrder::PLAYER_BULLET, ColType::OBBBOX3D, ColType::OBBBOX3D);

	if (nullptr != BulletCol)
	{
		// 나의 충돌체를 off
		// 애니메이션 렌더를 데스애니메이션으로전환 
		m_Collision->Off();
		CreateHitEffect();

		// 내가죽었으니까 -1 
		GetReturnCastLevel()->DisCount();
		ChangeState(PompState::HITGROUND);
		return;
	}
	// 뭔가가 들어왔다는건 충돌했다는거고 
	// 그럼 충돌한 액터를 데스시키고 레벨리셋 호출 
	if (nullptr != Col)
	{
		// 나의 충돌체를 off
		// 애니메이션 렌더를 데스애니메이션으로전환 
		m_Collision->Off();
		CreateHitEffect();
		CreateSlashHitEffect();

		// 내가죽었으니까 -1 
		GetReturnCastLevel()->DisCount();
		ChangeState(PompState::HITGROUND);
		return;
	}
}

void Monster_Pomp::CreateHitEffect()
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

void Monster_Pomp::CreateSlashHitEffect()
{
	std::shared_ptr<SlashHit_Effect> Effect = GetLevel()->CreateActor<SlashHit_Effect>(static_cast<int>(RenderOrder::EFFECT));
	Effect->SetObject(DynamicThis<Monster_Pomp>());
	Effect->SetPivot(float4{ 0.0f, 30.0f });
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


// 내리셋은 플레이어와 동일 
void Monster_Pomp::Reset()
{
	ComponentSetting();
	// 나의 초기 세팅위치로 이동하고
	GetTransform()->SetLocalPosition(GetInitPos());
	// 상태 아이들로 변경하고 
	ChangeState(PompState::IDLE);

	// 초기화필요한 값들 전부 초기화 
	ResetDir();
	m_FollowEffectOn = false;
	m_Collision->On();
	m_ChaseCollision->On();
	m_AttCollision->Off();
	m_HitPos = float4{ 0.0f , 0.0f };
	m_IsDeath = false;
	m_CurrentVerticalVelocity = 0.0f; 
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
		Effect->SetObject(DynamicThis<Monster_Pomp>());
		Effect->SetPivot(float4{ 0.0f, 90.0f });
	}
}


void Monster_Pomp::DirCheck()
{
	// 포지티브, 네거티브 함수 사용시에 렌더가 아니라 액터의 트랜스폼을 사용해야함 ㅎㅎ 
	// 방향체크 
	// 오른쪽 
	if (true == m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	// 왼쪽 
	else if (false == m_Direction)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
}

// -------------------------------------------- State ----------------------------------------------------

void Monster_Pomp::UpdateState(float _DeltaTime)
{
	// 현재 상태의 update 호출 
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
	case PompState::FORCEFALL:
		ForceFallUpdate(_DeltaTime);
		break;
	case PompState::RECORDING_PROGRESS:
		RecordingProgressUpdate(_DeltaTime);
		break;
	}
}

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
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
	case PompState::FORCEFALL:
		ForceFallStart();
		break;
	case PompState::RECORDING_PROGRESS:
		RecordingProgressStart();
		break;
	}

	// 이전 state의 end 
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
	case PompState::FORCEFALL:
		ForceFallEnd();
		break;
	case PompState::RECORDING_PROGRESS:
		RecordingProgressEnd();
		break;
	}
}

void Monster_Pomp::BulletCollision()
{
	DeathCheck();
}


void Monster_Pomp::IdleStart()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 4.0f });
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

	// 생존시간이 2초가 넘었다면 
	if (3.0f <= GetLiveTime())
	{
		ChangeState(PompState::WALK);
		return;
	}
}

void Monster_Pomp::IdleEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -4.0f });
}

void Monster_Pomp::WalkStart()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, 5.0f });
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
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f, -5.0f });
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

	// 이때 x 값이 나보다 크다면
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

// 이게 데스임
void Monster_Pomp::HitGroundStart()
{
	m_MainRender->ChangeAnimation("pomp_hurtground");
	m_HitPos = GetTransform()->GetLocalPosition();

	m_IsDeath = true;
}

void Monster_Pomp::HitGroundUpdate(float _DeltaTime)
{
	// 이상태에서 만약 내 서브콜리전이랑 보스익스플로전 이펙트랑 충돌했다면 
	std::shared_ptr<GameEngineCollision> ExCol = m_SubCollision->Collision(ColOrder::BOSS_EXPLOSION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != ExCol)
	{
		ChangeState(PompState::FORCEFALL);
		return;
	}

	// 픽셀체크 해야함
	std::shared_ptr<GameEngineCollision> PartitionCol = m_SubCollision->Collision(ColOrder::PARTITION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	std::shared_ptr<GameEngineCollision> DoorCol = m_SubCollision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (3 <= m_MainRender->GetCurrentFrame() || PartitionCol != nullptr || DoorCol != nullptr ||
		PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition() + float4::Up) ||
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition() + float4::Up))
	{
		// 나중에 추가할 거 있으면 추가 
		return;
	}

	// 플레이어 x축 계산  
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();
	float  FlyingSpeed = m_FlyingSpeed;
	
	float X = abs(MyPos.x - m_HitPos.x);
	if (X >= 100.0f)
	{
		FlyingSpeed *= 0.67f;
	}

	// 이때 나의 x축이 플레이어의 x축보다 크다면 우측으로
	// 아니라면 왼쪽으로
	if (PlayerPos.x <= MyPos.x)
	{
		// 우측
		GetTransform()->AddLocalPosition(float4::Right * FlyingSpeed * _DeltaTime);
	}

	else if (PlayerPos.x > MyPos.x)
	{
		// 좌측 
		GetTransform()->AddLocalPosition(float4::Left * FlyingSpeed * _DeltaTime);
	}
}

void Monster_Pomp::HitGroundEnd()
{
	m_HitPos = float4{ 0.0f, 0.0f };
	m_IsDeath = false;
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
		ChangeState(PompState::CHASE);
		return;
	}
}

void Monster_Pomp::KnockDownEnd()
{
	m_Collision->On();
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

void Monster_Pomp::ForceFallStart()
{
	m_MainRender->ChangeAnimation("pomp_forcefall");
	m_CurrentVerticalVelocity = m_JumpPower;
}

void Monster_Pomp::ForceFallUpdate(float _DeltaTime)
{
	m_CurrentVerticalVelocity -= m_GravityPower * _DeltaTime;
	GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);
}

void Monster_Pomp::ForceFallEnd()
{
	m_CurrentVerticalVelocity = 0.0f;
}

void Monster_Pomp::RecordingProgressStart()
{
}

void Monster_Pomp::RecordingProgressUpdate(float _DeltaTime)
{
	// 레코딩이 종료 되었다면 아이들로 전환. 
	if (true == m_Recording_Complete)
	{
		m_Recording_Complete = false;
		Reset();
		ChangeState(PompState::IDLE);
		return;
	}

	// 여기서 역재생을 수행하고, 
	Reverse(m_MainRender.get());
}

void Monster_Pomp::RecordingProgressEnd()
{
}

