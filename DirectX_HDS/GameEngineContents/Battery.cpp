#include "PrecompileHeader.h"
#include "Battery.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BaseLevel.h"
#include "MySpriteRenderer.h"


Battery* Battery::MainBattery = nullptr;

Battery::Battery()
{
	MainBattery = this;
}

Battery::~Battery()
{
}

void Battery::Start()
{
	{
		if (nullptr == GameEngineTexture::Find("Battery_00.png"))
		{
			GameEngineDirectory NewDir;
			// ���ϴ� ������ ���� ���͸��� �̵�
			NewDir.MoveParentToDirectory("katanazero_resources");
			// �� ������ �̵�
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("Battery");

			// ���� ��ü�ε� 
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}

		}
	}

	m_CaseRender = CreateComponent<GameEngineUIRenderer>();
	m_CaseRender->SetTexture("Battery_09.png");
	//m_CaseRender->GetTransform()->SetLocalScale({ 170, 40 , 0});
	m_CaseRender->SetScaleToTexture("Battery_00.png");
	m_CaseRender->GetTransform()->SetLocalPosition({ -550 , 330 });	
}

void Battery::Update(float _DeltaTime)
{
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	GameEngineLevel* Level = GetLevel();

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

void Battery::Render(float _DeltaTime)
{
}
