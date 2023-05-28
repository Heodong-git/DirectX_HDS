#include "PrecompileHeader.h"
#include "Monster_Grunt.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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

void Monster_Grunt::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::MONSTER));
	m_MainRender->GetTransform()->SetLocalPosition({ 0, 0 });
	m_MainRender->SetScaleRatio(2.0f);

	// 콜리전 생성
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::MONSTER));
	m_Collision->GetTransform()->SetLocalScale({ 100.0f, 100.0f });
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, 0.0f });
}

void Monster_Grunt::LoadAndCreateAnimation()
{
	//// 여기서 필요한 리소스 로드 후 애니메이션 만들어
	//{
	//	if (nullptr == GameEngineSprite::Find("grunt_idle"))
	//	{
	//		GameEngineDirectory Dir;
	//		Dir.MoveParentToDirectory("katanazero_resources");
	//		Dir.Move("katanazero_resources");
	//		Dir.Move("Texture");
	//		Dir.Move("ClubLevel");
	//		Dir.Move("grunt");

	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_idle").GetFullPath());
	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_walk").GetFullPath());
	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_hitground").GetFullPath());
	//		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_run").GetFullPath());

	//		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	//	}
	//}

	//m_MainRender->CreateAnimation({ .AnimationName = "grunt_idle", .SpriteName = "grunt_idle", .Start = 0, .End = 7 ,
	//							  .FrameInter = 0.12f , .Loop = true , .ScaleToTexture = true });
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
	}
}

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void Monster_Grunt::ChangeState(GruntState _State)
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
	}
}


void Monster_Grunt::IdleStart()
{
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
}

void Monster_Grunt::HitGroundUpdate(float _DeltaTime)
{
}

void Monster_Grunt::HitGroundEnd()
{
}
