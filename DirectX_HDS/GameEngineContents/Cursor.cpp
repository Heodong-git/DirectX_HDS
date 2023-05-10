#include "PrecompileHeader.h"
#include "Cursor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "BaseLevel.h"
#include "CPlayer.h"
#include "PlayManager.h"

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

// ShowCursor(false); ���콺 off 
// ShowCursor(ture); ���콺 on
// Ư���� ��Ȳ���� ���� ������Ʈ on off �� ���ÿ� ���� ���� ���콺�� ���̸� actor off, ���콺�� �Ⱥ��̸� actor on 
// ������ 2�� false ȣ�������� ture �ι� ȣ���ؾ� ����. �̰Ÿ� ���� 

void Cursor::Start()
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

	m_Renderer = CreateComponent<GameEngineRenderer>();
	m_Renderer->SetPipeLine("2DTexture");
	m_Renderer->GetShaderResHelper().SetTexture("DiffuseTex", "cursor_0.png");
	m_Renderer->GetTransform()->SetLocalScale(m_Scale);
	m_Renderer->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, 0.0f });
}

void Cursor::Update(float _DeltaTime)
{
	FollowCursor();
}

void Cursor::Render(float _DeltaTime)
{
}

void Cursor::FollowCursor()
{
	BaseLevel* Level = GetReturnCastLevel();

	// ���� ī�޶� ��ġ ��������
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 CameraMovePivot = PlayManager::GetInst()->GetCameraPivot();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	float4 PlayerPos = PlayManager::GetPlayer()->GetTransform()->GetLocalPosition();

	// y�� ���� 0���� ũ�ٸ� 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}

	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx(), 
							 OriginMousePos.y + GameEngineWindow::GetScreenSize().hy()};

	// ?? �ֵǴµ�??????????????????????? �� 
	WorldMousePos.y += CameraMovePivot.y*2;

	GetTransform()->SetLocalPosition(WorldMousePos);

	// �ܼ� �� üũ�� ���� 
	float4 check = GetTransform()->GetLocalPosition();
}
