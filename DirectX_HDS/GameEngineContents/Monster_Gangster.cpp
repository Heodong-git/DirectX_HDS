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
	// 렌더러생성 및 세팅
	ComponentSetting();
	// 리소스 로드
	LoadAndCreateAnimation();

	// aim 스테이트로 변경되면 방향확인해서 이미지세팅해줘야함 지금은 일단 띄워
	// m_GunRender->SetTexture("gangster_gun_left.png");

	ChangeState(GangsterState::IDLE);
}

void Monster_Gangster::Update(float _DeltaTime)
{
	// 내가 플레이어의 공격과 충돌했다면 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLAYER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	// 뭔가가 들어왔다는건 충돌했다는거고 
	// 그럼 충돌한 액터를 데스시키고 레벨리셋 호출 
	if (nullptr != Col)
	{
		// 나의 충돌체를 off
		// 애니메이션 렌더를 데스애니메이션으로전환 
		m_Collision->Off();
		
		// 내가죽었으니까 -1 
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
	
	// 렌더러, 충돌체 생성
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f , 38.0f});
	// m_MainRender->GetTransform()->SetLocalScale({ 200.0f , 200.0f });
	m_MainRender->SetScaleRatio(2.0f);

	// 총렌더 생성 ㅡㅡ 음.. 이미지세팅으로  
	m_GunRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	// 피봇추가해야함 
	m_GunRender->GetTransform()->SetLocalPosition(MyPos);
	m_GunRender->GetTransform()->SetLocalScale({ 54.0f , 12.0f });
	m_GunRender->Off();

	// 콜리전 생성
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::MONSTER);
	m_Collision->GetTransform()->SetLocalScale({ 50.0f, 50.0f });
	m_Collision->GetTransform()->SetLocalPosition({ 0.0, 50.0f });

	// 디버그렌더 생성
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
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
	// 나의 초기 세팅위치로 이동
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
	}
}


// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void Monster_Gangster::ChangeState(GangsterState _State)
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
