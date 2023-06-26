#include "PrecompileHeader.h"
#include "GunSpark_Effect2.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GunSpark_Effect2::GunSpark_Effect2()
{
}

GunSpark_Effect2::~GunSpark_Effect2()
{
}

void GunSpark_Effect2::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

	if (nullptr == GameEngineSprite::Find("gunspark_effect2"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunspark_effect2").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "gunspark_effect2", .SpriteName = "gunspark_effect2", .Start = 0, .End = 7 ,
								  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_Render->ChangeAnimation("gunspark_effect2");
	m_Render->SetScaleRatio(2.0f);
}

void GunSpark_Effect2::Update(float _DeltaTime)
{
	/*if (true == m_Render->IsAnimationEnd())
	{
		this->Death();
	}*/
}

void GunSpark_Effect2::Render(float _DeltaTime)
{
}
