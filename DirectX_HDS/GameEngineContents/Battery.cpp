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
			// 원하는 폴더를 가진 디렉터리로 이동
			NewDir.MoveParentToDirectory("katanazero_resources");
			// 그 폴더로 이동
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("Battery");

			// 파일 전체로드 
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}

		}
	}

	m_CaseRender = CreateComponent<GameEngineUIRenderer>();
	m_CaseRender->SetTexture("Battery_09.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 170, 40 , 1});
	m_CaseRender->GetTransform()->SetLocalPosition({ -500 , 300 });

	m_TestRender = CreateComponent<MySpriteRenderer>();
	m_TestRender->SetTexture("Battery_00.png");
	m_TestRender->GetTransform()->SetLocalScale({ 200, 200 , 1 });
	
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
