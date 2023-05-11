#include "PrecompileHeader.h"
#include "Timer.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseLevel.h"


Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Timer");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DTexture");
	m_CaseRender->SetTexture("spr_hud_timer_0.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 230.0f, 40.0f });
	m_CaseRender->GetTransform()->SetLocalPosition({ -10.0f , 338.0f });

	m_GageRender = CreateComponent<GameEngineSpriteRenderer>();
	m_GageRender->SetPipeLine("2DTexture");
	m_GageRender->SetTexture("spr_timer_0.png");
	m_GageRender->GetTransform()->SetLocalScale({ 200.0f, 25.0f });
	m_GageRender->GetTransform()->SetLocalPosition({ 10.0f , 342.0f });

	// ���̴������ �̰ɷ� ����
	/*m_GageRender = CreateComponent<GameEngineSpriteRenderer>();
	m_GageRender->SetPipeLine("2DBlinkTexture");
	m_GageRender->GetShaderResHelper().SetTexture("BlinkTex", "spr_timer_0.png");
	m_GageRender->GetTransform()->SetLocalScale({ 200.0f, 25.0f });
	m_GageRender->GetTransform()->SetLocalPosition({ 10.0f , 342.0f });*/

	/*m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DBlinkTexture");
	m_CaseRender->GetShaderResHelper().SetTexture("BlinkTex", "spr_hud_timer_0.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 230.0f, 40.0f });
	m_CaseRender->GetTransform()->SetLocalPosition({ -10.0f , 338.0f });*/
}

void Timer::Update(float _DeltaTime)
{
	// ������ play ���°� �ƴ϶�� ������Ʈ���� ���� 
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	int Random = GameEngineRandom::MainRandom.RandomInt(1, 40);
	if (Random == 1)
	{
		m_CaseRender->Off();
	}
	else
	{
		m_CaseRender->On();
	}
}

void Timer::Render(float _DeltaTime)
{
}