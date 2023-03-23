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
float TestAngle = 0.0f;
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
	float Value = 0.5f;

	ArrVertex[0] = { -Value, -Value };
	ArrVertex[1] = { Value, -Value };
	ArrVertex[2] = { Value, Value };
	ArrVertex[3] = { -Value, Value };

	float Scale = 100.0f;
	POINT ArrPoint[VertexCount];

	// 회전시킬 각도
	Angle += _Delta * 100.0f;

	for (size_t i = 0; i < VertexCount; ++i)
	{
		// 회전
		ArrVertex[i] *= Scale;
		ArrVertex[i].RotaitonYDeg(Angle);
		ArrVertex[i] += Pos;

		/*int X = ArrVertex[i].ix();
		int Y = ArrVertex[i].iy();*/

		//// 버텍스 위치확인용
		//SetPixel(Dc, X, Y, RGB(255, 0, 0));
		//Rectangle(Dc, X - 20, Y - 20, X + 20, Y + 20);

		// 이동하고 
		// 저장된 위치값을 POINT로 변환하여 POINT 배열에 저장
		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	// 원하는 각도만큼 회전 시키고, 원하는 위치로 이동시키고, 그 값을 POINT 배열에 저장후
	// 연산이 완료된 위치에 Polygon 함수로 그려 지금 업데이트마다 계속그리고 있으니까 
	// 회전하는거처럼 보임
	Polygon(Dc, ArrPoint, VertexCount);

	float4 TVertex[4] = {};
	POINT TestArr[4] = {};

	TVertex[0] = { -Value, -Value };
	TVertex[1] = { Value , -Value };
	TVertex[2] = { Value, Value };
	TVertex[3] = { -Value , Value };

	// 회전속도
	TestAngle += _Delta * 360.0f;

	for (size_t i = 0; i < 4; ++i)
	{
		// 크기
		TVertex[i] *= Scale;
		// 회전
		TVertex[i].RotaitonZDeg(TestAngle);
		// 이동
		TVertex[i] += float4{ 300, 300 };

		// 포인트 배열에 저장
		TestArr[i] = TVertex[i].ToWindowPOINT();
 	}


	Polygon(Dc, TestArr, 4);
}

// 메쉬 회전시키기
// Angle * 값 <--- 회전속도
// 1. 메쉬의 버텍스 
// 2. 버텍스를 저장할 POINT 배열
// 3. 크기, 자전, 이동으로 연산 <-- 하기전에 각도를 구해줌
// 4. 포인트배열에 넣어주고 Polygon <--- 함수로 그려준다. 
// 보통 버텍스는 합 1의 크기 (0.5,0.5) 로 설정하고 * Scale 로 크기를 늘려준다. 
// 모든회사 공통은 아니지만 대부분은 그렇다. 
