#include "PrecompileHeader.h"
#include "LaserSwitch.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


LaserSwitch::LaserSwitch()
{
}

LaserSwitch::~LaserSwitch()
{
}

void LaserSwitch::Start()
{
	ComponentSetting();
	LoadAndCreateAnimation();
}

void LaserSwitch::Update(float _DeltaTime)
{
	DebugUpdate();
}

void LaserSwitch::Render(float _DeltaTime)
{
}

void LaserSwitch::Reset()
{
}

void LaserSwitch::DebugUpdate()
{
}

void LaserSwitch::ComponentSetting()
{
	m_SwitchRender;
	m_Collision;
}

void LaserSwitch::LoadAndCreateAnimation()
{
}
