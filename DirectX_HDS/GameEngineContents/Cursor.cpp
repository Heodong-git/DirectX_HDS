#include "PrecompileHeader.h"
#include "Cursor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Player.h"
#include "PlayManager.h"

Cursor* Cursor::MainCursor = nullptr;

Cursor::Cursor()
{
	MainCursor = this;
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
		NewDir.Move("ClubLevel");
		NewDir.Move("Cursor");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	if (false == GameEngineInput::IsKey("cursor_DebugSwitch"))
	{
		GameEngineInput::CreateKey("cursor_DebugSwitch", 'Q');
	}

	// ���η����� 
	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetPipeLine("2DTexture");
	m_Render->SetScaleToTexture("cursor_0.png");
	m_Render->SetAtlasConstantBuffer();
	m_Render->GetTransform()->SetLocalScale(m_Scale);

	// ������ ���߾��� ����� ������ 
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender->SetPipeLine("2DTexture");
	m_DebugRender->SetAtlasConstantBuffer();
	m_DebugRender->GetTransform()->SetLocalScale( { 2, 2 });

	// �׽�Ʈ��, ���� 2������
	m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::CURSOR));
	m_Collision->GetTransform()->SetLocalScale(m_Scale);
	
}

void Cursor::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("cursor_DebugSwitch"))
	{
		DebugSwitch();
	}

	DebugUpdate();
	FollowCursor();
}

void Cursor::Render(float _DeltaTime)
{
}

void Cursor::DebugUpdate()
{
	if (true == IsDebug())
	{
		m_DebugRender->On();
	}

	else if (false == IsDebug())
	{
		m_DebugRender->Off();
	}
}

void Cursor::FollowCursor()
{
	// ���� ī�޶� ��ġ ��������
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 CameraMovePivot = PlayManager::GetInst()->GetCameraPivot();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	// y�� ���� 0���� ũ�ٸ� 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}

	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx(),
							 OriginMousePos.y + GameEngineWindow::GetScreenSize().hy() };

	// ?? �ֵǴµ�??????????????????????? �� �ֵ� 
	WorldMousePos.y += CameraMovePivot.y * 2;

	GetTransform()->SetLocalPosition(WorldMousePos);
	m_GameCursorPos = WorldMousePos;
};
