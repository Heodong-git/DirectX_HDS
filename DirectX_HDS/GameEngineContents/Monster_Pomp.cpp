#include "PrecompileHeader.h"
#include "Monster_Pomp.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"

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
	DirCheck();

	// 내가 플레이어의 공격과 충돌했다면 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	// 뭔가가 들어왔다는건 충돌했다는거고 
	// 그럼 충돌한 액터를 데스시키고 레벨리셋 호출 
	if (nullptr != Col)
	{
		GameEngineTransform* colobj = Col->GetTransform()->GetParent();
		// 나의 충돌체를 off
		// 애니메이션 렌더를 데스애니메이션으로전환 
		m_Collision->Off();
		// 내가죽었으니까 -1 
		GetReturnCastLevel()->DisCount();
		ChangeState(PompState::HITGROUND);
	}

	UpdateState(_DeltaTime);
	DebugUpdate();
}

void Monster_Pomp::Render(float _DeltaTime)
{
}

void Monster_Pomp::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("Pomp_DebugSwitch"))
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

void Monster_Pomp::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::MONSTER));
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f, 40.0f });
	m_MainRender->SetScaleRatio(2.0f);

	// 콜리전 생성
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::MONSTER));
	m_Collision->GetTransform()->SetLocalScale({ 50.0f, 50.0f });
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, 50.0f });

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>();
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

	m_MainRender->ChangeAnimation("pomp_turn");
}


// 내리셋은 플레이어와 동일 
void Monster_Pomp::Reset()
{
	// 나의 초기 세팅위치로 이동
	GetTransform()->SetLocalPosition(GetInitPos());
	ChangeState(PompState::IDLE);
	if (false == m_Collision->IsUpdate())
	{
		m_Collision->On();
	}
	ResetDir();
}

void Monster_Pomp::DirCheck()
{
	// 포지티브, 네거티브 함수 사용시에 렌더가 아니라 액터의 트랜스폼을 사용해야함 ㅎㅎ 
	// 방향체크 
	// 오른쪽 
	if (0 < m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	// 왼쪽 
	else if (0 > m_Direction)
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
	}
}

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void Monster_Pomp::ChangeState(PompState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	//WALK,	 // 걷기
	//	CHASE,	 // 뛰기 
	//	HIT,	 // 쳐맞음
	//	AIM,	 // 공격 

	// start 
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
	}
}


void Monster_Pomp::IdleStart()
{
	m_MainRender->ChangeAnimation("pomp_idle");
}

void Monster_Pomp::IdleUpdate(float _DeltaTime)
{
}

void Monster_Pomp::IdleEnd()
{
}

void Monster_Pomp::WalkStart()
{
}

void Monster_Pomp::WalkUpdate(float _DeltaTime)
{
}

void Monster_Pomp::WalkEnd()
{
}

void Monster_Pomp::ChaseStart()
{
}

void Monster_Pomp::ChaseUpdate(float _DeltaTime)
{
}

void Monster_Pomp::ChaseEnd()
{
}

void Monster_Pomp::HitGroundStart()
{
	m_MainRender->ChangeAnimation("pomp_hurtground");
}

void Monster_Pomp::HitGroundUpdate(float _DeltaTime)
{
}

void Monster_Pomp::HitGroundEnd()
{
}

void Monster_Pomp::AttackStart()
{
}

void Monster_Pomp::AttackUpdate(float _DeltaTime)
{
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
}

void Monster_Pomp::KnockDownUpdate(float _DeltaTime)
{
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
