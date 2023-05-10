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
	{
		//if (nullptr == GameEngineSprite::Find("player_idle"))
		//{
		//	GameEngineDirectory NewDir;
		//	NewDir.MoveParentToDirectory("katanazero_resources");
		//	NewDir.Move("katanazero_resources");
		//	NewDir.Move("Texture");
		//	NewDir.Move("Stage01Level");
		//	NewDir.Move("Player");

		//	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("player_idle").GetFullPath());

		//	// std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		//}
		

	}
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Player");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}


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

void Player::Update(float _DeltaTime)
{
	// �ȼ��׽�Ʈ�� �ڵ� , �ϴ� �ߴ�
	/*std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find("AAAA.png");
	GameEnginePixelColor Pixel = Ptr->GetPixel(359, 92);*/
	
	float4 CheckPos = GetTransform()->GetLocalPosition();
	GameEnginePixelColor CheckColor = GetPixelColor(CheckPos);
	if (true == IsBlackPixel(CheckColor))
	{
		GetTransform()->AddLocalPosition({ 0, +1 });
	}

	else if (IsWhitePixel(CheckColor))
	{
		// �� ������ ȭ��Ʈ��� ����ؼ� -1 , �߷�
		//Gravity(_DeltaTime);
	}

	UpdateState(_DeltaTime);
}

// ����׿����� ���
void Player::Render(float _Delta)
{
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
	case PlayerState::MOVE:
		MoveUpdate(_DeltaTime);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_DeltaTime);
		break;
	case PlayerState::SLASH:
		SlashUpdate(_DeltaTime);
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
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::JUMP:
		JumpStart();
		break;
	case PlayerState::SLASH:
		SlashStart();
		break;
	}

	// ���� state�� end 
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
	}
}

void Player::Gravity(float _DeltaTime)
{
	if (true == IsBlackPixel(GetPixelColor(GetTransform()->GetLocalPosition())))
	{
		return;
	}
	
	GetTransform()->AddLocalPosition(float4::Down * 100.0f * _DeltaTime);
}

GameEnginePixelColor Player::GetPixelColor(float4 _Pos)
{
	// �� ��ġ�� �ȼ����� �������� �� + ��ġ�� �ȼ����� �޾ƿ´�. 
	float4 CheckPos = GetTransform()->GetLocalPosition();

	// ����� �Ⱦ��°� ����. <-- �����ϰ�
	// �浹���� ���ٸ� assert 
	std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find("Club_0_ColMap.png");
	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
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
}

void Player::IdleUpdate(float _DeltaTime)
{
	// �ӽù��� 
	if (true == GameEngineInput::IsPress("player_left_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
		//GetLevel()->GetMainCamera()->GetTransform()->AddLocalPosition(float4::Left * m_MoveSpeed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("player_right_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
		//GetLevel()->GetMainCamera()->GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * _DeltaTime);
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
		//// ���ݾִϸ��̼��� ����ƴٸ� return ���� 
		//CKatanaZero_Level* CurLevel = GetReturnCastLevel();

		//// ������ �� ���콺�� ��ġ�� �����´�.
		//float4 cursorpos = CurLevel->GetCursor()->GetTransform()->GetLocalPosition();
		//GetTransform()->SetLocalPosition(cursorpos);
		//return;
	}
}

void Player::IdleEnd()
{
}

void Player::MoveStart()
{
}

void Player::MoveUpdate(float _DeltaTime)
{
}

void Player::MoveEnd()
{
}

// ����
void Player::SlashStart()
{
}

void Player::SlashUpdate(float _DeltaTime)
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

