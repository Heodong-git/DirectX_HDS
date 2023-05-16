#include "PrecompileHeader.h"
#include "Map.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::Start()
{
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Map");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	m_BackGround = CreateComponent<GameEngineSpriteRenderer>();
	m_BackGround->SetPipeLine("2DTexture");
	m_BackGround->SetTexture("background_black.png");
	m_BackGround->SetAtlasConstantBuffer();
	float4 screensize = GameEngineWindow::GetScreenSize();
	m_BackGround->GetTransform()->SetLocalScale({ screensize.x * 2.0f , screensize.y * 2.0f });

	m_MapRender = CreateComponent<GameEngineSpriteRenderer>();
	m_MapRender->SetPipeLine("2DTexture");
	m_MapRender->SetAtlasConstantBuffer();
}

