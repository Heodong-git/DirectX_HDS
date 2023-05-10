#include "PrecompileHeader.h"
#include "CHud.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

CHud::CHud()
{
}

CHud::~CHud()
{	
}

void CHud::Start()
{
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("Stage01Level");
		NewDir.Move("Hud");

		// ���� ��ü�ε� 
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
	m_Renderer->GetTransform()->SetLocalScale({ screensize.x , 50.0f });
	m_Renderer->GetTransform()->SetLocalPosition({ 0 , 338.0f });
}