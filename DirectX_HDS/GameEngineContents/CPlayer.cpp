#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineRenderer.h>

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	
}

void CPlayer::Update(float _Delta)
{
}

void CPlayer::Render(float _Delta)
{

}


// ������Ʈ ���� ����
// �޽� ȸ����Ű��
// Angle * �� <--- ȸ���ӵ�
// 1. �޽��� ���ؽ� 
// 2. ���ؽ��� ������ POINT �迭
// 3. ũ��, ����, �̵����� ���� <-- �ϱ����� ������ ������
// 4. ����Ʈ�迭�� �־��ְ� Polygon <--- �Լ��� �׷��ش�. 
// ���� ���ؽ��� �� 1�� ũ�� (0.5,0.5) �� �����ϰ� * Scale �� ũ�⸦ �÷��ش�. 
// ���ȸ�� ������ �ƴ����� ��κ��� �׷���




//	// ������ â�� �׸� �� �ִ� ������ �޾ƿ´�. HDC <-- 
//HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();
//
//// ����ü ������ 
//// �� �̷������� ȭ�鿡 ���̴°��� ������ �� �־�� �Ѵ�. 
//// �޽��� ���ؽ���� ���� �̾ ��������� �ǰ�. 
//// ���� ������ü�� ����� ���� �� 24���� ���ؽ��� �ʿ��ϴ�. ���̶�� ����ȴ�. 
//// ������ �ƴѰ����� ������ü�� �� ��� �ִ� 3����� �� �� �ִ�.
//// ������ ������ Ȱ���Ͽ� �������͸� ���ϰ�, �� ���������� z���� ���� ���� 3���� �׸��� ���� �� ���� 
//// ���� z���� �ٱ����� ����� ������ ���� ���ؾ���
//{
//	// ����ü�� �� 24���� ���� ���, ���ؽ�ī��Ʈ�� 24�� �ȴ�. 
//	const int VertexCount = 24;
//
//	float4 VertexArr[VertexCount] = {};
//	POINT VertexArrP[VertexCount] = {};
//	// x y z w 
//	// ������ �������� �簢��ó�� ���̰� �ϼ�
//	VertexArr[0] = { -0.5f, -0.5f, 0.5f };
//	VertexArr[1] = { 0.5f, -0.5f,0.5f };
//	VertexArr[2] = { 0.5f, 0.5f,0.5f };
//	VertexArr[3] = { -0.5f, 0.5f,0.5f };
//
//	// �޸�
//	VertexArr[4] = VertexArr[0].RotationXDegReturn(180.0f);
//	VertexArr[5] = VertexArr[1].RotationXDegReturn(180.0f);
//	VertexArr[6] = VertexArr[2].RotationXDegReturn(180.0f);
//	VertexArr[7] = VertexArr[3].RotationXDegReturn(180.0f);
//
//	// ����
//	VertexArr[8] = VertexArr[0].RotationYDegReturn(90.0f);
//	VertexArr[9] = VertexArr[1].RotationYDegReturn(90.0f);
//	VertexArr[10] = VertexArr[2].RotationYDegReturn(90.0f);
//	VertexArr[11] = VertexArr[3].RotationYDegReturn(90.0f);
//
//	// ������ 
//	VertexArr[12] = VertexArr[0].RotationYDegReturn(-90.0f);
//	VertexArr[13] = VertexArr[1].RotationYDegReturn(-90.0f);
//	VertexArr[14] = VertexArr[2].RotationYDegReturn(-90.0f);
//	VertexArr[15] = VertexArr[3].RotationYDegReturn(-90.0f);
//
//	// �Ʒ� 
//	VertexArr[16] = VertexArr[0].RotationXDegReturn(90.0f);
//	VertexArr[17] = VertexArr[1].RotationXDegReturn(90.0f);
//	VertexArr[18] = VertexArr[2].RotationXDegReturn(90.0f);
//	VertexArr[19] = VertexArr[3].RotationXDegReturn(90.0f);
//
//	// ��
//	VertexArr[20] = VertexArr[0].RotationXDegReturn(-90.0f);
//	VertexArr[21] = VertexArr[1].RotationXDegReturn(-90.0f);
//	VertexArr[22] = VertexArr[2].RotationXDegReturn(-90.0f);
//	VertexArr[23] = VertexArr[3].RotationXDegReturn(-90.0f);
//
//	// ũ��
//	float Check1 = VertexArr[0].w;
//	GetTransform().SetLocalScale({ 100 , 100, 100 });
//
//	// ȸ��
//	float Check2 = VertexArr[0].w;
//	// ī�޶� ��Ʈ���� ����
//	// ���ڷ� ī�޶��� �����, ������� 
//	GetTransform().SetCameraMatrix(GetLevel()->GetMainCamera()->GetView(), GetLevel()->GetMainCamera()->GetProjection());
//
//	for (size_t i = 0; i < VertexCount; i++)
//	{
//		// ��.. 
//		float4x4 Check3 = GetTransform().GetWorldMatrixRef();
//		VertexArr[i] = VertexArr[i] * GetTransform().GetWorldMatrixRef();
//
//		// ��������� �ٽ�
//		// �ƹ�ư -1 ~ 1 ���̿� �ĳְ� w�� 1��, �� �Ŀ� ����Ʈ����� ���ؼ� ����ũ��� ������ش�. 
//		float Check = VertexArr[i].w;
//		VertexArr[i] /= VertexArr[i].w;
//		VertexArr[i].w = 1.0f;
//		VertexArr[i] *= GetLevel()->GetMainCamera()->GetViewPort();
//
//		VertexArrP[i] = VertexArr[i].ToWindowPOINT();
//	}
//
//	// ������ü�� ���� �� 6�� , ���ϴ� ���ʸ��� �׸��� �ʴ´�. ��. 
//	for (size_t i = 0; i < 6; i++)
//	{
//		// n��° ���ؽ�
//		size_t Index = i * 4;
//
//		// ���� ������ ���� ������ ��鵵��(�ﰢ��) �� ���� �� �ְ� 
//		float4 Vector0 = VertexArr[Index + 0];
//		float4 Vector1 = VertexArr[Index + 1];
//		float4 Vector2 = VertexArr[Index + 2];
//
//		// �� ��鵵���� ������ ���ϰ� 
//		float4 Dir0 = Vector0 - Vector1;
//		float4 Dir1 = Vector0 - Vector2;
//
//		// ������ ���� ��ȯ�ް�. 
//		// �� ���� z ���� 0���� ũ�ٸ� �׸��� �ʴ´�. 
//		// �̰� ���� �Ѹ鸸 �ȱ׸��°� �ƴ϶� �� ������ �ȱ׸��°ű���? 
//		// ���� �Ǵ� �ٱ��ʿ� �ִ� ���� �׸��� �ʴ°���. 
//		float4 Cross = float4::Cross3DReturn(Dir0, Dir1);
//
//		// z���� 0���� �۴ٸ� �׸��� ����
//		if (0 >= Cross.z)
//		{
//			continue;
//		}
//
//		Polygon(Dc, &VertexArrP[i * 4], 4);
//	}
//}
//
//float4x4 Test = GetTransform().GetWorldMatrixRef();