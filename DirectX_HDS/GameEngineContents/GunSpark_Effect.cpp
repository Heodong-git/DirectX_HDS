#include "PrecompileHeader.h"
#include "GunSpark_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GunSpark_Effect::GunSpark_Effect()
{
}

GunSpark_Effect::~GunSpark_Effect()
{
}

void GunSpark_Effect::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	
	if (nullptr == GameEngineSprite::Find("gunspark_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunspark_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
	
	m_Render->CreateAnimation({ .AnimationName = "gunspark_effect", .SpriteName = "gunspark_effect", .Start = 0, .End = 7 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });
	m_Render->ChangeAnimation("gunspark_effect");
}

void GunSpark_Effect::Update(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		this->Death();
	}
}

void GunSpark_Effect::Render(float _DeltaTime)
{
}
