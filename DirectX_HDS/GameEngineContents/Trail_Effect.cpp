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
		// ���⼭ �÷��̾� ������ ��ġ�� ���� 

		// �갡���� �÷��̾� ���������� 
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
		// �긦 ���������� 
		m_Render->GetTransform()->SetLocalPosition(m_HeadHunterRenderPivot);
		// ���� ���ٲٱ� 
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

		// ���⼭ ���� ���� 
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
		MsgAssert("�ܻ��� Ÿ���� �������� �ʾҽ��ϴ�.");
		return;
	}

	if (m_MaxLivetime <= GetLiveTime())
	{
		this->Death();
	}
}
