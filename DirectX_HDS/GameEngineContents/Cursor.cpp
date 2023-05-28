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

// ShowCursor(false); 마우스 off 
// ShowCursor(ture); 마우스 on
// 특정한 상황에서 액터 업데이트 on off 와 동시에 수행 ㄱㄱ 마우스가 보이면 actor off, 마우스가 안보이면 actor on 
// 주의점 2번 false 호출했으면 ture 두번 호출해야 보임. 이거만 유의 

void Cursor::Start()
{
	{
		if (nullptr == GameEngineTexture::Find("Cursor_0.png"))
		{
			GameEngineDirectory NewDir;
			// 원하는 폴더를 가진 디렉터리로 이동
			NewDir.MoveParentToDirectory("katanazero_resources");
			// 그 폴더로 이동
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("Cursor");

			// 파일 전체로드 
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

	
	// 메인렌더러 
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::CURSOR);
	m_Render->SetScaleToTexture("cursor_0.png");
	m_Render->GetTransform()->SetLocalScale(m_Scale);
	m_Render->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -1.0f });

	// 렌더러 정중앙의 디버그 렌더러 
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

	// 플레이어가 데스상태고, 레벨이 대기상태일때만 작동
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
	
	// 현재 카메라 위치 가져오고
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	// y축 값이 0보다 크다면 
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

	// ?? 왜되는데??????????????????????? 모름 왜돼 어쨌든 되니까 그냥 사용 
	WorldMousePos.y += CameraPos.y * 2;

	GetTransform()->SetLocalPosition(WorldMousePos);
	m_GameCursorPos = WorldMousePos;
};
