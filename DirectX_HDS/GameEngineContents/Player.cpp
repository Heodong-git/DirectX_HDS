#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Cursor.h"
#include "PixelCollider.h"

// 임시
#include <algorithm>

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	// 플레이어는 어차피 하나 
	MainPlayer = this;
}

Player::~Player()
{
}

void Player::Start()
{
	if (false == GameEngineInput::IsKey("player_slash"))
	{
		GameEngineInput::CreateKey("player_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("player_slash", VK_LBUTTON);
		GameEngineInput::CreateKey("player_snail", VK_LSHIFT);
		GameEngineInput::CreateKey("player_left_Move", 'A');
		GameEngineInput::CreateKey("player_right_Move", 'D');
		GameEngineInput::CreateKey("player_jump", 'W');
		GameEngineInput::CreateKey("player_crouch", 'S');
	}

	// 플레이어 메인렌더러 세팅
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetPipeLine("2DTexture");
	m_Render->GetTransform()->SetLocalPosition({ 0, PlayerPos.y + 36.0f });
	m_Render->SetAtlasConstantBuffer();
	m_Render->SetScaleRatio(2.0f);

	// 디버그 렌더러 생성
	// 플레이어 바텀 위치
	m_DebugRender0 = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender0->SetPipeLine("2DTexture");
	m_DebugRender0->SetAtlasConstantBuffer();
	m_DebugRender0->GetTransform()->SetLocalScale({ 2  , 2 });

	// 픽셀컬라이더 생성
	m_PixelCollider = std::make_shared<PixelCollider>();
	// 현재 여기서 맵세팅중, 추후 수정 예정
	m_PixelCollider->Start();

	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::PLAYER));
	m_Collision->GetTransform()->SetLocalScale( { 75, 75 });
	m_Collision->GetTransform()->SetLocalPosition({ 0, PlayerPos.y + 36.0f });

	// 애니메이션 생성
	FindAndCreateAnimation();
}

void Player::Update(float _DeltaTime)
{
	//std::vector<std::shared_ptr<GameEngineCollision>> TestVector;
	//// 충돌테스트코드 잘된다 
	//if (m_Collision->CollisionAll(2, ColType::AABBBOX3D, ColType::AABBBOX3D, TestVector))
	//{
	//	int a = 0;
	//}

	DirCheck();
	UpdateState(_DeltaTime);
	DebugUpdate();
}

void Player::Render(float _DeltaTime)
{
}

void Player::FindAndCreateAnimation()
{
	// 파일로드 기본인터페이스 
	{
		if (nullptr == GameEngineSprite::Find("player_idle"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("katanazero_resources");
			Dir.Move("katanazero_resources");
			Dir.Move("Texture");
			Dir.Move("ClubLevel");
			Dir.Move("player");

			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_idle").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_attack").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_idle_to_run").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_run").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_run_to_idle").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_crouch").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_flip").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_doorbreak").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_doorbreak_full").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_dooropen_gentle").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_fall").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_hurtfly_begin").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_hurtfly_loop").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_hurtground").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_hurtrecover").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_jump").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_wallslide").GetFullPath());

			std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
		}
	}

	m_Render->CreateAnimation({ .AnimationName = "player_idle", .SpriteName = "player_idle", .Start = 2, .End = 10 ,
									  .FrameInter = 0.12f , .Loop = true , .ScaleToTexture = true});

	m_Render->CreateAnimation({ .AnimationName = "player_attack", .SpriteName = "player_attack", .Start = 0, .End = 6 ,
									  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_idle_to_run", .SpriteName = "player_idle_to_run", .Start = 0, .End = 3 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_run", .SpriteName = "player_run", .Start = 0, .End = 9 ,
								  .FrameInter = 0.05f , .Loop = true , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_run_to_idle", .SpriteName = "player_run_to_idle", .Start = 0, .End = 4 ,
								  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_crouch", .SpriteName = "player_crouch", .Start = 0, .End = 0 ,
							  .FrameInter = 0.01f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_flip", .SpriteName = "player_flip", .Start = 0, .End = 10,
						  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_doorbreak", .SpriteName = "player_doorbreak", .Start = 0, .End = 5,
						  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_doorbreak_full", .SpriteName = "player_doorbreak_full", .Start = 0, .End = 9,
						  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_dooropen_gentle", .SpriteName = "player_dooropen_gentle", .Start = 0, .End = 8,
						  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_fall", .SpriteName = "player_fall", .Start = 0, .End = 3,
						  .FrameInter = 0.05f , .Loop = true , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_hurtfly_begin", .SpriteName = "player_hurtfly_begin", .Start = 0, .End = 1,
						  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_hurtfly_loop", .SpriteName = "player_hurtfly_loop", .Start = 0, .End = 3,
						  .FrameInter = 0.05f , .Loop = true , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_hurtground", .SpriteName = "player_hurtground", .Start = 0, .End = 5,
					  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_hurtrecover", .SpriteName = "player_hurtrecover", .Start = 0, .End = 8,
					  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_jump", .SpriteName = "player_jump", .Start = 0, .End = 3,
					  .FrameInter = 0.05f , .Loop = true , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_wallslide", .SpriteName = "player_wallslide", .Start = 0, .End = 1,
					  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->ChangeAnimation("player_idle");
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsPress("player_left_move"))
	{
		m_Direction = false;
	}

	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		m_Direction = true;
	}
}

// ---------------------------------------- Debug -----------------------------------------
void Player::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_debugswitch"))
	{
		DebugSwitch();
	}

	if (true == IsDebug())
	{
		m_DebugRender0->On();
	}

	else if (false == IsDebug())
	{
		m_DebugRender0->Off();
	}
}

// ---------------------------------------- state ------------------------------------------ 
void Player::UpdateState(float _DeltaTime)
{
	// 맞나.
	// AddGravity(_DeltaTime);

	// 현재 상태의 update 호출 
	switch (m_CurState)
	{
	case PlayerState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_DeltaTime);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_DeltaTime);
		break;
	case PlayerState::SLASH:
		SlashUpdate(_DeltaTime);
		break; 
	case PlayerState::CROUCH:
		CrouchUpdate(_DeltaTime);
		break;
	case PlayerState::FLIP:
		FlipUpdate(_DeltaTime);
		break;
	case PlayerState::FALL:
		FallUpdate(_DeltaTime);
		break;
	}
}

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void Player::ChangeState(PlayerState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	// start 
	switch (m_NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::JUMP:
		JumpStart();
		break;
	case PlayerState::SLASH:
		SlashStart();
		break;
	case PlayerState::CROUCH:
		CrouchStart();
		break;
	case PlayerState::FLIP:
		FlipStart();
		break;
	case PlayerState::FALL:
		FallStart();
		break;
	}

	// 이전 state의 end 
	switch (m_PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	case PlayerState::JUMP:
		JumpEnd();
		break;
	case PlayerState::SLASH:
		SlashEnd();
		break;
	case PlayerState::CROUCH:
		CrouchEnd();
		break;
	case PlayerState::FLIP:
		FlipEnd();
		break;
	case PlayerState::FALL:
		FallEnd();
		break;
	}
}

void Player::IdleStart()
{
	m_Render->ChangeAnimation("player_idle");
}

void Player::IdleUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("player_jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	// 임시무브 
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}
	else if (true == GameEngineInput::IsPress("player_left_move"))
	{
		
		ChangeState(PlayerState::MOVE);
		return;
	}

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

}

void Player::IdleEnd()
{
}

void Player::IdleToRunStart()
{
}

void Player::IdleToRunUpdate(float _DeltaTime)
{
}

void Player::IdleToRunEnd()
{
}

void Player::MoveStart()
{
	m_Render->ChangeAnimation("player_run");
}

void Player::MoveUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	if (true == GameEngineInput::IsDown("player_jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == GameEngineInput::IsDown("player_crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (false == GameEngineInput::IsPress("player_left_move") && 
		false == GameEngineInput::IsPress("player_right_move"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}


	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
		GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
		//GetLevel()->GetMainCamera()->GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{
	
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
		GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
		//GetLevel()->GetMainCamera()->GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
	}
}

void Player::MoveEnd()
{
}

void Player::SlashStart()
{
	m_Render->ChangeAnimation("player_attack");
	m_AttackPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();

}

void Player::SlashUpdate(float _DeltaTime)
{
	if (true == m_Render->FindAnimation("player_attack")->IsEnd())
	{
		if (true == m_PixelCollider->GroundCheck(this))
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		ChangeState(PlayerState::FALL);
		return;
	}


	// 아래로 모션은 나와야함 음 일단 임시로, 맵밖,범위밖으로 공격했을 경우 
	if (true == m_PixelCollider->GroundCheck(this))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 만약 마우스의 x축이 나보다 크면 정방향 , x 축이 나보다 작으면 역방향
	float4 MyPos = GetTransform()->GetLocalPosition();
	if (MyPos.x <= m_AttackPos.x)
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
	}

	else if (MyPos.x > m_AttackPos.x)
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
	}

	float4 MoveDir = m_AttackPos - MyPos;
	MoveDir.Normalize();
	GetTransform()->AddLocalPosition(float4{ MoveDir.x * 1.2f , MoveDir.y } *m_MoveSpeed * _DeltaTime);
}

void Player::SlashEnd()
{
	m_AttackPos = { 0 , 0 };
}

void Player::JumpStart()
{
	if (false == m_IsJumping)
	{
		m_IsJumping = true;
		m_CurrentVerticalVelocity = m_JumpPower;
	}

	m_Render->ChangeAnimation("player_jump");
}

void Player::JumpUpdate(float _DeltaTime)
{
	if (true == m_PixelCollider->GroundCheck(this))
	{
		m_CurrentVerticalVelocity = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	// 테스트
	if (true == GameEngineInput::IsPress("player_slash"))
	{
		m_CurrentVerticalVelocity = 0.0f;
		ChangeState(PlayerState::SLASH);
		return;
	}

	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		m_CurrentVerticalVelocity = 0.0f;
		ChangeState(PlayerState::FALL);
		return;
	}
	//// 중력적용
	m_CurrentVerticalVelocity += -m_GravityPower * _DeltaTime;
	
	// 점프 
	GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);
	float4 Pos = GetTransform()->GetLocalPosition();

	// 좌우 이동
	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
		GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
		GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
	}
}

void Player::JumpEnd()
{
	m_IsJumping = false;
}

void Player::CrouchStart()
{
	m_Render->ChangeAnimation("player_crouch");
}

void Player::CrouchUpdate(float _DeltaTime)
{
	if (false == GameEngineInput::IsPress("player_crouch"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	if (true == GameEngineInput::IsDown("player_right_move"))
	{
		ChangeState(PlayerState::FLIP);
		return;
	}

	if (true == GameEngineInput::IsDown("player_left_move"))
	{
		ChangeState(PlayerState::FLIP);
		return;
	}
}

void Player::CrouchEnd()
{
}

void Player::FlipStart()
{
	m_Render->ChangeAnimation("player_flip");
}

void Player::FlipUpdate(float _DeltaTime)
{
	if (true == m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	else if (false == m_Direction)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}


	if (true == m_Render->FindAnimation("player_flip")->IsEnd())
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}
}

void Player::FlipEnd()
{
	if (true != GameEngineInput::IsPress("player_crouch"))
	{
		if (true == GameEngineInput::IsPress("player_right_move") || true == GameEngineInput::IsPress("player_left_move"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}
	}


}

void Player::FallStart()
{
	m_Render->ChangeAnimation("player_fall");
}

void Player::FallUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
		GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{

		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
		GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
	}

	// 현재 땅이라면
	if (true == m_PixelCollider->GroundCheck(this))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 땅이아니라면
	else if (false == m_PixelCollider->GroundCheck(this))
	{
		GetTransform()->AddLocalPosition(float4{ 0 , -1 } * 500.0f * _DeltaTime);
		return;
	}

	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		GetTransform()->AddLocalPosition(float4::Down * m_FallPower * _DeltaTime);
	}
}

void Player::FallEnd()
{
}

