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

void CMouse::Start()
{
	// 컴포넌트생성
	Renderer = CreateComponent<GameEngineRenderer>();
	// 파이프라인세팅 
	Renderer->SetPipeLine("2DTexture");
	// 리소스헬퍼 -> 사용할 상수버퍼 링크 , 상수버퍼의 OutPixelColor 컬러를 TestColor로 사용하겠다는 의미
	//Renderer->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// 렌더러의 크기
	Renderer->GetTransform()->SetLocalScale({ 10.0f, 10.0f , 0.0f });
	// 초기색상이고, 지금 TestColor 이랑 연동되어 있으니까  
	// Update에서 x값은 +- 하면 빨간색계열로 색변동이있음
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };

	Renderer->GetTransform()->SetLocalPosition({ 500.0f , 100.0f, 0.0f });
}

void CMouse::Update(float _DeltaTime)
{
	CKatanaZero_Level* Level = dynamic_cast<CKatanaZero_Level*>(GetLevel());
	float4 PlayerPos = Level->GetPlayer()->GetTransform()->GetWorldPosition();

	float4 MoveDir = PlayerPos - GetTransform()->GetWorldPosition();
	MoveDir.Normalize();

	GetTransform()->AddLocalPosition(MoveDir * 300.0f * _DeltaTime);
}

void CMouse::Render(float _DeltaTime)
{
}
