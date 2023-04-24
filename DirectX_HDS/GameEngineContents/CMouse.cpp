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

// ShowCursor(false); 마우스 off 
// ShowCursor(ture); 마우스 on
// 특정한 상황에서 액터 업데이트 on off 와 동시에 수행 ㄱㄱ 마우스가 보이면 actor off, 마우스가 안보이면 actor on 
// 주의점 2번 false 호출했으면 ture 두번 호출해야 보임. 이거만 유의 

void CMouse::Start()
{
	// 컴포넌트생성
	Renderer = CreateComponent<GameEngineRenderer>();
	// 파이프라인세팅 
	Renderer->SetPipeLine("2DTexture");
	// 리소스헬퍼 -> 사용할 상수버퍼 링크 , 상수버퍼의 OutPixelColor 컬러를 TestColor로 사용하겠다는 의미
	//Renderer->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// 렌더러의 크기
	Renderer->GetTransform()->SetLocalScale({ 50.0f, 50.0f , 0.0f });
	// 초기색상이고, 지금 TestColor 이랑 연동되어 있으니까  
	// Update에서 x값은 +- 하면 빨간색계열로 색변동이있음
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };

	Renderer->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, 0.0f });
}

void CMouse::Update(float _DeltaTime)
{
	CKatanaZero_Level* Level = dynamic_cast<CKatanaZero_Level*>(GetLevel());
	float4 PlayerPos = Level->GetPlayer()->GetTransform()->GetWorldPosition();

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 OriginMousePos = GameEngineWindow::GetMousePosition() + CameraPos;

	// y축 값이 0보다 크다면 
	if (0.0f < OriginMousePos.y)
	{
		OriginMousePos.y = -OriginMousePos.y;
	}
	// x축은 스크린 x절반 빼면 맞는거같고 
	float4 WorldMousePos = { OriginMousePos.x - GameEngineWindow::GetScreenSize().hx() ,
					   OriginMousePos.y + GameEngineWindow::GetScreenSize().hy() };

	GetTransform()->SetLocalPosition(WorldMousePos);
}

void CMouse::Render(float _DeltaTime)
{
}
