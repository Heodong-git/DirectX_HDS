#include "PrecompileHeader.h"
#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineContents/CKatanaZero_Level.h>

#include "CCursor.h"
#include "CFsm.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	if (false == GameEngineInput::IsKey("attack"))
	{
		GameEngineInput::CreateKey("player_slash", VK_LBUTTON);
		// GameEngineInput::CreateKey("test", VK_RBUTTON);
		GameEngineInput::CreateKey("player_snail", VK_LSHIFT);
		GameEngineInput::CreateKey("player_left_Move", 'A');
		GameEngineInput::CreateKey("player_right_Move", 'D');
		GameEngineInput::CreateKey("player_jump", 'W');
		GameEngineInput::CreateKey("player_crouch", 'S');
	}

	m_Renderer = CreateComponent<GameEngineSpriteRenderer>();

	m_Renderer->SetPipeLine("2DTexture");
	m_Renderer->GetShaderResHelper().SetTexture("DiffuseTex", "player_idle_0.png");
	m_Renderer->GetTransform()->SetLocalScale(m_LocalScale);

	// fsm 테스트
	
}

void CPlayer::Update(float _DeltaTime)
{
	// 픽셀테스트용 코드 , 일단 잘댐
	/*std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find("AAAA.png");
	GameEnginePixelColor Pixel = Ptr->GetPixel(359, 92);*/

	// 크로노스 사용시 
	if (true == GameEngineInput::IsPress("player_snail"))
	{
		m_Snail = true;
	}
	else if (false == GameEngineInput::IsPress("player_snail"))
	{
		m_Snail = false;
	}
	
	if (true == GameEngineInput::IsDown("player_right_Move"))
	{
		// GetTransform()->SetLocalPositiveScaleX();
	}

	UpdateState(_DeltaTime);
}

// 디버그용으로 사용
void CPlayer::Render(float _Delta)
{
}



// ---------------------------------------- state ------------------------------------------ 
void CPlayer::UpdateState(float _DeltaTime)
{
	// 현재 상태의 update 호출 
	switch (m_CurState)
	{
	case PLAYERSTATE::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case PLAYERSTATE::MOVE:
		MoveUpdate(_DeltaTime);
		break;
	case PLAYERSTATE::JUMP:
		JumpUpdate(_DeltaTime);
		break;
	case PLAYERSTATE::SLASH:
		SlashUpdate(_DeltaTime);
		break;
	}
}

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void CPlayer::ChangeState(PLAYERSTATE _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	// start 
	switch (m_NextState)
	{
	case PLAYERSTATE::IDLE:
		IdleStart();
		break;
	case PLAYERSTATE::MOVE:
		MoveStart();
		break;
	case PLAYERSTATE::JUMP:
		JumpStart();
		break;
	case PLAYERSTATE::SLASH:
		SlashStart();
		break;
	}

	// 이전 state의 end 
	switch (m_PrevState)
	{
	case PLAYERSTATE::IDLE:
		IdleEnd();
		break;
	case PLAYERSTATE::MOVE:
		MoveEnd();
		break;
	case PLAYERSTATE::JUMP:
		JumpEnd();
		break;
	case PLAYERSTATE::SLASH:
		SlashEnd();
		break;
	}
}


void CPlayer::IdleStart()
{
}

void CPlayer::IdleUpdate(float _DeltaTime)
{
	// 임시무브 
	if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("player_jump"))
	{
		GetTransform()->AddLocalPosition(float4::Up * m_MoveSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("player_crouch"))
	{
		GetTransform()->AddLocalPosition(float4::Down * m_MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsDown("player_slash"))
	{
		// 공격애니메이션이 종료됐다면 return ㅇㅇ 
		CKatanaZero_Level* CurLevel = GetReturnCastLevel();

		// 눌렸을 때 마우스의 위치를 가져온다.
		float4 cursorpos = CurLevel->GetCursor()->GetTransform()->GetLocalPosition();
		GetTransform()->SetLocalPosition(cursorpos);
		return;
	}
}

void CPlayer::IdleEnd()
{
}

void CPlayer::MoveStart()
{
}

void CPlayer::MoveUpdate(float _DeltaTime)
{
}

void CPlayer::MoveEnd()
{
}

// 공격
void CPlayer::SlashStart()
{
}

void CPlayer::SlashUpdate(float _DeltaTime)
{
	//// 공격애니메이션이 종료됐다면 return ㅇㅇ 
	//CKatanaZero_Level* CurLevel = dynamic_cast<CKatanaZero_Level*>(GetLevel());
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
}

void CPlayer::SlashEnd()
{
}

void CPlayer::JumpStart()
{
}

void CPlayer::JumpUpdate(float _DeltaTime)
{
}

void CPlayer::JumpEnd()
{
}

