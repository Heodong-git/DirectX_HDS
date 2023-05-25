#include "PrecompileHeader.h"
#include "Timer.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseLevel.h"

Timer* Timer::MainTimer = nullptr;

Timer::Timer()
{
	MainTimer = this;
}

Timer::~Timer()
{
}

void Timer::Start()
{
	{
		if (nullptr == GameEngineTexture::Find("spr_hud_timer_0.png"))
		{
			GameEngineDirectory NewDir;
			// ���ϴ� ������ ���� ���͸��� �̵�
			NewDir.MoveParentToDirectory("katanazero_resources");
			// �� ������ �̵�
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("Timer");

			// ���� ��ü�ε� 
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}
		}
	}

	m_MainRender = CreateComponent<GameEngineUIRenderer>();
	m_MainRender->SetTexture("spr_hud_timer_0.png");
	m_MainRender->GetTransform()->SetLocalScale({ 230.0f, 40.0f });
	m_MainRender->GetTransform()->SetLocalPosition({ -10.0f , 338.0f });

	m_GaugeRender = CreateComponent<GameEngineUIRenderer>();
	m_GaugeRender->SetScaleToTexture("spr_timer_0.png");
	m_GaugeRender->GetTransform()->SetLocalScale({ 200.0f, 25.0f });
	m_GaugeRender->GetTransform()->SetLocalPosition({ 10.0f , 342.0f });
}

void Timer::Update(float _DeltaTime)
{
	// ������ play ���°� �ƴ϶�� ������Ʈ���� ���� 
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	// ���� PLAY ���¶�� �����ͼ� �ڵ尡 ����� ���̰�.	
	GaugeUpdate();

	Blink();
}

void Timer::Render(float _DeltaTime)
{
}

void Timer::GaugeUpdate()
{
	
	// ���� �����ð� 
	float LimitTime = GetReturnCastLevel()->GetLimitTime();
	
	// ��
	float GaugeWidth = m_GaugeWidth * (LimitTime / m_FullGauge);

	// �������� ��ġ�� ���
	float GaugeX = (GaugeWidth - m_GaugeWidth) / 2.0f;
	m_GaugeRender->GetTransform()->SetLocalPosition({ GaugeX + 5.0f , 342.0f });
	m_GaugeRender->GetTransform()->SetLocalScale({ GaugeWidth  , static_cast<float>(m_GaugeHeight) });
}

void Timer::Blink()
{

	int Random = GameEngineRandom::MainRandom.RandomInt(1, 40);
	if (Random == 1)
	{
		m_MainRender->Off();
	}
	else
	{
		m_MainRender->On();
	}
}
