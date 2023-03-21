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
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	const int VertexCount = 4;

	float4 Pos = { 640, 360 };

	float4 ArrVertex[VertexCount];
	ArrVertex[0] = { -50, -50 };
	ArrVertex[1] = { 50, -50 };
	ArrVertex[2] = { 50, 50 };
	ArrVertex[3] = { -50, 50 };

	POINT ArrPoint[VertexCount];

	Angle += _Delta * 360.0f;

	// ũ���̰���

	// ũ�⸦ Ű���
	// ȸ����Ų����
	// �̵��ϰ�
	// ������Ű��
	// �θ��� ��ȯ�� �����Ų��.
	// ������ȯ�� ����.

	for (size_t i = 0; i < VertexCount; i++)
	{
		ArrVertex[i].RotaitonZDeg(Angle);
		ArrVertex[i] += Pos;


		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	Polygon(Dc, ArrPoint, VertexCount);
}
