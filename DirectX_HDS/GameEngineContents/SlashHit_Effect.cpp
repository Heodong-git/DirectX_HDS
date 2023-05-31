#include "PrecompileHeader.h"
#include "SlashHit_Effect.h"

#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

SlashHit_Effect::SlashHit_Effect()
{
}

SlashHit_Effect::~SlashHit_Effect()
{
}

void SlashHit_Effect::Start()
{
	if (nullptr == GameEngineSprite::Find("slash_hit"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("slash_hit").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	ComponentSetting();
}

void SlashHit_Effect::Update(float _DeltaTime)
{
	if (nullptr != m_MainRender)
	{
		if (m_MainRender->IsAnimationEnd())
		{
			this->Death();
			return;
		}
	}
}

void SlashHit_Effect::Render(float _DeltaTime)
{
}

void SlashHit_Effect::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_MainRender->SetScaleRatio(2.0f);

	m_MainRender->CreateAnimation({ .AnimationName = "slash_hit", .SpriteName = "slash_hit", .Start = 0, .End = 4 ,
								.FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->ChangeAnimation("slash_hit");
}
