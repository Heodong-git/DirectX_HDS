#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(float _Delta)
{
}

float Angle = 0.0f;
void CPlayer::Render(float _Delta)
{
	// 윈도우 창에 그릴 수 있는 권한을 받아온다. HDC <-- 
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	// 점의 개수 4 
	const int VertexCount = 4;

	// 그려질 위치는 x 축으로 640, y축으로 360만큼 이동한 위치
	float4 Pos = { 640 , 360 };
	
	// 크기
	float4 ArrVertex[VertexCount];
	float Value = 30.0f;
	ArrVertex[0] = { -Value, -Value };
	ArrVertex[1] = { Value, -Value };
	ArrVertex[2] = { Value, Value };
	ArrVertex[3] = { -Value, Value };
	
	POINT ArrPoint[VertexCount];

	// 회전시킬 각도
	Angle += _Delta * 100.0f;

	for (size_t i = 0; i < VertexCount; ++i)
	{
		// 회전
		ArrVertex[i].RotaitonZDeg(Angle);
		ArrVertex[i] += Pos;

		int X = ArrVertex[i].ix();
		int Y = ArrVertex[i].iy();

		// 버텍스 위치확인용
		SetPixel(Dc, X, Y, RGB(255, 0, 0));
		Rectangle(Dc, X - 20, Y - 20, X + 20, Y + 20);

		// 이동하고 
		// 저장된 위치값을 POINT로 변환하여 POINT 배열에 저장
		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	// 원하는 각도만큼 회전 시키고, 원하는 위치로 이동시키고, 그 값을 POINT 배열에 저장후
	// 연산이 완료된 위치에 Polygon 함수로 그려 지금 업데이트마다 계속그리고 있으니까 
	// 회전하는거처럼 보임
	Polygon(Dc, ArrPoint, VertexCount);

	// 크자이공부

	// 크기를 키우고
	// 회전시킨다음
	// 이동하고
	// 공전시키고
	// 부모의 변환을 적용시킨다.
	// 공간변환의 순서
	float4 TestVertex[4];

	TestVertex[0] = { -Value, -Value };
	TestVertex[1] = { Value, -Value };
	TestVertex[2] = { Value, Value };
	TestVertex[3] = { -Value, Value };

	POINT TestArrPoint[4];

	for (int i = 0; i < 4; ++i)
	{
		// 이동
		TestVertex[i] += float4{ 640 , 360 };
		
		// 회전
		TestVertex[i].RotaitonZDeg(Angle);

		TestArrPoint[i] = TestVertex[i].ToWindowPOINT();
	}

	Polygon(Dc, TestArrPoint, 4);
}
