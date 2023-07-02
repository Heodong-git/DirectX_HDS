#include "PrecompileHeader.h"
#include "HeadHunter_RifleEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Boss_HeadHunter.h"

HeadHunter_RifleEffect::HeadHunter_RifleEffect()
{
}

HeadHunter_RifleEffect::~HeadHunter_RifleEffect()
{
}

void HeadHunter_RifleEffect::SetType(RifleEffectType _Type)
{
	m_Type = _Type;
	switch (m_Type)
	{
	case RifleEffectType::NORMAL:
		break;
	case RifleEffectType::SWEEP:
	{
		// 만약 이펙트가 스윕이라면 렌더러 위치를 내 렌더크기의 절반만큼 밀어 
		m_Render->GetTransform()->AddLocalPosition(float4{ 500.0f , 0.0f });
		m_Render->ChangeAnimation("headhunter_rifle_effect_sweep");
		m_Collision->GetTransform()->AddLocalPosition(float4{ 500.0f , 0.0f });
	}
		break;
	}
}

void HeadHunter_RifleEffect::ChangeLoopAnimation()
{
	m_Render->ChangeAnimation("headhunter_rifle_effect_sweep_loop");
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
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("headhunter_rifle_effect_trans").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BOSS_EFFECT);
	m_Render->GetTransform()->SetLocalScale(float4{ 1000.0f , 2.0f, 1.0f });
	m_Render->GetTransform()->SetLocalPosition(float4{ 0.0f , 0.0f, -1.0f });

	m_Collision = CreateComponent<GameEngineCollision>(ColOrder::BOSS_ATTACK);
	m_Collision->GetTransform()->SetLocalScale(float4{ 1000.0f , 20.0f , 1.0f  });
	m_Collision->SetColType(ColType::OBBBOX3D);
	m_Collision->Off();

	
	
	{
		// 기본 라이플이펙트 
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
	}
	{
		// 스윕라이플 이펙트 
		std::vector<float> vFrameTime = std::vector<float>();
		vFrameTime.push_back(0.1f);
		vFrameTime.push_back(0.08f);
		vFrameTime.push_back(0.08f);

		AnimationParameter Para = {};
		Para.AnimationName = "headhunter_rifle_effect_sweep";
		Para.SpriteName = "headhunter_rifle_effect_trans";
		Para.Start = 0;
		Para.End = 2;
		Para.FrameTime = vFrameTime;
		Para.Loop = false;
		Para.ScaleToTexture = false;

		m_Render->CreateAnimation(Para);
	}
	{
		// 스윕라이플 이펙트 loop
		std::vector<float> vFrameTime = std::vector<float>();
		vFrameTime.push_back(0.15f);
		vFrameTime.push_back(0.15f);

		AnimationParameter Para = {};
		Para.AnimationName = "headhunter_rifle_effect_sweep_loop";
		Para.SpriteName = "headhunter_rifle_effect_trans";
		Para.Start = 1;
		Para.End = 2;
		Para.FrameTime = vFrameTime;
		Para.Loop = true;
		Para.ScaleToTexture = false;

		m_Render->CreateAnimation(Para);
	}
	
	m_Render->SetAnimationStartEvent("headhunter_rifle_effect_sweep", static_cast<size_t>(1), std::bind(&HeadHunter_RifleEffect::ChangeLoopAnimation, this));
	m_Render->ChangeAnimation("headhunter_rifle_effect");
}

void HeadHunter_RifleEffect::Update(float _DeltaTime)
{
	// 라이브타임으로 그냥 죽이자 
	if (RifleEffectType::CEILING_FIRE == m_Type)
	{
		if (true == m_Render->IsAnimationEnd())
		{
			this->Death();
			return;
		}


		if (1 == m_Render->GetCurrentFrame())
		{
			m_Render->GetTransform()->SetLocalScale(float4{ 1000.0f , 20.0f, 1.0f });
			m_Collision->On();
		}

		return;
	}


	if (RifleEffectType::SWEEP == m_Type)
	{
		// 만약, 라이플 타입이 sweep 이라면, 내가 애니메이션프레임이 1일 경우, 렌더러의 y축 크기를 증가시킨다. 
		if (1 == m_Render->GetCurrentFrame())
		{
			m_Render->GetTransform()->SetLocalScale(float4{ 1000.0f , 20.0f, 1.0f });
			m_Collision->On();
		}

		return;
	}

	// 노말이펙트일 경우 
	if (RifleEffectType::NORMAL == m_Type)
	{
		BossState CurState = m_Actor->GetCurState();
		if (true == m_Render->IsAnimationEnd())
		{
			this->Death();
			if (nullptr != m_Render)
			{
				m_Render = nullptr;
				m_Actor = nullptr;
			}
			return;
		}
	}

	size_t Frame = m_Render->GetCurrentFrame();
	switch (Frame)
	{
	case 0:
		m_Render->ColorOptionValue.MulColor.a -= _DeltaTime;
		break;
	case 1:
		m_Render->ColorOptionValue.MulColor.a = 0.0f;
		break;
	default:
		m_Render->ColorOptionValue.MulColor.a = 1.0f;
		m_Render->GetTransform()->SetLocalScale(float4{ 1000.0f , 20.0f });
		m_Collision->On();
		break;
	}
	
}

void HeadHunter_RifleEffect::Render(float _DeltaTime)
{
}
