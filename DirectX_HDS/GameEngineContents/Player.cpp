#include "PrecompileHeader.h"
#include "Player.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineCollision.h>

// ������ �߰��ɶ����� ����߰� �� Reset �Լ��� �߰�.. 
#include "ClubLevel_00.h"
#include "ClubLevel_01.h"
#include "ClubLevel_02.h"
#include "ClubLevel_03.h"
#include "ClubLevel_04.h"
#include "ClubLevel_Boss.h"

#include "Monster_Grunt.h"

// ī�޶�
#include "PlaySupporter.h"

#include "BaseLevel.h"
#include "Cursor.h"
#include "PixelCollider.h"
#include "SlashEffect.h"
#include "JumpEffect.h"
#include "LandEffect.h"
#include "DashEffect.h"
#include "HitEffect.h"
#include "IronDoor.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	MainPlayer = this;
}

Player::~Player()
{
}

// �ѿ� �¾Ҵٸ� 
void Player::BulletCollision()
{
	if (PlayerState::DEATH != m_CurState)
	{
		m_Collision->Off();
		ChangeState(PlayerState::DEATH);
	}
}

void Player::Start()
{
	// ���� ��ŸƮ �⺻�������̽� ����
	// Ű����

	// ������Ʈ ����
	ComponentSetting();
	// �ʿ��� ���ҽ� �ε�� �ִϸ��̼� ����	
	LoadAndCreateAnimation();

	LoadSound();

	if (false == GameEngineInput::IsKey("player_slash"))
	{
		GameEngineInput::CreateKey("player_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("player_slash", VK_LBUTTON);
		GameEngineInput::CreateKey("player_skill_slow", VK_LSHIFT);
		GameEngineInput::CreateKey("player_debug_move", VK_RBUTTON);
		GameEngineInput::CreateKey("player_left_Move", 'A');
		GameEngineInput::CreateKey("player_right_Move", 'D');
		GameEngineInput::CreateKey("player_jump", 'W');
		GameEngineInput::CreateKey("player_crouch", 'S');
		GameEngineInput::CreateKey("player_invincibility", 'I');
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
									  .FrameInter = 0.025f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_crouch", .SpriteName = "player_crouch", .Start = 0, .End = 0 ,
							  .FrameInter = 0.01f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_flip", .SpriteName = "player_flip", .Start = 0, .End = 10,
						  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_doorbreak", .SpriteName = "player_doorbreak", .Start = 0, .End = 5,
						  .FrameInter = 0.05f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "player_doorbreak_full", .SpriteName = "player_doorbreak_full", .Start = 0, .End = 9,
						  .FrameInter = 0.035f , .Loop = false , .ScaleToTexture = true });

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

	// �̺�Ʈ�߰� 
	// std::bind, 1������ : ����Լ��� ������ / 2������ : this ������
	m_Render->SetAnimationStartEvent("player_attack", static_cast<size_t>(1), std::bind(&Player::CreateSlashEffect, this));
}

// �÷��̾�� ���õ� ����� ���� �÷��̾�� �ε� 
void Player::LoadSound()
{
	// ����ε� 
	{
		// ���丮 Ŭ��������
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("sound");
		NewDir.Move("player");
		
		// ��
		GameEngineSound::Load(NewDir.GetPlusFileName("door_open.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("gun_fire_00.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("death_sword.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("death_bullet.wav").GetFullPath());

		GameEngineSound::Load(NewDir.GetPlusFileName("slash_00.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("slash_01.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("slash_02.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_roll.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_jump.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_land.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_die.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_run.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("player_prerun.wav").GetFullPath());
		GameEngineSound::Load(NewDir.GetPlusFileName("slash_bullet_parring.wav").GetFullPath());
	}
}

void Player::NextPosUpdate()
{
	m_NextTrans->SetLocalPosition(GetTransform()->GetWorldPosition());
}

void Player::Update(float _DeltaTime)
{
	// ����� ������Ʈ
	DebugUpdate();

	// ���ѽð� �ʰ� üũ 
	TimeOutCheck();

	HitCheck();

	// ��ų ������Ʈ 
	SkillUpdate(_DeltaTime);

	// nextpos ���� �÷��̾� ��ġ�� �̵�
	NextPosUpdate();
	
	// ���� �÷����� �浹���� ���¿��� �Ʒ�Ű �Է½� ������ȯ 
	if (true == PlatformColCheck() && GameEngineInput::IsDown("player_crouch"))
	{
		// ���� �Ʒ� �ȼ��� �������� �ƴ϶�� fall�� ��ȯ 
		if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
		}
	}

	// ������ �浹üũ
	LaserColCheck();

	// ȯǳ�� �浹üũ 
	FanBladeColCheck();

	// ���¾�����Ʈ 
	UpdateState(_DeltaTime);
}

void Player::Render(float _DeltaTime)
{
}

void Player::LevelChangeEnd()
{
	m_MoveSoundPlayer.Stop();
}

void Player::SlashSoundPlay()
{
	// 3���߿� �����Ѱ�. 
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 2);
	switch (RandomValue)
	{
	case 0:
		m_SoundPlayer = GameEngineSound::Play("Slash_00.wav");
		break;
	case 1:
		m_SoundPlayer = GameEngineSound::Play("Slash_01.wav");
		break;
	case 2:
		m_SoundPlayer = GameEngineSound::Play("Slash_02.wav");
		break;
	}

	m_SoundPlayer.SetVolume(0.7f);
}

bool Player::DoorColCheck()
{
	std::shared_ptr<GameEngineCollision> DoorCol = m_Collision->Collision(ColOrder::DOOR, ColType::AABBBOX2D, ColType::AABBBOX2D);
	if (nullptr != DoorCol)
	{
		return true;
	}

	return false; 
}

bool Player::PlatformColCheck()
{
	std::shared_ptr<GameEngineCollision> PlatformCol = m_Collision->Collision(ColOrder::PLATFORM, ColType::AABBBOX2D, ColType::AABBBOX2D);
	if (nullptr != PlatformCol)
	{
		return true;
	}

	return false;
}

bool Player::LaserColCheck()
{
	std::shared_ptr<GameEngineCollision> LaserCol = m_Collision->Collision(ColOrder::LASER, ColType::AABBBOX2D, ColType::AABBBOX2D);
	if (nullptr != LaserCol)
	{
		ChangeState(PlayerState::DEATH);
		m_Collision->Off();
		return true;
	}

	return false;
}

bool Player::FanBladeColCheck()
{
	std::shared_ptr<GameEngineCollision> FanCol = m_SubCollision->Collision(ColOrder::FANBLADE, ColType::AABBBOX2D, ColType::AABBBOX2D);
	if (nullptr != FanCol)
	{
		ChangeState(PlayerState::DEATH);
		m_Collision->Off();
		m_SubCollision->Off();
		return true;
	}

	return false;
}

bool Player::HitCheck()
{
	// ?? ���� 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::MONSTER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	if (nullptr != Col)
	{
		CreateHitEffect(Col);
		// ���� �������·� 
		ChangeState(PlayerState::DEATH);
		m_Collision->Off();
		m_SubCollision->Off();
		return true;
	}

	return false;
}

void Player::CreateSlashEffect()
{
	GetLevel()->CreateActor<SlashEffect>(static_cast<int>(RenderOrder::PLAYER_EFFECT));
}

void Player::CreateHitEffect(std::shared_ptr<class GameEngineCollision> _Col)
{
	// ����Ʈ����� 
	std::shared_ptr<HitEffect> Effect = GetLevel()->CreateActor<HitEffect>(static_cast<int>(RenderOrder::EFFECT));
	Effect->SetPivot(float4{ 10.0f, -10.0f });
	// ����ġ 
	float4 MyPos = GetTransform()->GetWorldPosition();
	// �����ġ 
	float4 ColActorPos = _Col->GetActor()->GetTransform()->GetLocalPosition();
	float4 MoveDir = ColActorPos - MyPos;

	Effect->SetObject(this->DynamicThis<GameEngineObject>());
	if (ColActorPos.x > MyPos.x)
	{
		Effect->GetTransform()->SetLocalPositiveScaleX();
		m_Direction = true;
	}

	else if (ColActorPos.x <= MyPos.x)
	{
		m_Direction = false;
		Effect->GetTransform()->SetLocalNegativeScaleX();
	}
}

void Player::TimeOutCheck()
{
	// ����üũ, ���� �������� ���ѽð��� �Ѿ�ٸ� 
	if (0.0f >= GetReturnCastLevel()->GetLimitTime())
	{
		if (PlayerState::DEATH == m_CurState ||
			PlayerState::NONE == m_CurState)
		{
			return;
		}

		ChangeState(PlayerState::DEATH);
	}
}


void Player::Reset()
{
	float4 SetPos = GetInitPos();

	GetTransform()->SetLocalPosition(SetPos);
	ResetSkillLimitTime();
	ResetDir();	
	m_Collision->On();
	m_SubCollision->On();
	ChangeState(PlayerState::IDLE);
}

void Player::ComponentSetting()
{
	// �ȼ��浹 
	CreateComponent<PixelCollider>();

	// �ؽ�Ʈ����üũ�� Ʈ������
	m_NextTrans = std::make_shared<GameEngineTransform>();

	// ���η��� 
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER);
	m_Render->GetTransform()->SetLocalPosition({ 0, m_RenderPivot });
	m_Render->SetScaleRatio(2.0f);

	// �ݸ��� 
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::PLAYER));
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0, m_ColPivot });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->DebugOff();

	// �긦 ��� �ҰŴ�? 
	m_SubCollision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::PLAYER_SUB));
	m_SubCollision->GetTransform()->SetLocalScale(float4{ m_ColScale.x - 20.0f, m_ColScale.y - 20.0f });
	m_SubCollision->GetTransform()->SetLocalPosition({ 0, m_ColPivot });
	m_SubCollision->SetColType(ColType::OBBBOX3D);
	m_SubCollision->DebugOff();

	// --------------------------- Debug Render ------------------------------

	m_DebugRenders.reserve(8);
	m_DebugRender_Bottom = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Bottom->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Bottom->Off();
	m_DebugRenders.push_back(m_DebugRender_Bottom);

	m_DebugRender_Top = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Top->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Top->GetTransform()->SetLocalPosition({ 0.0f , m_RenderPivot * 2.0f });
	m_DebugRender_Top->Off();
	m_DebugRenders.push_back(m_DebugRender_Top);

	m_DebugRender_Left = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Left->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Left->GetTransform()->SetLocalPosition({ -36.0f, m_RenderPivot });
	m_DebugRender_Left->Off();
	m_DebugRenders.push_back(m_DebugRender_Left);
	
	m_DebugRender_Right = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Right->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Right->GetTransform()->SetLocalPosition({ 36.0f, m_RenderPivot });
	m_DebugRender_Right->Off();
	m_DebugRenders.push_back(m_DebugRender_Right);

	m_DebugRender_Wall_Left = CreateComponent <GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Wall_Left->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Wall_Left->GetTransform()->SetLocalPosition({ -m_WallDebugPivotX , m_WallDebugPivotY });
	m_DebugRender_Wall_Left->Off();
	m_DebugRenders.push_back(m_DebugRender_Wall_Left);

	m_DebugRender_Wall_Right = CreateComponent <GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Wall_Right->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Wall_Right->GetTransform()->SetLocalPosition({ m_WallDebugPivotX , m_WallDebugPivotY });
	m_DebugRender_Wall_Right->Off();
	m_DebugRenders.push_back(m_DebugRender_Wall_Right);
	
	m_DebugRender_Bottom_Down = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender_Bottom_Down->GetTransform()->SetLocalScale(m_DebugRenderScale);
	m_DebugRender_Bottom_Down->GetTransform()->SetLocalPosition({ 0.0f, -1.0f });
	m_DebugRender_Bottom_Down->Off();
	m_DebugRenders.push_back(m_DebugRender_Bottom_Down);
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
	// ����׿�
	if (true == GameEngineInput::IsDown("player_debug_move"))
	{
		float4 MovePos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
		GetTransform()->SetLocalPosition(MovePos);
	}
	
	if (true == GameEngineInput::IsDown("player_invincibility"))
	{
		m_Invincibility = !m_Invincibility;

		if (true == m_Collision->IsUpdate())
		{
			m_Collision->Off();
			m_SubCollision->Off();
		}

		else
		{
			m_Collision->On();
			m_SubCollision->On();
		}
	
	}

	if (true == GameEngineInput::IsDown("player_debugswitch"))
	{
		DebugSwitch();

		/*if (nullptr != m_Collision)
		{
			if (true == m_Collision->IsDebug())
			{
				m_Collision->DebugOff();
				m_SubCollision->DebugOff();
			}

			else
			{
				m_Collision->DebugOn();
				m_SubCollision->DebugOn();
			}
		}*/

		if (true == IsDebug())
		{
			// player 
			m_DebugRender_Bottom->On();
			m_DebugRender_Left->On();
			m_DebugRender_Right->On();
			m_DebugRender_Top->On();
			m_DebugRender_Bottom_Down->On();

			// wall check
			m_DebugRender_Wall_Right->On();
			m_DebugRender_Wall_Left->On();
		}

		else if (false == IsDebug())
		{
			m_DebugRender_Bottom->Off();
			m_DebugRender_Left->Off();
			m_DebugRender_Right->Off();
			m_DebugRender_Top->Off();
			m_DebugRender_Bottom_Down->Off();

			m_DebugRender_Wall_Right->Off();
			m_DebugRender_Wall_Left->Off();
		}
	}

	
}

void Player::SkillUpdate(float _DeltaTime)
{
	if (PlayerState::DEATH == m_CurState)
	{
		// ��ų false
		m_IsSkill = false;
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
		m_SkillLimitTime += OriginTime;
		m_LimitTimeValue = m_SkillLimitTime;
		if (true == GameEngineInput::IsPress("player_skill_slow"))
		{
			m_Render->ColorOptionValue.MulColor.r = 1.0f;

			if (9.0f <= m_SkillLimitTime)
			{
				m_SkillLimitTime = 9.0f;
				m_BatteryCharge = false;
			}
			return;
		}

		else if (true == GameEngineInput::IsUp("player_skill_slow"))
		{
			m_SkillLimitTime = m_LimitTimeValue;
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
		if (0.0f >= m_SkillLimitTime)
		{
			m_BatteryCharge = true;
			SlowReset();
			m_SkillLimitTime = 0.0f;
			m_IsSkill = false;
			return;
		}

		// ���� ������ �ִ� �����̱� ������ ��ų�� 
		m_IsSkill = true;

		// ���ӽð��� ���ҽ�Ų��. 
		m_SkillLimitTime -= OriginTime;

		// ��ŸŸ�ӿ� �������� �����Ѵ�. 
		Slow();
	}

	// ���� ������ �ȴ��� ���´ϱ� ������ ��ŸŸ���� ���ðŰ� 
	else if (false == GameEngineInput::IsPress("player_skill_slow"))
	{
		m_Render->ColorOptionValue.MulColor.r = 1.0f;
		// �ȴ������� �ٷ� Ÿ�ӽ����ϸ��� 
		SlowReset();
		m_IsSkill = false;
		if (9.0f <= m_SkillLimitTime)
		{
			m_SkillLimitTime = 9.0f;
			return;
		}

		m_SkillLimitTime += _DeltaTime;
	}
}

// ---------------------------------skill --------------------------------------
void Player::Slow()
{
	if (true == m_IsSkill)
	{
		GameEngineTime::GlobalTime.SetGlobalTimeScale(0.15f);

		 //�Һ��̵�� ���⼭ �������� ����� 
		 GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(RenderOrder::FANBLADE, 0.1f);
	}
}

void Player::SlowReset()
{
	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.0f);
	GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(RenderOrder::FANBLADE, 1.0f);
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
	case PlayerState::RIGHTFLIP:
		RightFlipUpdate(_DeltaTime);
		break;
	case PlayerState::LEFTFLIP:
		LeftFlipUpdate(_DeltaTime);
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
	case PlayerState::DOORBREAK:
		DoorBreakUpdate(_DeltaTime);
		break;
	case PlayerState::NONE:
		NoneUpdate(_DeltaTime);
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
	case PlayerState::RIGHTFLIP:
		RightFlipStart();
		break;
	case PlayerState::LEFTFLIP:
		LeftFlipStart();
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
	case PlayerState::DOORBREAK:
		DoorBreakStart();
		break;
	case PlayerState::NONE:
		NoneStart();
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
	case PlayerState::RIGHTFLIP:
		RightFlipEnd();
		break;
	case PlayerState::LEFTFLIP:
		LeftFlipEnd();
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
	case PlayerState::DOORBREAK:
		DoorBreakEnd();
		break;
	case PlayerState::NONE:
		NoneEnd();
		break;
	}
}

void Player::IdleStart()
{
	// ���� ������Ʈ�� ������� �������� ��Ŭ����,
	// �������� ������ ( ������ ) , ���� �� NONE ���·� ����� 
	if (PlayerState::NONE == m_PrevState)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition()))
	{
		// ���� �� �ȼ��� �������̶�� ���� �÷��ش�.
		PixelCollider::PixelCol->GroundCheck(this);
	}

	m_Render->ChangeAnimation("player_idle");

	// ���� ���°� �������µ�, Idle�� ���� �Ǿ��ٸ� ���� ���̶�� ���̱� ������ ��������Ʈ ����
	if (PlayerState::JUMP == m_PrevState)
	{
		GetLevel()->CreateActor<LandEffect>();
	}
}

void Player::IdleUpdate(float _DeltaTime)
{
	// ����, ���콺 ��Ŭ�� 
	if (true == GameEngineInput::IsDown("player_slash"))
	{
		if (true == DoorColCheck())
		{
			ChangeState(PlayerState::DOORBREAK);
			return;
		}

		ChangeState(PlayerState::SLASH);
		return;
	}

	// ����Ű , w
	if (true == GameEngineInput::IsDown("player_jump"))
	{
		if (true == DoorColCheck())
		{
			return;
		}

		ChangeState(PlayerState::JUMP);
		return;
	}

	// ũ���ġ , s
	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	// ���ÿ� ���������� ��� �ƹ��͵� �������� ���� 
	if (true == GameEngineInput::IsPress("player_right_move") && true == GameEngineInput::IsPress("player_left_move"))
	{
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
}

void Player::IdleEnd()
{
}

void Player::IdleToRunStart()
{
	m_SoundPlayer = GameEngineSound::Play("player_prerun.wav");
	m_SoundPlayer.SetVolume(0.6f);
	DirCheck();
	m_Render->ChangeAnimation("player_idle_to_run");
}

void Player::IdleToRunUpdate(float _DeltaTime)
{
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		std::shared_ptr<GameEngineCollision> PlatformCol = m_Collision->Collision(ColOrder::PLATFORM, ColType::AABBBOX2D, ColType::AABBBOX2D);

		// �̶� ����, ���� ����Ű�� ������ �ְ� �÷����� �浹���̶�� �����ϰ� �̵��Ѵ�. 
		if (true == GameEngineInput::IsPress("player_left_move") && nullptr != PlatformCol)
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		else if (true == GameEngineInput::IsPress("player_right_move") && nullptr != PlatformCol)
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		ChangeState(PlayerState::FALL);
		return;
	}

	if (true == m_Render->IsAnimationEnd())
	{
		// �ִϸ��̼��� ����� ������ ����Ű�� ������Ű�� �����ִٸ�
		// ���� ���·� ��ȯ 
		if (true == GameEngineInput::IsPress("player_right_move") ||
			true == GameEngineInput::IsPress("player_left_move"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		// ���� ���� �ʴٸ�, �ٽ� IDLE 
		ChangeState(PlayerState::IDLE);
		return;
	}

if (true == GameEngineInput::IsDown("player_slash"))
{
	if (true == DoorColCheck())
	{
		ChangeState(PlayerState::DOORBREAK);
		return;
	}

	ChangeState(PlayerState::SLASH);
	return;
}

if (true == GameEngineInput::IsDown("player_jump"))
{
	if (true == DoorColCheck())
	{
		return;
	}

	ChangeState(PlayerState::JUMP);
	return;
}

if (true == GameEngineInput::IsPress("player_right_move") && false == DoorColCheck())
{
	DirCheck();
	if (true == GameEngineInput::IsPress("player_left_move"))
	{
		return;
	}

	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
	{
		// ���� �� �ٷ� ���� �ȼ��� �������� ���
		// �߰��� �� ���� �ټ�ĭ�� ����̶�� 
		float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Right;
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Right)) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
		{
			// �̵���Ű��, �����Ĺ����ִٸ� �÷��ش�. 
			GetTransform()->AddLocalPosition(float4::Right * m_StartMoveSpeed * _DeltaTime);
			PixelCollider::PixelCol->GroundCheck(this);
			return;
		}

		m_NextTrans->AddLocalPosition(float4::Right * m_StartMoveSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
		{
			return;
		}
		GetTransform()->AddLocalPosition(float4::Right * m_StartMoveSpeed * _DeltaTime);
		return;
	}
}

if (true == GameEngineInput::IsPress("player_left_move"))
{
	DirCheck();
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		return;
	}

	// �� ���� üũ �ȼ��� ����� ( negative �������� right �ȼ�üũ ) 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
	{
		float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Left;
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Left)) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
		{
			// �̵���Ű��, �����Ĺ����ִٸ� �÷��ش�. 
			GetTransform()->AddLocalPosition(float4::Left * m_StartMoveSpeed * _DeltaTime);
			PixelCollider::PixelCol->GroundCheck(this);
			return;
		}

		// ���̸� �̵������� �� �� ��ġ�� �ѹ��� �˻��ؼ� 
		m_NextTrans->AddLocalPosition(float4::Left * m_StartMoveSpeed * _DeltaTime);
		// �� ��ġ�� ������ �ȼ��̶�� �̵����� �ʰ�
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
		{
			return;
		}

		// �װ� �ƴ϶�� ��¥ ���� ��ġ�� �̵���
		GetTransform()->AddLocalPosition(float4::Left * m_StartMoveSpeed * _DeltaTime);
		return;
	}
}
}

void Player::IdleToRunEnd()
{
}

void Player::MoveStart()
{
	m_MoveSoundPlayer = GameEngineSound::Play("player_run.wav");
	m_MoveSoundPlayer.SetPitch(0.6f);
	m_MoveSoundPlayer.SetLoop(-1);
	m_Render->ChangeAnimation("player_run");
}

void Player::MoveUpdate(float _DeltaTime)
{
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		std::shared_ptr<GameEngineCollision> PlatformCol = m_Collision->Collision(ColOrder::PLATFORM, ColType::AABBBOX2D, ColType::AABBBOX2D);
	
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

		// �̶� ����, ���� ����Ű�� ������ �ְ� �÷����� �浹���̶�� �����ϰ� �̵��Ѵ�. 
		if (true == GameEngineInput::IsPress("player_left_move") && nullptr != PlatformCol)
		{
			DirCheck();
			GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
			return;
		}

		else if (true == GameEngineInput::IsPress("player_right_move") && nullptr != PlatformCol)
		{
			DirCheck();
			GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
			return;
		}

		else if (nullptr == PlatformCol)
		{
			ChangeState(PlayerState::FALL);
			return;
		}
		
	}

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		if (true == DoorColCheck())
		{
			ChangeState(PlayerState::DOORBREAK);
			return;
		}

		ChangeState(PlayerState::SLASH);
		return;
	}

	if (true == GameEngineInput::IsDown("player_jump"))
	{
		if (true == DoorColCheck())
		{
			return;
		}

		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == GameEngineInput::IsDown("player_crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (true == GameEngineInput::IsPress("player_left_move") &&
		true == GameEngineInput::IsPress("player_right_move"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (false == GameEngineInput::IsPress("player_left_move") &&
		false == GameEngineInput::IsPress("player_right_move"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// ����Ű�� ������ ������, ���� �̵��� üũ 
	if (true == GameEngineInput::IsPress("player_right_move") &&  false == GameEngineInput::IsPress("player_left_move") && false == DoorColCheck())
	{
		DirCheck();
		// ���� ����Ű�� ���� ���¿��� ��Ŭ�� �Է��� �Ǿ����� ���,
		if (true == GameEngineInput::IsPress("player_left_move"))
		{
			DirCheck();
			if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
			{
				float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Left;
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Left)) &&
					PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
				{
					// �̵���Ű��, �����Ĺ����ִٸ� �÷��ش�. 
					GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
					PixelCollider::PixelCol->GroundCheck(this);
					return;
				}

				// ���̸� �̵������� �� �� ��ġ�� �ѹ��� �˻��ؼ� 
				m_NextTrans->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
				float4 CheckPos = m_NextTrans->GetLocalPosition() + float4{ -m_RenderPivot ,0.0f };

				// �� ��ġ�� ������ �ȼ��̶�� �̵����� �ʰ�
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
				{
					return;
				}

				// �װ� �ƴ϶�� ��¥ ���� ��ġ�� �̵���
				GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
				return;
			}
		}

		// right 
		// ������ üũ�ȼ��� ����� �� �̵��Ұǵ� 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// ���� �� �ٷ� ���� �ȼ��� �������� ���
			// �߰��� �� ���� �ټ�ĭ�� ����̶�� 
			float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Right;
			if(PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) || 
			   PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Right)) &&
			   PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
			{
				// �̵���Ű��, �����Ĺ����ִٸ� �÷��ش�. 
				GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
				PixelCollider::PixelCol->GroundCheck(this);
				return;
			}
			// ������ġ�� �̵���Ű��.
			m_NextTrans->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
			// ���� ��ġ�� ����üũ�ȼ��� �˻��ؼ� 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot };
			// �� �ȼ��� �������̶�� �������� �����ž�
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				return;
			}
			GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
			return;
		}
	}

	if (true == GameEngineInput::IsPress("player_left_move") && false == GameEngineInput::IsPress("player_right_move"))
	{
		DirCheck();
		if (true == GameEngineInput::IsPress("player_right_move"))
		{
			DirCheck();
			if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
			{
				float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Right;
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Right)) &&
					PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
				{
					// �̵���Ű��, �����Ĺ����ִٸ� �÷��ش�. 
					GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
					PixelCollider::PixelCol->GroundCheck(this);
					return;
				}

				// �ؽ�Ʈ���� üũ�ϰ�
				m_NextTrans->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
				{
					return;
				}

				GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
				return;
			}
		}

		// �� ���� üũ �ȼ��� ����� ( negative �������� right �ȼ�üũ ) 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Left;

			// �̵��� ��ġ�� ������, �̵��� ��ġ�� ���� �ȼ��� ������, ������ �ȼ��� Ư�������� �����ؼ�. �űⰡ ����̸� �����̵����ݾ� ?
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
				PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Left)) &&
				PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
			{
				// �̵���Ű��, �����Ĺ����ִٸ� �÷��ش�. 
				GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
				PixelCollider::PixelCol->GroundCheck(this);
				return;
			}
			
			// ���̸� �̵������� �� �� ��ġ�� �ѹ��� �˻��ؼ� 
			m_NextTrans->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
			float4 CheckPos = m_NextTrans->GetLocalPosition() + float4{ -m_RenderPivot ,0.0f };
			// �� ��ġ�� ������ �ȼ��̶�� �̵����� �ʰ�
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_RenderPivot , m_RenderPivot }))
			{
				return;
			}

			// �װ� �ƴ϶�� ��¥ ���� ��ġ�� �̵���
			GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
			return;
		}
	}
}

void Player::MoveEnd()
{
	m_MoveSoundPlayer.Stop();
}

// �ϴ� ������������ ���� ���� �Ϸ�
void Player::SlashStart()
{
	m_AttackPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	m_MyOriginPos = GetTransform()->GetLocalPosition();
	m_Render->ChangeAnimation("player_attack");
	SlashSoundPlay();
}

void Player::SlashUpdate(float _DeltaTime)
{ 
	// ���� ���� �ִϸ��̼��� ����Ǿ��� �� 
	if (true == m_Render->IsAnimationEnd())
	{
		// ���� ���߻��¶�� 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
			return;
		}
		
		// ���� �ٴ��ε�, ���� ������ ���°� MOVE���ٸ� MOVE���·� ����
		else if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
				 PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()) &&
				 PlayerState::MOVE == m_PrevState)
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		// �װ� �ƴ϶�� ���̵�� ����
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::FALL);
		return;
	}

	float4 AttDir = m_AttackPos - m_MyOriginPos;
	AttDir.Normalize();

	// ���� ���� ���°� fall �� ���¿��� y�� ������ǥ�� ������ ���ٸ� 
	if (PlayerState::FALL == m_PrevState && m_MyOriginPos.y <= m_AttackPos.y)
	{
		AttDir.y = 0.0f;
	}
	// ������ ������ǥ�� ������ ���ٸ� 
	else if (PlayerState::FALL == m_PrevState && m_MyOriginPos.y > m_AttackPos.y)
	{
		//? 
		int a = 0;
	}

	if (m_MyOriginPos.x <= m_AttackPos.x)
	{
		m_Direction = true;
		GetTransform()->SetLocalPositiveScaleX();
	}
	else if (m_MyOriginPos.x > m_AttackPos.x)
	{
		m_Direction = false;
		GetTransform()->SetLocalNegativeScaleX();
	}
	
	// ���� ������ �� 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// ������ġ�� ������ ���ٸ� 
		if (m_AttackPos.y < m_MyOriginPos.y)
		{
			// y�� �̵��� ���� �ʴ´�. 
			AttDir.y = 0.0f;
		}

		// �� ���¿��� �ؽ�Ʈ������ üũ�ؼ� 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 {m_RenderPivot, m_RenderPivot}) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 {-m_RenderPivot, m_RenderPivot }))
		{
			// ���� �̵� ��ġ�� �����ȼ��̶�� �̵����� ����.
			return;
		}

		// �����ȼ��� �ƴ϶�� �ش� ��ġ�� �̵�.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// ���� ���߿� �� ���� �� 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()))
	{
		// �ؽ�Ʈ���� üũ �� 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// ���� �̵� ��ġ�� �����ȼ��̶�� �̵����� ����.
			return;
		}

		// �����ȼ��� �ƴ϶�� �ش� ��ġ�� �̵�.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}
	
	// ���� Ȥ�� �������� ���� ���¿��� ���Ʒ��� ���̸� 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) ||
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// ������ġ�� ������ ���ٸ� 
		if (m_AttackPos.y < m_MyOriginPos.y)
		{
			// y�� �̵��� ���� �ʴ´�. 
			AttDir.y = 0.0f;
		}

		// �� ���¿��� �ؽ�Ʈ������ üũ�ؼ� 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// ���� �̵� ��ġ�� �����ȼ��̶�� �̵����� ����.
			return;
		}

		// �����ȼ��� �ƴ϶�� �ش� ��ġ�� �̵�.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// �׳� ���� ���°� �����Ŀ� ���� üũ
	if (PlayerState::RIGHTWALL == m_PrevState)
	{
		// �� ���¿��� �ؽ�Ʈ������ üũ�ؼ� 
		m_NextTrans->AddLocalPosition(AttDir* m_AttSpeed* _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// ���� �̵� ��ġ�� �����ȼ��̶�� �̵����� ����.
			return;
		}

		// �����ȼ��� �ƴ϶�� �ش� ��ġ�� �̵�.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// �׳� ���� ���°� �����Ŀ� ���� üũ
	if (PlayerState::LEFTWALL == m_PrevState)
	{
		// �� ���¿��� �ؽ�Ʈ������ üũ�ؼ� 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }))
		{
			// ���� �̵� ��ġ�� �����ȼ��̶�� �̵����� ����.
			return;
		}

		// �����ȼ��� �ƴ϶�� �ش� ��ġ�� �̵�.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// ���� Ȥ�� �������� ���� ���¿��� ���Ʒ��� ����̸� 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) ||
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// �� ���¿��� �ؽ�Ʈ������ üũ�ؼ� 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed* _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// ���� �̵� ��ġ�� �����ȼ��̶�� �̵����� ����.
			return;
		}

		// �����ȼ��� �ƴ϶�� �ش� ��ġ�� �̵�.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}
}

// ������ ����Ǹ� ������ġ�� �ʱ�ȭ 
void Player::SlashEnd()
{
	m_AttackPos = { 0 , 0 };
	m_MyOriginPos = { 0 , 0 };
}

// �ϴ� �ӽ� ������ 
void Player::JumpStart()
{
	// ���� ���°� false �� ��� 
	if (false == m_IsJumping)
	{
		// true �� ������ش�. 
		m_IsJumping = true;
		m_CurrentVerticalVelocity = m_JumpPower;
	}

	m_SoundPlayer = GameEngineSound::Play("player_jump.wav");
	m_SoundPlayer.SetVolume(0.7f);
	m_Render->ChangeAnimation("player_jump");
	GetLevel()->CreateActor<JumpEffect>(static_cast<int>(RenderOrder::PLAYER_EFFECT));
}

void Player::JumpUpdate(float _DeltaTime)
{
	// �ܼ��ϰ� �Ӹ�������� fall �ιٲٴ°͵� �����ؾߵɼ��� 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::FALL);
		return;
	}

	if (true == GameEngineInput::IsPress("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		ChangeState(PlayerState::FALL);
		return;
	}

	if (true == DoorColCheck())
	{
		// ���� ���� �浹�ߴٸ� fall ���·� ����
		ChangeState(PlayerState::FALL);
		return;
	}

	// �� ���ȼ��� ����� ���� �̵��ϰ� 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		// ������ ���� �߷��� �����ش�. 
		m_CurrentVerticalVelocity += -m_GravityPower * _DeltaTime;
		m_NextTrans->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);

		// ���࿡ �� �ҹ�Ⱑ �������ȼ��̰ų� 
		// �ִ� �������̿� �����ߴٸ� fall ���·� ���� <--- �긦 ���? 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{0.0f, m_RenderPivot * 2.0f}) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
			return;
		}
		GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);
	}

	// ���� �����϶� �� �Ʒ��ȼ��� ���ΰ�찡 ������? 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// �� �ʱ�ȭ �� ���̵�� ����
		m_CurrentVerticalVelocity = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	// ������ ����, ����Ű�� ������ ������ 
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		DirCheck();
		if (true == GameEngineInput::IsPress("player_left_move"))
		{
			return;
		}

		// ���� ���� ���� �ȼ��� ����� ��
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// ���� ���� ����� �ȼ��� ������ġ�� �޾ƿ´�. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;	

			// ���� wall �ȼ��� �������� ���  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// ���⼭ ��ġ������ �������
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// �ܼ��� ���� �ȼ��� �������̶�� �ϰ͵� ���� 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			return;
		}

		// ����Ű�� ������ �� ó������ blackpixel �̶��  
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// ���� ���� ����� �ȼ��� ������ġ�� �޾ƿ´�. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;

			// ���� wall �ȼ��� �������� ���  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// ���⼭ ��ġ������ �������
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// �ܼ��� ���� �ȼ��� �������̶�� �ϰ͵� ���� 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			return;
		}
	}

	if (true == GameEngineInput::IsPress("player_left_move"))
	{
		DirCheck();
		if (true == GameEngineInput::IsPress("player_right_move"))
		{
			return;
		}

		// ���� ���� ���� �ȼ��� ����� ��
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// ���� ���� ����� �ȼ��� ������ġ�� �޾ƿ´�. 
			float4 DebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
			m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + DebugPos;

			// ���� wall �ȼ��� �������� ���  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// ���⼭ ��ġ������ �������
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::LEFTWALL);
					return;
				}

				// �ܼ��� ���� �ȼ��� �������̶�� �ϰ͵� ���� 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			return;
		}

		// ����Ű�� ������ �� ó������ blackpixel �̶��  
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			
			// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
			m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot ,0.0f };

			// ���� wall �ȼ��� �������� ���  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// ���⼭ ��ġ������ �������
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::LEFTWALL);
					return;
				}

				// �ܼ��� ���� �ȼ��� �������̶�� �ϰ͵� ���� 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			return;
		}
	}
}

void Player::JumpEnd()
{
	m_CurrentVerticalVelocity = 0.0f;
	// ���� 
	//m_JumpCutLine = 0.0f;
	m_IsJumping = false;
}

void Player::CrouchStart()
{
	m_Render->ChangeAnimation("player_crouch");
	DirCheck();
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
	
	// ũ���ġ ���¿��� ����Ű Down, 
	if (true == GameEngineInput::IsDown("player_right_move"))
	{
		DirCheck();
		// �������� �ȼ��� ����� �� 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// �ؽ�Ʈ���� üũ �� 
			m_NextTrans->AddLocalPosition(m_RightRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);

			// ������ �ȼ��̶�� ������Ʈ ���� X 
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
			{
				return;
			}

			// ���� ���� �浹���̶�� �ƹ����۵� �������� ���� 
			if (true == DoorColCheck())
			{
				return;
			}

			// �����ȼ��� �ƴ϶�� ������Ʈ����
			m_RightRoll = true;
			ChangeState(PlayerState::ROLL);
			return;
		}
	}

	if (true == GameEngineInput::IsDown("player_left_move"))
	{
		DirCheck();
		// �� ����(��������) �ȼ��� ����϶� 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// �ؽ�Ʈ���� üũ �� 
			m_NextTrans->AddLocalPosition(m_LeftRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);

			// ������ �ȼ��̶�� ������Ʈ ���� X 
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
			{
				return;
			}

			// �����ȼ��� �ƴ϶�� ������Ʈ����
			m_LeftRoll = true;
			ChangeState(PlayerState::ROLL);
			return;
		}
	}
}

void Player::CrouchEnd()
{
}

void Player::RollStart()
{
	m_Collision->Off();

	bool test = m_Collision->IsUpdate();

	if (true == m_RightRoll)
	{
		m_RollEndPos = GetTransform()->GetLocalPosition() + m_RightRollDir;
	}

	else if (true == m_LeftRoll)
	{
		m_RollEndPos = GetTransform()->GetLocalPosition() + m_LeftRollDir;
	}

	m_SoundPlayer = GameEngineSound::Play("player_roll.wav");
	m_SoundPlayer.SetVolume(0.7f);
	m_Render->ChangeAnimation("player_roll");
	DirCheck();
}

void Player::RollUpdate(float _DeltaTime)
{
	// ����, ��, ���Ʒ��� ����̶�� 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// fall �˻� �Ҷ��� On ���Ѽ� üũ�Ѵ�. 
		m_Collision->On(); 
		// �÷����� �浹���� �ƴҶ��� 
		if (false == PlatformColCheck())
		{
			ChangeState(PlayerState::FALL);
			return;
		}
		
	}

	// ���� ���� �����浹���¶�� ���̻� �������� ���� 
	std::shared_ptr<GameEngineCollision> DoorCol = m_SubCollision->Collision(ColOrder::DOOR, ColType::OBBBOX2D, ColType::OBBBOX2D);
	if (nullptr != DoorCol)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == GameEngineInput::IsDown("player_jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	// ���� RightRoll �����϶� �ִ� �̵��Ÿ��� �����ߴٸ� ����� ������Ʈ�� ���� 
	if (true == m_RightRoll && GetTransform()->GetLocalPosition().x >= m_RollEndPos.x)
	{
		// �̶� ���������� 
		// ������ �ȼ��� ��Ȳ���� �Ʒ� Ű�� ������ �ִٸ� ũ���ġ ���·� ����
		if (true == GameEngineInput::IsPress("player_crouch"))
		{
			ChangeState(PlayerState::CROUCH);
			return;
		}

		// �װ� �ƴ϶�� ���̵�� ���� 
		ChangeState(PlayerState::IDLE);
		return;
	}

	// ���� LeftRoll �����϶� �ִ� �̵��Ÿ��� �����ߴٸ� ����� ������Ʈ�� ���� 
	if (true == m_LeftRoll && GetTransform()->GetLocalPosition().x <= m_RollEndPos.x)
	{
		// �̶� ���������� 
		// ������ �ȼ��� ��Ȳ���� �Ʒ� Ű�� ������ �ִٸ� ũ���ġ ���·� ����
		if (true == GameEngineInput::IsPress("player_crouch"))
		{
			ChangeState(PlayerState::CROUCH);
			return;
		}

		// �װ� �ƴ϶�� ���̵�� ���� 
		ChangeState(PlayerState::IDLE);
		return;
	}

	// ȸ���� ����Ű�� �����ٸ� �����÷� ��ȯ 
	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	// ���� ����Ʈ�� ������ �� 
	if (false == m_LeftRoll && true == m_RightRoll)
	{
		if (true == DoorColCheck())
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		// �������� �ȼ��� ����� �� 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// �ؽ�Ʈ���� üũ �� 
			m_NextTrans->AddLocalPosition(m_RightRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			// ������ �ȼ��̶��
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
			{
				// ������ �ȼ��� ��Ȳ���� �Ʒ� Ű�� ������ �ִٸ� ũ���ġ ���·� ����
				if (true == GameEngineInput::IsPress("player_crouch"))
				{
					ChangeState(PlayerState::CROUCH);
					return;
				}

				// �װ� �ƴ϶�� ���̵�� ���� 
				ChangeState(PlayerState::IDLE);
				return;
			}

			GetTransform()->AddLocalPosition(m_RightRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			return;
		}

		// ���� ���� üũ�ȼ��� �ٷ� BlackPixel �̶�� 
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }) ||
				 PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
		{
			// ������ �ȼ��� ��Ȳ���� �Ʒ� Ű�� ������ �ִٸ� ũ���ġ ���·� ����
			if (true == GameEngineInput::IsPress("player_crouch"))
			{
				ChangeState(PlayerState::CROUCH);
				return;
			}

			// �װ� �ƴ϶�� ���̵�� ���� 
			ChangeState(PlayerState::IDLE);
			return;
		}

	}

	// Left Roll �϶�
	// ���� ����Ʈ�� ������ �� 
	if (false == m_RightRoll && true == m_LeftRoll)
	{
		// �������� �ȼ��� ����� �� 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// �ؽ�Ʈ���� üũ �� 
			m_NextTrans->AddLocalPosition(m_LeftRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			// ������ �ȼ��̶��
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }) ||
				PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
			{
				// ������ �ȼ��� ��Ȳ���� �Ʒ� Ű�� ������ �ִٸ� ũ���ġ ���·� ����
				if (true == GameEngineInput::IsPress("player_crouch"))
				{
					ChangeState(PlayerState::CROUCH);
					return;
				}

				// �װ� �ƴ϶�� ���̵�� ���� 
				ChangeState(PlayerState::IDLE);
				return;
			}

			GetTransform()->AddLocalPosition(m_LeftRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			return;
		}

		// ���� ���� üũ�ȼ��� �ٷ� BlackPixel �̶�� 
		else if  (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }) || 
				  PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
		{
			// ������ �ȼ��� ��Ȳ���� �Ʒ� Ű�� ������ �ִٸ� ũ���ġ ���·� ����
			if (true == GameEngineInput::IsPress("player_crouch"))
			{
				ChangeState(PlayerState::CROUCH);
				return;
			}

			// �װ� �ƴ϶�� ���̵�� ���� 
			ChangeState(PlayerState::IDLE);
			return;
		}

	}
}

void Player::RollEnd()
{
	if (false == m_Invincibility)
	{
		m_Collision->On();
	}

	m_RightRoll = false;
	m_LeftRoll = false;
	m_RollEndPos = float4::Null;
}

void Player::RightFlipStart()
{
	m_SoundPlayer = GameEngineSound::Play("player_roll.wav");
	m_SoundPlayer.SetVolume(0.7f);
	m_Collision->Off();
	m_Render->ChangeAnimation("player_flip");
	GetTransform()->SetLocalPositiveScaleX();
}


void Player::RightFlipUpdate(float _DeltaTime)
{
	// ���� �ø����ӽð����� ���� ������ �ʾҰ�, ���� ����ȼ��̶�� 
	m_FlipTime -= _DeltaTime;
	if (0 >= m_FlipTime)
	{
		m_FlipTime = m_FlipMaxTime;
		
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
			return;
		}
	}

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::FALL);
		return;
	}

	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		float4 MoveDir = m_RightFlipDir.NormalizeReturn();
		// ȭ��Ʈ�ȼ��� �� �̵��ϰ�, ���� �̵��� ��ġ�� �����ȼ��̶��
		m_NextTrans->AddLocalPosition(MoveDir * m_RollSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_WallDebugPivotX , m_WallDebugPivotY }))
		{
			ChangeState(PlayerState::RIGHTWALL);
			return;
		}

		GetTransform()->AddLocalPosition(MoveDir * m_RollSpeed * _DeltaTime);
		return;
	}

	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// ���� üũ�ȼ��� �������̶�� �ٷ� ����Ʈ���� ����
		ChangeState(PlayerState::LEFTWALL);
		return;
	}
}

void Player::RightFlipEnd()
{
	m_Collision->On();
	m_FlipTime = m_FlipMaxTime;
}

void Player::LeftFlipStart()
{
	m_SoundPlayer = GameEngineSound::Play("player_roll.wav");
	m_SoundPlayer.SetVolume(0.7f);

	m_Collision->Off();
	// �̶� ������ �������� �׷� 
	m_Render->ChangeAnimation("player_flip");
	GetTransform()->SetLocalNegativeScaleX();
}

void Player::LeftFlipUpdate(float _DeltaTime)
{
	// ���� �ø����ӽð����� ���� ������ �ʾҰ�, ���� ����ȼ��̶�� 
	m_FlipTime -= _DeltaTime;
	if (0 >= m_FlipTime)
	{
		m_FlipTime = m_FlipMaxTime;

		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
			return;
		}
	}

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::FALL);
		return;
	}

	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		float4 MoveDir = m_LeftFlipDir.NormalizeReturn();
		// ȭ��Ʈ�ȼ��� �� �̵��ϰ�, ���� �̵��� ��ġ�� �����ȼ��̶��
		m_NextTrans->AddLocalPosition(MoveDir * m_RollSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_WallDebugPivotX , m_WallDebugPivotY }))
		{
			ChangeState(PlayerState::LEFTWALL);
			return;
		}
		
		GetTransform()->AddLocalPosition(MoveDir * m_RollSpeed * _DeltaTime);
		return;
	}

	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// ���� üũ�ȼ��� �������̶�� �ٷ� ����Ʈ���� ����
		ChangeState(PlayerState::LEFTWALL);
		return;
	}
}

void Player::LeftFlipEnd()
{
	m_Collision->On();
	m_FlipTime = m_FlipMaxTime;
}

void Player::FallStart()
{
	m_Render->ChangeAnimation("player_fall");
}

void Player::FallUpdate(float _DeltaTime)
{
	// �ܼ��ϰ�. ���Ʒ��ȼ��� �������̶��.
	// ���� ������ �÷��ְ� IDLE�� ��ȯ. 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// ���ȼ��� ����̶�� �߷�����
	else if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()))
	{
		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 3.3f) * _DeltaTime);
	}

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}


	// sŰ ������ ���� ��� �ް��� 
	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		if (true == GameEngineInput::IsDown("player_slash"))
		{
			ChangeState(PlayerState::SLASH);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Down * m_FallPower * _DeltaTime);
		return;
	}

	// ������ ����, ����Ű�� ������ ������ 
	if (true == GameEngineInput::IsPress("player_right_move") && false == DoorColCheck())
	{
		DirCheck();
		if (true == GameEngineInput::IsPress("player_left_move"))
		{
			return;
		}

		// ���� ���� ���� �ȼ��� ����� ��
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// ���� ���� ����� �ȼ��� ������ġ�� �޾ƿ´�. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;

			// ���� wall �ȼ��� �������� ���  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// ���⼭ ��ġ������ �������
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// �ܼ��� ���� �ȼ��� �������̶�� �ϰ͵� ���� 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			return;
		}

		// ����Ű�� ������ �� ó������ blackpixel �̶��  
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// ���� ���� ����� �ȼ��� ������ġ�� �޾ƿ´�. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;

			// ���� wall �ȼ��� �������� ���  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// ���⼭ ��ġ������ �������
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// �ܼ��� ���� �ȼ��� �������̶�� �ϰ͵� ���� 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			return;
		}
	}

	if (true == GameEngineInput::IsPress("player_left_move"))
	{
		DirCheck();
		if (true == GameEngineInput::IsPress("player_right_move"))
		{
			return;
		}

		// �� ���� üũ �ȼ��� ����� ( negative �������� right �ȼ�üũ ) 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// ���̸� �̵������� �� �� ��ġ�� �ѹ��� �˻��ؼ� 
			m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);

			float4 CheckPos = m_NextTrans->GetLocalPosition() + float4{ -m_RenderPivot ,0.0f };
			// �� ��ġ�� ������ �ȼ��̶�� �̵����� �ʰ�
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
			{
				// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// ���⼭ ��ġ������ �������
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::LEFTWALL);
					return;
				}

				return;
			}

			// �װ� �ƴ϶�� ��¥ ���� ��ġ�� �̵���
			GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			return;
		}
	}

	// ����Ű�� ������ �� ó������ blackpixel �̶��  
	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{

		// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
		m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot ,0.0f };

		// ���� wall �ȼ��� �������� ���  
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
		{
			// ��,�ϴ��� üũ�ؼ� �Ѵ� ������ �ȼ��̶�� 
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
				PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
			{
				// ���⼭ ��ġ������ �������
				float4 MyPos = GetTransform()->GetLocalPosition();
				ChangeState(PlayerState::LEFTWALL);
				return;
			}

			// �ܼ��� ���� �ȼ��� �������̶�� �ϰ͵� ���� 
			return;
		}

		GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		return;
	}
}

void Player::FallEnd()
{
	// ��������Ʈ 
	if (PlayerState::IDLE == m_NextState)
	{
		m_SoundPlayer = GameEngineSound::Play("player_land.wav");
		m_SoundPlayer.SetVolume(0.7f);
		GetLevel()->CreateActor<LandEffect>();
	}
}

void Player::RightWallStart()
{
	m_Render->ChangeAnimation("player_wallslide");
	GetTransform()->SetLocalPositiveScaleX();

	if (true == GameEngineInput::IsPress("player_jump"))
	{
		float PressTime = GameEngineInput::GetPressTime("player_jump");
		m_WallJumpPower = 630.0f;
	}
}

void Player::RightWallUpdate(float _DeltaTime)
{
	// ���Ӹ����� �ȼ��� �������� �ƴҶ���
	// ���� ����Ű�� ������ �ִ� ���¶�� 
	if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		if (true == GameEngineInput::IsPress("player_jump"))
		{
			if (0.0f >= m_WallPressTime)
			{
				m_WallJumpPower = 0.0f;
			}

			m_WallPressTime -= _DeltaTime;

			// �����̵���ġ�� üũ�ؼ� , ���� �̵���ġ�� top �ȼ��� black �� �ƴ� ��쿡�� �̵��ϵ��� 
			m_NextTrans->AddWorldPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ 0.0f,  m_RenderPivot * 2.0f }))
			{
				GetTransform()->AddLocalPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			}
		}
	}

	// ���� �� �ٴ��ȼ��� ���̶��. 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// ����Ű �Է½�
	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}


	if (true == GameEngineInput::IsDown("player_jump"))
	{
		ChangeState(PlayerState::LEFTFLIP);
		return;
	}

	// ���⼭ �ܼ��ϰ� fall�� �ٲٴ°� �ƴ϶�, ��ġ�� �̵� ��Ű�� fall�� �ٲ۴� 
	// ���� �������� ���¿��� �ٷ� ������ ���ϸ��� �����ϱ� �ٷ� �̵����ѵ� �ɵ� ��. 
	if (true == GameEngineInput::IsDown("player_left_move"))
	{
		GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		ChangeState(PlayerState::FALL);
		return;
	}

	// ���� ���� ���� �ȼ��� ����� �� 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
		m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ m_WallDebugPivotX , m_WallDebugPivotY };

		// �̵��� ��ġ�� ����(��������) ������ȼ��� �������̰�, �̵��� ��ġ�� ���� �ȼ��� ������ ����̶�� 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition()))
		{
			// ���� ���� ������ 
			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed / 10.0f * _DeltaTime);
			GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		return;
	}

	// �̹� �������̶�� ���� ���ʺ��� �پ��ִ� �����̰�, �߷����޾Ƽ� �Ʒ��θ� �������� �ȴ�. 
	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// �����̵���ġ üũ �� 
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ m_WallDebugPivotX , m_WallDebugPivotY };

		// ���� �̵���ġ�� �ȼ��� ����̶�� fall 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
		{
			GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
			ChangeState(PlayerState::FALL);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		return;
	}
}

void Player::RightWallEnd()
{
	m_WallJumpPower = 0.0f;
	m_WallPressTime = m_WallPressInitTime;
}

void Player::LeftWallStart()
{
	m_Render->ChangeAnimation("player_wallslide");
	GetTransform()->SetLocalNegativeScaleX();

	if (true == GameEngineInput::IsPress("player_jump"))
	{
		float PressTime = GameEngineInput::GetPressTime("player_jump");
		m_WallJumpPower = 630.0f;
	}
}

void Player::LeftWallUpdate(float _DeltaTime)
{
	// ���Ӹ����� �ȼ��� �������� �ƴҶ��� 
	if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		if (true == GameEngineInput::IsPress("player_jump"))
		{
			if (0.0f >= m_WallPressTime)
			{
				m_WallJumpPower = 0.0f;
			}

			m_WallPressTime -= _DeltaTime;

			// �� ������ġ�� Top �� �������� �ƴ� ����.
			// �ؽ�Ʈ���� ��� �ؾ��� 
			m_NextTrans->AddWorldPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{0.0f,  m_RenderPivot * 2.0f}))
			{
				GetTransform()->AddLocalPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			}
		}
	}
	// ���� �� �ٴ��ȼ��� ���̶��. 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		PixelCollider::PixelCol->GroundCheck(this);
		ChangeState(PlayerState::IDLE);
		return;
	}

	// ����Ű �Է½�
	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}


	if (true == GameEngineInput::IsDown("player_jump"))
	{
		ChangeState(PlayerState::RIGHTFLIP);
		return;
	}

	// ���⼭ �ܼ��ϰ� fall�� �ٲٴ°� �ƴ϶�, ��ġ�� �̵� ��Ű�� fall�� �ٲ۴� 
	// ���� �������� ���¿��� �ٷ� ������ ���ϸ��� �����ϱ� �ٷ� �̵����ѵ� �ɵ� ��. 
	if (true == GameEngineInput::IsDown("player_right_move"))
	{
		GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		ChangeState(PlayerState::FALL);
		return;
	}	

	// ���� ���� ���� �ȼ��� ����� �� 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// ���� NextPos �� ���� ��ġ�� �̵���Ű�� 
		m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		// �̵��� ��ġ�� ���� ����� �ȼ� ��ġ�� üũ�ؼ� 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_WallDebugPivotX , m_WallDebugPivotY };

		// �̵��� ��ġ�� ����(��������) ������ȼ��� �������̰�, �̵��� ��ġ�� ���� �ȼ��� ������ ����̶�� 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition()))
		{
			// ���� ���� ������ 
			GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed / 10.0f * _DeltaTime);
			GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
			return;
		}


		GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		return;
	}	

	// �̹� �������̶�� ���� ���ʺ��� �پ��ִ� �����̰�, �߷����޾Ƽ� �Ʒ��θ� �������� �ȴ�. 
	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// �����̵���ġ üũ �� 
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime); 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_WallDebugPivotX , m_WallDebugPivotY };

		// ���� �̵���ġ�� �ȼ��� ����̶�� fall 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
		{
			GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
			ChangeState(PlayerState::FALL);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		return;
	}
}

void Player::LeftWallEnd()
{
	m_WallJumpPower = 0.0f;
	m_WallPressTime = m_WallPressInitTime;
}

void Player::DoorBreakStart()
{
	DirCheck();
	GetLevel()->GetMainCamera()->SetZoomRatio(0.975f);
	m_Render->ChangeAnimation("player_doorbreak_full");
}

void Player::DoorBreakUpdate(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		// �ִϸ��̼��̳����� 
		// ���� �浹���ִ� ���� �����ͼ� �ִϸ��̼��� �����Ų��. 
		std::shared_ptr<GameEngineCollision> DoorCol = m_Collision->Collision(ColOrder::DOOR, ColType::AABBBOX2D, ColType::AABBBOX2D);
		if (nullptr != DoorCol)
		{
			std::shared_ptr<IronDoor> Door = DoorCol->GetActor()->DynamicThis<IronDoor>();
			if (nullptr != Door)
			{
				Door->ChangeState(IronDoorState::OPEN);
				DoorCol->Off();
			}
		}

		ChangeState(PlayerState::IDLE);
		return;
	}
}

void Player::DoorBreakEnd()
{
	// �̶� ���Ͷ� �浹�ߴٸ� ī�޶� ����Ʈ ȣ�� 
	GetLevel()->GetMainCamera()->SetZoomRatio(1.00f);
}

// �ϴ� ����
// �ʹ����ڿ������� 
// �׾����� �� ���ڰ� ���ư��� �ٲ����
void Player::DeathStart()
{
	// �̶� �����׾����� �����ؼ� ��Ȳ�� ���� �ִϸ��̼� ���� 
	m_HitPos = GetTransform()->GetLocalPosition();
	DirCheck();
	m_SoundPlayer = GameEngineSound::Play("player_die.wav");
	m_SoundPlayer.SetVolume(0.7f);
	m_Render->ChangeAnimation("player_die");
	m_Render->GetTransform()->AddLocalPosition({ 0 , -15.0f });
}

void Player::DeathUpdate(float _DeltaTime)
{
	// ���̻��� �ٲ����  
	if (true == m_Render->IsAnimationEnd())
	{
		ChangeState(PlayerState::NONE);
		return;
	}

	float FlyingSpeed = m_MoveSpeed * 1.3f;
	float4 MyPos = GetTransform()->GetLocalPosition();
	float X = abs(MyPos.x - m_HitPos.x);
	if (X >= 60.0f)
	{
		FlyingSpeed *= 0.67f;
	}

	
	if (true == m_Direction)
	{
		m_NextTrans->AddLocalPosition(float4::Left * FlyingSpeed * _DeltaTime);

		// ���� ���� ���� �ȼ��� ����� �� 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_RenderPivot, m_RenderPivot }))
		{
			return;
		}

		GetTransform()->AddLocalPosition(float4::Left * FlyingSpeed * _DeltaTime);
	}
	else if (false == m_Direction)
	{
		m_NextTrans->AddLocalPosition(float4::Right * FlyingSpeed * _DeltaTime);
		// ���� ���� ���� �ȼ��� ����� �� 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { m_RenderPivot, m_RenderPivot }))
		{
			return;
		}

		GetTransform()->AddLocalPosition(float4::Right * FlyingSpeed * _DeltaTime);
	}
	
	
}

void Player::DeathEnd()
{
	m_Render->GetTransform()->AddLocalPosition({ 0 , 15.0f });
	m_HitPos = float4{ 0.0f, 0.0f };
}

void Player::NoneStart()
{
	m_Render->GetTransform()->AddLocalPosition({ 0 , -15.0f });
}

void Player::NoneUpdate(float _DeltaTime)
{
	
}



void Player::NoneEnd()
{
	m_Render->GetTransform()->AddLocalPosition({ 0 , 15.0f });
}

