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

// ShowCursor(false); 마우스 off 
// ShowCursor(ture); 마우스 on
// 특정한 상황에서 액터 업데이트 on off 와 동시에 수행 ㄱㄱ 마우스가 보이면 actor off, 마우스가 안보이면 actor on 
// 주의점 2번 false 호출했으면 ture 두번 호출해야 보임. 이거만 유의 

void Cursor::Start()
{
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

	if (false == GameEngineInput::IsKey("cursor_DebugSwitch"))
	{
		GameEngineInput::CreateKey("cursor_DebugSwitch", 'Q');
	}

	// 메인렌더러 
	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetPipeLine("2DTexture");
	m_Render->SetScaleToTexture("cursor_0.png");
	m_Render->SetAtlasConstantBuffer();
	m_Render->GetTransform()->SetLocalScale(m_Scale);

	// 렌더러 정중앙의 디버그 렌더러 
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRender->SetPipeLine("2DTexture");
	m_DebugRender->SetAtlasConstantBuffer();
	m_DebugRender->GetTransform()->SetLocalScale( { 2, 2 });

	// 테스트용, 오더 2번지정
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
	// 현재 카메라 위치 가져오고
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 CameraMovePivot = PlayManager::GetInst()->GetCameraPivot();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	// y축 값이 0보다 크다면 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}

	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx(),
							 OriginMousePos.y + GameEngineWindow::GetScreenSize().hy() };

	// ?? 왜되는데??????????????????????? 모름 왜돼 
	WorldMousePos.y += CameraMovePivot.y * 2;

	GetTransform()->SetLocalPosition(WorldMousePos);
	m_GameCursorPos = WorldMousePos;
};
