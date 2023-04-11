#include "PrecompileHeader.h"
#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	if (false == GameEngineInput::IsKey("PlayerMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerMoveLeft", 'A');
		GameEngineInput::CreateKey("PlayerMoveRight", 'D');
		GameEngineInput::CreateKey("PlayerMoveUp", 'Q');
		GameEngineInput::CreateKey("PlayerMoveDown", 'E');
		GameEngineInput::CreateKey("PlayerMoveForward", 'W');
		GameEngineInput::CreateKey("PlayerMoveBack", 'S');

		GameEngineInput::CreateKey("PlayerScaleY+", 'Y');
		GameEngineInput::CreateKey("PlayerScaleY-", 'U');
		GameEngineInput::CreateKey("PlayerScaleZ+", 'H');
		GameEngineInput::CreateKey("PlayerScaleZ-", 'J');
		GameEngineInput::CreateKey("PlayerScaleX+", 'N');
		GameEngineInput::CreateKey("PlayerScaleX-", 'M');


		GameEngineInput::CreateKey("PlayerRotX+", 'R');
		GameEngineInput::CreateKey("PlayerRotX-", 'T');
		GameEngineInput::CreateKey("PlayerRotY+", 'F');
		GameEngineInput::CreateKey("PlayerRotY-", 'G');
		GameEngineInput::CreateKey("PlayerRotZ+", 'V');
		GameEngineInput::CreateKey("PlayerRotZ-", 'B');
		GameEngineInput::CreateKey("PlayerSpeedBoost", VK_LSHIFT);
	}


	// ���� �������� 1�� ������ ���°� ����.
	Render0 = CreateComponent<GameEngineRenderer>();
	Render1 = CreateComponent<GameEngineRenderer>();
	Render2 = CreateComponent<GameEngineRenderer>();

	Render1->GetTransform()->DebugOn();

	Render0->GetTransform()->SetLocalPosition({ -200.0f, 0.0f, 0.0f });
	Render2->GetTransform()->SetLocalPosition({ 200.0f, 0.0f, 0.0f });
}

void CPlayer::Update(float _DeltaTime)
{
	float RotSpeed = 180.0f;

	float Speed = 200.0f;


	if (true == GameEngineInput::IsPress("PlayerSpeedBoost"))
	{
		Speed = 500.0f;
	}

	if (true == GameEngineInput::IsPress("PlayerMoveLeft"))
	{
		GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveRight"))
	{
		GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveUp"))
	{
		GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveDown"))
	{
		GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveForward"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetLocalForwardVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveBack"))
	{
		GetTransform()->AddLocalPosition(float4::Back * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("PlayerRotY+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotY-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, -RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotZ+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerRotZ-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerRotX+"))
	{
		GetTransform()->AddLocalRotation({ RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotX-"))
	{
		GetTransform()->AddLocalRotation({ -RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}

	float ScaleSpeed = 10.0f;

	if (true == GameEngineInput::IsPress("PlayerScaleY+"))
	{
		GetTransform()->AddLocalScale({ 0.0f, ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleY-"))
	{
		GetTransform()->AddLocalScale({ 0.0f, -ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleZ+"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleZ-"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, -ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleX+"))
	{
		GetTransform()->AddLocalScale({ ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleX-"))
	{
		GetTransform()->AddLocalScale({ -ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}

	Render1->GetTransform()->SetWorldRotation(float4{ 0 , 0, 0 });
	//GetTransform()->SetLocalRotation(float4{ 0 , 0, 0 });
	GameEngineTransform* ActorTrans = GetTransform();
	GameEngineTransform* CheckTrans = Render1->GetTransform();
 
	float4x4 Test = Render1->GetTransform()->GetLocalWorldMatrixRef();
	int a = 0;
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