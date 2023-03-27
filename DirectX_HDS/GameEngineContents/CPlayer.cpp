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
		ArrVertex[i].RotationYDeg(Angle);
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
	// Polygon(Dc, ArrPoint, VertexCount);

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
		TVertex[i].RotationZDeg(TestAngle);
		// 이동
		TVertex[i] += float4{ 300, 300 };

		// 포인트 배열에 저장
		TestArr[i] = TVertex[i].ToWindowPOINT();
 	}

	Polygon(Dc, TestArr, 4);

	// 육면체 만들어보기 
	// 왜 이런식으로 화면에 보이는건지 설명할 수 있어야 한다. 
	// 메쉬는 버텍스라는 점을 이어서 만들어지게 되고. 
	// 현재 정육면체를 만들기 위해 총 24개의 버텍스가 필요하다. 점이라고 보면된다. 
	// 정면이 아닌곳에서 정육면체를 볼 경우 최대 3면까지 볼 수 있다.
	// 벡터의 외적을 활용하여 법선벡터를 구하고, 그 법선벡터의 z축의 값에 따라 3면을 그리지 않을 수 있음 
	// 물론 z축은 바깥쪽을 양수나 음수로 할지 정해야함
	// 
	{
		// 육면체는 총 24개의 점을 사용, 버텍스카운트는 24가 된다. 
		const int VertexCount = 24;

		// 육면체가 출력될 위치는 화면의 중앙보다 살짝우측
		float4 SetPos = float4{ 840 , 360 };

		float4 VertexArr[VertexCount] = {};
		POINT VertexArrP[VertexCount] = {};
		float Scale = 100.0f;
		// x y z w 
		// 정면을 기준으로 사각형처럼 보이게 완성
		VertexArr[0] = { -0.5f, -0.5f, 0.5f };
		VertexArr[1] = { 0.5f, -0.5f,0.5f };
		VertexArr[2] = { 0.5f, 0.5f,0.5f };
		VertexArr[3] = { -0.5f, 0.5f,0.5f };

		// 뒷면
		VertexArr[4] = VertexArr[0].RotationXDegReturn(180.0f);
		VertexArr[5] = VertexArr[1].RotationXDegReturn(180.0f);
		VertexArr[6] = VertexArr[2].RotationXDegReturn(180.0f);
		VertexArr[7] = VertexArr[3].RotationXDegReturn(180.0f);

		// 왼쪽
		VertexArr[8] = VertexArr[0].RotationYDegReturn(90.0f);
		VertexArr[9] = VertexArr[1].RotationYDegReturn(90.0f);
		VertexArr[10] = VertexArr[2].RotationYDegReturn(90.0f);
		VertexArr[11] = VertexArr[3].RotationYDegReturn(90.0f);
		
		// 오른쪽 
		VertexArr[12] = VertexArr[0].RotationYDegReturn(-90.0f);
		VertexArr[13] = VertexArr[1].RotationYDegReturn(-90.0f);
		VertexArr[14] = VertexArr[2].RotationYDegReturn(-90.0f);
		VertexArr[15] = VertexArr[3].RotationYDegReturn(-90.0f);

		// 아래 
		VertexArr[16] = VertexArr[0].RotationXDegReturn(90.0f);
		VertexArr[17] = VertexArr[1].RotationXDegReturn(90.0f);
		VertexArr[18] = VertexArr[2].RotationXDegReturn(90.0f);
		VertexArr[19] = VertexArr[3].RotationXDegReturn(90.0f);

		// 위
		VertexArr[20] = VertexArr[0].RotationXDegReturn(-90.0f);
		VertexArr[21] = VertexArr[1].RotationXDegReturn(-90.0f);
		VertexArr[22] = VertexArr[2].RotationXDegReturn(-90.0f);
		VertexArr[23] = VertexArr[3].RotationXDegReturn(-90.0f);

		// 이게 지금 정면에서 보이는 사각형을 만든거고 이 사각형을
		// 각각 x, y , z 축으로 회전시켜서 추가로 5개를 더 만들어주게 되면
		// 정육면체를 완성할 수 있게 된다. 
		for (size_t i = 0; i < VertexCount; i++)
		{
			VertexArr[i] *= Scale;
			VertexArr[i].RotationXDeg(Angle);
			VertexArr[i].RotationYDeg(Angle);
			VertexArr[i].RotationZDeg(Angle);
			VertexArr[i] += Pos;
			VertexArrP[i] = VertexArr[i].ToWindowPOINT();
		}
		
		// 정육면체의 면은 총 6개 , 원하는 한쪽면은 그리지 않는다. 음. 
		for (size_t i = 0; i < 6; i++)
		{
			// n번째 버텍스
			size_t Index = i * 4;

			// 현재 세개의 점만 가지고도 평면도형(삼각형) 을 만들 수 있고 
			float4 Vector0 = VertexArr[Index + 0];
			float4 Vector1 = VertexArr[Index + 1];
			float4 Vector2 = VertexArr[Index + 2];

			// 그 평면도형의 직선을 구하고 
			float4 Dir0 = Vector0 - Vector1;
			float4 Dir1 = Vector0 - Vector2;

			// 외적한 값을 반환받고. 
			// 그 값의 z 축이 0보다 크다면 그리지 않는다. 
			// 이게 지금 한면만 안그리는게 아니라 면 세개를 안그리는거구나? 
			// 안쪽 또는 바깥쪽에 있는 면을 그리지 않는거임. 
			float4 Cross = float4::CrossReturn(Dir0, Dir1);
			if (0 <= Cross.z)
			{
				continue;
			}

			Polygon(Dc, &VertexArrP[i * 4], 4);
		}
		
	}
}


// 업데이트 이전 기준
// 메쉬 회전시키기
// Angle * 값 <--- 회전속도
// 1. 메쉬의 버텍스 
// 2. 버텍스를 저장할 POINT 배열
// 3. 크기, 자전, 이동으로 연산 <-- 하기전에 각도를 구해줌
// 4. 포인트배열에 넣어주고 Polygon <--- 함수로 그려준다. 
// 보통 버텍스는 합 1의 크기 (0.5,0.5) 로 설정하고 * Scale 로 크기를 늘려준다. 
// 모든회사 공통은 아니지만 대부분은 그렇다. 
