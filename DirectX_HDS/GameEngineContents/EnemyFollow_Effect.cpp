#include "PrecompileHeader.h"
#include "EnemyFollow_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>


EnemyFollow_Effect::EnemyFollow_Effect()
{
}

EnemyFollow_Effect::~EnemyFollow_Effect()
{
}

void EnemyFollow_Effect::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

	// 스프라이트네임이 nullptr 일때만 
	if (nullptr == GameEngineSprite::Find("enemy_follow"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("enemy_follow").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "enemy_follow", .SpriteName = "enemy_follow", .Start = 0, .End = 1 ,
								  .FrameInter = 0.2f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(2.0f);
	m_Render->ChangeAnimation("enemy_follow");
}

void EnemyFollow_Effect::Update(float _DeltaTime)
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

void EnemyFollow_Effect::Render(float _DeltaTime)
{
}
