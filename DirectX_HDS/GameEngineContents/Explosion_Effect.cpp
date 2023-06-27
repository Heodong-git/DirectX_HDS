#include "PrecompileHeader.h"
#include "Explosion_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Explosion_Effect::Explosion_Effect()
{
}

Explosion_Effect::~Explosion_Effect()
{
}

void Explosion_Effect::SetType(EffectType _Type)
{
	{
		switch (_Type)
		{
		case EffectType::NONE:
		{
			MsgAssert("Explosion 이펙트의 타입을 지정하지 않았습니다.");

		}
		break;
		case EffectType::FIRST:
			m_Render->ChangeAnimation("explosion_effect1");
			break;
		case EffectType::SECOND:
			m_Render->ChangeAnimation("explosion_effect2");
			break;
		}
	}
}

void Explosion_Effect::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BOSS_EXPLOSION);

	m_Collision->GetTransform()->SetLocalScale(float4{ 20.0f , 20.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);

	if (nullptr == GameEngineSprite::Find("explosion_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("explosion_effect").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("explosion_effect2").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "explosion_effect", .SpriteName = "explosion_effect", .Start = 0, .End = 9 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });

	m_Render->CreateAnimation({ .AnimationName = "explosion_effect2", .SpriteName = "explosion_effect2", .Start = 0, .End = 9 ,
								  .FrameInter = 0.1f , .Loop = false , .ScaleToTexture = true });

	m_Render->SetScaleRatio(2.0f);
	m_Render->ChangeAnimation("explosion_effect");
}

void Explosion_Effect::Update(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		Death();
	}
}

void Explosion_Effect::Render(float _DeltaTime)
{
}
