#include "PrecompileHeader.h"
#include "Bullet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	if (nullptr == GameEngineSprite::Find("Bullet"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("bullet").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BULLET);
	m_Render->SetScaleToTexture("Bullet_00.png");
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BULLET);
}

void Bullet::Update(float _DeltaTime)
{
	int a = 0;
}

void Bullet::Render(float _DeltaTime)
{
}
