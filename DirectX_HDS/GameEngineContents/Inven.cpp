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
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Inven");

		// ���� ��ü�ε� 
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

void Inven::Render(float _DeltaTime)
{
}
