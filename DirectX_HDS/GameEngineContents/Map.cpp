#include "PrecompileHeader.h"
#include "Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	ComponentSetting();
}

void Map::ComponentSetting()
{
	float4 screensize = GameEngineWindow::GetScreenSize();
	m_BackGround = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGround->SetTexture("background_black.png");
	m_BackGround->GetTransform()->SetLocalScale({ screensize.x * 2.0f , screensize.y * 2.0f });

	m_MapRender = CreateComponent<GameEngineSpriteRenderer>();
}

