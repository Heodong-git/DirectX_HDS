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
	// ������ â�� �׸� �� �ִ� ������ �޾ƿ´�. HDC <-- 
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	// ���� ���� 4 
	const int VertexCount = 4;

	// �׷��� ��ġ�� x ������ 640, y������ 360��ŭ �̵��� ��ġ
	float4 Pos = { 640 , 360 };
	
	// ũ��
	float4 ArrVertex[VertexCount];
	float Value = 30.0f;
	ArrVertex[0] = { -Value, -Value };
	ArrVertex[1] = { Value, -Value };
	ArrVertex[2] = { Value, Value };
	ArrVertex[3] = { -Value, Value };
	
	POINT ArrPoint[VertexCount];

	// ȸ����ų ����
	Angle += _Delta * 100.0f;

	for (size_t i = 0; i < VertexCount; ++i)
	{
		// ȸ��
		ArrVertex[i].RotaitonZDeg(Angle);
		ArrVertex[i] += Pos;

		int X = ArrVertex[i].ix();
		int Y = ArrVertex[i].iy();

		// ���ؽ� ��ġȮ�ο�
		SetPixel(Dc, X, Y, RGB(255, 0, 0));
		Rectangle(Dc, X - 20, Y - 20, X + 20, Y + 20);

		// �̵��ϰ� 
		// ����� ��ġ���� POINT�� ��ȯ�Ͽ� POINT �迭�� ����
		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	// ���ϴ� ������ŭ ȸ�� ��Ű��, ���ϴ� ��ġ�� �̵���Ű��, �� ���� POINT �迭�� ������
	// ������ �Ϸ�� ��ġ�� Polygon �Լ��� �׷� ���� ������Ʈ���� ��ӱ׸��� �����ϱ� 
	// ȸ���ϴ°�ó�� ����
	Polygon(Dc, ArrPoint, VertexCount);

	// ũ���̰���

	// ũ�⸦ Ű���
	// ȸ����Ų����
	// �̵��ϰ�
	// ������Ű��
	// �θ��� ��ȯ�� �����Ų��.
	// ������ȯ�� ����
	float4 TestVertex[4];

	TestVertex[0] = { -Value, -Value };
	TestVertex[1] = { Value, -Value };
	TestVertex[2] = { Value, Value };
	TestVertex[3] = { -Value, Value };

	POINT TestArrPoint[4];

	for (int i = 0; i < 4; ++i)
	{
		// �̵�
		TestVertex[i] += float4{ 640 , 360 };
		
		// ȸ��
		TestVertex[i].RotaitonZDeg(Angle);

		TestArrPoint[i] = TestVertex[i].ToWindowPOINT();
	}

	Polygon(Dc, TestArrPoint, 4);
}
