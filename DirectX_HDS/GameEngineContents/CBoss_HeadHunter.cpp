#include "PrecompileHeader.h"

#include "CBoss_HeadHunter.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>


CBoss_HeadHunter::CBoss_HeadHunter()
{
}

CBoss_HeadHunter::~CBoss_HeadHunter()
{
}

void CBoss_HeadHunter::Start()
{
	Render0 = CreateComponent<GameEngineRenderer>();
	// 파이프라인세팅 
	Render0->SetPipeLine("2DTexture");
	// 리소스헬퍼 -> 사용할 상수버퍼 링크 , 상수버퍼의 OutPixelColor 컬러를 TestColor로 사용하겠다는 의미
	// Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// 렌더러의 크기
	Render0->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	// 초기색상이고, 지금 TestColor 이랑 연동되어 있으니까  
	// Update에서 x값은 +- 하면 빨간색계열로 색변동이있음
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };
}

void CBoss_HeadHunter::Update(float _DeltaTime)
{
	//float4x4 Check = Render0->GetActor()->GetTransform()->GetWorldMatrixRef();
}

void CBoss_HeadHunter::Render(float _DeltaTime)
{
	
}

//HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();
//
//// 1. 버텍스와 버텍스를 저장할 POINT 배열 준비
//// 2. 한면을 구성할 점 
//float4 ArrVertex[4] = {};
//POINT ArrPoint[4] = {};
//
//ArrVertex[0] = float4{ -0.5f , -0.5f };
//ArrVertex[1] = float4{ 0.5f , -0.5f };
//ArrVertex[2] = float4{ 0.5f, 0.5f };
//ArrVertex[3] = float4{ -0.5f, 0.5f };
//
//GetTransform().SetLocalScale({ 100, 100 , 100 });
//GetTransform().AddLocalRotation({ 10 * _Delta , 0 , 10 * _Delta });
//
//GetTransform().SetCameraMatrix(GetLevel()->GetMainCamera()->GetView(), GetLevel()->GetMainCamera()->GetProjection());
//
//for (int i = 0; i < 4; ++i)
//{
//	ArrVertex[i] = ArrVertex[i] * GetTransform().GetWorldMatrixRef();
//
//	// 투영행렬의 핵심
//	ArrVertex[i] /= ArrVertex[i].w;
//	ArrVertex[i].w = 1.0f;
//
//	ArrVertex[i] *= GetLevel()->GetMainCamera()->GetViewPort();
//	//SetPixel(Dc, ArrVertex[i].x, ArrVertex[i].y, RGB(255, 0, 0));
//	ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
//}
//
//Polygon(Dc, ArrPoint, 3);