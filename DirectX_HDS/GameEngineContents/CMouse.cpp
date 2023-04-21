#include "PrecompileHeader.h"
#include "CMouse.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEngineContents/CKatanaZero_Level.h>
#include "CPlayer.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
}

void CMouse::Start()
{
	// ������Ʈ����
	Renderer = CreateComponent<GameEngineRenderer>();
	// ���������μ��� 
	Renderer->SetPipeLine("2DTexture");
	// ���ҽ����� -> ����� ������� ��ũ , ��������� OutPixelColor �÷��� TestColor�� ����ϰڴٴ� �ǹ�
	//Renderer->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// �������� ũ��
	Renderer->GetTransform()->SetLocalScale({ 10.0f, 10.0f , 0.0f });
	// �ʱ�����̰�, ���� TestColor �̶� �����Ǿ� �����ϱ�  
	// Update���� x���� +- �ϸ� �������迭�� ������������
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };

	Renderer->GetTransform()->SetLocalPosition({ 500.0f , 100.0f, 0.0f });
}

void CMouse::Update(float _DeltaTime)
{
	CKatanaZero_Level* Level = dynamic_cast<CKatanaZero_Level*>(GetLevel());
	float4 PlayerPos = Level->GetPlayer()->GetTransform()->GetWorldPosition();

	float4 MoveDir = PlayerPos - GetTransform()->GetWorldPosition();
	MoveDir.Normalize();

	GetTransform()->AddLocalPosition(MoveDir * 300.0f * _DeltaTime);
}

void CMouse::Render(float _DeltaTime)
{
}
