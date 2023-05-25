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

	// �̰��� �̻��ѰŰ��⵵�ϰ�? 
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("�÷��̾ nullptr �Դϴ�.");
		return;
	}
}

void RollEffect::Render(float _DeltaTime)
{
}
