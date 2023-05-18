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
	m_BackGround = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGround->SetTexture("background_black.png");
	float4 screensize = GameEngineWindow::GetScreenSize();
	m_BackGround->GetTransform()->SetLocalScale({ screensize.x * 2.0f , screensize.y * 2.0f });

	m_MapRender = CreateComponent<GameEngineSpriteRenderer>();
}

