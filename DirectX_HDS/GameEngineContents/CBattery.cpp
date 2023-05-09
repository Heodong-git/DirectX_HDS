#include "PrecompileHeader.h"
#include "CBattery.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "CKatanaZero_Level.h"

CBattery::CBattery()
{
}

CBattery::~CBattery()
{
}

void CBattery::Start()
{
	{
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Battery");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DTexture");
	m_CaseRender->GetShaderResHelper().SetTexture("DiffuseTex", "Battery_09.png");
	/*m_CaseRender->SetPipeLine("2DBlinkTexture");
	m_CaseRender->GetShaderResHelper().SetTexture("BlinkTex", "Battery_09.png");*/
	m_CaseRender->GetTransform()->SetLocalScale({ 170, 40 });
	m_CaseRender->GetTransform()->SetLocalPosition({ -560 , 335 });
}

void CBattery::Update(float _DeltaTime)
{
	if (ELEVEL_STATE::WAIT == GetReturnCastLevel()->GetCurState())
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

void CBattery::Render(float _DeltaTime)
{
}
