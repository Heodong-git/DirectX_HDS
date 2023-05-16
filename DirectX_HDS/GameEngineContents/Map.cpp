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
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Map");

		// 파일 전체로드 
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

