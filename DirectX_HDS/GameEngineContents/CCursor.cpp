#include "PrecompileHeader.h"
#include "CCursor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEngineContents/CKatanaZero_Level.h>
#include "CPlayer.h"

CCursor::CCursor()
{
}

CCursor::~CCursor()
{
}

// ShowCursor(false); ���콺 off 
// ShowCursor(ture); ���콺 on
// Ư���� ��Ȳ���� ���� ������Ʈ on off �� ���ÿ� ���� ���� ���콺�� ���̸� actor off, ���콺�� �Ⱥ��̸� actor on 
// ������ 2�� false ȣ�������� ture �ι� ȣ���ؾ� ����. �̰Ÿ� ���� 

void CCursor::Start()
{
	// ������Ʈ����
	m_Renderer = CreateComponent<GameEngineRenderer>();
	// ���������μ��� 
	m_Renderer->SetPipeLine("2DTexture");
	m_Renderer->GetShaderResHelper().SetTexture("DiffuseTex", "cursor_0.png");
	// ���ҽ����� -> ����� ������� ��ũ , ��������� OutPixelColor �÷��� TestColor�� ����ϰڴٴ� �ǹ�
	//Renderer->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	
	// �������� ũ��
	m_Renderer->GetTransform()->SetLocalScale(m_Scale);

	// �����Ҷ� ������ ����
	//
	//m_Renderer->Off();

	// �ʱ�����̰�, ���� TestColor �̶� �����Ǿ� �����ϱ�  
	// Update���� x���� +- �ϸ� �������迭�� ������������
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };

	m_Renderer->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, 0.0f });
}

void CCursor::Update(float _DeltaTime)
{
	// Ŀ�� �Ѿư��� 
	FollowCursor();
}

void CCursor::Render(float _DeltaTime)
{
}

void CCursor::FollowCursor()
{
	CKatanaZero_Level* Level = dynamic_cast<CKatanaZero_Level*>(GetLevel());
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
	
	float4 check = GetTransform()->GetLocalPosition();
}