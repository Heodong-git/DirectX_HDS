#include "PrecompileHeader.h"
#include "Monster_Grunt.h"

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

	// 렌더러생성 및 세팅
	ComponentSetting();
	// 리소스 로드
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
	// 내가 플레이어의 공격과 충돌했다면 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	if (nullptr != Col)
	{
		GameEngineTransform* colobj = Col->GetTransform()->GetParent();
		std::shared_ptr<SlashHit_Effect> Effect = GetLevel()->CreateActor<SlashHit_Effect>(static_cast<int>(RenderOrder::EFFECT));
		float4 MyPos = GetTransform()->GetLocalPosition();
		Effect->GetTransform()->SetLocalPosition({ MyPos.x, MyPos.y + m_HitEffectPivot });
		m_Collision->Off();

		// 내가죽었으니까 -1 
		GetReturnCastLevel()->DisCount();
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

	// 콜리전 생성
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0.0f, m_ColPivot });
	m_Collision->DebugOff();

	// 디버그렌더
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale({ 4,  4 });
	m_DebugRender->Off();
}

void Monster_Grunt::LoadAndCreateAnimation()
{
	// 여기서 필요한 리소스 로드 후 애니메이션 만들어
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

	m_MainRender->ChangeAnimation("grunt_turn");
}

void Monster_Grunt::Reset()
{
	// 나의 초기 세팅위치로 이동
	GetTransform()->SetLocalPosition(GetInitPos());
	ChangeState(GruntState::IDLE);
	if (false == m_Collision->IsUpdate())
	{
		m_Collision->On();
	}
	ResetDir();
}


void Monster_Grunt::DirCheck()
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

void Monster_Grunt::UpdateState(float _DeltaTime)
{
	// 현재 상태의 update 호출 
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

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
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

	// 이전 state의 end 
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
}

void Monster_Grunt::IdleEnd()
{
}

void Monster_Grunt::WalkStart()
{
}

void Monster_Grunt::WalkUpdate(float _DeltaTime)
{
}

void Monster_Grunt::WalkEnd()
{
}

void Monster_Grunt::ChaseStart()
{
}

void Monster_Grunt::ChaseUpdate(float _DeltaTime)
{
}

void Monster_Grunt::ChaseEnd()
{
}

void Monster_Grunt::HitGroundStart()
{
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
