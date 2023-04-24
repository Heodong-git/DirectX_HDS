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

// ShowCursor(false); ���콺 off 
// ShowCursor(ture); ���콺 on
// Ư���� ��Ȳ���� ���� ������Ʈ on off �� ���ÿ� ���� ���� ���콺�� ���̸� actor off, ���콺�� �Ⱥ��̸� actor on 
// ������ 2�� false ȣ�������� ture �ι� ȣ���ؾ� ����. �̰Ÿ� ���� 

void CMouse::Start()
{
	// ������Ʈ����
	Renderer = CreateComponent<GameEngineRenderer>();
	// ���������μ��� 
	Renderer->SetPipeLine("2DTexture");
	// ���ҽ����� -> ����� ������� ��ũ , ��������� OutPixelColor �÷��� TestColor�� ����ϰڴٴ� �ǹ�
	//Renderer->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// �������� ũ��
	Renderer->GetTransform()->SetLocalScale({ 50.0f, 50.0f , 0.0f });
	// �ʱ�����̰�, ���� TestColor �̶� �����Ǿ� �����ϱ�  
	// Update���� x���� +- �ϸ� �������迭�� ������������
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };

	Renderer->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, 0.0f });
}

void CMouse::Update(float _DeltaTime)
{
	CKatanaZero_Level* Level = dynamic_cast<CKatanaZero_Level*>(GetLevel());
	float4 PlayerPos = Level->GetPlayer()->GetTransform()->GetWorldPosition();

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	// y�� ���� 0���� ũ�ٸ� 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}
	// x���� ��ũ�� x���� ���� �´°Ű��� 
	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx() ,
					   OriginMousePos.y + GameEngineWindow::GetScreenSize().hy() };

	GetTransform()->SetLocalPosition(WorldMousePos);
}

void CMouse::Render(float _DeltaTime)
{
}
