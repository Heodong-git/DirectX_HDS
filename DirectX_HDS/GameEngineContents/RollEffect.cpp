#include "PrecompileHeader.h"
#include "RollEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineComponent.h>
#include "Player.h"

RollEffect::RollEffect()
{
}

RollEffect::~RollEffect()
{
}

void RollEffect::Start()
{
}

void RollEffect::Update(float _DeltaTime)
{
	if (nullptr != m_Render)
	{
		if (m_Render->IsAnimationEnd())
		{
			this->Death();
			return;
		}
	}

	// 이게좀 이상한거같기도하고? 
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("플레이어가 nullptr 입니다.");
		return;
	}
}

void RollEffect::Render(float _DeltaTime)
{
}
