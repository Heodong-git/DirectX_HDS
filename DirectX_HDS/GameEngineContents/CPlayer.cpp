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


	// 나는 스케일을 1로 고정해 놓는게 좋다.
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


// 업데이트 이전 기준
// 메쉬 회전시키기
// Angle * 값 <--- 회전속도
// 1. 메쉬의 버텍스 
// 2. 버텍스를 저장할 POINT 배열
// 3. 크기, 자전, 이동으로 연산 <-- 하기전에 각도를 구해줌
// 4. 포인트배열에 넣어주고 Polygon <--- 함수로 그려준다. 
// 보통 버텍스는 합 1의 크기 (0.5,0.5) 로 설정하고 * Scale 로 크기를 늘려준다. 
// 모든회사 공통은 아니지만 대부분은 그렇다




//	// 윈도우 창에 그릴 수 있는 권한을 받아온다. HDC <-- 
//HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();
//
//// 육면체 만들어보기 
//// 왜 이런식으로 화면에 보이는건지 설명할 수 있어야 한다. 
//// 메쉬는 버텍스라는 점을 이어서 만들어지게 되고. 
//// 현재 정육면체를 만들기 위해 총 24개의 버텍스가 필요하다. 점이라고 보면된다. 
//// 정면이 아닌곳에서 정육면체를 볼 경우 최대 3면까지 볼 수 있다.
//// 벡터의 외적을 활용하여 법선벡터를 구하고, 그 법선벡터의 z축의 값에 따라 3면을 그리지 않을 수 있음 
//// 물론 z축은 바깥쪽을 양수나 음수로 할지 정해야함
//{
//	// 육면체는 총 24개의 점을 사용, 버텍스카운트는 24가 된다. 
//	const int VertexCount = 24;
//
//	float4 VertexArr[VertexCount] = {};
//	POINT VertexArrP[VertexCount] = {};
//	// x y z w 
//	// 정면을 기준으로 사각형처럼 보이게 완성
//	VertexArr[0] = { -0.5f, -0.5f, 0.5f };
//	VertexArr[1] = { 0.5f, -0.5f,0.5f };
//	VertexArr[2] = { 0.5f, 0.5f,0.5f };
//	VertexArr[3] = { -0.5f, 0.5f,0.5f };
//
//	// 뒷면
//	VertexArr[4] = VertexArr[0].RotationXDegReturn(180.0f);
//	VertexArr[5] = VertexArr[1].RotationXDegReturn(180.0f);
//	VertexArr[6] = VertexArr[2].RotationXDegReturn(180.0f);
//	VertexArr[7] = VertexArr[3].RotationXDegReturn(180.0f);
//
//	// 왼쪽
//	VertexArr[8] = VertexArr[0].RotationYDegReturn(90.0f);
//	VertexArr[9] = VertexArr[1].RotationYDegReturn(90.0f);
//	VertexArr[10] = VertexArr[2].RotationYDegReturn(90.0f);
//	VertexArr[11] = VertexArr[3].RotationYDegReturn(90.0f);
//
//	// 오른쪽 
//	VertexArr[12] = VertexArr[0].RotationYDegReturn(-90.0f);
//	VertexArr[13] = VertexArr[1].RotationYDegReturn(-90.0f);
//	VertexArr[14] = VertexArr[2].RotationYDegReturn(-90.0f);
//	VertexArr[15] = VertexArr[3].RotationYDegReturn(-90.0f);
//
//	// 아래 
//	VertexArr[16] = VertexArr[0].RotationXDegReturn(90.0f);
//	VertexArr[17] = VertexArr[1].RotationXDegReturn(90.0f);
//	VertexArr[18] = VertexArr[2].RotationXDegReturn(90.0f);
//	VertexArr[19] = VertexArr[3].RotationXDegReturn(90.0f);
//
//	// 위
//	VertexArr[20] = VertexArr[0].RotationXDegReturn(-90.0f);
//	VertexArr[21] = VertexArr[1].RotationXDegReturn(-90.0f);
//	VertexArr[22] = VertexArr[2].RotationXDegReturn(-90.0f);
//	VertexArr[23] = VertexArr[3].RotationXDegReturn(-90.0f);
//
//	// 크기
//	float Check1 = VertexArr[0].w;
//	GetTransform().SetLocalScale({ 100 , 100, 100 });
//
//	// 회전
//	float Check2 = VertexArr[0].w;
//	// 카메라 매트릭스 세팅
//	// 인자로 카메라의 뷰행렬, 투영행렬 
//	GetTransform().SetCameraMatrix(GetLevel()->GetMainCamera()->GetView(), GetLevel()->GetMainCamera()->GetProjection());
//
//	for (size_t i = 0; i < VertexCount; i++)
//	{
//		// 후.. 
//		float4x4 Check3 = GetTransform().GetWorldMatrixRef();
//		VertexArr[i] = VertexArr[i] * GetTransform().GetWorldMatrixRef();
//
//		// 투영행렬의 핵심
//		// 아무튼 -1 ~ 1 사이에 쳐넣고 w는 1로, 그 후에 뷰포트행렬을 곱해서 원래크기로 만들어준다. 
//		float Check = VertexArr[i].w;
//		VertexArr[i] /= VertexArr[i].w;
//		VertexArr[i].w = 1.0f;
//		VertexArr[i] *= GetLevel()->GetMainCamera()->GetViewPort();
//
//		VertexArrP[i] = VertexArr[i].ToWindowPOINT();
//	}
//
//	// 정육면체의 면은 총 6개 , 원하는 한쪽면은 그리지 않는다. 음. 
//	for (size_t i = 0; i < 6; i++)
//	{
//		// n번째 버텍스
//		size_t Index = i * 4;
//
//		// 현재 세개의 점만 가지고도 평면도형(삼각형) 을 만들 수 있고 
//		float4 Vector0 = VertexArr[Index + 0];
//		float4 Vector1 = VertexArr[Index + 1];
//		float4 Vector2 = VertexArr[Index + 2];
//
//		// 그 평면도형의 직선을 구하고 
//		float4 Dir0 = Vector0 - Vector1;
//		float4 Dir1 = Vector0 - Vector2;
//
//		// 외적한 값을 반환받고. 
//		// 그 값의 z 축이 0보다 크다면 그리지 않는다. 
//		// 이게 지금 한면만 안그리는게 아니라 면 세개를 안그리는거구나? 
//		// 안쪽 또는 바깥쪽에 있는 면을 그리지 않는거임. 
//		float4 Cross = float4::Cross3DReturn(Dir0, Dir1);
//
//		// z축이 0보다 작다면 그리지 않음
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