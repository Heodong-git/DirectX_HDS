#include "PrecompileHeader.h"
#include "Hud.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "CKatanaZero_Level.h"

Hud::Hud()
{
}

Hud::~Hud()
{	
}

void Hud::Start()
{
	{
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Hud");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	float4 screensize = GameEngineWindow::GetScreenSize();
	
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>();
	m_Renderer->SetPipeLine("2DTexture");
	m_Renderer->SetTexture("HUD.png");
	m_Renderer->GetTransform()->SetLocalScale({ screensize.x , 50.0f } );
	m_Renderer->GetTransform()->SetLocalPosition({ 0 , 0 });
}
