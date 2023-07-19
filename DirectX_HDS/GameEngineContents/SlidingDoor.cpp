#include "PrecompileHeader.h"
#include "SlidingDoor.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "LandEffect.h"

#include "BaseLevel.h"
SlidingDoor::SlidingDoor()
{
}

SlidingDoor::~SlidingDoor()
{
}

void SlidingDoor::Start()
{
	ComponentSetting();
	LoadAndCreateAnimation();
	ChangeState(SlidingDoorState::OPEN);
}

void SlidingDoor::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
}

void SlidingDoor::Render(float _DeltaTime)
{
}

void SlidingDoor::DebugUpdate()
{
}

void SlidingDoor::ComponentSetting()
{
	m_DoorRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DOOR);
	m_BaseRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DOOR);

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::SLIDINGDOOR);
	m_Collision->GetTransform()->SetLocalScale(float4{ 20.0f , 20.0f });
}

void SlidingDoor::LoadAndCreateAnimation()
{
	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("slidingdoor_base_green"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("sliding_door");
		
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("slidingdoor_base_green").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("slidingdoor_base_red").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("slidingdoor_0").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_BaseRender->CreateAnimation({ .AnimationName = "slidingdoor_base_green", .SpriteName = "slidingdoor_base_green", .Start = 0, .End = 2 ,
								.FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_BaseRender->CreateAnimation({ .AnimationName = "slidingdoor_base_red", .SpriteName = "slidingdoor_base_red", .Start = 0, .End = 2 ,
							.FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_BaseRender->ChangeAnimation("slidingdoor_base_green");
	m_BaseRender->SetScaleRatio(2.0f);

	m_DoorRender->SetTexture("spr_sliding_door_0.png");
	m_DoorRender->GetTransform()->SetLocalScale(float4{ 34.0f, 160.0f });
	m_DoorRender->GetTransform()->SetLocalPosition(float4{ 0.0f, 80.0f });
}

void SlidingDoor::Reset()
{
	// 만약 내가 오픈상태라면 클로즈 상태로 변경 
	if (SlidingDoorState::OPEN == m_CurState)
	{
		ChangeState(SlidingDoorState::CLOSE);
		float4 Pos = m_BaseRender->GetTransform()->GetLocalPosition();
		m_DoorRender->GetTransform()->SetLocalPosition(Pos);
		m_Collision->GetTransform()->SetLocalPosition(Pos);
	}
}
// -------------------------------------------- State ----------------------------------------------------

void SlidingDoor::UpdateState(float _DeltaTime)
{
	// 현재 상태의 update 호출 
	switch (m_CurState)
	{
	case SlidingDoorState::CLOSE:
		CloseUpdate(_DeltaTime);
		break;
	case SlidingDoorState::OPEN:
		OpenUpdate(_DeltaTime);
		break;
	}
}

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void SlidingDoor::ChangeState(SlidingDoorState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	switch (m_NextState)
	{
	case SlidingDoorState::CLOSE:
		CloseStart();
		break;
	case SlidingDoorState::OPEN:
		OpenStart();
		break;
	}

	// 이전 state의 end 
	switch (m_PrevState)
	{
	case SlidingDoorState::CLOSE:
		CloseEnd();
		break;
	case SlidingDoorState::OPEN:
		OpenEnd();
		break;
	}
}

void SlidingDoor::CloseStart()
{
	GameEngineSound::Play("sound_boss_wall_open.wav");
	m_BaseRender->ChangeAnimation("slidingdoor_base_red");
}

void SlidingDoor::CloseUpdate(float _DeltaTime)
{
	// 도어렌더러를 아래로 이동시킨다.
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::PLATFORM, ColType::OBBBOX2D, ColType::OBBBOX2D);
	if (nullptr == Col)
	{
		m_Collision->GetTransform()->AddLocalPosition(float4::Down * 500.0f * _DeltaTime);
		m_DoorRender->GetTransform()->AddLocalPosition(float4::Down * 500.0f * _DeltaTime);
	}
}

void SlidingDoor::CloseEnd()
{
}

void SlidingDoor::OpenStart()
{
	
	m_BaseRender->ChangeAnimation("slidingdoor_base_green");
}

void SlidingDoor::OpenUpdate(float _DeltaTime)
{
	if (BaseLevel::LevelState::PLAY == GetReturnCastLevel()->GetCurState())
	{
		ChangeState(SlidingDoorState::CLOSE);
		return;
	}
}

void SlidingDoor::OpenEnd()
{
}
