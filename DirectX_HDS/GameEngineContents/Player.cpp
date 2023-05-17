#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Cursor.h"
#include "PixelCollider.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	// �÷��̾�� ������ �ϳ� 
	MainPlayer = this;
}

Player::~Player()
{
}

void Player::Start()
{
	// ���� ��ŸƮ �⺻�������̽� ����
	// Ű����
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

	// ������Ʈ ����
	ComponentSetting();

	// �ʿ��� ���ҽ� �ε�� �ִϸ��̼� ����
	LoadAndCreateAnimation();
}

void Player::LoadAndCreateAnimation()
{
	// ���Ϸε� �⺻�������̽� 
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
									  .FrameInter = 0.12f , .Loop = true , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_attack", .SpriteName = "player_attack", .Start = 0, .End = 6 ,
									  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_idle_to_run", .SpriteName = "player_idle_to_run", .Start = 0, .End = 3 ,
								  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

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

void Player::Update(float _DeltaTime)
{
	//std::vector<std::shared_ptr<GameEngineCollision>> TestVector;
	//// �浹�׽�Ʈ�ڵ� �ߵȴ� 
	//if (m_Collision->CollisionAll(2, ColType::AABBBOX3D, ColType::AABBBOX3D, TestVector))
	//{
	//	int a = 0;
	//}

	// �������üũ 
	DirCheck();

	// ���¾�����Ʈ
	UpdateState(_DeltaTime);

	// ����� ������Ʈ
	DebugUpdate();
}

void Player::Render(float _DeltaTime)
{
}

void Player::ComponentSetting()
{
	// �÷��̾� ���η���
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->GetTransform()->SetLocalPosition({ 0, PlayerPos.y + 36.0f });
	m_Render->SetScaleRatio(2.0f);

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::PLAYER));
	m_Collision->GetTransform()->SetLocalScale(m_LocalScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0, PlayerPos.y + 36.0f });

	// �ȼ��ö��̴� ����
	m_PixelCollider = std::make_shared<PixelCollider>();
	// ���� ���⼭ �ʼ�����, ���� ����
	m_PixelCollider->Start();

	// --------------------------- Debug Render ------------------------------

	// bottom 
	m_DebugRender_Bottom = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender_Bottom->GetTransform()->SetLocalScale(m_DebugRenderScale);

	m_DebugRender_Left = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender_Left->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Left->GetTransform()->SetLocalPosition({ -36.0f, PlayerPos.y + 36.0f });
	
	m_DebugRender_Right = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender_Right->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Right->GetTransform()->SetLocalPosition({ 36.0f, PlayerPos.y + 36.0f });

	m_DebugRender_Top = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender_Top->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Top->GetTransform()->SetLocalPosition({ 0.0f , PlayerPos.y + 72.0f });
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
	}

	if (true == GameEngineInput::IsPress("player_left_move"))
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
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
		m_DebugRender_Bottom->On();
		m_DebugRender_Left->On();
		m_DebugRender_Right->On();
		m_DebugRender_Top->On();
	}

	else if (false == IsDebug())
	{
		m_DebugRender_Bottom->Off();
		m_DebugRender_Left->Off();
		m_DebugRender_Right->Off();
		m_DebugRender_Top->Off();
	}
}

// ---------------------------------------- state ------------------------------------------ 
void Player::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
	switch (m_CurState)
	{
	case PlayerState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case PlayerState::IDLETORUN:
		IdleToRunUpdate(_DeltaTime);
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

// state ����, ����� ������ start, ���� ������ end ����
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
	case PlayerState::IDLETORUN:
		IdleToRunStart();
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

	// ���� state�� end 
	switch (m_PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::IDLETORUN:
		IdleToRunEnd();
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
	// ����Ű , w
	if (true == GameEngineInput::IsDown("player_jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	// ũ���ġ , s
	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	// �����̵� , d
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		ChangeState(PlayerState::IDLETORUN);
		return;
	}

	// �����̵� , a 
	else if (true == GameEngineInput::IsPress("player_left_move"))
	{
		ChangeState(PlayerState::IDLETORUN);
		return;
	}

	// ����, ���콺 ��Ŭ�� 
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
	m_Render->ChangeAnimation("player_idle_to_run");
}

void Player::IdleToRunUpdate(float _DeltaTime)
{
	// �ִϸ��̼��� ����Ǹ� Move�� ��ȯ�ϴµ�. 
	// ���� ����� ������ Ű�� �������� �ʰ� ���� ���� �ִٸ� ���̵�� �ٽ� ��ȯ. 
	if (true == m_Render->IsAnimationEnd())
	{
		if (true == GameEngineInput::IsPress("player_right_move") ||
			true == GameEngineInput::IsPress("player_left_move"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		// �װ� �ƴ϶�� 
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == GameEngineInput::IsPress("player_jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == GameEngineInput::IsPress("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	// �����Ҽ���
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		// true �̸� �� ���ΰɷ�
		if (false == m_PixelCollider->RightPixelCheck())
		{
			if (false == m_PixelCollider->GroundCheck(this))
			{
				//GetTransform()->AddLocalPosition(float4::Down * m_GravityPower * _DeltaTime);
			}

			DirCheck();
			GetTransform()->AddLocalPosition(float4::Right * m_StartMoveSpeed * _DeltaTime);
		}
		return;
	}

	else if (true == GameEngineInput::IsPress("player_left_move"))
	{
		if (false == m_PixelCollider->LeftPixelCheck())
		{
			if (false == m_PixelCollider->GroundCheck(this))
			{
				//GetTransform()->AddLocalPosition(float4::Down * m_GravityPower * _DeltaTime);
			}
			DirCheck();
			GetTransform()->AddLocalPosition(float4::Left * m_StartMoveSpeed * _DeltaTime);
		}
		return;
	}
	
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
	if (false == m_PixelCollider->GroundCheck(this))
	{
		//GetTransform()->AddLocalPosition(float4::Down * m_GravityPower * _DeltaTime);
	}
	

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
	
		// true �̸� �� ���ΰɷ�
		if (false == m_PixelCollider->RightPixelCheck())
		{
			m_Direction = true;
			GetTransform()->SetLocalPositiveScaleX();
			GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
		}
		
		return;
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		// true �̸� �� ���ΰɷ�
		if (false == m_PixelCollider->LeftPixelCheck())
		{
			m_Direction = false;
			GetTransform()->SetLocalNegativeScaleX();
			GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
		}
		
		return;
	}
}

void Player::MoveEnd()
{
}

void Player::SlashStart()
{
	m_Render->ChangeAnimation("player_attack");
	// ���ݽ��۽� ���� ���������� �޾Ƶд�. 
	m_AttackPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
}

void Player::SlashUpdate(float _DeltaTime)
{
	// ���� �ִϸ��̼� ����� ������ �� 
	if (true == m_Render->FindAnimation("player_attack")->IsEnd())
	{
		// ��ġ�� ���̶�� ���̵�� ����
		if (true == m_PixelCollider->GroundCheck(this))
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		// ���� �ƴ� ��� fall ���·� ����
		ChangeState(PlayerState::FALL);
		return;
	}

	// �Ʒ��� ����� ���;��� �� �ϴ� �ӽ÷�, �ʹ�,���������� �������� ��� 
	if (true == m_PixelCollider->GroundCheck(this))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	// ����ġ
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

	// �����ؾ� �� ����.
	if (true == m_PixelCollider->TopPixelCheck())
	{
		MoveDir.y = 0.0f;
	}

	GetTransform()->AddLocalPosition(float4{ MoveDir.x * 1.2f , MoveDir.y } *m_MoveSpeed * _DeltaTime);
}

// ������ ����Ǹ� ������ġ�� �ʱ�ȭ 
void Player::SlashEnd()
{
	m_AttackPos = { 0 , 0 };
}


void Player::JumpStart()
{
	// ���� ���°� false �� ��� 
	if (false == m_IsJumping)
	{
		// true �� ������ش�. 
		m_IsJumping = true;
		m_CurrentVerticalVelocity = m_JumpPower;
	}

	m_Render->ChangeAnimation("player_jump");
}

void Player::JumpUpdate(float _DeltaTime)
{
	if (true == m_PixelCollider->TopPixelCheck())
	{
		m_CurrentVerticalVelocity /= 4.0f;
	}

	// ���� ���� ������ �� ���� ���̶��
	if (true == m_PixelCollider->GroundCheck(this))
	{
		// �� �ʱ�ȭ �� ���̵�� ����
		m_CurrentVerticalVelocity = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	// �׽�Ʈ
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

	// ������ ���� �߷��� �����ش�. 
	m_CurrentVerticalVelocity += -m_GravityPower * _DeltaTime;
	
	// ���� 
	GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);

	// ��ġüũ�� ���� 
	float4 Pos = GetTransform()->GetLocalPosition();

	// ������ �¿� �̵��� ������ �ڵ� 
	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		// �ִϸ��̼� ���⺸��
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

	if (true == GameEngineInput::IsPress("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
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
	if (false == m_PixelCollider->GroundCheck(this))
	{
		//GetTransform()->AddLocalPosition(float4::Down * m_GravityPower * _DeltaTime);
	}

	// ���⺸�� 
	if (true == m_Direction)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	else if (false == m_Direction)
	{
		GetTransform()->SetLocalNegativeScaleX();
	}

	// �ø� ���� , �ȼ��浹 ���ó��� �߰��ؾ��� 
	// ���� �ø��� true ��� 
	if (true == m_RightFlip)
	{
		// �ø� �ִϸ��̼��� ���� �Ǿ��ٸ�
		if (true == m_Render->FindAnimation("player_flip")->IsEnd())
		{
			// ����ġ�� ���̶�� 
			if (true == m_PixelCollider->GroundCheck(this))
			{
				// ���ε� �Ʒ�Ű�� �����ִٸ� 
				if (true == GameEngineInput::IsPress("player_crouch"))
				{
					ChangeState(PlayerState::CROUCH);
					return;
				}

				// �װ� �ƴ϶�� ���̵� 
				ChangeState(PlayerState::IDLE);
				return;
			}
		}

		GetTransform()->AddLocalPosition(float4::Right * m_FlipSpeed * _DeltaTime);
	}

	else if (true == m_LeftFlip)
	{
		// �ø� �ִϸ��̼��� ���� �Ǿ��ٸ�
		if (true == m_Render->FindAnimation("player_flip")->IsEnd())
		{
			// ����ġ�� ���̶�� 
			if (true == m_PixelCollider->GroundCheck(this))
			{
				// ���ε� �Ʒ�Ű�� �����ִٸ� 
				if (true == GameEngineInput::IsPress("player_crouch"))
				{
					ChangeState(PlayerState::CROUCH);
					return;
				}

				// �װ� �ƴ϶�� ���̵� 
				ChangeState(PlayerState::IDLE);
				return;
			}
		}

		GetTransform()->AddLocalPosition(float4::Left * m_FlipSpeed * _DeltaTime);
	}

	// �ִϸ��̼��� ����Ǹ� 
	if (true == m_Render->FindAnimation("player_flip")->IsEnd())
	{
		if (true == GameEngineInput::IsPress("player_crouch"))
		{
			ChangeState(PlayerState::CROUCH);
			return;
		}

		ChangeState(PlayerState::IDLE);
		return;
	}

	// ������ �¿� �̵��� ������ �ڵ� 
	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		// �ִϸ��̼� ���⺸��
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
		m_RightFlip = true;
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
		m_LeftFlip = true;
	}
}

void Player::FlipEnd()
{
	m_RightFlip = false;
	m_LeftFlip = false;

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
		//dsafdfdsf
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
		GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
	}

	// ���� ���̶��
	if (true == m_PixelCollider->GroundCheck(this))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// ���̾ƴ϶��
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

