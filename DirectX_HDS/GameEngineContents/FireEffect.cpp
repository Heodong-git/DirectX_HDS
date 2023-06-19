#include "PrecompileHeader.h"
#include "FireEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

FireEffect::FireEffect()
{
}

FireEffect::~FireEffect()
{
}

void FireEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("gangster_fire_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("gangster");
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gangster_fire_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Render->CreateAnimation({ .AnimationName = "gangster_fire_effect", .SpriteName = "gangster_fire_effect", .Start = 0, .End = 7 ,
							  .FrameInter = 0.03f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(2.0f);

	m_Render->ChangeAnimation("gangster_fire_effect");
}

void FireEffect::Update(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		this->Death();
		if (nullptr != m_Render)
		{
			m_Render = nullptr;
		}
	}
}

void FireEffect::Render(float _DeltaTime)
{
}
