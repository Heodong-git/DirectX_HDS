#include "PrecompileHeader.h"
#include "Partition.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Partition::Partition()
{
}

Partition::~Partition()
{
}

void Partition::Start()
{
	ComponentSetting();
}

void Partition::Update(float _DeltaTime)
{
	DebugUpdate();
}

void Partition::Render(float _DeltaTime)
{
}

void Partition::DebugUpdate()
{
	if (true == GameEngineInput::IsDown("player_debugswitch"))
	{
		DebugSwitch();

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

void Partition::ComponentSetting()
{
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::PARTITION);
	m_Collision->GetTransform()->SetLocalScale(m_Scale);
	m_Collision->GetTransform()->SetLocalPosition(float4{ 0.0f , m_Scale.y / 2.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);
	
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 2 , 2 });
	m_DebugRender->Off();
}
