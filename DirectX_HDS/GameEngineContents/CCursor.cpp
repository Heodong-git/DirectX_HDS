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

// ShowCursor(false); 마우스 off 
// ShowCursor(ture); 마우스 on
// 특정한 상황에서 액터 업데이트 on off 와 동시에 수행 ㄱㄱ 마우스가 보이면 actor off, 마우스가 안보이면 actor on 
// 주의점 2번 false 호출했으면 ture 두번 호출해야 보임. 이거만 유의 

void CCursor::Start()
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

	// 컴포넌트생성
	m_Renderer = CreateComponent<GameEngineRenderer>();
	// 파이프라인세팅 
	m_Renderer->SetPipeLine("2DTexture");
	m_Renderer->GetShaderResHelper().SetTexture("DiffuseTex", "cursor_0.png");
	// 리소스헬퍼 -> 사용할 상수버퍼 링크 , 상수버퍼의 OutPixelColor 컬러를 TestColor로 사용하겠다는 의미
	//Renderer->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	
	// 렌더러의 크기
	m_Renderer->GetTransform()->SetLocalScale(m_Scale);

	// 시작할땐 렌더러 오프
	//
	//m_Renderer->Off();

	// 초기색상이고, 지금 TestColor 이랑 연동되어 있으니까  
	// Update에서 x값은 +- 하면 빨간색계열로 색변동이있음
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };

	m_Renderer->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, 0.0f });
}

void CCursor::Update(float _DeltaTime)
{
	// 커서 쫓아가기 
	FollowCursor();
}

void CCursor::Render(float _DeltaTime)
{
}

void CCursor::FollowCursor()
{
	CKatanaZero_Level* Level = GetReturnCastLevel();

	// 현재 카메라 위치 가져오고. 
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 CameraMovePivot = CPlayManager::GetInst()->GetCameraPivot();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	float4 PlayerPos = CPlayManager::GetPlayer()->GetTransform()->GetLocalPosition();


	// y축 값이 0보다 크다면 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}

	// x축은 스크린 x절반 빼면 맞는거같고 
	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx(), 
							 OriginMousePos.y + GameEngineWindow::GetScreenSize().hy()};

	// ?? 왜되는데??????????????????????? 
	WorldMousePos.y += CameraMovePivot.y*2;

	GetTransform()->SetLocalPosition(WorldMousePos);

	// 단순 값 체크용 변수 
	float4 check = GetTransform()->GetLocalPosition();
}
