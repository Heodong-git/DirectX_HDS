#include "PrecompileHeader.h"
#include "Cursor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>

#include "BaseLevel.h"
#include "Player.h"
#include "CameraSetter.h"

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
		if (nullptr == GameEngineTexture::Find("Cursor_0.png"))
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
		
	}

	if (false == GameEngineInput::IsKey("cursor_DebugSwitch"))
	{
		GameEngineInput::CreateKey("cursor_DebugSwitch", 'Q');
		GameEngineInput::CreateKey("cursor_leftclick", VK_LBUTTON);
	}

	
	// ���η����� 
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::CURSOR);
	m_Render->SetScaleToTexture("cursor_0.png");
	m_Render->GetTransform()->SetLocalScale(m_Scale);
	m_Render->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -1.0f });

	// ������ ���߾��� ����� ������ 
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender->GetTransform()->SetLocalScale( { 2, 2 });
}

void Cursor::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("cursor_DebugSwitch"))
	{
		DebugSwitch();
	}

	DebugUpdate();
	FollowCursor();

	// �÷��̾ �������°�, ������ �������϶��� �۵�
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState() && PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		if (true == GameEngineInput::IsDown("cursor_leftclick"))
		{
			if (nullptr == m_Collision)
			{
				m_Collision = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::CURSOR));
				m_Collision->GetTransform()->SetLocalPosition(GetReturnCastLevel()->GetMainCamera()->GetTransform()->GetLocalPosition());
				m_Collision->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
			}
			
			else if (nullptr != m_Collision)
			{
				m_Collision->On();
			}
		}
	}
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
	GameEngineLevel* Level = GameEngineCore::GetCurLevel().get();
	BaseLevel* CurLevel = dynamic_cast<BaseLevel*>(Level);
	LevelType CurLevelType = CurLevel->GetLevelType();

	if (nullptr == Level->GetMainCamera())
	{
		return;
	}
	
	// ���� ī�޶� ��ġ ��������
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	// y�� ���� 0���� ũ�ٸ� 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}

	else if (0.0f > OriginMousePos.y)
	{
		OriginMousePos.y = abs(OriginMousePos.y);
	}

	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx(),
							 OriginMousePos.y + GameEngineWindow::GetScreenSize().hy() };

	// ?? �ֵǴµ�??????????????????????? �� �ֵ� ��·�� �Ǵϱ� �׳� ��� 
	WorldMousePos.y += CameraPos.y * 2;

	GetTransform()->SetLocalPosition(WorldMousePos);
	m_GameCursorPos = WorldMousePos;
};
