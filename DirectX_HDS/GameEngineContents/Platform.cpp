#include "PrecompileHeader.h"
#include "Platform.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Platform::Platform()
{
}

Platform::~Platform()
{
}

void Platform::Start()
{
	if (false == GameEngineInput::IsKey("Platform_DebugSwitch"))
	{
		DebugSwitch();
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetPipeLine("2DTexture");
	m_Render->SetAtlasConstantBuffer();
}

void Platform::Update(float _DeltaTime)
{
	// Å×½ºÆ® 
	/*if(m_Render->GetTransform()->Collision({ Player::MainPlayer->GetRender()->GetTransform() , ColType::OBBBOX3D, ColType::OBBBOX3D }))
	{
		Player::MainPlayer->GetRender()->GetTransform()->AddLocalPosition({ 0 , 1 });
	}*/

	DebugUpdate();
}

void Platform::Render(float _DeltaTime)
{
}

void Platform::DebugUpdate()
{
	if (true == IsDebug())
	{
		int a = 0;
	}

	else if (false == IsDebug())
	{
		
	}
}
