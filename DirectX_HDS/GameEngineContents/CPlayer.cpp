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

	// fsm �׽�Ʈ
	
}

void CPlayer::Update(float _DeltaTime)
{
	// �ȼ��׽�Ʈ�� �ڵ� , �ϴ� �ߴ�
	/*std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find("AAAA.png");
	GameEnginePixelColor Pixel = Ptr->GetPixel(359, 92);*/

	// ũ�γ뽺 ���� 
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

// ����׿����� ���
void CPlayer::Render(float _Delta)
{
}



// ---------------------------------------- state ------------------------------------------ 
void CPlayer::UpdateState(float _DeltaTime)
{
	// ���� ������ update ȣ�� 
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

// state ����, ����� ������ start, ���� ������ end ����
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

	// ���� state�� end 
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
	// �ӽù��� 
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
		// ���ݾִϸ��̼��� ����ƴٸ� return ���� 
		CKatanaZero_Level* CurLevel = GetReturnCastLevel();

		// ������ �� ���콺�� ��ġ�� �����´�.
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

// ����
void CPlayer::SlashStart()
{
}

void CPlayer::SlashUpdate(float _DeltaTime)
{
	//// ���ݾִϸ��̼��� ����ƴٸ� return ���� 
	//CKatanaZero_Level* CurLevel = dynamic_cast<CKatanaZero_Level*>(GetLevel());
	//if (nullptr == CurLevel)
	//{
	//	MsgAssert("Level �� dynamic_cast�� ���� �߽��ϴ�.");
	//	return;
	//}

	//// ������ �� ���콺�� ��ġ�� �����´�.
	//float4 cursorpos = CurLevel->GetCursor()->GetTransform()->GetLocalPosition();

	//// ����ġ 
	//float4 pos = GetTransform()->GetLocalPosition();
	//// �̵������� ���콺����
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

