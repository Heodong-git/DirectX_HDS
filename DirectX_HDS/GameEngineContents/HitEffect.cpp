#include "PrecompileHeader.h"
#include "HitEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

HitEffect::HitEffect()
{
}

HitEffect::~HitEffect()
{
}

void HitEffect::SetObject(std::shared_ptr<GameEngineObject> _Obj)
{
	if (nullptr == _Obj)
	{
		MsgAssert("오브젝트가 nullptr 입니다.");
	}
	
	m_FollowObj = _Obj;
}

void HitEffect::Start()
{
	if (nullptr == GameEngineSprite::Find("hit_effect"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("Effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("hit_effect").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::EFFECT);
	m_MainRender->ColorOptionValue.MulColor.r = 0.7f;
	m_MainRender->SetScaleRatio(2.0f);
	m_MainRender->CreateAnimation({ .AnimationName = "hit_effect", .SpriteName = "hit_effect", .Start = 0, .End = 5 ,
								  .FrameInter = 0.06f , .Loop = false , .ScaleToTexture = true });
	m_MainRender->GetTransform()->SetLocalPosition(float4{ 47.0f, 30.0f });
	m_MainRender->ChangeAnimation("hit_effect");
}

void HitEffect::Update(float _DeltaTime)
{
	if (true == m_MainRender->IsAnimationEnd())
	{
		this->Death();
		if (nullptr != m_MainRender)
		{
			m_MainRender = nullptr;
		}
	}

	if (nullptr != m_FollowObj)
	{
		GetTransform()->SetWorldPosition(m_FollowObj->GetTransform()->GetWorldPosition());		
	}
}

void HitEffect::Render(float _DeltaTime)
{
}
