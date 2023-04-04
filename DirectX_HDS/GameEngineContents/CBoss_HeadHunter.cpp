#include "CBoss_HeadHunter.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>


CBoss_HeadHunter::CBoss_HeadHunter()
{
}

CBoss_HeadHunter::~CBoss_HeadHunter()
{
}

void CBoss_HeadHunter::Update(float _Delta)
{
}

void CBoss_HeadHunter::Render(float _Delta)
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