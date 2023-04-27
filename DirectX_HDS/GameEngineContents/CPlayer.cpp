#include "PrecompileHeader.h"
#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineContents/CKatanaZero_Level.h>

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
		GameEngineInput::CreateKey("player_attack", VK_LBUTTON);
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

	// ���ҽ����� -> ����� ������� ��ũ , ��������� OutPixelColor �÷��� TestColor�� ����ϰڴٴ� �ǹ�
	// Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// �ʱ�����̰�, ���� TestColor �̶� �����Ǿ� �����ϱ�  
	// Update���� x���� +- �ϸ� �������迭�� ������������
	// TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };
}

void CPlayer::Update(float _DeltaTime)
{
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

	if (true == GameEngineInput::IsDown("player_attack"))
	{
		
	}

	if (5.0f <= m_Renderer->GetLiveTime())
	{
		m_Renderer->Off();
	}
}

// ����׿����� ���
void CPlayer::Render(float _Delta)
{
}
