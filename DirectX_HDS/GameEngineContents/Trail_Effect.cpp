#include "PrecompileHeader.h"
#include "Trail_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Player.h"
#include "Boss_HeadHunter.h"

Trail_Effect::Trail_Effect()
{
}

Trail_Effect::~Trail_Effect()
{
}

void Trail_Effect::SetTexture(std::string_view _Name, float4& _Size, TrailType _Type)
{
	std::string Name = _Name.data();
	float4 Size = _Size * 1.9f;

	m_Type = _Type;

	switch (m_Type)
	{
	case TrailType::PLAYER:
	{
		// 여기서 플레이어 렌더러 위치랑 동일 

		// 얘가지금 플레이어 로컬포지션 
		m_Render->GetTransform()->SetLocalPosition(m_PlayerRenderPivot);
		m_Render->SetTexture(_Name);
		m_Render->GetTransform()->SetLocalScale(Size);

		m_Render->ColorOptionValue.PlusColor.r = 0.0f;
		m_Render->ColorOptionValue.PlusColor.g = 0.5f;
		m_Render->ColorOptionValue.PlusColor.b = 0.5f;
		m_Render->ColorOptionValue.PlusColor.a = 0.0f;

		m_Render->ColorOptionValue.MulColor.r = 0.0f;
		m_Render->ColorOptionValue.MulColor.g = 1.0f;
		m_Render->ColorOptionValue.MulColor.b = 1.0f;
		m_Render->ColorOptionValue.MulColor.a = 0.4f;

		bool PlayerDir = Player::MainPlayer->GetDir();
		if (true == PlayerDir)
		{
			GetTransform()->SetLocalPositiveScaleX();
		}

		else if (false == PlayerDir)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}
		break;
	case TrailType::BOSS:
	{
		// 얘를 보스렌더러 
		m_Render->GetTransform()->SetLocalPosition(m_HeadHunterRenderPivot);
		// 봐서 색바꾸기 
		m_Render->SetTexture(_Name);
		m_Render->GetTransform()->SetLocalScale(Size);

		m_Render->ColorOptionValue.PlusColor.r = 0.5f;
		m_Render->ColorOptionValue.PlusColor.g = 0.0f;
		m_Render->ColorOptionValue.PlusColor.b = 0.5f;
		m_Render->ColorOptionValue.PlusColor.a = 0.0f;
	
		m_Render->ColorOptionValue.MulColor.r = 1.0f;
		m_Render->ColorOptionValue.MulColor.g = 0.0f;
		m_Render->ColorOptionValue.MulColor.b = 1.0f;
		m_Render->ColorOptionValue.MulColor.a = 0.4f;

		// 여기서 방향 ㅇㅇ 
		bool BossDir = Boss_HeadHunter::m_MainBoss->GetDir();
		if (true == BossDir)
		{
			GetTransform()->SetLocalPositiveScaleX();
		}

		else if (false == BossDir)
		{
			GetTransform()->SetLocalNegativeScaleX();
		}
	}
		break;
	}

}

void Trail_Effect::Start()
{
	m_Render = CreateComponent<GameEngineSpriteRenderer>();

	
}

void Trail_Effect::Update(float _DeltaTime)
{
	if (TrailType::NONE == m_Type)
	{
		MsgAssert("잔상의 타입을 설정하지 않았습니다.");
		return;
	}

	if (m_MaxLivetime <= GetLiveTime())
	{
		this->Death();
	}
}
