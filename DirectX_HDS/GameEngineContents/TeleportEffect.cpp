#include "PrecompileHeader.h"
#include "TeleportEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

TeleportEffect::TeleportEffect()
{
	
}

TeleportEffect::~TeleportEffect()
{
}

void TeleportEffect::Start()
{
	// µð¹ö±× ·»´õ
	m_DebugRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DEBUG);
	m_DebugRender->GetTransform()->SetLocalScale(float4{ 2.0f, 2.0f });
	m_DebugRender->On();


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

	m_SparkRenders.reserve(m_RenderCount);
	for (size_t i = 0; i < m_RenderCount; ++i)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
		Render->CreateAnimation({ .AnimationName = "gunspark_effect", .SpriteName = "gunspark_effect", .Start = 0, .End = 7 ,
							  .FrameInter = 0.2f , .Loop = false , .ScaleToTexture = true });
		Render->ChangeAnimation("gunspark_effect");
		m_SparkRenders.push_back(Render);
	}

	m_SparkRenders[0]->GetTransform()->SetLocalPosition(float4{ -100.0f , 0.0f });
	m_SparkRenders[0]->GetTransform()->SetLocalRotation(float4{ 0.0f, 0.0f, 180.0f });
	// m_SparkRenders[1]->GetTransform()->SetLocalPosition(float4{})
}

void TeleportEffect::Update(float _DeltaTime)
{
	if (true == m_SparkRenders[m_RenderCount - 1]->IsAnimationEnd())
	{
		int a = 0;
		this->Death();
	}
}

void TeleportEffect::Render(float _DeltaTime)
{
}
