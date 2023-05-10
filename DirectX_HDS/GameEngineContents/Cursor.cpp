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
		NewDir.Move("Stage01Level");
		NewDir.Move("Cursor");

		// 파일 전체로드 
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

	// 현재 카메라 위치 가져오고
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 CameraMovePivot = PlayManager::GetInst()->GetCameraPivot();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	float4 PlayerPos = PlayManager::GetPlayer()->GetTransform()->GetLocalPosition();

	// y축 값이 0보다 크다면 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}

	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx(), 
							 OriginMousePos.y + GameEngineWindow::GetScreenSize().hy()};

	// ?? 왜되는데??????????????????????? 모름 
	WorldMousePos.y += CameraMovePivot.y*2;

	GetTransform()->SetLocalPosition(WorldMousePos);

	// 단순 값 체크용 변수 
	float4 check = GetTransform()->GetLocalPosition();
}
