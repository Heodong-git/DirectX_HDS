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

#include "BaseLevel.h"
#include "Cursor.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
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
			GameEngineSprite::LoadFolder(Dir.GetPlusFileName("player_crouch").GetFullPath());

			std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
		}
	}
	
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

	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetPipeLine("2DTexture");
	m_Render->GetTransform()->SetLocalScale(m_LocalScale);
	m_Render->GetTransform()->SetLocalPosition({ 0, m_LocalScale.y / 2 });


	// 디버그 렌더러0
	// 플레이어 위치 그대로 출력 
	float4 PlayerPos = GetTransform()->GetLocalPosition();
	m_DebugRender0 = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender0->SetPipeLine("2DTexture");
	m_DebugRender0->GetTransform()->SetLocalScale({ 3  , 3 });
	//m_DebugRender0->GetTransform()->SetLocalPosition({ 0, PlayerPos.y - 36.0f });
	m_DebugRender0->Off();

	// 애니메이션 생성
	CreateAnimation();
}

void Player::Update(float _DeltaTime)
{
	DirCheck();
	UpdateState(_DeltaTime);
	DebugUpdate();
}

void Player::Render(float _DeltaTime)
{
}

void Player::CreateAnimation()
{
	m_Render->CreateAnimation("player_idle", "player_idle", 0.1f, 0, 10, true, true);
	m_Render->CreateAnimation("player_attack", "player_attack", 0.1f, 0, 6, false, true);
	m_Render->CreateAnimation("player_idle_to_run", "player_idle_to_run", 0.1f, 0, 3, true, true);
	m_Render->CreateAnimation("player_run", "player_run", 0.05f, 0, 9 , true , true);
	m_Render->CreateAnimation("player_crouch", "player_crouch", 0.01f , 0, 0 , false , true);
	m_Render->GetTransform()->SetLocalScale(m_LocalScale);
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
	if (true == m_IsDebug)
	{
		m_DebugRender0->On();
	}

	else if (false == m_IsDebug)
	{
		m_DebugRender0->Off();
	}
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
	}
}



// 보류
GameEnginePixelColor Player::GetPixelColor(float4 _Pos)
{
	// 내 위치의 픽셀값을 기준으로 한 + 위치의 픽셀값을 받아온다. 
	float4 CheckPos = GetTransform()->GetLocalPosition();

	// 상수는 안쓰는게 좋다. <-- 인지하고
	// 충돌맵이 없다면 assert 
	std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find("Club_0_ColMap.png");
	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
		return GameEnginePixelColor{ 0 , 0 , 0 , 0 };
	}

	float WidthHalf = static_cast<float>(ColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(ColMap->GetHeight() / 2);

	CheckPos += { WidthHalf , HeightHalf };

	GameEnginePixelColor Color = ColMap->GetPixel(static_cast<int>(CheckPos.x),static_cast<int>(CheckPos.y));

	return Color;
}

void Player::IdleStart()
{
	m_Render->ChangeAnimation("player_idle");
}

void Player::IdleUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("player_debugswitch"))
	{
		DebugSwitch();
	}

	if (true == GameEngineInput::IsDown("player_crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	// 임시무브 
	if (true == GameEngineInput::IsDown("player_right_move"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}
	else if (true == GameEngineInput::IsDown("player_left_move"))
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
}

void Player::SlashUpdate(float _DeltaTime)
{
	//// 공격애니메이션이 종료됐다면 return ㅇㅇ 
	//BaseLevel* CurLevel = dynamic_cast<BaseLevel*>(GetLevel());
	//if (nullptr == CurLevel)
	//{
	//	MsgAssert("Level 의 dynamic_cast에 실패 했습니다.");
	//	return;
	//}

	//// 눌렸을 때 마우스의 위치를 가져온다.
	//float4 cursorpos = CurLevel->GetCursor()->GetTransform()->GetLocalPosition();

	//// 내위치 
	//float4 pos = GetTransform()->GetLocalPosition();
	//// 이동방향은 마우스방향
	//float4 movedir = cursorpos - pos;
	//movedir.Normalize();
	////movedir *= m_SlashMoveRange;

	//GetTransform()->AddLocalPosition(movedir * m_MoveSpeed * _DeltaTime);

	if (true == m_Render->FindAnimation("player_attack")->IsEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}

void Player::SlashEnd()
{
}

void Player::JumpStart()
{
}

void Player::JumpUpdate(float _DeltaTime)
{
}

void Player::JumpEnd()
{
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
}

void Player::CrouchEnd()
{
}

