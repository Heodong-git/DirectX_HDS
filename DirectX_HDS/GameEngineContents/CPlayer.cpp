#include "PrecompileHeader.h"
#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEngineContents/CKatanaZero_Level.h>
#include "CBoss_HeadHunter.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	// Ű����
	if (false == GameEngineInput::IsKey("Attack"))
	{
		// �� �̰� �����ΰ� ��ģ����? 
		GameEngineInput::CreateKey("Player_Attack", VK_LBUTTON);
		GameEngineInput::CreateKey("Test", VK_RBUTTON);
		GameEngineInput::CreateKey("Player_Left_Move", 'A');
		GameEngineInput::CreateKey("Player_Right_Move", 'D');
		GameEngineInput::CreateKey("Player_Jump", 'W');
		GameEngineInput::CreateKey("Player_Down_Move", 'S');
	}

	// ������Ʈ����
	Render0 = CreateComponent<GameEngineRenderer>();
	// ���������μ��� 
	Render0->SetPipeLine("2DTexture");
	// ���ҽ����� -> ����� ������� ��ũ , ��������� OutPixelColor �÷��� TestColor�� ����ϰڴٴ� �ǹ�
	Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// �������� ũ��
	Render0->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	// �ʱ�����̰�, ���� TestColor �̶� �����Ǿ� �����ϱ�  
	// Update���� x���� +- �ϸ� �������迭�� ������������
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };
}

void CPlayer::Update(float _DeltaTime)
{
	float Speed = 1000.0f;

	// �ӽù��� 
	if (true == GameEngineInput::IsPress("Player_Left_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("Player_Right_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("Player_Jump"))
	{
		GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("Player_Down_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("Player_Attack"))
	{
		// �ϴ� �̰� �´µ�. ���콺�� �Ϸ��� ���? 
		CKatanaZero_Level* Level = dynamic_cast<CKatanaZero_Level*>(GetLevel());
		float4 BossPos = Level->GetBoss()->GetTransform()->GetWorldPosition();
		
		float4 MoveDir = BossPos - GetTransform()->GetWorldPosition();
		MoveDir.Normalize();

		GetTransform()->AddLocalPosition(MoveDir * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("Test"))
	{
		// ���콺��ġ ���� ���� �׽�Ʈ��
		// ���콺�� ���ͷ� ������ �� �� ������ 
	}

}

// ����׿����� ���
void CPlayer::Render(float _Delta)
{
}
