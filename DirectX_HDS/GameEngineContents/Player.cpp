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

// 레벨이 추가될때마다 헤더추가 후 Reset 함수에 추가.. 
#include "ClubLevel_00.h"
#include "ClubLevel_01.h"
#include "ClubLevel_02.h"
#include "ClubLevel_03.h"
#include "ClubLevel_04.h"
#include "ClubLevel_Boss.h"

#include "Monster_Grunt.h"

// 카메라
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

// 총에 맞았다면 
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
	// 액터 스타트 기본인터페이스 구성
	// 키생성

	// 컴포넌트 세팅
	ComponentSetting();
	// 필요한 리소스 로드및 애니메이션 생성	
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

	// 이벤트추가 
	// std::bind, 1번인자 : 멤버함수의 포인터 / 2번인자 : this 포인터
	m_Render->SetAnimationStartEvent("player_attack", static_cast<size_t>(1), std::bind(&Player::CreateSlashEffect, this));
}

// 플레이어와 관련된 사운드는 전부 플레이어에서 로드 
void Player::LoadSound()
{
	// 사운드로드 
	{
		// 디렉토리 클래스생성
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("sound");
		NewDir.Move("player");
		
		// 문
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
	// 디버그 업데이트
	DebugUpdate();

	// 제한시간 초과 체크 
	TimeOutCheck();

	HitCheck();

	// 스킬 업데이트 
	SkillUpdate(_DeltaTime);

	// nextpos 현재 플레이어 위치로 이동
	NextPosUpdate();
	
	// 만약 플랫폼과 충돌중인 상태에서 아래키 입력시 상태전환 
	if (true == PlatformColCheck() && GameEngineInput::IsDown("player_crouch"))
	{
		// 나의 아래 픽셀이 검은색이 아니라면 fall로 전환 
		if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
		}
	}

	// 레이저 충돌체크
	LaserColCheck();

	// 환풍기 충돌체크 
	FanBladeColCheck();

	// 상태업데이트 
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
	// 3개중에 랜덤한거. 
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
	// ?? 뭐야 
	std::shared_ptr<GameEngineCollision> Col = m_Collision->Collision(ColOrder::MONSTER_ATTACK, ColType::OBBBOX3D, ColType::OBBBOX3D);

	if (nullptr != Col)
	{
		CreateHitEffect(Col);
		// 나를 데스상태로 
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
	// 이펙트만들고 
	std::shared_ptr<HitEffect> Effect = GetLevel()->CreateActor<HitEffect>(static_cast<int>(RenderOrder::EFFECT));
	Effect->SetPivot(float4{ 10.0f, -10.0f });
	// 내위치 
	float4 MyPos = GetTransform()->GetWorldPosition();
	// 상대위치 
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
	// 데스체크, 만약 스테이지 제한시간을 넘어섰다면 
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
	// 픽셀충돌 
	CreateComponent<PixelCollider>();

	// 넥스트포스체크용 트랜스폼
	m_NextTrans = std::make_shared<GameEngineTransform>();

	// 메인렌더 
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER);
	m_Render->GetTransform()->SetLocalPosition({ 0, m_RenderPivot });
	m_Render->SetScaleRatio(2.0f);

	// 콜리전 
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::PLAYER));
	m_Collision->GetTransform()->SetLocalScale(m_ColScale);
	m_Collision->GetTransform()->SetLocalPosition({ 0, m_ColPivot });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->DebugOff();

	// 얘를 어떻게 할거니? 
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
	// 디버그용
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
		// 스킬 false
		m_IsSkill = false;
		// 색돌리고 
		m_Render->ColorOptionValue.MulColor.r = 1.0f;
		// 슬로우리셋
		SlowReset();
		return;
	}

	// 스케일적용 X 델타타임을 받아둔다.  
	float OriginTime = GameEngineTime::GlobalTime.GetDeltaTime();

	// 만약 배터리가 모두 소모 되었을 때의 충전로직
	// 아래 if 문이랑 합쳐질거같기도한데 일단은 되니까 나중에
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

	// 눌려있으면 스킬발동중 인거고 , 배터리 차지가 false 일때만 들어온다. 
	if (true == GameEngineInput::IsPress("player_skill_slow"))
	{
		m_Render->ColorOptionValue.MulColor.r = 0.1f;
		
		// 만약 누르고 있는중에 지속시간이 0.0초보다 작아지게 되면 스킬을 종료하고
		// 스킬 사용 상태를 false로 변경, 제한시간을 0.0초로 초기화한다. 
		if (0.0f >= m_SkillLimitTime)
		{
			m_BatteryCharge = true;
			SlowReset();
			m_SkillLimitTime = 0.0f;
			m_IsSkill = false;
			return;
		}

		// 지금 누르고 있는 상태이기 때문에 스킬온 
		m_IsSkill = true;

		// 지속시간을 감소시킨다. 
		m_SkillLimitTime -= OriginTime;

		// 델타타임에 스케일을 적용한다. 
		Slow();
	}

	// 여긴 어차피 안눌린 상태니까 기존의 델타타임이 들어올거고 
	else if (false == GameEngineInput::IsPress("player_skill_slow"))
	{
		m_Render->ColorOptionValue.MulColor.r = 1.0f;
		// 안눌렸으면 바로 타임스케일리셋 
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

		 //팬블레이드는 여기서 더느리게 만들어 
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
	// 현재 상태의 update 호출 
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

	// 이전 state의 end 
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
	// 이전 스테이트가 데스라면 스테이지 미클리어,
	// 난무조건 정방향 ( 오른쪽 ) , 데스 후 NONE 상태로 변경됨 
	if (PlayerState::NONE == m_PrevState)
	{
		GetTransform()->SetLocalPositiveScaleX();
	}

	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(GetTransform()->GetLocalPosition()))
	{
		// 만약 내 픽셀이 검은색이라면 위로 올려준다.
		PixelCollider::PixelCol->GroundCheck(this);
	}

	m_Render->ChangeAnimation("player_idle");

	// 이전 상태가 점프였는데, Idle로 변경 되었다면 내가 땅이라는 뜻이기 때문에 착지이펙트 생성
	if (PlayerState::JUMP == m_PrevState)
	{
		GetLevel()->CreateActor<LandEffect>();
	}
}

void Player::IdleUpdate(float _DeltaTime)
{
	// 공격, 마우스 좌클릭 
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

	// 점프키 , w
	if (true == GameEngineInput::IsDown("player_jump"))
	{
		if (true == DoorColCheck())
		{
			return;
		}

		ChangeState(PlayerState::JUMP);
		return;
	}

	// 크라우치 , s
	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	// 동시에 눌러져있을 경우 아무것도 수행하지 않음 
	if (true == GameEngineInput::IsPress("player_right_move") && true == GameEngineInput::IsPress("player_left_move"))
	{
		return;
	}

	// 우측이동 , d
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		ChangeState(PlayerState::IDLETORUN); 
		return;
	}

	// 좌측이동 , a 
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

		// 이때 만약, 내가 왼쪽키를 누르고 있고 플랫폼과 충돌중이라면 무시하고 이동한다. 
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
		// 애니메이션이 종료된 시점에 왼쪽키나 오른쪽키가 눌려있다면
		// 무브 상태로 전환 
		if (true == GameEngineInput::IsPress("player_right_move") ||
			true == GameEngineInput::IsPress("player_left_move"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		// 눌려 있지 않다면, 다시 IDLE 
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
		// 만약 내 바로 다음 픽셀이 검은색일 경우
		// 추가로 내 위로 다섯칸이 흰색이라면 
		float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Right;
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Right)) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
		{
			// 이동시키고, 땅에쳐박혀있다면 올려준다. 
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

	// 내 왼쪽 체크 픽셀이 흰색이 ( negative 적용으로 right 픽셀체크 ) 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
	{
		float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Left;
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Left)) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
		{
			// 이동시키고, 땅에쳐박혀있다면 올려준다. 
			GetTransform()->AddLocalPosition(float4::Left * m_StartMoveSpeed * _DeltaTime);
			PixelCollider::PixelCol->GroundCheck(this);
			return;
		}

		// 더미를 이동시켰을 때 의 위치를 한번더 검사해서 
		m_NextTrans->AddLocalPosition(float4::Left * m_StartMoveSpeed * _DeltaTime);
		// 그 위치가 검은색 픽셀이라면 이동하지 않고
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
		{
			return;
		}

		// 그게 아니라면 진짜 나의 위치를 이동해
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

		// 이때 만약, 내가 왼쪽키를 누르고 있고 플랫폼과 충돌중이라면 무시하고 이동한다. 
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

	// 우측키를 누르고 있을때, 우측 이동만 체크 
	if (true == GameEngineInput::IsPress("player_right_move") &&  false == GameEngineInput::IsPress("player_left_move") && false == DoorColCheck())
	{
		DirCheck();
		// 만약 우측키를 누른 상태에서 좌클릭 입력이 되어있을 경우,
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
					// 이동시키고, 땅에쳐박혀있다면 올려준다. 
					GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
					PixelCollider::PixelCol->GroundCheck(this);
					return;
				}

				// 더미를 이동시켰을 때 의 위치를 한번더 검사해서 
				m_NextTrans->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
				float4 CheckPos = m_NextTrans->GetLocalPosition() + float4{ -m_RenderPivot ,0.0f };

				// 그 위치가 검은색 픽셀이라면 이동하지 않고
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
				{
					return;
				}

				// 그게 아니라면 진짜 나의 위치를 이동해
				GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
				return;
			}
		}

		// right 
		// 내우측 체크픽셀이 흰색일 때 이동할건데 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// 만약 내 바로 다음 픽셀이 검은색일 경우
			// 추가로 내 위로 다섯칸이 흰색이라면 
			float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Right;
			if(PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) || 
			   PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Right)) &&
			   PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
			{
				// 이동시키고, 땅에쳐박혀있다면 올려준다. 
				GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
				PixelCollider::PixelCol->GroundCheck(this);
				return;
			}
			// 다음위치로 이동시키고.
			m_NextTrans->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
			// 다음 위치의 우측체크픽셀을 검사해서 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot };
			// 그 픽셀이 검은색이라면 움직이지 않을거야
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
					// 이동시키고, 땅에쳐박혀있다면 올려준다. 
					GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
					PixelCollider::PixelCol->GroundCheck(this);
					return;
				}

				// 넥스트포스 체크하고
				m_NextTrans->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
				{
					return;
				}

				GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
				return;
			}
		}

		// 내 왼쪽 체크 픽셀이 흰색이 ( negative 적용으로 right 픽셀체크 ) 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			float4 NextPixelPos = GetTransform()->GetWorldPosition() + float4::Left;

			// 이동한 위치가 검은색, 이동한 위치의 다음 픽셀이 검은색, 그위쪽 픽셀을 특정범위를 지정해서. 거기가 흰색이면 위로이동이잖아 ?
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos) ||
				PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Left)) &&
				PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(NextPixelPos + (float4::Up * m_DiagonalPivot)))
			{
				// 이동시키고, 땅에쳐박혀있다면 올려준다. 
				GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
				PixelCollider::PixelCol->GroundCheck(this);
				return;
			}
			
			// 더미를 이동시켰을 때 의 위치를 한번더 검사해서 
			m_NextTrans->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
			float4 CheckPos = m_NextTrans->GetLocalPosition() + float4{ -m_RenderPivot ,0.0f };
			// 그 위치가 검은색 픽셀이라면 이동하지 않고
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 { -m_RenderPivot , m_RenderPivot }))
			{
				return;
			}

			// 그게 아니라면 진짜 나의 위치를 이동해
			GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
			return;
		}
	}
}

void Player::MoveEnd()
{
	m_MoveSoundPlayer.Stop();
}

// 일단 현시점에서는 버그 없음 완료
void Player::SlashStart()
{
	m_AttackPos = Cursor::MainCursor->GetTransform()->GetLocalPosition();
	m_MyOriginPos = GetTransform()->GetLocalPosition();
	m_Render->ChangeAnimation("player_attack");
	SlashSoundPlay();
}

void Player::SlashUpdate(float _DeltaTime)
{ 
	// 만약 공격 애니메이션이 종료되었을 때 
	if (true == m_Render->IsAnimationEnd())
	{
		// 내가 공중상태라면 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
			return;
		}
		
		// 내가 바닥인데, 공격 이전의 상태가 MOVE였다면 MOVE상태로 변경
		else if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
				 PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()) &&
				 PlayerState::MOVE == m_PrevState)
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		// 그게 아니라면 아이들로 변경
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

	// 만약 이전 상태가 fall 인 상태에서 y축 공격좌표가 나보다 높다면 
	if (PlayerState::FALL == m_PrevState && m_MyOriginPos.y <= m_AttackPos.y)
	{
		AttDir.y = 0.0f;
	}
	// 나보다 공격좌표가 나보다 낮다면 
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
	
	// 내가 지상일 때 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// 공격위치가 나보다 낮다면 
		if (m_AttackPos.y < m_MyOriginPos.y)
		{
			// y축 이동을 하지 않는다. 
			AttDir.y = 0.0f;
		}

		// 그 상태에서 넥스트포스를 체크해서 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 {m_RenderPivot, m_RenderPivot}) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4 {-m_RenderPivot, m_RenderPivot }))
		{
			// 다음 이동 위치가 검은픽셀이라면 이동하지 않음.
			return;
		}

		// 검은픽셀이 아니라면 해당 위치로 이동.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// 내가 공중에 떠 있을 때 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()))
	{
		// 넥스트포스 체크 후 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// 다음 이동 위치가 검은픽셀이라면 이동하지 않음.
			return;
		}

		// 검은픽셀이 아니라면 해당 위치로 이동.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}
	
	// 왼쪽 혹은 오른쪽이 벽인 상태에서 내아래가 땅이면 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) ||
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// 공격위치가 나보다 낮다면 
		if (m_AttackPos.y < m_MyOriginPos.y)
		{
			// y축 이동을 하지 않는다. 
			AttDir.y = 0.0f;
		}

		// 그 상태에서 넥스트포스를 체크해서 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// 다음 이동 위치가 검은픽셀이라면 이동하지 않음.
			return;
		}

		// 검은픽셀이 아니라면 해당 위치로 이동.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// 그냥 이전 상태가 뭐였냐에 따라서 체크
	if (PlayerState::RIGHTWALL == m_PrevState)
	{
		// 그 상태에서 넥스트포스를 체크해서 
		m_NextTrans->AddLocalPosition(AttDir* m_AttSpeed* _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// 다음 이동 위치가 검은픽셀이라면 이동하지 않음.
			return;
		}

		// 검은픽셀이 아니라면 해당 위치로 이동.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// 그냥 이전 상태가 뭐였냐에 따라서 체크
	if (PlayerState::LEFTWALL == m_PrevState)
	{
		// 그 상태에서 넥스트포스를 체크해서 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }))
		{
			// 다음 이동 위치가 검은픽셀이라면 이동하지 않음.
			return;
		}

		// 검은픽셀이 아니라면 해당 위치로 이동.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}

	// 왼쪽 혹은 오른쪽이 벽인 상태에서 내아래가 흰색이면 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) ||
		PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Left->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// 그 상태에서 넥스트포스를 체크해서 
		m_NextTrans->AddLocalPosition(AttDir * m_AttSpeed* _DeltaTime);
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot, m_RenderPivot }) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot, m_RenderPivot }))
		{
			// 다음 이동 위치가 검은픽셀이라면 이동하지 않음.
			return;
		}

		// 검은픽셀이 아니라면 해당 위치로 이동.
		GetTransform()->AddLocalPosition(AttDir * m_AttSpeed * _DeltaTime);
		return;
	}
}

// 공격이 종료되면 공격위치를 초기화 
void Player::SlashEnd()
{
	m_AttackPos = { 0 , 0 };
	m_MyOriginPos = { 0 , 0 };
}

// 일단 임시 마무리 
void Player::JumpStart()
{
	// 점프 상태가 false 일 경우 
	if (false == m_IsJumping)
	{
		// true 로 만들어준다. 
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
	// 단순하게 머리통박으면 fall 로바꾸는것도 수정해야될수도 
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
		// 만약 문과 충돌했다면 fall 상태로 변경
		ChangeState(PlayerState::FALL);
		return;
	}

	// 내 윗픽셀이 흰색일 때만 이동하고 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		// 점프의 힘에 중력을 더해준다. 
		m_CurrentVerticalVelocity += -m_GravityPower * _DeltaTime;
		m_NextTrans->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);

		// 만약에 내 뚝배기가 검은색픽셀이거나 
		// 최대 점프높이에 도달했다면 fall 상태로 변경 <--- 얘를 어떻게? 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{0.0f, m_RenderPivot * 2.0f}) ||
			PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
		{
			ChangeState(PlayerState::FALL);
			return;
		}
		GetTransform()->AddLocalPosition(float4::Up * m_CurrentVerticalVelocity * _DeltaTime);
	}

	// 점프 상태일때 내 아랫픽셀이 땅인경우가 있을까? 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// 값 초기화 후 아이들로 변경
		m_CurrentVerticalVelocity = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	// 점프시 우측, 좌측키를 누르고 있을때 
	if (true == GameEngineInput::IsPress("player_right_move"))
	{
		DirCheck();
		if (true == GameEngineInput::IsPress("player_left_move"))
		{
			return;
		}

		// 현재 나의 우측 픽셀이 흰색일 때
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// 나의 우측 디버그 픽셀의 로컬위치를 받아온다. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// 나의 NextPos 를 다음 위치로 이동시키고 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;	

			// 우측 wall 픽셀이 검은색일 경우  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// 여기서 위치보정을 어떻게하지
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// 단순히 우측 픽셀만 검은색이라면 암것도 안함 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			return;
		}

		// 우측키를 눌렀을 때 처음부터 blackpixel 이라면  
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// 나의 우측 디버그 픽셀의 로컬위치를 받아온다. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// 나의 NextPos 를 다음 위치로 이동시키고 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;

			// 우측 wall 픽셀이 검은색일 경우  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// 여기서 위치보정을 어떻게하지
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// 단순히 우측 픽셀만 검은색이라면 암것도 안함 
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

		// 현재 나의 우측 픽셀이 흰색일 때
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// 나의 우측 디버그 픽셀의 로컬위치를 받아온다. 
			float4 DebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// 나의 NextPos 를 다음 위치로 이동시키고 
			m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + DebugPos;

			// 우측 wall 픽셀이 검은색일 경우  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// 여기서 위치보정을 어떻게하지
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::LEFTWALL);
					return;
				}

				// 단순히 우측 픽셀만 검은색이라면 암것도 안함 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			return;
		}

		// 우측키를 눌렀을 때 처음부터 blackpixel 이라면  
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			
			// 나의 NextPos 를 다음 위치로 이동시키고 
			m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot ,0.0f };

			// 우측 wall 픽셀이 검은색일 경우  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// 여기서 위치보정을 어떻게하지
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::LEFTWALL);
					return;
				}

				// 단순히 우측 픽셀만 검은색이라면 암것도 안함 
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
	// 보류 
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
	
	// 크라우치 상태에서 우측키 Down, 
	if (true == GameEngineInput::IsDown("player_right_move"))
	{
		DirCheck();
		// 내오른쪽 픽셀이 흰색일 때 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// 넥스트포스 체크 후 
			m_NextTrans->AddLocalPosition(m_RightRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);

			// 검은색 픽셀이라면 스테이트 변경 X 
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
			{
				return;
			}

			// 만약 문과 충돌중이라면 아무동작도 수행하지 않음 
			if (true == DoorColCheck())
			{
				return;
			}

			// 검은픽셀이 아니라면 스테이트변경
			m_RightRoll = true;
			ChangeState(PlayerState::ROLL);
			return;
		}
	}

	if (true == GameEngineInput::IsDown("player_left_move"))
	{
		DirCheck();
		// 내 왼쪽(리버스고) 픽셀이 흰색일때 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// 넥스트포스 체크 후 
			m_NextTrans->AddLocalPosition(m_LeftRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);

			// 검은색 픽셀이라면 스테이트 변경 X 
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
			{
				return;
			}

			// 검은픽셀이 아니라면 스테이트변경
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
	// 우측, 나, 내아래가 흰색이라면 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()) &&
		PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		// fall 검사 할때만 On 시켜서 체크한다. 
		m_Collision->On(); 
		// 플랫폼과 충돌중이 아닐때만 
		if (false == PlatformColCheck())
		{
			ChangeState(PlayerState::FALL);
			return;
		}
		
	}

	// 만약 내가 문과충돌상태라면 더이상 진행하지 않음 
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

	// 만약 RightRoll 상태일때 최대 이동거리에 도달했다면 그즉시 스테이트를 종료 
	if (true == m_RightRoll && GetTransform()->GetLocalPosition().x >= m_RollEndPos.x)
	{
		// 이때 마찬가지로 
		// 검은색 픽셀인 상황에서 아래 키를 누르고 있다면 크라우치 상태로 변경
		if (true == GameEngineInput::IsPress("player_crouch"))
		{
			ChangeState(PlayerState::CROUCH);
			return;
		}

		// 그게 아니라면 아이들로 변경 
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 만약 LeftRoll 상태일때 최대 이동거리에 도달했다면 그즉시 스테이트를 종료 
	if (true == m_LeftRoll && GetTransform()->GetLocalPosition().x <= m_RollEndPos.x)
	{
		// 이때 마찬가지로 
		// 검은색 픽셀인 상황에서 아래 키를 누르고 있다면 크라우치 상태로 변경
		if (true == GameEngineInput::IsPress("player_crouch"))
		{
			ChangeState(PlayerState::CROUCH);
			return;
		}

		// 그게 아니라면 아이들로 변경 
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 회피중 공격키를 누른다면 슬래시로 전환 
	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}

	// 내가 라이트롤 상태일 때 
	if (false == m_LeftRoll && true == m_RightRoll)
	{
		if (true == DoorColCheck())
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		// 내오른쪽 픽셀이 흰색일 때 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// 넥스트포스 체크 후 
			m_NextTrans->AddLocalPosition(m_RightRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			// 검은색 픽셀이라면
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
			{
				// 검은색 픽셀인 상황에서 아래 키를 누르고 있다면 크라우치 상태로 변경
				if (true == GameEngineInput::IsPress("player_crouch"))
				{
					ChangeState(PlayerState::CROUCH);
					return;
				}

				// 그게 아니라면 아이들로 변경 
				ChangeState(PlayerState::IDLE);
				return;
			}

			GetTransform()->AddLocalPosition(m_RightRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			return;
		}

		// 만약 나의 체크픽셀이 바로 BlackPixel 이라면 
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }) ||
				 PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ m_RenderPivot , m_RenderPivot }))
		{
			// 검은색 픽셀인 상황에서 아래 키를 누르고 있다면 크라우치 상태로 변경
			if (true == GameEngineInput::IsPress("player_crouch"))
			{
				ChangeState(PlayerState::CROUCH);
				return;
			}

			// 그게 아니라면 아이들로 변경 
			ChangeState(PlayerState::IDLE);
			return;
		}

	}

	// Left Roll 일때
	// 내가 라이트롤 상태일 때 
	if (false == m_RightRoll && true == m_LeftRoll)
	{
		// 내오른쪽 픽셀이 흰색일 때 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// 넥스트포스 체크 후 
			m_NextTrans->AddLocalPosition(m_LeftRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			// 검은색 픽셀이라면
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }) ||
				PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
			{
				// 검은색 픽셀인 상황에서 아래 키를 누르고 있다면 크라우치 상태로 변경
				if (true == GameEngineInput::IsPress("player_crouch"))
				{
					ChangeState(PlayerState::CROUCH);
					return;
				}

				// 그게 아니라면 아이들로 변경 
				ChangeState(PlayerState::IDLE);
				return;
			}

			GetTransform()->AddLocalPosition(m_LeftRollDir.NormalizeReturn() * m_RollSpeed * _DeltaTime);
			return;
		}

		// 만약 나의 체크픽셀이 바로 BlackPixel 이라면 
		else if  (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }) || 
				  PixelCollider::g_ErrorPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
		{
			// 검은색 픽셀인 상황에서 아래 키를 누르고 있다면 크라우치 상태로 변경
			if (true == GameEngineInput::IsPress("player_crouch"))
			{
				ChangeState(PlayerState::CROUCH);
				return;
			}

			// 그게 아니라면 아이들로 변경 
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
	// 만약 플립지속시간동안 벽을 만나지 않았고, 내가 흰색픽셀이라면 
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
		// 화이트픽셀일 때 이동하고, 만약 이동한 위치가 검은픽셀이라면
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
		// 만약 체크픽셀이 검은색이라면 바로 레프트월로 변경
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
	// 이때 무조건 왼쪽으로 그려 
	m_Render->ChangeAnimation("player_flip");
	GetTransform()->SetLocalNegativeScaleX();
}

void Player::LeftFlipUpdate(float _DeltaTime)
{
	// 만약 플립지속시간동안 벽을 만나지 않았고, 내가 흰색픽셀이라면 
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
		// 화이트픽셀일 때 이동하고, 만약 이동한 위치가 검은픽셀이라면
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
		// 만약 체크픽셀이 검은색이라면 바로 레프트월로 변경
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
	// 단순하게. 내아래픽셀이 검은색이라면.
	// 나를 땅으로 올려주고 IDLE로 전환. 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 내픽셀이 흰색이라면 중력적용
	else if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom->GetTransform()->GetWorldPosition()))
	{
		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 3.3f) * _DeltaTime);
	}

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		ChangeState(PlayerState::SLASH);
		return;
	}


	// s키 누르고 있을 경우 급강하 
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

	// 점프시 우측, 좌측키를 누르고 있을때 
	if (true == GameEngineInput::IsPress("player_right_move") && false == DoorColCheck())
	{
		DirCheck();
		if (true == GameEngineInput::IsPress("player_left_move"))
		{
			return;
		}

		// 현재 나의 우측 픽셀이 흰색일 때
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// 나의 우측 디버그 픽셀의 로컬위치를 받아온다. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// 나의 NextPos 를 다음 위치로 이동시키고 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;

			// 우측 wall 픽셀이 검은색일 경우  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// 여기서 위치보정을 어떻게하지
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// 단순히 우측 픽셀만 검은색이라면 암것도 안함 
				return;
			}

			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			return;
		}

		// 우측키를 눌렀을 때 처음부터 blackpixel 이라면  
		else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
		{
			// 나의 우측 디버그 픽셀의 로컬위치를 받아온다. 
			float4 RightDebugPos = m_DebugRender_Wall_Right->GetTransform()->GetLocalPosition();

			// 나의 NextPos 를 다음 위치로 이동시키고 
			m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
			// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
			float4 CheckPos = m_NextTrans->GetWorldPosition() + RightDebugPos;

			// 우측 wall 픽셀이 검은색일 경우  
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
			{
				// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// 여기서 위치보정을 어떻게하지
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::RIGHTWALL);
					return;
				}

				// 단순히 우측 픽셀만 검은색이라면 암것도 안함 
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

		// 내 왼쪽 체크 픽셀이 흰색이 ( negative 적용으로 right 픽셀체크 ) 
		if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Right->GetTransform()->GetWorldPosition()))
		{
			// 더미를 이동시켰을 때 의 위치를 한번더 검사해서 
			m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);

			float4 CheckPos = m_NextTrans->GetLocalPosition() + float4{ -m_RenderPivot ,0.0f };
			// 그 위치가 검은색 픽셀이라면 이동하지 않고
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot , m_RenderPivot }))
			{
				// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
				if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
					PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
				{
					// 여기서 위치보정을 어떻게하지
					float4 MyPos = GetTransform()->GetLocalPosition();
					ChangeState(PlayerState::LEFTWALL);
					return;
				}

				return;
			}

			// 그게 아니라면 진짜 나의 위치를 이동해
			GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
			return;
		}
	}

	// 우측키를 눌렀을 때 처음부터 blackpixel 이라면  
	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{

		// 나의 NextPos 를 다음 위치로 이동시키고 
		m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_RenderPivot ,0.0f };

		// 우측 wall 픽셀이 검은색일 경우  
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos))
		{
			// 상,하단을 체크해서 둘다 검은색 픽셀이라면 
			if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Up) &&
				PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos + float4::Down))
			{
				// 여기서 위치보정을 어떻게하지
				float4 MyPos = GetTransform()->GetLocalPosition();
				ChangeState(PlayerState::LEFTWALL);
				return;
			}

			// 단순히 우측 픽셀만 검은색이라면 암것도 안함 
			return;
		}

		GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		return;
	}
}

void Player::FallEnd()
{
	// 착지이펙트 
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
	// 내머리위의 픽셀이 검은색이 아닐때만
	// 내가 점프키를 누르고 있는 상태라면 
	if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		if (true == GameEngineInput::IsPress("player_jump"))
		{
			if (0.0f >= m_WallPressTime)
			{
				m_WallJumpPower = 0.0f;
			}

			m_WallPressTime -= _DeltaTime;

			// 다음이동위치를 체크해서 , 다음 이동위치의 top 픽셀이 black 이 아닐 경우에만 이동하도록 
			m_NextTrans->AddWorldPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{ 0.0f,  m_RenderPivot * 2.0f }))
			{
				GetTransform()->AddLocalPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			}
		}
	}

	// 만약 내 바닥픽셀이 블랙이라면. 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 공격키 입력시
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

	// 여기서 단순하게 fall로 바꾸는게 아니라, 위치를 이동 시키고 fall로 바꾼다 
	// 내가 우측벽인 상태에서 바로 왼쪽이 벽일리가 없으니까 바로 이동시켜도 될듯 함. 
	if (true == GameEngineInput::IsDown("player_left_move"))
	{
		GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		ChangeState(PlayerState::FALL);
		return;
	}

	// 현재 나의 좌측 픽셀이 흰색일 때 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// 나의 NextPos 를 다음 위치로 이동시키고 
		m_NextTrans->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ m_WallDebugPivotX , m_WallDebugPivotY };

		// 이동한 위치의 좌측(리버스임) 디버그픽셀이 검은색이고, 이동한 위치의 나의 픽셀이 아직도 흰색이라면 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition()))
		{
			// 보다 약한 힘으로 
			GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed / 10.0f * _DeltaTime);
			GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
			return;
		}

		GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		return;
	}

	// 이미 검은색이라면 현재 왼쪽벽에 붙어있는 상태이고, 중력을받아서 아래로만 내려가면 된다. 
	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// 다음이동위치 체크 후 
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ m_WallDebugPivotX , m_WallDebugPivotY };

		// 다음 이동위치의 픽셀이 흰색이라면 fall 
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
	// 내머리위의 픽셀이 검은색이 아닐때만 
	if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_DebugRender_Top->GetTransform()->GetWorldPosition()))
	{
		if (true == GameEngineInput::IsPress("player_jump"))
		{
			if (0.0f >= m_WallPressTime)
			{
				m_WallJumpPower = 0.0f;
			}

			m_WallPressTime -= _DeltaTime;

			// 내 다음위치의 Top 이 검은색이 아닐 때만.
			// 넥스트포스 사용 해야함 
			m_NextTrans->AddWorldPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			if (PixelCollider::g_BlackPixel != PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition() + float4{0.0f,  m_RenderPivot * 2.0f}))
			{
				GetTransform()->AddLocalPosition(float4::Up * m_WallJumpPower * _DeltaTime);
			}
		}
	}
	// 만약 내 바닥픽셀이 블랙이라면. 
	if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Bottom_Down->GetTransform()->GetWorldPosition()))
	{
		PixelCollider::PixelCol->GroundCheck(this);
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 공격키 입력시
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

	// 여기서 단순하게 fall로 바꾸는게 아니라, 위치를 이동 시키고 fall로 바꾼다 
	// 내가 우측벽인 상태에서 바로 왼쪽이 벽일리가 없으니까 바로 이동시켜도 될듯 함. 
	if (true == GameEngineInput::IsDown("player_right_move"))
	{
		GetTransform()->AddLocalPosition(float4::Right * m_JumpMoveSpeed * _DeltaTime);
		ChangeState(PlayerState::FALL);
		return;
	}	

	// 현재 나의 좌측 픽셀이 흰색일 때 
	if (PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// 나의 NextPos 를 다음 위치로 이동시키고 
		m_NextTrans->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		// 이동한 위치의 우측 디버그 픽셀 위치를 체크해서 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_WallDebugPivotX , m_WallDebugPivotY };

		// 이동한 위치의 좌측(리버스임) 디버그픽셀이 검은색이고, 이동한 위치의 나의 픽셀이 아직도 흰색이라면 
		if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(CheckPos) &&
			PixelCollider::g_WhitePixel == PixelCollider::PixelCol->PixelCollision(m_NextTrans->GetWorldPosition()))
		{
			// 보다 약한 힘으로 
			GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed / 10.0f * _DeltaTime);
			GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
			return;
		}


		GetTransform()->AddLocalPosition(float4::Left * m_JumpMoveSpeed * _DeltaTime);
		GetTransform()->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime);
		return;
	}	

	// 이미 검은색이라면 현재 왼쪽벽에 붙어있는 상태이고, 중력을받아서 아래로만 내려가면 된다. 
	else if (PixelCollider::g_BlackPixel == PixelCollider::PixelCol->PixelCollision(m_DebugRender_Wall_Right->GetTransform()->GetWorldPosition()))
	{
		// 다음이동위치 체크 후 
		m_NextTrans->AddLocalPosition(float4::Down * (m_GravityPower / 6.0f) * _DeltaTime); 
		float4 CheckPos = m_NextTrans->GetWorldPosition() + float4{ -m_WallDebugPivotX , m_WallDebugPivotY };

		// 다음 이동위치의 픽셀이 흰색이라면 fall 
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
		// 애니메이션이끝나면 
		// 현재 충돌해있는 문을 가져와서 애니메이션을 변경시킨다. 
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
	// 이때 몬스터랑 충돌했다면 카메라 이펙트 호출 
	GetLevel()->GetMainCamera()->SetZoomRatio(1.00f);
}

// 일단 보류
// 너무부자연스러움 
// 죽었을때 좀 예쁘게 날아가게 바꿔야함
void Player::DeathStart()
{
	// 이때 뭐에죽었는지 구분해서 상황에 따라서 애니메이션 변경 
	m_HitPos = GetTransform()->GetLocalPosition();
	DirCheck();
	m_SoundPlayer = GameEngineSound::Play("player_die.wav");
	m_SoundPlayer.SetVolume(0.7f);
	m_Render->ChangeAnimation("player_die");
	m_Render->GetTransform()->AddLocalPosition({ 0 , -15.0f });
}

void Player::DeathUpdate(float _DeltaTime)
{
	// 개이상함 바꿔야함  
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

		// 현재 나의 좌측 픽셀이 흰색일 때 
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
		// 현재 나의 좌측 픽셀이 흰색일 때 
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

