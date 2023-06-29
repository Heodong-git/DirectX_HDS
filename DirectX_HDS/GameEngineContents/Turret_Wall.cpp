#include "PrecompileHeader.h"
#include "Turret_Wall.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Turret_Wall::Turret_Wall()
{
}

Turret_Wall::~Turret_Wall()
{
}

void Turret_Wall::Start()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	LoadAndCreateAnimation();
}


void Turret_Wall::Update(float _DeltaTime)
{
	int a = 0;
}

void Turret_Wall::DebugUpdate()
{
}

void Turret_Wall::LoadAndCreateAnimation()
{
	if (nullptr == GameEngineSprite::Find("turret_wall"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("turret");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("turret_wall").GetFullPath());

		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_MainRender->CreateAnimation({ .AnimationName = "turret_wall", .SpriteName = "turret_wall", .Start = 0, .End = 20 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->SetScaleRatio(2.0f);

	m_MainRender->ChangeAnimation("turret_wall");
}
