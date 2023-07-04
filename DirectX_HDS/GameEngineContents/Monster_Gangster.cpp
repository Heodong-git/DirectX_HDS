#include "PrecompileHeader.h"
#include "Monster_Gangster.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Player.h"
#include "SlashHit_Effect.h"
#include "EnemyFollow_Effect.h"
#include "IronDoor.h"
#include "FireEffect.h"
#include "Bullet.h"
#include "HitEffect.h"

#include "PixelCollider.h"

Monster_Gangster::Monster_Gangster()
{
}

Monster_Gangster::~Monster_Gangster()
{
}

void Monster_Gangster::BulletCollision()
{
	DeathCheck();
}

void Monster_Gangster::Start()
{
	if (false == GameEngineInput::IsKey("gangster_DebugSwitch"))
	{
		GameEngineInput::CreateKey("gangster_DebugSwitch", 'Q');
	}
	
	ComponentSetting();
	LoadAndCreateAnimation();
	ChangeState(GangsterState::IDLE);
}

void Monster_Gangster::Update(float _DeltaTime)
{
	// 레벨의 상태를 체크한다. 
	BaseLevel::LevelState CurState = GetLevelState();
	if (BaseLevel::LevelState::RECORDING_PROGRESS == CurState &&
		GangsterState::RECORDING_PROGRESS != m_CurState)
	{
		ChangeState(GangsterState::RECORDING_PROGRESS);
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
	
	DebugUpdate();
	DirCheck();
	DeathCheck();
	UpdateState(_DeltaTime);

	if (GangsterState::RECORDING_PROGRESS != m_CurState)
	{
		InfoSetting(m_MainRender.get());
	}
}

void Monster_Gangster::Render(float _DeltaTime)
{
}

void Monster_Gangster::DebugUpdate()
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

// 필요 없어도 공통적으로 해 .
void Monster_Gangster::ComponentSetting()
{
	if (nullptr == m_MainRender)
	{
		m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
		m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
		m_ChaseCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHASE);
		m_SubCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_CHECK);
		m_AimCollision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER_RANGE_CHECK);
		m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);

		m_Collision->DebugOff();
		m_ChaseCollision->DebugOff();
		m_AimCollision->DebugOff();
		m_DebugRender->Off();
	}
	
	
	// 렌더러, 충돌체 생성
	
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f , m_RenderPivot });
	m_MainRender->SetScaleRatio(2.0f);

	// 콜리전 생성
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, m_ColPivot });
	m_Collision->SetColType(ColType::OBBBOX3D);

	m_ChaseCollision->GetTransform()->SetLocalScale(float4{ 300.0f, 80.0f });
	m_ChaseCollision->GetTransform()->SetLocalPosition({ 50.0f, m_ColPivot });
	m_ChaseCollision->SetColType(ColType::OBBBOX3D);

	m_SubCollision->GetTransform()->SetLocalScale(float4{ 50.0f , 50.0f });
	m_SubCollision->GetTransform()->SetLocalPosition({ 0.0f, m_RenderPivot });

	m_AimCollision->GetTransform()->SetLocalScale(float4{ 550.0f , 20.0f });
	m_AimCollision->GetTransform()->SetLocalPosition({ 275.0f, m_RenderPivot });
	m_AimCollision->SetColType(ColType::OBBBOX3D);

	// 디버그렌더 생성
	m_DebugRender->GetTransform()->SetLocalScale({ 4, 4 });
}

void Monster_Gangster::LoadAndCreateAnimation()
{
	// 여기서 필요한 리소스 로드 후 애니메이션 만들어
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
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_fire_effect").GetFullPath());
			
			// 강제fall 애니메이션
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_forcefall").GetFullPath());
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

	m_MainRender->CreateAnimation({ .AnimationName = "gangster_aim", .SpriteName = "gangster_idle", .Start = 0, .End = 5 ,
								  .FrameInter = 0.09f , .Loop = false ,.ScaleToTexture = true });

	m_MainRender->CreateAnimation({ .AnimationName = "gangster_forcefall", .SpriteName = "gangster_forcefall", .Start = 0, .End = 1 ,
								  .FrameInter = 0.15f , .Loop = false ,.ScaleToTexture = true });

	m_MainRender->ChangeAnimation("gangster_aim");
}

// 완성하면 리셋목록 확인해서 다시작성
void Monster_Gangster::Reset()
{
	ComponentSetting();
	GetTransform()->SetLocalPosition(GetInitPos());
	ChangeState(GangsterState::IDLE);
	ResetDir();
	m_Collision->On();
	m_SubCollision->On();
	m_AimCollision->On();
	m_FireCount = 0;
	m_FireTime = 0.0f;
	m_CurrentVerticalVelocity = 0.0f;
	m_FollowEffectOn = false;
	m_IsDeath = false;
}

void Monster_Gangster::ResetDir()
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

void Monster_Gangster::DirCheck()
{
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

void Monster_Gangster::CreateFollowEffect()
{
	if (false == m_FollowEffectOn)
	{
		m_FollowEffectOn = true;
		std::shared_ptr<EnemyFollow_Effect> Effect = GetLevel()->CreateActor<EnemyFollow_Effect>();
		Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4{ 0.0f, 85.0f });
		Effect->SetObject(DynamicThis<Monster_Gangster>());
		Effect->SetPivot(float4{ 0.0f, 90.0f });
	}
}

void Monster_Gangster::CreateFireEffect()
{
	std::shared_ptr<FireEffect> Effect = GetLevel()->CreateActor<FireEffect>();
	float PivotX = 0.0f;
	if (true == m_Direction)
	{
		PivotX = 56.0f;
		Effect->GetTransform()->SetLocalPositiveScaleX();
	}
	else if (false == m_Direction)
	{
		PivotX = -56.0f;
		Effect->GetTransform()->SetLocalNegativeScaleX();
	}

	Effect->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4 { PivotX, 39.0f });
}

void Monster_Gangster::CreateBullet()
{
	std::shared_ptr<Bullet> Obj = GetLevel()->CreateActor<Bullet>();
	float PivotX = 0.0f;
	if (true == m_Direction)
	{
		PivotX = 56.0f;
		Obj->GetTransform()->SetLocalPositiveScaleX();
		Obj->SetMoveDir(float4::Right);
	}
	else if (false == m_Direction)
	{
		PivotX = -56.0f;
		Obj->GetTransform()->SetLocalNegativeScaleX();
		Obj->SetMoveDir(float4::Left);
	}

	Obj->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4 { PivotX, 39.0f });
}

void Monster_Gangster::CreateHitEffect()
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

void Monster_Gangster::CreateSlashHitEffect()
{
	std::shared_ptr<SlashHit_Effect> Effect = GetLevel()->CreateActor<SlashHit_Effect>(static_cast<int>(RenderOrder::EFFECT));
	Effect->SetObject(DynamicThis<Monster_Gangster>());
	Effect->SetPivot(float4{ 0.0f, 30.0f });
}

bool Monster_Gangster::AimRangeCheck()
{
	// 만약 플레이어와 충돌했다면 에임 상태로 전환 
	std::shared_ptr<GameEngineCollision> PlayerCol = m_AimCollision->Collision(ColOrder::PLAYER, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != PlayerCol)
	{
		ChangeState(GangsterState::AIM);
		return true;
	}

	return false;
}

bool Monster_Gangster::ChaseCheck()
{
	// 체이스 체크용 충돌체를 확인
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

void Monster_Gangster::DoorOpenCheck()
{
	// Door 의 상태체크용 충돌체와 충돌중인 상태에서, 문이 OPEN 상태로 변경되면 나의 상태변경
	std::shared_ptr<GameEngineCollision> OpenEventCol = m_Collision->Collision(ColOrder::DOOR_OPEN_EVENT, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != OpenEventCol)
	{
		std::shared_ptr<IronDoor> Door = OpenEventCol->GetActor()->DynamicThis<IronDoor>();
		if (nullptr != Door && IronDoorState::OPEN == Door->GetCurState())
		{
			if (GangsterState::CHASE != m_CurState)
			{
				ChangeState(GangsterState::CHASE);
			}
		}
	}
}

bool Monster_Gangster::DoorCollisionCheck()
{
	std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		return true;
	}
	return false;
}

bool Monster_Gangster::PartitionCollisionCheck()
{
	std::shared_ptr<GameEngineCollision> Col = m_ChaseCollision->Collision(ColOrder::PARTITION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != Col)
	{
		return true;
	}
	return false;
}

void Monster_Gangster::DeathCheck()
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
		ChangeState(GangsterState::HITGROUND);
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
		ChangeState(GangsterState::HITGROUND);
		return;
	}
}


// -------------------------------------------- State ----------------------------------------------------

void Monster_Gangster::UpdateState(float _DeltaTime)
{
	// 현재 상태의 update 호출 
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
	case GangsterState::FORCEFALL:
		ForceFallUpdate(_DeltaTime);
		break;
	case GangsterState::RECORDING_PROGRESS:
		RecordingProgressUpdate(_DeltaTime);
		break;
	}
}


// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void Monster_Gangster::ChangeState(GangsterState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;
	
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
	case GangsterState::FORCEFALL:
		ForceFallStart();
		break;
	case GangsterState::RECORDING_PROGRESS:
		RecordingProgressStart();
		break;
	}

	// 이전 state의 end 
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
	case GangsterState::FORCEFALL:
		ForceFallEnd();
		break;
	case GangsterState::RECORDING_PROGRESS:
		RecordingProgressEnd();
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
	// 플레이어가 데스상태라면 아무것도 안함. 
	if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		return;
	}

	AimRangeCheck();

	// 일단 워크상태로 가고.
	// 생존시간이 2초가 넘었다면 <-- 이건바꿔야함 
	if (3.0f <= GetLiveTime())
	{
		ChangeState(GangsterState::WALK);
		return;
	}
}

void Monster_Gangster::IdleEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition({ 0.0f , -10.f });
}

void Monster_Gangster::WalkStart()
{
	m_MainRender->ChangeAnimation("gangster_walk");
	
	DirCheck();
}

void Monster_Gangster::WalkUpdate(float _DeltaTime)
{
	// chase col이 player 와 충돌하고, 문과 충돌상태가 아닐때 chase로 변경할거야
	if (true == ChaseCheck() && false == DoorCollisionCheck())
	{
		ChangeState(GangsterState::CHASE);
		return;
	}

	AimRangeCheck();


	// 파티션과 충돌했다면
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

	// 충돌한 상태가 아니라면 현재 방향값에 따라서 이동시킨다. 
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

void Monster_Gangster::WalkEnd()
{
}

void Monster_Gangster::ChaseStart()
{
	m_MainRender->ChangeAnimation("gangster_run");
}

void Monster_Gangster::ChaseUpdate(float _DeltaTime)
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

	if (200.0f >= abs(PlayerPos.x - MyPos.x))
	{
		ChangeState(GangsterState::AIM);
		return;
	}

	MoveDir.y = 0.0f;
	MoveDir.Normalize();
	GetTransform()->AddWorldPosition(MoveDir * m_ChaseMoveSpeed * _DeltaTime);
}

void Monster_Gangster::ChaseEnd()
{
}

void Monster_Gangster::AimStart()
{
	m_MainRender->ChangeAnimation("gangster_aim");
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f , 11.0f });
	CreateFollowEffect();
}

void Monster_Gangster::AimUpdate(float _DeltaTime)
{
	if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		ChangeState(GangsterState::IDLE);
		return;
	}

	if (3 == m_FireCount)
	{
		m_FireCount = 0;
		m_FireTime = 0.0f;

		if (true == AimRangeCheck())
		{
			ChangeState(GangsterState::AIM);
			return;
		}

		ChangeState(GangsterState::CHASE);
		return;
	}

	m_FireTime += _DeltaTime;
	if (m_ShotCoolTime <= m_FireTime)
	{
		++m_FireCount;
		m_FireTime = 0.0f;
		GameEngineSound::Play("gun_fire_00.wav");
		CreateBullet();
		CreateFireEffect();
	}
}

void Monster_Gangster::AimEnd()
{
	m_MainRender->GetTransform()->AddLocalPosition(float4{ 0.0f , -11.0f });
	m_FireCount = 0;
	m_FireTime = 0.0f;
	
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
	m_HitPos = float4{ 0.0f, 0.0f };
	DirCheck();
	m_MainRender->ChangeAnimation("gangster_hitground");
	m_IsDeath = true;
}

void Monster_Gangster::HitGroundUpdate(float _DeltaTime)
{
	// 이상태에서 만약 내 서브콜리전이랑 보스익스플로전 이펙트랑 충돌했다면 
	std::shared_ptr<GameEngineCollision> ExCol = m_SubCollision->Collision(ColOrder::BOSS_EXPLOSION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (nullptr != ExCol)
	{
		// ㅇㅋ 잘되고 
		ChangeState(GangsterState::FORCEFALL);
		return;
	}

	// 픽셀체크 해야함
	std::shared_ptr<GameEngineCollision> PartitionCol = m_SubCollision->Collision(ColOrder::PARTITION, ColType::OBBBOX3D, ColType::OBBBOX3D);
	std::shared_ptr<GameEngineCollision> DoorCol = m_SubCollision->Collision(ColOrder::DOOR, ColType::OBBBOX3D, ColType::OBBBOX3D);
	if (4 <= m_MainRender->GetCurrentFrame() || PartitionCol != nullptr || DoorCol != nullptr ||
		PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition() + float4::Up) ||
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition() + float4::Up))
	{
		// 나중에 추가할 거 있으면 추가 
		return;
	}

	// 플레이어 x축 계산  
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MyPos = GetTransform()->GetWorldPosition();
	float FlyingSpeed = m_FlyingSpeed;

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

void Monster_Gangster::HitGroundEnd()
{
	m_HitPos = float4{ 0.0f, 0.0f };
	m_IsDeath = false;
}

void Monster_Gangster::ForceFallStart()
{
	m_MainRender->ChangeAnimation("gangster_forcefall");
	m_CurrentVerticalVelocity = m_JumpPower;
}

void Monster_Gangster::ForceFallUpdate(float _DeltaTime)
{
	m_CurrentVerticalVelocity -= m_GravityPower * _DeltaTime;
	GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);
}

void Monster_Gangster::ForceFallEnd()
{
	m_CurrentVerticalVelocity = 0.0f;
}

void Monster_Gangster::RecordingProgressStart()
{
}

void Monster_Gangster::RecordingProgressUpdate(float _DeltaTime)
{
	// 레코딩이 종료 되었다면 아이들로 전환. 
	if (true == m_Recording_Complete)
	{
		m_Recording_Complete = false;
		Reset();
		ChangeState(GangsterState::IDLE);
		return;
	}

	// 여기서 역재생을 수행하고, 
	Reverse(m_MainRender.get());
}

void Monster_Gangster::RecordingProgressEnd()
{
}

