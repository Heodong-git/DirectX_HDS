#include "PrecompileHeader.h"
#include "HeadHunter_RifleEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

HeadHunter_RifleEffect::HeadHunter_RifleEffect()
{
}

HeadHunter_RifleEffect::~HeadHunter_RifleEffect()
{
}

void HeadHunter_RifleEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("headhunter_rifle_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("headhunter");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_rifle_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_Render->GetTransform()->SetLocalScale(float4{ 1000.0f , 4.0f });

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BOSS_ATTACK);
	m_Collision->GetTransform()->SetLocalScale(float4{ 1000.0f , 4.0f });
	m_Collision->SetColType(ColType::OBBBOX3D);

	std::vector<float> vFrameTime = std::vector<float>();
	vFrameTime.push_back(0.8f);
	vFrameTime.push_back(0.3f);
	vFrameTime.push_back(0.2f);

	AnimationParameter Para = {};
	Para.AnimationName = "headhunter_rifle_effect";
	Para.SpriteName = "headhunter_rifle_effect";
	Para.Start = 0;
	Para.End = 2;
	Para.FrameTime = vFrameTime;
	Para.Loop = false;
	Para.ScaleToTexture = false;

	m_Render->CreateAnimation(Para);
	m_Render->ChangeAnimation("headhunter_rifle_effect");
}

void HeadHunter_RifleEffect::Update(float _DeltaTime)
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

void HeadHunter_RifleEffect::Render(float _DeltaTime)
{
}
