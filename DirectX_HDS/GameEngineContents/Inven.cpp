#include "PrecompileHeader.h"
#include "Inven.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseLevel.h"
#include <GameEngineBase/GameEngineRandom.h>

Inven::Inven()
{
}

Inven::~Inven()
{
}

void Inven::Start()
{
	{
		if (nullptr == GameEngineTexture::Find("Inven_0.png"))
		{
			GameEngineDirectory NewDir;
			// 원하는 폴더를 가진 디렉터리로 이동
			NewDir.MoveParentToDirectory("katanazero_resources");
			// 그 폴더로 이동
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("Inven");

			// 파일 전체로드 
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}
		}

		
	}
	m_MainRender = CreateComponent<GameEngineUIRenderer>();
	m_MainRender->GetShaderResHelper().SetTexture("DiffuseTex", "Inven_0.png");
	m_MainRender->GetTransform()->SetLocalScale({ 115, 45 });
	m_MainRender->GetTransform()->SetLocalPosition({ 564 , 335 });

	m_LeftRender = CreateComponent<GameEngineUIRenderer>();
	m_LeftRender->SetTexture("spr_left_click_1.png");
	m_LeftRender->GetTransform()->SetLocalScale({ 25 , 30 });
	m_LeftRender->GetTransform()->SetLocalPosition({ 550 , 310 });

	m_RightRender = CreateComponent<GameEngineUIRenderer>();
	m_RightRender->SetTexture("spr_right_click_1.png");
	m_RightRender->GetTransform()->SetLocalScale({ 25 , 30 });
	m_RightRender->GetTransform()->SetLocalPosition({ 615 , 310 });
}

void Inven::Update(float _DeltaTime)
{
	// 레벨이 play 상태가 아니라면 업데이트하지 않음 
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	Blink();
}

void Inven::Render(float _DeltaTime)
{
}

void Inven::Blink()
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
