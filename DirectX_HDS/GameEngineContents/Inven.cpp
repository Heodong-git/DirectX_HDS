#include "PrecompileHeader.h"
#include "Inven.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
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
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Inven");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	m_CaseRender = CreateComponent<GameEngineSpriteRenderer>();
	m_CaseRender->SetPipeLine("2DTexture");
	m_CaseRender->GetShaderResHelper().SetTexture("DiffuseTex", "Inven_0.png");
	m_CaseRender->GetTransform()->SetLocalScale({ 115, 45 });
	m_CaseRender->GetTransform()->SetLocalPosition({ 564 , 335 });
}

void Inven::Update(float _DeltaTime)
{
	// 레벨이 play 상태가 아니라면 업데이트하지 않음 
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

void Inven::Render(float _DeltaTime)
{
}
