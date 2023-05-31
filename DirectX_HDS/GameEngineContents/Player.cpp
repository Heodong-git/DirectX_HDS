#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ÿ������ 
#include <typeinfo>

// ������ �߰��ɶ����� ����߰� �� Reset �Լ��� �߰�.. 
#include "ClubLevel_00.h"
#include "ClubLevel_01.h"
#include "ClubLevel_02.h"
#include "ClubLevel_03.h"
#include "ClubLevel_04.h"
#include "ClubLevel_Boss.h"

// ī�޶�
#include "PlaySupporter.h"

#include "BaseLevel.h"
#include "Cursor.h"
#include "PixelCollider.h"
#include "SlashEffect.h"
#include "JumpEffect.h"
#include "LandEffect.h"
#include "DashEffect.h"

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

	// ������Ʈ ����
	ComponentSetting();
	// �ʿ��� ���ҽ� �ε�� �ִϸ��̼� ����
	LoadAndCreateAnimation();

	if (false == GameEngineInput::IsKey("player_slash"))
	{
		GameEngineInput::CreateKey("player_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("player_slash", VK_LBUTTON);
		GameEngineInput::CreateKey("player_skill_slow", VK_LSHIFT);
		GameEngineInput::CreateKey("player_left_Move", 'A');
		GameEngineInput::CreateKey("player_right_Move", 'D');
		GameEngineInput::CreateKey("player_jump", 'W');
		GameEngineInput::CreateKey("player_crouch", 'S');
	}
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
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_roll").GetFullPath());
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_die").GetFullPath());

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

	m_Render->CreateAnimation({ .AnimationName = "player_roll", .SpriteName = "player_roll", .Start = 0, .End = 6 ,
									  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });

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
						  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_hurtground", .SpriteName = "player_hurtground", .Start = 0, .End = 5,
					  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_hurtrecover", .SpriteName = "player_hurtrecover", .Start = 0, .End = 8,
					  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_jump", .SpriteName = "player_jump", .Start = 0, .End = 3,
					  .FrameInter = 0.05f , .Loop = true , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_wallslide", .SpriteName = "player_wallslide", .Start = 0, .End = 1,
					  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_die", .SpriteName = "player_die", .Start = 0, .End = 11,
					  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });

	m_Render->ChangeAnimation("player_idle");
}

void Player::Update(float _DeltaTime)
{
	
	//std::vector<std::shared_ptr<GameEngineCollision>> TestVector;
	//// �浹�׽�Ʈ�ڵ� �ߵȴ� ����  
	//if (m_Collision->CollisionAll(ColOrder::CURSOR, TestVector))
	//{
	//	// �̷� ������ �����ͼ� Ȱ���� �� ����.
	//	for (std::shared_ptr<GameEngineCollision> Col : TestVector)
	//	{
	//		Col->GetActor()->Death();
	//	}
	//}
	
	
	SkillUpdate(_DeltaTime);
	
	// ���¾�����Ʈ
	UpdateState(_DeltaTime);

	// ī�޶󹫺� ������Ʈ
	if (nullptr != PlaySupporter::MainSupporter)
	{
		PlaySupporter::MainSupporter->Update(_DeltaTime);
	}

	// ����� ������Ʈ
	DebugUpdate();

	// ����üũ, ���� �������� ���ѽð��� �Ѿ�ٸ� 
	if (0.0f >= GetReturnCastLevel()->GetLimitTime())
	{
		if (PlayerState::DEATH == m_CurState)
		{
			return;
		}

		ChangeState(PlayerState::DEATH);
	}
}

void Player::Render(float _DeltaTime)
{
}

// �̰Ŵ� ��� �ʿ���°Ű���.. 
// �ϴ� ���� 
float4 Player::FindSettingPos()
{
	BaseLevel* CurLevel = GetReturnCastLevel();

	if (nullptr == CurLevel)
	{
		MsgAssert("���� ������ nullptr �Դϴ�.");
	}

	// ��ü�� Ÿ�Կ� ���� ���� ��� 
	const std::type_info& type = typeid(*CurLevel);

	// ���� �ʱ�ȭ 
	float4 SetPos = {};

	// �� ������ ���� ���õǴ� �������� �޾ƿ´�. 
	if (type == typeid(ClubLevel_00))
	{
		// ��.. 
		ClubLevel_00* CastLevel = nullptr;
		CastLevel = dynamic_cast<ClubLevel_00*>(CurLevel);
		SetPos = CastLevel->GetPlayerSetPos();
	}

	else if (type == typeid(ClubLevel_01))
	{
		ClubLevel_01* CastLevel = nullptr;
		CastLevel = dynamic_cast<ClubLevel_01*>(CurLevel);
		SetPos = CastLevel->GetPlayerSetPos();
	}

	else if (type == typeid(ClubLevel_02))
	{
		ClubLevel_02* CastLevel = nullptr;
		CastLevel = dynamic_cast<ClubLevel_02*>(CurLevel);
		SetPos = CastLevel->GetPlayerSetPos();
	}

	else if (type == typeid(ClubLevel_03))
	{
		ClubLevel_03* CastLevel = nullptr;
		CastLevel = dynamic_cast<ClubLevel_03*>(CurLevel);
	}

	else if (type == typeid(ClubLevel_04))
	{
		ClubLevel_04* CastLevel = nullptr;
		CastLevel = dynamic_cast<ClubLevel_04*>(CurLevel);
	}

	return SetPos;
}

void Player::Reset()
{
	// ���� ���õ� ��ġ�� ã�ƿ´�. 
	// �׳� ���� ������ �ְ� �ϸ� �Ǵµ� �ʹ� ���Ƽ� ��. 
	// �ϴ� �����
	float4 SetPos = FindSettingPos();

	GetTransform()->SetLocalPosition(SetPos);
	ResetSlowLimitTime();
	ResetDir();	
	ChangeState(PlayerState::IDLE);
}

void Player::ComponentSetting()
{
	// �÷��̾� ���η���
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER);
	m_Render->GetTransform()->SetLocalPosition({ 0, PlayerPos.y + 36.0f });
	m_Render->SetScaleRatio(2.0f);

	// �ݸ��� ����
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::PLAYER));
	m_Collision->GetTransform()->SetLocalScale(m_LocalScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0, PlayerPos.y + 36.0f });

	// ������Ʈ��ӹ޴°ɷ� ���� ����
	// �ȼ��ö��̴� ����
	CreateComponent<PixelCollider>();
	
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

	m_DebugRender_WallRight = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender_WallRight->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_WallRight->GetTransform()->SetLocalPosition({ 2.0f , PlayerPos.y + 36.0f });
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
		m_DebugRender_WallRight->On();
	}

	else if (false == IsDebug())
	{
		m_DebugRender_Bottom->Off();
		m_DebugRender_Left->Off();
		m_DebugRender_Right->Off();
		m_DebugRender_Top->Off();
		m_DebugRender_WallRight->Off();
	}
}

void Player::SkillUpdate(float _DeltaTime)
{
	// 
	if (PlayerState::DEATH == m_CurState)
	{
		// ��ų false
		m_IsSlowSkill = false;
		// �������� 
		m_Render->ColorOptionValue.MulColor.r = 1.0f;
		// ���ο츮��
		SlowReset();
		return;
	}

	// ���������� X ��ŸŸ���� �޾Ƶд�.  
	float OriginTime = GameEngineTime::GlobalTime.GetDeltaTime();

	// ���� ���͸��� ��� �Ҹ� �Ǿ��� ���� ��������
	// �Ʒ� if ���̶� �������Ű��⵵�ѵ� �ϴ��� �Ǵϱ� ���߿�
	if (true == m_BatteryCharge)
	{
		m_SlowLimitTime += OriginTime;
		m_LimitTimeValue = m_SlowLimitTime;
		if (true == GameEngineInput::IsPress("player_skill_slow"))
		{
			m_Render->ColorOptionValue.MulColor.r = 1.0f;

			if (9.0f <= m_SlowLimitTime)
			{
				m_SlowLimitTime = 9.0f;
				m_BatteryCharge = false;
			}
			return;
		}

		else if (true == GameEngineInput::IsUp("player_skill_slow"))
		{
			m_SlowLimitTime = m_LimitTimeValue;
			m_LimitTimeValue = 0.0f;
			m_BatteryCharge = false;
			return;
		}
	}

	// ���������� ��ų�ߵ��� �ΰŰ� , ���͸� ������ false �϶��� ���´�. 
	if (true == GameEngineInput::IsPress("player_skill_slow"))
	{
		m_Render->ColorOptionValue.MulColor.r = 0.1f;
		
		// ���� ������ �ִ��߿� ���ӽð��� 0.0�ʺ��� �۾����� �Ǹ� ��ų�� �����ϰ�
		// ��ų ��� ���¸� false�� ����, ���ѽð��� 0.0�ʷ� �ʱ�ȭ�Ѵ�. 
		if (0.0f >= m_SlowLimitTime)
		{
			m_BatteryCharge = true;
			SlowReset();
			m_SlowLimitTime = 0.0f;
			m_IsSlowSkill = false;
			return;
		}

		// ���� ������ �ִ� �����̱� ������ ��ų�� 
		m_IsSlowSkill = true;

		// ���ӽð��� ���ҽ�Ų��. 
		m_SlowLimitTime -= OriginTime;

		// ��ŸŸ�ӿ� �������� �����Ѵ�. 
		Slow();
	}

	// ���� ������ �ȴ��� ���´ϱ� ������ ��ŸŸ���� ���ðŰ� 
	else if (false == GameEngineInput::IsPress("player_skill_slow"))
	{
		m_Render->ColorOptionValue.MulColor.r = 1.0f;
		// �ȴ������� �ٷ� Ÿ�ӽ����ϸ��� 
		SlowReset();
		m_IsSlowSkill = false;
		if (9.0f <= m_SlowLimitTime)
		{
			m_SlowLimitTime = 9.0f;
			return;
		}

		m_SlowLimitTime += _DeltaTime;
	}
}

// ---------------------------------skill --------------------------------------
void Player::Slow()
{
	if (true == m_IsSlowSkill)
	{
		GameEngineTime::GlobalTime.SetTimeScale(0.15f);
	}
}

void Player::SlowReset()
{
	GameEngineTime::GlobalTime.SetTimeScale(1.0f);
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
	case PlayerState::ROLL:
		RollUpdate(_DeltaTime);
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
	case PlayerState::RIGHTWALL:
		RightWallUpdate(_DeltaTime);
		break;
	case PlayerState::LEFTWALL:
		LeftWallUpdate(_DeltaTime);
		break;
	case PlayerState::DEATH:
		DeathUpdate(_DeltaTime);
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
	case PlayerState::ROLL:
		RollStart();
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
	case PlayerState::RIGHTWALL:
		RightWallStart();
		break;
	case PlayerState::LEFTWALL:
		LeftWallStart();
		break;
	case PlayerState::DEATH:
		DeathStart();
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
	case PlayerState::ROLL:
		RollEnd();
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
	case PlayerState::RIGHTWALL:
		RightWallEnd();
		break;
	case PlayerState::LEFTWALL:
		LeftWallEnd();
		break;
	case PlayerState::DEATH:
		DeathEnd();
		break;
	}
}

void Player::IdleStart()
{
	// ���� ���� ������Ʈ�� �������ٸ�
	// ����� ������ ������ ������ 
	if (PlayerState::DEATH == m_PrevState)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	m_Render->ChangeAnimation("player_idle");

	// ���� ���� ������ �� ���� ���̶��
	if (PlayerState::JUMP == m_PrevState)
	{
		GetLevel()->CreateActor<LandEffect>();
	}
}

void Player::IdleUpdate(float _DeltaTime)
{
	// death test
	/*if (true == GameEngineInput::IsDown("player_jump"))
	{
		ChangeState(PlayerState::DEATH);
		return;
	}*/

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

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	// �����Ҽ���
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		// true �̸� �� ���ΰɷ�
		if (false == PixelCollider::PixelCol->RightPixelCheck())
		{
			DirCheck();
			GetTransform()->AddLocalPosition(float4::Right * m_StartMoveSpeed * _DeltaTime);
		}
		return;
	}

	if (true == GameEngineInput::IsPress("player_left_move"))
	{
		if (false == PixelCollider::PixelCol->LeftPixelCheck())
		{
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
	GetLevel()->CreateActor<DashEffect>(static_cast<int>(RenderOrder::PLAYER_EFFECT));
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
		bool test = PixelCollider::PixelCol->RightPixelCheck();
		if (false == PixelCollider::PixelCol->RightPixelCheck())
		{
			m_Direction = true;
			GetTransform()->SetLocalPositiveScaleX();
			GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
		}
		
		return;
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		if (false == PixelCollider::PixelCol->LeftPixelCheck())
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

	// ���ݽ��ۼ��� ����Ʈ���� ?? 
	GetLevel()->CreateActor<SlashEffect>(static_cast<int>(RenderOrder::PLAYER_EFFECT));
}

void Player::SlashUpdate(float _DeltaTime)
{
	// ���� �ִϸ��̼� ����� ������ �� 
	if (true == m_Render->FindAnimation("player_attack")->IsEnd())
	{
		// ��ġ�� ���̶�� ���̵�� ����
		if (true == PixelCollider::PixelCol->GroundCheck(this))
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		// ���� �ƴ� ��� fall ���·� ����
		ChangeState(PlayerState::FALL);
		return;
	}

	// �Ʒ��� ����� ���;��� �� �ϴ� �ӽ÷�, �ʹ�,���������� �������� ��� 
	if (true == PixelCollider::PixelCol->GroundCheck(this))
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

	// ���� ������ ���ؿ´�. 
	float4 MoveDir = m_AttackPos - MyPos;
	MoveDir.Normalize();

	if ((false == PixelCollider::PixelCol->GroundCheck(this) && PlayerState::IDLE == m_PrevState && m_AttackPos.y < MyPos.y) ||
		(false == PixelCollider::PixelCol->GroundCheck(this) && PlayerState::CROUCH == m_PrevState && m_AttackPos.y < MyPos.y) ||
		(false == PixelCollider::PixelCol->GroundCheck(this) && PlayerState::IDLETORUN == m_PrevState && m_AttackPos.y < MyPos.y) ||
		(false == PixelCollider::PixelCol->GroundCheck(this) && PlayerState::ROLL == m_PrevState && m_AttackPos.y < MyPos.y))
	{
		MoveDir.y = 0.0f;
		// �÷��̾ ���� ���� �浹���� ���
		// �ϴ� �ӽ÷� 
		if (true == PixelCollider::PixelCol->LeftPixelCheck())
		{
			// ������ �������� �������� ���� �̵��Ѵ�.
			if (m_AttackPos.x >= MyPos.x)
			{
				GetTransform()->AddLocalPosition(float4{ MoveDir.x * 1.2f , MoveDir.y } *m_MoveSpeed * _DeltaTime);
				return;
			}
		}

		// ���� ���� ���� �浹���� ��� 
		if (true == PixelCollider::PixelCol->RightPixelCheck())
		{
			// ������ �������� ������������ �̵��Ѵ�. 
			if (m_AttackPos.x <= MyPos.x)
			{
				GetTransform()->AddLocalPosition(float4{ MoveDir.x * 1.2f , MoveDir.y } *m_MoveSpeed * _DeltaTime);
				return;
			}
		}
	}

	// �÷��̾ ���� ���� �浹���� ���
	// �ϴ� �ӽ÷� 
	if (true == PixelCollider::PixelCol->LeftPixelCheck())
	{
		// ������ �������� �������� ���� �̵��Ѵ�.
		if (m_AttackPos.x >= MyPos.x)
		{
			GetTransform()->AddLocalPosition(float4{ MoveDir.x * 1.2f , MoveDir.y } *m_MoveSpeed * _DeltaTime);
			return;
		}
	}

	// ���� ���� ���� �浹���� ��� 
	if (true == PixelCollider::PixelCol->RightPixelCheck())
	{
		// ������ �������� ������������ �̵��Ѵ�. 
		if (m_AttackPos.x <= MyPos.x)
		{
			GetTransform()->AddLocalPosition(float4{ MoveDir.x * 1.2f , MoveDir.y } *m_MoveSpeed * _DeltaTime);
			return;
		}
	}

	// �÷��̾ ���ʺ��̳� ������ ���� �浹���� ���
	if (true == PixelCollider::PixelCol->LeftPixelCheck() ||
		true == PixelCollider::PixelCol->RightPixelCheck())
	{
		return;
	}

	// �����ؾ� �� ����.
	if (true == PixelCollider::PixelCol->TopPixelCheck())
	{
		ChangeState(PlayerState::FALL);
		return;
	}

	if (false == PixelCollider::PixelCol->LeftPixelCheck() ||
		false == PixelCollider::PixelCol->RightPixelCheck())
	{	
		GetTransform()->AddLocalPosition(float4{ MoveDir.x * 1.2f , MoveDir.y } *m_MoveSpeed * _DeltaTime);
	}
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
	GetLevel()->CreateActor<JumpEffect>(static_cast<int>(RenderOrder::PLAYER_EFFECT));
}

void Player::JumpUpdate(float _DeltaTime)
{
	// ���� ���� ������ �� ���� ���̶��
	if (true == PixelCollider::PixelCol->GroundCheck(this))
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

	// ����ȼ� �ε����� ���� 
	if (true == PixelCollider::PixelCol->TopPixelCheck())
	{
		m_CurrentVerticalVelocity /= 4.0f;
	}
	// ������ ���� �߷��� �����ش�. 
	m_CurrentVerticalVelocity += -m_GravityPower * _DeltaTime;
	
	// ���� 
	GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);

	// ������ �¿� �̵��� ������ �ڵ� 
	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		// true �̸� �� ���ΰɷ�
		if (false == PixelCollider::PixelCol->RightPixelCheck())
		{
			m_Direction = true;
			GetTransform()->SetLocalPositiveScaleX();
			GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
			
			/*float4 CheckPos = m_DebugRender_WallRight->GetTransform()->GetLocalPosition();
			if (true == PixelCollider::PixelCol->RightWallCheck(CheckPos))
			{
				ChangeState(PlayerState::RIGHTWALL);
				return;
			}*/

			return;
		}
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		// true �̸� �� ���ΰɷ�
		if (false == PixelCollider::PixelCol->LeftPixelCheck())
		{
			m_Direction = false;
			GetTransform()->SetLocalNegativeScaleX();
			GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
			return;
		}
	}
}

void Player::JumpEnd()
{
	m_CurrentVerticalVelocity = 0.0f;
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

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}
	
	if (true == GameEngineInput::IsDown("player_right_move"))
	{
		if (true == PixelCollider::PixelCol->RightPixelCheck())
		{
			return;
		}

		ChangeState(PlayerState::ROLL);
		return;
	}

	else if (true == GameEngineInput::IsDown("player_left_move"))
	{
		if (true == PixelCollider::PixelCol->LeftPixelCheck())
		{
			return;
		}

		ChangeState(PlayerState::ROLL);
		return;
	}
}

void Player::CrouchEnd()
{
}

void Player::RollStart()
{
	m_Render->ChangeAnimation("player_roll");
}

void Player::RollUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	// �ø� ���� , �ȼ��浹 ���ó��� �߰��ؾ��� 
	// ���� �ø��� true ��� 
	if (true == m_RightRoll && false == m_LeftRoll)
	{
		// �ø� �ִϸ��̼��� ���� �Ǿ��ٸ�
		if (true == m_Render->IsAnimationEnd())
		{
			// ����ġ�� ���̶�� 
			if (true == PixelCollider::PixelCol->GroundCheck(this))
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

		if (true == PixelCollider::PixelCol->RightPixelCheck())
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Right * m_RollSpeed * _DeltaTime);
	}

	else if (true == m_LeftRoll)
	{
		// �ø� �ִϸ��̼��� ���� �Ǿ��ٸ�
		if (true == m_Render->IsAnimationEnd())
		{
			// ����ġ�� ���̶�� 
			if (true == PixelCollider::PixelCol->GroundCheck(this))
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

		if (true == PixelCollider::PixelCol->LeftPixelCheck())
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Left * m_RollSpeed * _DeltaTime);
	}

	// �ִϸ��̼��� ����Ǹ� 
	if (true == m_Render->IsAnimationEnd())
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
		m_RightRoll = true;

		return;
	}

	else if (true == GameEngineInput::IsPress("player_left_Move") && false == m_RightRoll)
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
		m_LeftRoll = true;

		return;
	}
}

void Player::RollEnd()
{
	m_RightRoll = false;
	m_LeftRoll = false;

	if (true != GameEngineInput::IsPress("player_crouch"))
	{
		if (true == GameEngineInput::IsPress("player_right_move") || true == GameEngineInput::IsPress("player_left_move"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}
	}
}

void Player::FlipStart()
{
	
}

// �ø����¿����� �����̱� ������ �浹ü off ó�� ����
// �¿��� �ȼ��˻�� ���̸� �̵� ���� �߰��ؾ��� 
// �̳༮�� �ø��� �ƴ϶� ���̾����� 
void Player::FlipUpdate(float _DeltaTime)
{
	
}

void Player::FlipEnd()
{

}

void Player::FallStart()
{
	m_Render->ChangeAnimation("player_fall");
}

// ���ʿ����� �ȼ�üũ �߰��ؾ��� 
void Player::FallUpdate(float _DeltaTime)
{
	// ���� ���̶��
	if (true == PixelCollider::PixelCol->GroundCheck(this))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}


	// ���̾ƴ϶��
	else if (false == PixelCollider::PixelCol->GroundCheck(this))
	{
		GetTransform()->AddLocalPosition(float4{ 0 , -1 } *300.0f * _DeltaTime);
	}

	// �̷��� ���ִ°� ������ ���̻��� 
	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		if (true == GameEngineInput::IsDown("player_slash"))
		{
			ChangeState(PlayerState::SLASH);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Down * m_FallPower * _DeltaTime);

		// ���� ���̶��
		if (true == PixelCollider::PixelCol->GroundCheck(this))
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		// ���̾ƴ϶��
		else if (false == PixelCollider::PixelCol->GroundCheck(this))
		{
			GetTransform()->AddLocalPosition(float4{ 0 , -1 } *300.0f * _DeltaTime);
			return;
		}
	}

	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		if (false == PixelCollider::PixelCol->RightPixelCheck())
		{
			m_Direction = true;
			GetTransform()->SetLocalPositiveScaleX();
			GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
			return;
		}
	}

	else if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		if (false == PixelCollider::PixelCol->LeftPixelCheck())
		{
			m_Direction = false;
			GetTransform()->SetLocalNegativeScaleX();
			GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
			return;
		}
	}
}

void Player::FallEnd()
{
	GetLevel()->CreateActor<LandEffect>();
}

void Player::RightWallStart()
{
	//m_Render->ChangeAnimation("player_wallslide");
}

void Player::RightWallUpdate(float _DeltaTime)
{
	/*if (true == PixelCollider::PixelCol->GroundCheck(this))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	else
	{
		GetTransform()->AddLocalPosition(float4::Down * 200.0f * _DeltaTime);
		return;
	}*/
}

void Player::RightWallEnd()
{
}

void Player::LeftWallStart()
{
}

void Player::LeftWallUpdate(float _DeltaTime)
{
}

void Player::LeftWallEnd()
{
}

// �ϴ� ����
// �ʹ����ڿ������� 
// �׾����� �� ���ڰ� ���ư��� �ٲ����
void Player::DeathStart()
{
	DirCheck();
	m_Render->ChangeAnimation("player_die");
	m_Render->GetTransform()->AddLocalPosition({ 0 , -15.0f });
}

void Player::DeathUpdate(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		return;
	}

	if (false == PixelCollider::PixelCol->GroundCheck(this))
	{
		if (true == PixelCollider::PixelCol->GroundCheck(this))
		{
			return;
		}

		GetTransform()->AddLocalPosition(float4::Down * 50.0f * _DeltaTime);
	}
}

void Player::DeathEnd()
{
	m_Render->GetTransform()->AddLocalPosition({ 0 , 15.0f });
}

