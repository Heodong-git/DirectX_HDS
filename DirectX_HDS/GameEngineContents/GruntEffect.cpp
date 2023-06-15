#include "PrecompileHeader.h"
#include "GruntEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Monster_Grunt.h"

GruntEffect::GruntEffect()
{
}

GruntEffect::~GruntEffect()
{
}

void GruntEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("grunt_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("grunt");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("grunt_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Render->CreateAnimation({ .AnimationName = "grunt_effect", .SpriteName = "grunt_effect", .Start = 0, .End = 4 ,
								  .FrameInter = 0.04f , .Loop = false , .ScaleToTexture = true });
	m_Render->SetScaleRatio(1.5f);
	m_Render->ChangeAnimation("grunt_effect");
}

void GruntEffect::Update(float _DeltaTime)
{
	if (true == m_Render->IsAnimationEnd())
	{
		this->Death();
		
	}
}

void GruntEffect::Render(float _DeltaTime)
{
}
