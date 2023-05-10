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
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Player");

		// 파일 전체로드 
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

	// fsm 테스트
	
}

void Player::Update(float _DeltaTime)
{
	// 픽셀테스트용 코드 , 일단 잘댐
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
		// 내 색상이 화이트라면 계속해서 -1 , 중력
		//Gravity(_DeltaTime);
	}

	UpdateState(_DeltaTime);
}

// 디버그용으로 사용
void Player::Render(float _Delta)
{
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
}

void Player::IdleUpdate(float _DeltaTime)
{
	// 임시무브 
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
		//// 공격애니메이션이 종료됐다면 return ㅇㅇ 
		//CKatanaZero_Level* CurLevel = GetReturnCastLevel();

		//// 눌렸을 때 마우스의 위치를 가져온다.
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

// 공격
void Player::SlashStart()
{
}

void Player::SlashUpdate(float _DeltaTime)
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

