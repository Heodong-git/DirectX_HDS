#include "PrecompileHeader.h"
#include "ReflectEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

ReflectEffect::ReflectEffect()
{
}

ReflectEffect::~ReflectEffect()
{
}

void ReflectEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("bullet_reflect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("bullet_reflect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Render->CreateAnimation({ .AnimationName = "bullet_reflect", .SpriteName = "bullet_reflect", .Start = 0, .End = 4 ,
							  .FrameInter = 0.02f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(2.0f);

	m_Render->ChangeAnimation("bullet_reflect");
}

void ReflectEffect::Update(float _DeltaTime)
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

void ReflectEffect::Render(float _DeltaTime)
{
}
