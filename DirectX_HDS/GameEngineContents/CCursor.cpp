#include "PrecompileHeader.h"
#include "CCursor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEngineContents/CKatanaZero_Level.h>
#include "CPlayer.h"
#include "CPlayManager.h"

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
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Cursor");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

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
	CKatanaZero_Level* Level = GetReturnCastLevel();

	// ���� ī�޶� ��ġ ��������. 
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 CameraMovePivot = CPlayManager::GetInst()->GetCameraPivot();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	float4 PlayerPos = CPlayManager::GetPlayer()->GetTransform()->GetLocalPosition();


	// y�� ���� 0���� ũ�ٸ� 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}

	// x���� ��ũ�� x���� ���� �´°Ű��� 
	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx(), 
							 OriginMousePos.y + GameEngineWindow::GetScreenSize().hy()};

	// ?? �ֵǴµ�??????????????????????? 
	WorldMousePos.y += CameraMovePivot.y*2;

	GetTransform()->SetLocalPosition(WorldMousePos);

	// �ܼ� �� üũ�� ���� 
	float4 check = GetTransform()->GetLocalPosition();
}
