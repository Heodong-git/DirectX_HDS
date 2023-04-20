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
	// 키생성
	if (false == GameEngineInput::IsKey("Attack"))
	{
		// 음 이게 전부인가 이친구는? 
		GameEngineInput::CreateKey("Player_Attack", VK_LBUTTON);
		GameEngineInput::CreateKey("Player_Left_Move", 'A');
		GameEngineInput::CreateKey("Player_Right_Move", 'D');
		GameEngineInput::CreateKey("Player_Jump", 'W');
		GameEngineInput::CreateKey("Player_Down_Move", 'S');
	}

	// 컴포넌트생성
	Render0 = CreateComponent<GameEngineRenderer>();
	// 파이프라인세팅 
	Render0->SetPipeLine("2DTexture");
	// 리소스헬퍼 -> 사용할 상수버퍼 링크 , 상수버퍼의 OutPixelColor 컬러를 TestColor로 사용하겠다는 의미
	Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TestColor);
	// 렌더러의 크기
	Render0->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	// 초기색상이고, 지금 TestColor 이랑 연동되어 있으니까  
	// Update에서 x값은 +- 하면 빨간색계열로 색변동이있음
	TestColor = { 1.0f, 0.0f, 0.0f, 1.0f };
}

void CPlayer::Update(float _DeltaTime)
{
	float Speed = 200.0f;

	// 임시무브 
	if (true == GameEngineInput::IsPress("Player_Left_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("Player_Right_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("Player_Jump"))
	{
		GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("Player_Down_Move"))
	{
		GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
	}
}

// 디버그용으로 사용
void CPlayer::Render(float _Delta)
{
}
