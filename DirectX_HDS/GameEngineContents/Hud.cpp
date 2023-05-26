#include "PrecompileHeader.h"
#include "Hud.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BaseLevel.h"

Hud* Hud::MainHud = nullptr;

Hud::Hud()
{
	// 상관없나?? 
	MainHud = this;
}

Hud::~Hud()
{	
}

void Hud::Start()
{
	{
		if (nullptr == GameEngineTexture::Find("Hud.png"))
		{
			GameEngineDirectory NewDir;
			// 원하는 폴더를 가진 디렉터리로 이동
			NewDir.MoveParentToDirectory("katanazero_resources");
			// 그 폴더로 이동
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("Hud");

			// 파일 전체로드 
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}
		}
		
	}

	float4 screensize = GameEngineWindow::GetScreenSize();
	
	m_MainRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	m_MainRender->SetTexture("HUD.png");
	m_MainRender->GetTransform()->SetLocalScale({ screensize.x , 50.0f } );
	m_MainRender->GetTransform()->SetLocalPosition({ 0 , 340.0f });
}
