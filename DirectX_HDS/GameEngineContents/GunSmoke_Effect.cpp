#include "PrecompileHeader.h"
#include "GunSmoke_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GunSmoke_Effect::GunSmoke_Effect()
{
}

GunSmoke_Effect::~GunSmoke_Effect()
{
}

void GunSmoke_Effect::SetType(EffectType _Type)
{
	{
		switch (_Type)
		{
		case EffectType::NONE:
		{
			MsgAssert("GunSmoke 이펙트의 타입을 지정하지 않았습니다.");

		}
		break;
		case EffectType::FIRST:
			m_Render->ChangeAnimation("gunsmoke_effect1");
			break;
		case EffectType::SECOND:
			m_Render->ChangeAnimation("gunsmoke_effect2");
			break;
		case EffectType::THIRD:
			m_Render->ChangeAnimation("gunsmoke_effect3");
			break;
		}
	}
}

void GunSmoke_Effect::Start()
{
	// 렌더러만들고, 애니메이션 세개만들어서 넣어두고, 이펙트생성할때 
	// 어떤 애니메이션을 보여줄건지 set 
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);

	if (nullptr == GameEngineSprite::Find("gunsmoke_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");
		Dir.Move("gunsmoke_effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunsmoke_effect1").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunsmoke_effect2").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("gunsmoke_effect3").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render->CreateAnimation({ .AnimationName = "gunsmoke_effect1", .SpriteName = "gunsmoke_effect1", .Start = 0, .End = 9 ,
								  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_Render->CreateAnimation({ .AnimationName = "gunsmoke_effect2", .SpriteName = "gunsmoke_effect2", .Start = 0, .End = 11 ,
							  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_Render->CreateAnimation({ .AnimationName = "gunsmoke_effect3", .SpriteName = "gunsmoke_effect3", .Start = 0, .End = 10 ,
							  .FrameInter = 0.1f , .Loop = true , .ScaleToTexture = true });
	m_Render->SetScaleRatio(2.0f);
}

void GunSmoke_Effect::Update(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		// this->Death();
	}
}

void GunSmoke_Effect::Render(float _DeltaTime)
{
}
