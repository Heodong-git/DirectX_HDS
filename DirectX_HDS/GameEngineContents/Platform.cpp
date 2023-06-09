#include "PrecompileHeader.h"
#include "Platform.h"

#include <GameEngineCore/GameEngineCollision.h>
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
	ComponentSetting();
}

void Platform::Update(float _DeltaTime)
{
	DebugUpdate();
}

void Platform::Render(float _DeltaTime)
{
}


void Platform::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_debugswitch"))
	{
		DebugSwitch();

		if (nullptr != m_Collision)
		{
			if (true == m_Collision->IsDebug())
			{
				m_Collision->DebugOff();
			}

			else
			{
				m_Collision->DebugOn();
			}
		}

		if (true == IsDebug())
		{
			m_DebugRender->On();
		}

		else if (false == IsDebug())
		{
			m_DebugRender->Off();
		}
	}
}

void Platform::ComponentSetting()
{
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::PLATFORM);

	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 2 , 2 });
	m_DebugRender->Off();
}
