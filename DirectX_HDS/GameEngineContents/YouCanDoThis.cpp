#include "PrecompileHeader.h"
#include "YouCanDoThis.h"

#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

YouCanDoThis::YouCanDoThis()
{
}

YouCanDoThis::~YouCanDoThis()
{
}

void YouCanDoThis::Start()
{
	ComponentSetting();
}

void YouCanDoThis::Update(float _DeltaTime)
{
}

void YouCanDoThis::Render(float _DeltaTime)
{
}

void YouCanDoThis::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::UI);
	m_MainRender->SetTexture("youcandothis.png");
	m_MainRender->GetTransform()->SetLocalPosition(GameEngineWindow::GetScreenSize());
}
