#include "GameEngineCamera.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
}


void GameEngineCamera::Start()
{
	if (false == GameEngineInput::IsKey("CamMoveLeft"))
	{
		GameEngineInput::CreateKey("CamMoveLeft", 'A');
		GameEngineInput::CreateKey("CamMoveRight", 'D');
		GameEngineInput::CreateKey("CamMoveUp", 'Q');
		GameEngineInput::CreateKey("CamMoveDown", 'E');
		GameEngineInput::CreateKey("CamMoveForward", 'W');
		GameEngineInput::CreateKey("CamMoveBack", 'S');

		GameEngineInput::CreateKey("RotX+", 'U');
		GameEngineInput::CreateKey("RotX-", 'I');
		GameEngineInput::CreateKey("RotY+", 'J');
		GameEngineInput::CreateKey("RotY-", 'K');
		GameEngineInput::CreateKey("RotZ+", 'N');
		GameEngineInput::CreateKey("RotZ-", 'M');

		GameEngineInput::CreateKey("SpeedBoost", VK_LSHIFT);
		GameEngineInput::CreateKey("FreeCameraSwitch", 'P');
	}
}

void GameEngineCamera::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("FreeCameraSwitch"))
	{
		FreeCamera = !FreeCamera;
	}

	if (true == FreeCamera)
	{
		float Speed = 200.0f;
		float RotSpeed = 180.0f;

		if (true == GameEngineInput::IsPress("SpeedBoost"))
		{
			Speed = 500.0f;
		}

		if (true == GameEngineInput::IsPress("CamMoveLeft"))
		{
			GetTransform().AddLocalPosition(float4::Left * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveRight"))
		{
			GetTransform().AddLocalPosition(float4::Right * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveUp"))
		{
			GetTransform().AddLocalPosition(float4::Up * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveDown"))
		{
			GetTransform().AddLocalPosition(float4::Down * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveForward"))
		{
			GetTransform().AddLocalPosition(float4::Forward * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveBack"))
		{
			GetTransform().AddLocalPosition(float4::Back * Speed * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("RotY+"))
		{
			GetTransform().AddLocalRotation({ 0.0f, RotSpeed * _DeltaTime, 0.0f });
		}
		if (true == GameEngineInput::IsPress("RotY-"))
		{
			GetTransform().AddLocalRotation({ 0.0f, -RotSpeed * _DeltaTime, 0.0f });
		}
		if (true == GameEngineInput::IsPress("RotZ+"))
		{
			GetTransform().AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _DeltaTime });
		}
		if (true == GameEngineInput::IsPress("RotZ-"))
		{
			GetTransform().AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _DeltaTime });
		}
		if (true == GameEngineInput::IsPress("RotX+"))
		{
			GetTransform().AddLocalRotation({ RotSpeed * _DeltaTime, 0.0f, 0.0f });
		}
		if (true == GameEngineInput::IsPress("RotX-"))
		{
			GetTransform().AddLocalRotation({ -RotSpeed * _DeltaTime, 0.0f, 0.0f });
		}
	}

	float4 EyeDir = GetTransform().GetLocalForwardVector();
	float4 EyeUp = GetTransform().GetLocalUpVector();
	float4 EyePos = GetTransform().GetLocalPosition();

	// 뷰행렬 연산
	View.LookToLH(EyePos, EyeDir, EyeUp);

	// 투영행렬 시야각 연산
	Projection.PerspectiveFovLH(60.0f, GameEngineWindow::GetScreenSize().x / GameEngineWindow::GetScreenSize().y, Near, Far);
	ViewPort.ViewPort(GameEngineWindow::GetScreenSize().x, GameEngineWindow::GetScreenSize().y, 0.0f, 0.0f);
}