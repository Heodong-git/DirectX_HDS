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
	// ������ â�� �׸� �� �ִ� ������ �޾ƿ´�. HDC <-- 
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	// ���� ���� 4 
	const int VertexCount = 4;

	// �׷��� ��ġ�� x ������ 640, y������ 360��ŭ �̵��� ��ġ
	float4 Pos = { 640 , 360 };

	// ũ��
	float4 ArrVertex[VertexCount];
	float Value = 0.5f;

	ArrVertex[0] = { -Value, -Value };
	ArrVertex[1] = { Value, -Value };
	ArrVertex[2] = { Value, Value };
	ArrVertex[3] = { -Value, Value };

	float Scale = 100.0f;
	POINT ArrPoint[VertexCount];

	// ȸ����ų ����
	Angle += _Delta * 100.0f;

	for (size_t i = 0; i < VertexCount; ++i)
	{
		// ȸ��
		ArrVertex[i] *= Scale;
		ArrVertex[i].RotaitonYDeg(Angle);
		ArrVertex[i] += Pos;

		/*int X = ArrVertex[i].ix();
		int Y = ArrVertex[i].iy();*/

		//// ���ؽ� ��ġȮ�ο�
		//SetPixel(Dc, X, Y, RGB(255, 0, 0));
		//Rectangle(Dc, X - 20, Y - 20, X + 20, Y + 20);

		// �̵��ϰ� 
		// ����� ��ġ���� POINT�� ��ȯ�Ͽ� POINT �迭�� ����
		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	// ���ϴ� ������ŭ ȸ�� ��Ű��, ���ϴ� ��ġ�� �̵���Ű��, �� ���� POINT �迭�� ������
	// ������ �Ϸ�� ��ġ�� Polygon �Լ��� �׷� ���� ������Ʈ���� ��ӱ׸��� �����ϱ� 
	// ȸ���ϴ°�ó�� ����
	Polygon(Dc, ArrPoint, VertexCount);

	float4 TVertex[4] = {};
	POINT TestArr[4] = {};

	TVertex[0] = { -Value, -Value };
	TVertex[1] = { Value , -Value };
	TVertex[2] = { Value, Value };
	TVertex[3] = { -Value , Value };

	// ȸ���ӵ�
	TestAngle += _Delta * 360.0f;

	for (size_t i = 0; i < 4; ++i)
	{
		// ũ��
		TVertex[i] *= Scale;
		// ȸ��
		TVertex[i].RotaitonZDeg(TestAngle);
		// �̵�
		TVertex[i] += float4{ 300, 300 };

		// ����Ʈ �迭�� ����
		TestArr[i] = TVertex[i].ToWindowPOINT();
 	}


	Polygon(Dc, TestArr, 4);
}

// �޽� ȸ����Ű��
// Angle * �� <--- ȸ���ӵ�
// 1. �޽��� ���ؽ� 
// 2. ���ؽ��� ������ POINT �迭
// 3. ũ��, ����, �̵����� ���� <-- �ϱ����� ������ ������
// 4. ����Ʈ�迭�� �־��ְ� Polygon <--- �Լ��� �׷��ش�. 
// ���� ���ؽ��� �� 1�� ũ�� (0.5,0.5) �� �����ϰ� * Scale �� ũ�⸦ �÷��ش�. 
// ���ȸ�� ������ �ƴ����� ��κ��� �׷���. 
